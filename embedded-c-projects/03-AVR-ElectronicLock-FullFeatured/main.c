
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lcd.h"
#include "mat_kbrd.h"
#include "tc0_pwm.h"
#include "KeyPadScan.h"
#include "T1EINT.h"

void configIo(); 
void mostrarHora();

int main(void)
{
	
	//vars
	uniS=48;
	decS=48;
	uniM=48;
	decM=48;
	uniH=48;
	decH=48;
	cuenta=0;
	regresa=0;
    //int reinicio=0;
	
	
	unsigned int aciertos2=0;
	unsigned int fallos=0;
	unsigned int fin2=0;
	unsigned int pin=0;
	char password2[5]="4322";
	unsigned char key2=255;
	unsigned char key3=255;
	unsigned char datoi;
	pospass2 = 0;
	unsigned int pospass3 = 0;
	unsigned char str_pass2[5];
	
	int acierto=0;
	char key1,c_aciertos;
	char password[5]="1234";
	unsigned char duty='0';
	unsigned char mensaje;
	unsigned int pos=0, fin=0,dutyint=0;
	char setPoint[16];
	char str[16];
	unsigned char str_pass[5];
	unsigned int pospass = 0;
	unsigned int pospass4 = 0;
	unsigned char dato;             //Dato introducido con teclado
	unsigned char str_RPM[3];       //Dato de RPM a introducidir
	unsigned int nRPM = 0;          //Variable auxiliar para recorrer el arreglo str_RMP
	float RPM;
	
	//inits
	lcd_init(LCD_DISP_ON); //INICIALIZA LA LDC, EL PUERTO AL QUE ESTÃ• CONECTADO PUERTO D
	 //INICIA TECLADO
	configIo();
	configTC0();
	counTCR1();
	configET1();
	configET2();
	
	lcd_home(); //ENVIAR EL PUNTERO A LA POSICION INICIAL
	lcd_puts(" BMO 4.0"); //IMPRIME EL CARACTER
	//_delay_ms(500);
	lcd_clrscr();
	sei();
	
	
    /* Replace with your application code */
    while (1) 
    {
		
		
		//unsigned int reinicio=0;
		unsigned char key1;
	    //char password[5]="1234";
		char c_aciertos[16];
		unsigned int acierto=0;
		//unsigned int reinicio=0;
	    pospass=0;         

		PORTC=0x00;
		
		inicio:
		
		pospass=0;
		
		
		//reinicio=0;
		if(reinicio!=0){
			reinicio=0;
		}
		
		
		do{
			fallos=0;
			PORTC=PORTC^(1<<3);
			
			mostrarHora();
			
			
			
			key1=getKeyPadData();
			
			if((key1!=255)&&(pospass<=3)&&(reinicio!=1)&&(menu2!=1)&&(regresa!=1)){
					str_pass[pospass] = key1+48;
					
					lcd_gotoxy(pospass,1);
					lcd_putc('*');
					_delay_ms(100);
					pospass++;
					
					if (strcmp(str_pass,password)==0)
					{
						acierto=1;
					}
			}
			key1=255;
			if ((((pospass>3)&(acierto!=1))&&(reinicio!=1)))
			{
				lcd_clrscr();
				pospass=0;
				break;
			}else{
			
			if (acierto==1)
			{
				
				lcd_clrscr();
				lcd_home();
				lcd_puts("MODO NORMAL");
				_delay_ms(200);
				lcd_clrscr();
				
				//inicio
				_delay_ms(100);
				while ((fin!=1)&&(reinicio!=1)&&(menu2!=1)&&(regresa!=1))
				{
					mostrarHora();
					if(reinicio==1){
						goto inicio;
					}
					
					
					dato = getKeyPadData();
					
				
				if(dato != 255)                                            //Se valida un ingreso de dato
				{if( nRPM != 4 )        //Se verifica que no se ingrese un dato de RPM mayor a 3 digitos
					{   
						if (dato==0x1A)
						{
							dato='.';
						}else{
						str_RPM[nRPM] = dato+48;
						}
						lcd_gotoxy(nRPM,1);
						if (dato=='.')
						{
							lcd_putc(dato);
						}else{
							lcd_putc(dato+48);
						}
						_delay_ms(100);
						nRPM++;
					}
					if( (dato == 0x0A) & (nRPM != 0))                           //Opcion para aceptar los RPM introducidos
					{
						RPM = atof(str_RPM);
						if(RPM > 200)             //Segun caracterizacion, RPM no puede ser mayor a 167, por ello se restringe
						{
							lcd_clrscr();
							mostrarHora();
							
							lcd_gotoxy(0,1);
							lcd_puts("Dato desbordado");
							_delay_ms(200);
							free(str_RPM);
							nRPM = 0;
							lcd_clrscr();
							mostrarHora();
							
							
						}
						else                                       //Ecuacion para introducir el PWM del motor
						{
							OCR0 = (float)(255/100)*RPM;
							fin=1;
							PORTC |= (2<<1);
							PORTC &= ~(1<<1);
							lcd_clrscr();
							mostrarHora();
							lcd_gotoxy(0,1);
							lcd_puts("Ajustando");
							_delay_ms(200);
							free(str_RPM);
							nRPM = 0;
							lcd_clrscr();
							mostrarHora();
							
						}
						if(RPM == 0)                                //Si RPM = 0, Deshabilita el motor
						{
							PORTC &= ~(1<<1);
							PORTC &= ~(2<<1);
							OCR0 = 0;
							fin=1;
							lcd_clrscr();
							lcd_puts("Ajustando");
							lcd_gotoxy(0,1);
							lcd_puts("Velocidad en RPM");
							_delay_ms(100);
							free(str_RPM);
							nRPM = 0;
							RPM = 0;
							lcd_clrscr();
							lcd_puts("Ingresar RPM");
							lcd_gotoxy(0,2);
							lcd_puts("Velocidad Motor");
							lcd_gotoxy(0,3);
							lcd_puts("(RPM): 0.000");
							
						}
					}
				}
				}
				fin=0;
				//fin
			}
			
			}
			} while ((reinicio!=1)&&(menu2!=1)&&(regresa!=1));
			
			if ((menu2==1)&&(reinicio!=1)&&(fallos==0)||(regresa==1))
			{
				regresa=0;
				
				lcd_clrscr();
				lcd_home();
				lcd_puts("MODO ADMIN");
				_delay_ms(200);
				lcd_clrscr();
				do
				{
					
					
					
					do{
						mostrarHora();
						key2=getKeyPadData();
						if((key2!=255)&&(pospass2<=3)){
							str_pass2[pospass2] = key2+48;
							
							lcd_gotoxy(pospass2,1);
							lcd_putc('*');
							_delay_ms(100);
							pospass2++;
							
							if (strcmp(str_pass2,password2)==0)
							{
								
								aciertos2=1;
								
								lcd_clrscr();
								mostrarHora();
								lcd_gotoxy(0,1);
								lcd_puts("admin");
								_delay_ms(200);
							}if ((((pospass2>3)&(aciertos2!=1))))
							{
								lcd_clrscr();
								mostrarHora();
								pospass2=0;
								fallos=1;
								
							}
						}
						key2=255;
						
						}
						while((aciertos2!=1)&&(fallos==0)&&(reinicio!=1));
						if (aciertos2==1)
						{
						
				
							
							do 
							{
						
							lcd_clrscr();
							mostrarHora();
							lcd_gotoxy(0,1);
							lcd_puts("1.CH 2.CC 3.E");
							
							key3=getKeyPadData();
							if (key3!=255)
							{
								lcd_gotoxy(0,1);
								lcd_putc(key3+48);
							}
							
							if (key3+48=='3')
							{
							
							fin2=1;
							lcd_clrscr();
							_delay_ms(100);
							mostrarHora();	
							}
							if (key3+48=='1')
							{
								lcd_clrscr();
								mostrarHora();
								lcd_gotoxy(0,0);
								lcd_puts("HH/MM/SS");
								lcd_gotoxy(0,1);
								key2=255;
								//menu2=0;
								
								do
								{
									
									mostrarHora();
									key2=255;
									_delay_ms(100);
									key2=getKeyPadData();
									
										
										if((key2!=255)&&(pospass4<=7)){
											if (pospass4==0)
											{
												decH=key2+48;
												lcd_gotoxy(pospass4,1);
												lcd_putc(key2+48);
											}
											if (pospass4==1)
											{
												uniH=key2+48;
												lcd_gotoxy(pospass4,1);
												lcd_putc(key2+48);
											}
											if (pospass4==2)
											{
									
												lcd_gotoxy(pospass4,1);
												lcd_putc('/');
											}
											
											if (pospass4==3)
											{
												
												decM=key2+48;
												lcd_gotoxy(pospass4,1);
												lcd_putc(key2+48);
											}
											if (pospass4==4)
											{
												
												uniM=key2+48;
												lcd_gotoxy(pospass4,1);
												lcd_putc(key2+48);
											}
											if (pospass4==5)
											{
												
												lcd_gotoxy(pospass4,1);
												lcd_putc('/');
											}
											if (pospass4==6)
											{
												
												decS=key2+48;
												lcd_gotoxy(pospass4,1);
												lcd_putc(key2+48);
											}
											if (pospass4==7)
											{
												
												uniS=key2+48;
												lcd_gotoxy(pospass4,1);
												lcd_putc(key2+48);
												_delay_ms(100);
											}
											pospass4++;
										}
										
										
									} while ((pospass4<=7)&&(reinicio!=1)&& (regresa!=1)/*&&(menu2!=1)*/);
									fin2=1;
								key2=255;
								pospass4=0;
								lcd_clrscr();
								mostrarHora();
								
							}
							if(key3+48=='2'){
							lcd_clrscr();
							mostrarHora();
							lcd_gotoxy(0,1);
							lcd_puts("ingrese pass1");
							_delay_ms(200);
							lcd_clrscr();
							mostrarHora();
							lcd_home();
							//menu2=0;
							
							do
							{
								
								mostrarHora();
								key2=255;
								key2=getKeyPadData();
								
								if((key2!=255)&&(pospass3<=3)){
									password[pospass3] = key2+48;
									lcd_gotoxy(pospass3,1);
									lcd_putc(password[pospass3]);
									_delay_ms(100);
									pospass3++;
									
								}
								fin2=1;
								
							} while ((pospass3<=3)&&(reinicio!=1)&& (regresa!=1)/*&&(menu2!=1)*/);
							lcd_gotoxy(0,0);
							lcd_puts(password);
							_delay_ms(100);
							lcd_clrscr();
							mostrarHora();
							lcd_home();
							}
						
						 }while (((key3+48)!='3')&&(fin2!=1)&&(reinicio!=1)&& (regresa!=1));
						
					}
					} while ((fin2=!1)&&(reinicio!=1)&&(menu2!=1)&& (regresa!=1));
					mostrarHora();
					pin=0;
					pospass=0;
					pospass2=0;
					pospass3=0;
					aciertos2=0;
					pospass=0;
					fin2=0;
					key2=255;
					key3=255;
					menu2=0;
					
					bzero(str_pass2,5);
					
			}
			if(reinicio!=0)
			{
				lcd_clrscr();
				lcd_puts("reiniciado");
				_delay_ms(100);
				lcd_clrscr();
				lcd_home();
				acierto=0;
				
				bzero(str_pass,5);
				pospass=0;
				key1=255;
				PORTC=0x00;
				bzero(str_RPM,3);
				nRPM = 0;
				RPM = 0;
				
				
				goto inicio;
				
				
				
			}
			
		
		
    } 
}

void configIo(){
	DDRD=0b11110111;
	DDRC=0xFF;
	DDRA=0x0F;
	DDRB=0xFF;

}
void mostrarHora(){
	lcd_gotoxy(15,0);
	lcd_putc(uniS);
	lcd_gotoxy(14,0);
	lcd_putc(decS);
	lcd_gotoxy(13,0);
	lcd_putc(':');
	lcd_gotoxy(12,0);
	lcd_putc(uniM);
	lcd_gotoxy(11,0);
	lcd_putc(decM);
	lcd_gotoxy(10,0);
	lcd_putc(':');
	lcd_gotoxy(9,0);
	lcd_putc(uniH);
	lcd_gotoxy(8,0);
	lcd_putc(decH);
}

