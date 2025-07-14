//Jhoan Eduardo Saldarriaga Serna
//Julian Andres Barona Herrera

#define F_CPU 8000000UL  
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "lcd.h"  
#include <stdlib.h>  // Para usar dtostrf


#define THRESHOLD 3.0     // Umbral de 3V

// Define una variable global en EEPROM
char EEMEM storedValue[10];

void SPI_SlaveInit(void) {
	DDRB = (1<<PB6);  // Configura MISO como salida
	SPCR = (1<<SPE);  // Habilita SPI
}

char SPI_SlaveReceive(void) {
	while(!(SPSR & (1<<SPIF)));  // Espera hasta recibir dato
	return SPDR;  // Lee el dato recibido
}

void SPI_ReceiveString(char* buffer, uint8_t max_length) {
	uint8_t i = 0;
	while (i < max_length - 1) {
		buffer[i] = SPI_SlaveReceive();
		if (buffer[i] == '\0') break;
		i++;
	}
	buffer[i] = '\0';  // Asegura la terminación de la cadena
}

int main(void) {
	char promedio_str[10];
	float promedio;

	// Inicializa LCD y SPI
	lcd_init(LCD_DISP_ON);
	SPI_SlaveInit();

	// Configura el LED como salida
	DDRD |= (1<<PD3);

	while (1) {
		SPI_ReceiveString(promedio_str, sizeof(promedio_str));  // Recibe el promedio del maestro

		eeprom_update_block((const void*)promedio_str, (void*)storedValue, sizeof(promedio_str));  // Guarda el promedio en la EEPROM

		eeprom_read_block((void*)promedio_str, (const void*)storedValue, sizeof(promedio_str));  // Lee el promedio desde la EEPROM

		promedio = atof(promedio_str);  // Convierte la cadena a float

		// Muestra el promedio en el LCD
		lcd_clrscr();
		lcd_gotoxy(0, 0);
		lcd_puts("Promedio: ");
		lcd_puts(promedio_str);
		lcd_puts("V");

		// Enciende el LED si el promedio es mayor al umbral
		if (promedio > THRESHOLD) {
			PORTD |= (1<<PD3);  // Enciende el LED
			} else {
			PORTD &= ~(1<<PD3);  // Apaga el LED
		}

		//_delay_ms(1000);  // Espera 1 segundo antes de la siguiente operación
	}
	return 0;
}