//Jhoan Eduardo Saldarriaga Serna
//Julian Andres Barona Herrera

#define F_CPU 8000000UL  
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"  
#include <stdlib.h>  // Para usar dtostrf



void SPI_MasterInit(void) {
	// Configura MOSI, SCK y SS como salidas, MISO como entrada
	DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);
	PORTB |= (1<<PB4);  // Desactiva SS al inicio
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);  // Habilita SPI, configura maestro, velocidad Fosc/16
}

void SPI_MasterTransmit(char cData) {
	SPDR = cData;  // Carga el dato en el registro SPI data
	while(!(SPSR & (1<<SPIF)));  // Espera hasta que la transmisión esté completa
}

void ADC_Init(void) {
	ADMUX = (1<<REFS0);  // Selecciona AVcc como  5V y canal ADC0
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);  // Habilita ADC y establece prescaler en 128
}

uint16_t ADC_Read(uint8_t channel) {
	channel &= 0x07;  //  canal esté entre 0 y 7
	ADMUX = (ADMUX & 0xF8) | channel;  // Selecciona el canal ADC
	ADCSRA |= (1<<ADSC);  // Inicia la conversión
	while(ADCSRA & (1<<ADSC));  // Espera hasta que la conversión esté completa
	return ADC;
}

float ADC_to_Voltage(uint16_t adc_value) {
	return (adc_value * 5.0) / 1024.0;  // Convierte el valor ADC a voltaje
}

void float_to_string(float value, char* buffer, int decimal_points) {
	dtostrf(value, 4, decimal_points, buffer);  // Convierte float a string
}

void SPI_SendString(const char* str) {
	PORTB &= ~(1<<PB4);  // Activa SS (bajo)
	while (*str) {
		SPI_MasterTransmit(*str++);
	}
	SPI_MasterTransmit('\0');  // Enviar terminador de cadena
	PORTB |= (1<<PB4);  // Desactiva SS (alto)
}

int main(void) {
	uint16_t adc1, adc2, adc3;
	float volt1, volt2, volt3, promedio;
	char buffer[10];

	// Inicializa LCD, ADC y SPI
	lcd_init(LCD_DISP_ON);
	ADC_Init();
	SPI_MasterInit();
	
	while (1) {
		adc1 = ADC_Read(0);  // Lee ADC en el canal 0
		adc2 = ADC_Read(1);  // Lee ADC en el canal 1
		adc3 = ADC_Read(2);  // Lee ADC en el canal 2

		volt1 = ADC_to_Voltage(adc1);  // Convierte ADC a voltaje
		volt2 = ADC_to_Voltage(adc2);
		volt3 = ADC_to_Voltage(adc3);

		promedio = (volt1 + volt2 + volt3) / 3.0;  // Calcula el promedio de voltajes

		// Muestra las lecturas en el LCD
		lcd_clrscr();
		lcd_gotoxy(0, 0);
		float_to_string(volt1, buffer, 2);
		lcd_puts("V1:");
		lcd_puts(buffer);
		lcd_puts("V ");
		
		float_to_string(volt2, buffer, 2);
		lcd_puts("V2:");
		lcd_puts(buffer);
		lcd_puts("V ");
		
		lcd_gotoxy(0, 1);
		float_to_string(volt3, buffer, 2);
		lcd_puts("V3:");
		lcd_puts(buffer);
		lcd_puts("V ");
		
		float_to_string(promedio, buffer, 2);
		lcd_puts("P:");
		lcd_puts(buffer);
		lcd_puts("V");

		// Transmite el promedio por SPI
		SPI_SendString(buffer);

		_delay_ms(1000);  // Espera 1 segundo antes de la siguiente lectura
	}
	return 0;
}