/**
 * @file main.c
 * @author Jhoan Eduardo Saldarriaga Serna
 * @brief Project 01: Blinking all LEDs on a port (AVR "Hello, World!")
 * @version 1.1 (Corrected)
 * @date 2024-07-05
 *
 * This is a fundamental "Hello, World" program for AVR microcontrollers.
 * It configures all pins of PORTB as outputs and makes them blink in unison
 * with a one-second interval, demonstrating basic GPIO control.
 */

#define F_CPU 4000000UL // Set CPU frequency to 4MHz for _delay_ms()

#include <avr/io.h>
#include <util/delay.h>

// --- Hardware Definitions ---
#define LED_PORT    PORTB
#define LED_DDR     DDRB

// --- Function Prototypes ---
void init_gpio(void);

// --- Main Program ---
int main(void) {
    init_gpio();

    while (1) {
        // Turn all LEDs ON
        LED_PORT = 0xFF;
        _delay_ms(1000);

        // Turn all LEDs OFF
        LED_PORT = 0x00;
        _delay_ms(1000);
    }
    
    return 0; // Should not be reached
}

/**
 * @brief Configures the necessary GPIO pins.
 *
 * This function sets the Data Direction Register (DDR) for the LED port,
 * configuring all its pins as outputs.
 */
void init_gpio(void) {
    // Set all pins of LED_DDR to output mode.
    // DDRB = 0xFF is the correct configuration.
    LED_DDR = 0xFF;
}