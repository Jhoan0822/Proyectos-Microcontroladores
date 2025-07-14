#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
/**
 * @file main.c
 * @author Jhoan Eduardo Saldarriaga Serna
 * @brief Ultrasonic Distance Sensor (HC-SR04) Driver using Timer1 Input Capture
 * @version 1.0
 * @date 2024-07-05
 *
 * This project measures distance using an HC-SR04 ultrasonic sensor. It employs
 * the Timer1 Input Capture Unit (ICP1) to precisely measure the width of the
 * echo pulse, which is proportional to the distance. The result is then
 * displayed on a 16x2 LCD screen.
 *
 * The use of ICP is a highly accurate, hardware-based method for timestamping
 * events (rising/falling edges) without CPU polling overhead.
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h> // For dtostrf()
#include "lcd.h"

// --- Hardware Pin Definitions ---
#define TRIGGER_DDR   DDRD
#define TRIGGER_PORT  PORTD
#define TRIGGER_PIN   PD0

#define ECHO_DDR      DDRD
#define ECHO_PIN_REG  PIND
#define ECHO_PIN      PD6 // ICP1 pin on ATmega32A

#define LED_DDR       DDRA
#define LED_PORT      PORTA
#define LED_PIN       PA6

// --- Global Variable for Timer Overflow ---
volatile uint16_t timer1_overflow_count = 0;

// --- ISR for Timer1 Overflow ---
ISR(TIMER1_OVF_vect) {
    timer1_overflow_count++;
}


int main(void) {
    char distance_str[10];
    uint32_t pulse_ticks = 0;
    double distance_cm = 0;

    // --- Hardware Initialization ---
    TRIGGER_DDR |= (1 << TRIGGER_PIN);  // Trigger pin as output
    LED_DDR |= (1 << LED_PIN);          // LED pin as output
    
    lcd_init(LCD_DISP_ON);
    lcd_puts("Ultrasonic Meter");
    _delay_ms(1000);
    
    // --- Timer1 and Interrupt Initialization ---
    TCCR1A = 0; // Normal timer operation
    TIMSK = (1 << TOIE1); // Enable Timer1 Overflow interrupt
    sei(); // Enable global interrupts

    while (1) {
        // --- 1. Send Trigger Pulse ---
        TRIGGER_PORT |= (1 << TRIGGER_PIN);
        _delay_us(10);
        TRIGGER_PORT &= ~(1 << TRIGGER_PIN);

        // --- 2. Measure Echo Pulse Width using Input Capture ---
        
        // Configure to capture the RISING edge
        TCCR1B = (1 << ICES1) | (1 << CS10); // Capture on rising, no prescaler
        TIFR |= (1 << ICF1) | (1 << TOV1);    // Clear flags
        timer1_overflow_count = 0;
        
        // Wait for the rising edge
        while ((TIFR & (1 << ICF1)) == 0);
        TCNT1 = 0; // Reset timer count to 0 *after* the rising edge
        TIFR |= (1 << ICF1); // Clear flag

        // Configure to capture the FALLING edge
        TCCR1B &= ~(1 << ICES1); // Capture on falling edge now
        
        // Wait for the falling edge
        while ((TIFR & (1 << ICF1)) == 0);
        pulse_ticks = ICR1 + (65536UL * timer1_overflow_count); // Read total ticks
        TIFR |= (1 << ICF1); // Clear flag
        
        // --- 3. Calculate and Display Distance ---

        // Distance (cm) = (Pulse Duration in seconds * Speed of Sound in cm/s) / 2
        // Pulse Duration (s) = pulse_ticks / F_CPU
        // Speed of Sound = 34300 cm/s
        // Distance (cm) = (pulse_ticks / 8,000,000) * 34300 / 2
        // Distance (cm) = pulse_ticks * (34300 / 16,000,000)
        // Distance (cm) = pulse_ticks / 466.47
        distance_cm = (double)pulse_ticks / 466.47;

        // --- 4. User Feedback ---
        // Turn on an LED if the object is within a certain range
        if (distance_cm >= 5 && distance_cm <= 10) {
            LED_PORT |= (1 << LED_PIN);
        } else {
            LED_PORT &= ~(1 << LED_PIN);
        }

        // Display on LCD
        lcd_clrscr();
        lcd_gotoxy(0, 0);
        lcd_puts("Dist: ");
        dtostrf(distance_cm, 4, 2, distance_str); // Format to "xx.xx"
        lcd_puts(distance_str);
        lcd_puts(" cm");
        
        _delay_ms(300); // Wait before next measurement
    }
}
