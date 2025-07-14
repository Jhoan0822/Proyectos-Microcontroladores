/*
 * T1EINT.c
 *
 * Created: 6/05/2024 10:24:12 a. m.
 *  Author: Usuario
 */ 
#define F_CPU 8000000UL

#include "T1EINT.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lcd.h"




void configET1()
{
	sei();

	MCUCR |= (1<<ISC10) | (1<<ISC11);
	GICR |= (1<<INT1);
	         
	reinicio = 0;
}
void configET2()
{
	sei();

	MCUCSR |= (1<<ISC2) ;
	GICR |= (1<<INT2);
	
}

void counTCR1()
{
	
	TIMSK=(1<<OCIE1A);
	OCR1A=31250;
	TCCR1B=(1<<WGM12)|(1<<CS10);
	sei();
	
}


ISR(INT1_vect)                
{
	reinicio = 1;
}

ISR(INT2_vect)
{   pospass2 = 0;
	lcd_clrscr();
	mostrarHora();
	menu2=1;
	regresa=1;
	}

ISR(TIMER1_COMPA_vect)
{
	PORTC^=(1<<PINC3);
	cuenta++;
	if (cuenta==128)
	{
		uniS++;
		cuenta=0;
		if (uniS==58)
		{
			uniS=48;
			decS++;
			if (decS==54)
			{
				decS=48;
				uniM++;
				if (uniM==58)
				{
					uniM=48;
					decM++;
					if (decM==54)
					{
						decM=48;
						uniH++;
						if (uniH==58)
						{
							uniH=48;
							decH++;
						}
					    if ((decH==50)&&(uniH==52))
							{
								decH=48;
								uniH=48;
								decM=48;
								uniM=48;
								decS=48;
								uniS=48;
							
						     }
					}
				}
			}
		}
	}
}