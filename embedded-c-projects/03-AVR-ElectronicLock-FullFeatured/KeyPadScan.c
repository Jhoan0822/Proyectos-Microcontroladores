/*
 * KeyPadScan.c
 *
 * Created:
 *  Author:
 */ 
#include "KeyPadScan.h"
#include "T1EINT.h"
#include <util/delay.h>


unsigned char getKeyPadData()
{
	_delay_ms(10);
	unsigned int iRow, iCol = 0;
	unsigned char myKeyPressed;
	unsigned char keyMap[4][4];
	
	// Inits
	keyMap[0][0] = 0x01;
	keyMap[0][1] = 0x02;
	keyMap[0][2] = 0x03;
	keyMap[0][3] = 0x0A;
	keyMap[1][0] = 0x04;
	keyMap[1][1] = 0x05;
	keyMap[1][2] = 0x06;
	keyMap[1][3] = 0x0B;
	keyMap[2][0] = 0x07;
	keyMap[2][1] = 0x08;
	keyMap[2][2] = 0x09;
	keyMap[2][3] = 0x0C;
	keyMap[3][0] = 0x1A;
	keyMap[3][1] = 0x00;
	keyMap[3][2] = 0x1B;
	keyMap[3][3] = 0x0D;
	
	myKeyPressed = 0xff;
	
	// Key pad Scan
	for(;;)
	{
		if (reinicio!=0)
		{
			break;
		}
		KEYPAD_PORT &= 0xf0;
		
		KEYPAD_PORT |= (1 << iCol);
		
		for(iRow=0; iRow < 4; iRow++)
		{
			if (KEYPAD_PIN & (0x10 << iRow))
			{
				//PORTA |= (1 << 0);
				myKeyPressed = keyMap[iRow][iCol];
				return myKeyPressed;
			}
			//else
				//PORTA &= 0xfe;
				
			_delay_ms(KEYPAD_DELAY);
		}
		
		KEYPAD_PORT &= 0xf0;
		
		iCol++;
		if (iCol == 4)
			break;
	}
	
	return myKeyPressed;
}
