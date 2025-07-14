/**
 * @file main.c
 * @author Jhoan Eduardo Saldarriaga Serna
 * @brief Four-function calculator on an ATmega32A with keypad and LCD.
 * @version 2.0
 * @date 2024-07-05
 *
 * This project implements a basic arithmetic calculator that can perform addition,
 * subtraction, multiplication, and division on floating-point numbers. Input is
 * handled by a 4x4 matrix keypad, and the expression and result are shown on
 * a 16x2 LCD.
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // For atof, dtostrf
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lcd.h"
#include "mat_kbrd.h"

// --- Constants and Definitions ---
#define MAX_BUFFER_SIZE 8

// --- Data Structures ---
// Using a struct to manage the calculator's state is cleaner than static variables.
typedef struct {
    char num1_str[MAX_BUFFER_SIZE];
    char num2_str[MAX_BUFFER_SIZE];
    char result_str[MAX_BUFFER_SIZE];
    char op;
    int num1_idx;
    int num2_idx;
    bool is_operator_set;
    bool has_decimal1;
    bool has_decimal2;
} CalculatorState;

// --- Function Prototypes ---
void init_hardware(void);
void reset_calculator(CalculatorState *calc);
void process_input(char key, CalculatorState *calc);
void update_display(const CalculatorState *calc);
void perform_calculation(CalculatorState *calc);


// --- Main Program ---
int main(void) {
    init_hardware();
    
    CalculatorState calculator;
    reset_calculator(&calculator);

    while (1) {
        char key = kbrd_read();

        if (key != 0) { // A key was pressed
            if (key == '+') { // Using '+' as the clear key in this keypad layout
                reset_calculator(&calculator);
            } else {
                process_input(key, &calculator);
            }
            update_display(&calculator);
        }
         _delay_ms(100); // Simple debounce and CPU relief
    }
}

// --- Function Definitions ---

void init_hardware(void) {
    lcd_init(LCD_DISP_ON);
    kbrd_init();
    lcd_clrscr();
    lcd_puts("AVR Calculator");
    _delay_ms(1000);
    lcd_clrscr();
}

void reset_calculator(CalculatorState *calc) {
    memset(calc, 0, sizeof(CalculatorState)); // Clears all fields to 0/NULL/false
    lcd_clrscr();
}

void process_input(char key, CalculatorState *calc) {
    // Process digits and decimal point
    if ((key >= '0' && key <= '9') || key == '.') {
        if (!calc->is_operator_set) { // Inputting the first number
            if (key == '.' && !calc->has_decimal1 && calc->num1_idx < MAX_BUFFER_SIZE - 1) {
                calc->num1_str[calc->num1_idx++] = key;
                calc->has_decimal1 = true;
            } else if (key != '.' && calc->num1_idx < MAX_BUFFER_SIZE - 1) {
                calc->num1_str[calc->num1_idx++] = key;
            }
        } else { // Inputting the second number
            if (key == '.' && !calc->has_decimal2 && calc->num2_idx < MAX_BUFFER_SIZE - 1) {
                calc->num2_str[calc->num2_idx++] = key;
                calc->has_decimal2 = true;
            } else if (key != '.' && calc->num2_idx < MAX_BUFFER_SIZE - 1) {
                calc->num2_str[calc->num2_idx++] = key;
            }
        }
    } 
    // Process operators
    else if (key == '+' || key == '-' || key == 'x' || key == '/') {
        if (calc->num1_idx > 0 && !calc->is_operator_set) {
            calc->op = key;
            calc->is_operator_set = true;
        }
    } 
    // Process calculation
    else if (key == '=') {
        if (calc->num1_idx > 0 && calc->num2_idx > 0 && calc->is_operator_set) {
            perform_calculation(calc);
        }
    }
}

void update_display(const CalculatorState *calc) {
    lcd_clrscr();
    lcd_gotoxy(0, 0);
    lcd_puts(calc->num1_str);
    if (calc->is_operator_set) {
        lcd_putc(calc->op);
    }
    lcd_puts(calc->num2_str);

    if (calc->result_str[0] != '\0') {
        lcd_gotoxy(0, 1);
        lcd_putc('=');
        lcd_puts(calc->result_str);
    }
}

void perform_calculation(CalculatorState *calc) {
    float num1 = atof(calc->num1_str);
    float num2 = atof(calc->num2_str);
    float result = 0.0f;

    switch (calc->op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case 'x': result = num1 * num2; break;
        case '/': 
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                // Handle division by zero
                strcpy(calc->result_str, "Div by 0 Error");
                return;
            }
            break;
    }
    dtostrf(result, MAX_BUFFER_SIZE - 1, 2, calc->result_str);
}