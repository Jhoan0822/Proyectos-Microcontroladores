//Jhoan Eduardo Saldarriaga Serna
//Julian Andres Barona Herrera

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

#define SLA_ADDR 0x20  // Dirección del esclavo (0x10 << 1)

void TWI_Slave_Init(uint8_t address) {
	TWAR = address;  // Carga la dirección en el registro de dirección TWI
	TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWIE);  // Habilita TWI y la interrupción
}

ISR(TWI_vect) {
	static char data;  // Declara la variable fuera de la instrucción switch
	
	switch (TWSR & 0xF8) {
		case TW_SR_SLA_ACK:  // SLA+W propio ha sido recibido, ACK ha sido devuelto
		case TW_SR_DATA_ACK:  // Byte de datos ha sido recibido, ACK ha sido devuelto
		data = TWDR;  // Lee los datos recibidos
		
		// Detener ambos motores por defecto
		PORTA &= ~(1<<PA0) & ~(1<<PA1) & ~(1<<PA2) & ~(1<<PA3);
		PORTA &= ~(1<<PA5) & ~(1<<PA6);

		if (data == 'F') {
			// Adelante
			PORTA |= (1<<PA5) | (1<<PA6);  // Habilita ambos motores
			PORTA |= (1<<PA0) | (1<<PA2);  // IN1 e IN3 en alto
			PORTA &= ~(1<<PA1) & ~(1<<PA3);  // IN2 e IN4 en bajo
			} else if (data == 'B') {
			// Atrás
			PORTA |= (1<<PA5) | (1<<PA6);  // Habilita ambos motores
			PORTA &= ~(1<<PA0) & ~(1<<PA2);  // IN1 e IN3 en bajo
			PORTA |= (1<<PA1) | (1<<PA3);  // IN2 e IN4 en alto
			} else if (data == 'L') {
			// Girar a la izquierda (Motor A hacia adelante, Motor B hacia atrás)
			PORTA |= (1<<PA5) | (1<<PA6);  // Habilita ambos motores
			PORTA |= (1<<PA0);  // IN1 en alto
			PORTA &= ~(1<<PA1);  // IN2 en bajo
			PORTA &= ~(1<<PA2);  // IN3 en bajo
			PORTA |= (1<<PA3);  // IN4 en alto
			} else if (data == 'R') {
			// Girar a la derecha (Motor A hacia atrás, Motor B hacia adelante)
			PORTA |= (1<<PA5) | (1<<PA6);  // Habilita ambos motores
			PORTA &= ~(1<<PA0);  // IN1 en bajo
			PORTA |= (1<<PA1);  // IN2 en alto
			PORTA |= (1<<PA2);  // IN3 en alto
			PORTA &= ~(1<<PA3);  // IN4 en bajo
		}

		TWCR |= (1<<TWINT);  // Limpia la bandera de interrupción para reanudar la operación TWI
		break;
		case TW_SR_STOP:
		TWCR |= (1<<TWINT) | (1<<TWEA);  // Limpia la bandera de interrupción y habilita TWI
		break;
		default:
		TWCR |= (1<<TWINT);  // Limpia la bandera de interrupción
		break;
	}
}

int main(void) {
	DDRA |= (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA5) | (1<<PA6);  // Configura PD0, PD1, PD2, PD3, PD5, PD6 como salidas

	TWI_Slave_Init(SLA_ADDR);  // Inicializa TWI como esclavo
	sei();  // Habilita las interrupciones globales

	while (1) {
		// El bucle principal no hace nada, la interrupción TWI maneja la comunicación
	}
}
