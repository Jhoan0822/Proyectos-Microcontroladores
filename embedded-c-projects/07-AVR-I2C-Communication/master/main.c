//Jhoan Eduardo Saldarriaga Serna
//Julian Andres Barona Herrera

#define F_CPU 8000000UL
#define SCL_CLOCK 100000L
#include <avr/io.h>
#include <util/delay.h>


void TWI_Init(void) {
	TWSR = 0x00;
	TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;
	TWCR = (1<<TWEN);
}

void TWI_Start(void) {
	TWCR = (1<<TWSTA) | (1<<TWEN) | (1<<TWINT);
	while (!(TWCR & (1<<TWINT)));
}

void TWI_Stop(void) {
	TWCR = (1<<TWSTO) | (1<<TWEN) | (1<<TWINT);
	while (TWCR & (1<<TWSTO));
}

void TWI_Write(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWEN) | (1<<TWINT);
	while (!(TWCR & (1<<TWINT)));
}

int main(void) {
	DDRD &= ~(1<<PD2) & ~(1<<PD3) & ~(1<<PD4);  // Configura PD2, PD3, PD4 como entrada
	PORTD |= (1<<PD2) | (1<<PD3) | (1<<PD4);    // Habilita resistencias pull-up internas

	TWI_Init();
	
	while (1) {
		char symbol = 'N';  // Símbolo por defecto (Ninguno)

		// Evaluar directamente el estado de cada pulsador
		if (!(PIND & (1<<PD2))) {
			symbol = 'F';  // Adelante (PD2)
			} else if (!(PIND & (1<<PD3))) {
			symbol = 'B';  // Atrás (PD3)
			} else if (!(PIND & (1<<PD4))) {
			symbol = 'L';  // Izquierda (PD4)
			} else if (!(PIND & (1<<PD2)) && !(PIND & (1<<PD3))) {
			symbol = 'R';  // Derecha (PD2 y PD3)
		}

		TWI_Start();
		TWI_Write(0x20);  // Dirección del esclavo (0x10 << 1 para escribir)
		TWI_Write(symbol);
		TWI_Stop();

		_delay_ms(500);  // Retraso para evitar rebote de los pulsadores
	}
}
