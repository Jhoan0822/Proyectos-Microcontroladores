

 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "tc0_pwm.h"

void configTC0()
{
	//Clock Source: clk_IO/64
	TCCR0 |= (1<<CS01| (1<<CS00));
	
	//Operation Mode: Fast PWM
	TCCR0 |= (1<<WGM01) | (1<<WGM00);
	
	//OC0 Mode: Non inverting
	TCCR0 |= (1<<COM01);
}


