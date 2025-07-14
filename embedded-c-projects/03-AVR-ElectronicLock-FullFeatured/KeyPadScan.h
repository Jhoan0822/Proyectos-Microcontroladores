/*
 * KeyPadScan.h
 *
 * Created:
 *  Author:
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define KEYPAD_PORT PORTA
#define KEYPAD_PIN	PINA
#define KEYPAD_DELAY 16

unsigned char getKeyPadData();
