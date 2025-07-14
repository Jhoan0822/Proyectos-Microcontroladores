/**
 * @file main.c
 * @author [Tu Nombre]
 * @brief 8-bit Square Wave Frequency Generator using Timer0
 * @version 1.0
 * @date 2024-07-05
 *
 * This project demonstrates how to use the 8-bit Timer0 on an ATmega32A
 * to generate a square wave of a fixed frequency. It utilizes the CTC
 * (Clear Timer on Compare Match) mode and an interrupt service routine (ISR)
 * to toggle an output pin.
 *
 * This is a resource-efficient alternative to using the 16-bit Timer1 for
 * simpler frequency generation tasks.
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

// --- Configuration ---
#define OUTPUT_PIN      PD7
#define OUTPUT_DDR      DDRD
#define OUTPUT_PORT     PORTD

/**
 * --- Frequency Calculation ---
 * Formula: f_out = F_CPU / (2 * N * (1 + OCR0))
 * Where:
 *   - F_CPU = 8,000,000 Hz
 *   - N = Prescaler value (we'll use 256)
 *   - OCR0 = Compare value (we'll use 49)
 *
 * Calculation:
 * f_out = 8,000,000 / (2 * 256 * (1 + 49))
 * f_out = 8,000,000 / (512 * 50)
 * f_out = 8,000,000 / 25,600
 * f_out = 312.5 Hz
 */

int main(void) {
    // --- Pin Configuration ---
    // Set the output pin as an output
    OUTPUT_DDR |= (1 << OUTPUT_PIN);

    // --- Timer0 Configuration ---
    // Using explicit bit shifts for clarity instead of magic numbers.
    
    // Set the compare value.
    OCR0 = 49;

    // Configure TCCR0 (Timer/Counter Control Register 0)
    // Mode: CTC (Clear Timer on Compare Match)
    // Prescaler: 256
    TCCR0 = (1 << WGM01) |   // Set WGM01 for CTC mode
            (1 << CS02);    // Set CS02 for a prescaler of 256

    // Enable the Timer0 Compare Match Interrupt
    TIMSK |= (1 << OCIE0);

    // Enable global interrupts
    sei();

    // The main loop is empty as the hardware timer and ISR handle everything.
    while (1) {
    }

    return 0; // Should not be reached
}

/**
 * @brief Interrupt Service Routine for Timer0 Compare Match.
 *
 * This function is automatically called by the hardware every time
 * the TCNT0 counter reaches the value in OCR0. It toggles the state
 * of the output pin, generating the square wave.
 */
ISR(TIMER0_COMP_vect) {
    // Toggle the output pin
    OUTPUT_PORT ^= (1 << OUTPUT_PIN);
}