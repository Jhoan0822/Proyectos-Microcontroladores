/**
 * @file main.c
 * @author [Tu Nombre]
 * @brief AVR Music Player for a Piezo Buzzer
 * @version 2.0
 * @date 2024-07-05
 *
 * This project uses Timer1 in CTC mode with an interrupt to generate square waves
 * of varying frequencies, playing a melody on a piezo buzzer. The song played is
 * a simplified version of "Rosas" by La Oreja de Van Gogh.
 *
 * The code is structured to be data-driven, with the song defined as an
 * array of Note structs, making it easy to change or add new songs.
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// --- Hardware Abstraction ---
#define BUZZER_PIN      PD5
#define BUZZER_DDR      DDRD
#define BUZZER_PORT     PORTD

// --- Musical Note Frequencies (Hz) ---
// Using standard names. "S" = Sharp, e.g., CS is C#
#define NOTE_SILENCE    0
#define NOTE_A4         440
#define NOTE_B4         494
#define NOTE_CS5        554
#define NOTE_D5         587
#define NOTE_E5         659
#define NOTE_FS5        740
#define NOTE_GS5        831
#define NOTE_A5         880
#define NOTE_B5         988

// --- Note Durations (in milliseconds) ---
// Based on a tempo of ~120 BPM
#define TEMPO_BPM       120
#define D_QUARTER       (60000 / TEMPO_BPM)
#define D_EIGHTH        (D_QUARTER / 2)
#define D_SIXTEENTH     (D_EIGHTH / 2)
#define D_HALF          (D_QUARTER * 2)
#define D_WHOLE         (D_QUARTER * 4)

// --- Data Structures ---
typedef struct {
    unsigned int frequency;
    unsigned int duration;
} Note;

// --- Global variables for the Timer ISR ---
volatile long timer1_toggle_count;
volatile uint8_t *timer1_pin_port;
volatile uint8_t timer1_pin_mask;

// --- Function Prototypes ---
void init_hardware(void);
void tone(unsigned int frequency, unsigned long duration);
void no_tone(void);
void play_note(Note note);

// --- The Song: "Rosas" by La Oreja de Van Gogh (Verse) ---
// Using a data-driven approach is much cleaner and more professional.
const Note song[] = {
    // Por eso esperaba...
    {NOTE_CS5, D_EIGHTH}, {NOTE_A5, D_EIGHTH}, {NOTE_A5, D_EIGHTH}, {NOTE_A5, D_EIGHTH},
    {NOTE_A5, D_QUARTER}, {NOTE_A5, D_EIGHTH}, {NOTE_FS5, D_EIGHTH}, {NOTE_GS5, D_EIGHTH},
    // con la carita empapada...
    {NOTE_A5, D_EIGHTH}, {NOTE_A5, D_EIGHTH}, {NOTE_A5, D_EIGHTH}, {NOTE_GS5, D_EIGHTH},
    {NOTE_A5, D_EIGHTH}, {NOTE_A5, D_EIGHTH}, {NOTE_A5, D_EIGHTH}, {NOTE_B5, D_EIGHTH},
    // que llegaras con rosas...
    {NOTE_GS5, D_EIGHTH}, {NOTE_GS5, D_EIGHTH}, {NOTE_GS5, D_EIGHTH}, {NOTE_GS5, D_QUARTER},
    {NOTE_GS5, D_EIGHTH}, {NOTE_GS5, D_EIGHTH}, {NOTE_B5, D_EIGHTH},
    // con mil rosas para mi...
    {NOTE_B5, D_QUARTER}, {NOTE_A5, D_QUARTER}, {NOTE_GS5, D_EIGHTH}, {NOTE_FS5, D_EIGHTH},
    {NOTE_SILENCE, D_EIGHTH}, {NOTE_E5, D_EIGHTH}, {NOTE_SILENCE, D_QUARTER},
    // End of phrase
    {NOTE_SILENCE, D_WHOLE}
};


// --- Main Program ---
int main(void) {
    init_hardware();
    sei(); // Enable global interrupts

    while (1) {
        // Play the entire song
        int song_length = sizeof(song) / sizeof(Note);
        for (int i = 0; i < song_length; i++) {
            play_note(song[i]);
        }
        _delay_ms(2000); // Wait 2 seconds before repeating
    }
    return 0; // Should not be reached
}


// --- Function Definitions ---

void init_hardware(void) {
    // Set buzzer pin as output
    BUZZER_DDR |= (1 << BUZZER_PIN);
}

void play_note(Note note) {
    // If the frequency is 0, it's a rest. Just delay for the duration.
    if (note.frequency == NOTE_SILENCE) {
        for (unsigned int i = 0; i < note.duration; i++) {
            _delay_ms(1);
        }
        return;
    }
    
    // Play the tone. The ISR will handle stopping it after the duration.
    tone(note.frequency, note.duration);
    
    // Block for the duration of the note plus a small gap for separation
    for (unsigned int i = 0; i < (note.duration + (note.duration / 10)); i++) {
        _delay_ms(1);
    }
}


void tone(unsigned int frequency, unsigned long duration) {
    long ocr;
    uint8_t prescaler_bits = 0;

    // Prescaler values: 1(001), 8(010), 64(011), 256(100), 1024(101)
    ocr = (F_CPU / (2UL * frequency)) - 1;
    prescaler_bits = (1 << CS10); // Prescaler 1
    
    if (ocr > 0xFFFF) {
        ocr = (F_CPU / (16UL * frequency)) - 1;
        prescaler_bits = (1 << CS11); // Prescaler 8
    }
    if (ocr > 0xFFFF) {
        ocr = (F_CPU / (128UL * frequency)) - 1;
        prescaler_bits = (1 << CS11) | (1 << CS10); // Prescaler 64
    }
    // Add more prescalers if needed for very low frequencies
    
    TCCR1B = 0; // Stop timer
    TCCR1A = 0; // Configure for CTC mode
    TCCR1B |= (1 << WGM12) | prescaler_bits;
    
    OCR1A = ocr;

    // Calculate toggle count for the desired duration
    timer1_toggle_count = (2UL * frequency * duration) / 1000;
    timer1_pin_port = &BUZZER_PORT;
    timer1_pin_mask = (1 << BUZZER_PIN);

    // Enable Timer1 Compare Match interrupt
    TIMSK |= (1 << OCIE1A);
}

void no_tone(void) {
    TIMSK &= ~(1 << OCIE1A);      // Disable interrupt
    BUZZER_PORT &= ~timer1_pin_mask; // Ensure pin is low
}

ISR(TIMER1_COMPA_vect) {
    if (timer1_toggle_count != 0) {
        *timer1_pin_port ^= timer1_pin_mask; // Toggle the pin

        if (timer1_toggle_count > 0) {
            timer1_toggle_count--;
        }
    } else {
        no_tone(); // Stop the tone when duration is over
    }
}