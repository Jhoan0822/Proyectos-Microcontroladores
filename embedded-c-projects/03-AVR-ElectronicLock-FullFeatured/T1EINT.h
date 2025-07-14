/*
 * T1EINT.h
 *
 * Created: 6/05/2024 10:23:57 a. m.
 *  Author: Usuario
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lcd.h"

#ifndef T1EINT_H_
#define T1EINT_H_

volatile unsigned int pospass2;
volatile unsigned int regresa;
volatile unsigned int reinicio;
volatile unsigned int menu2;
volatile char password[5];
volatile unsigned char uniS;
volatile unsigned char decS;
volatile unsigned char uniM;
volatile unsigned char decM;
volatile unsigned char uniH;
volatile unsigned char decH;
volatile unsigned int cuenta;

void configET1();

void configTCR1();

void counTCR1();



#endif /* T1EINT_H_ */