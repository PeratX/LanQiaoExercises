#include <STC15F2K60S2.h>

#include "intrins.h"

unsigned char code t_display[] = {
	//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71,
	//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
	0x00, 0x40, 0x76, 0x1E, 0x70, 0x38, 0x37, 0x5C, 0x73, 0x3E, 0x78, 0x3d, 0x67, 0x50, 0x37, 0x6e,
	0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0x46}; //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

void delay1000ms()
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k)
				;
		} while (--j);
	} while (--i);
}

unsigned char trg;
unsigned char cont;

void keyRead()
{
	unsigned char readData = P3 ^ 0xFF;
	trg = readData & (readData ^ cont);
	cont = readData;
}

char currentValue = 0;

void main()
{
	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;

	P2 = 0x80;
	P0 = ~0x80;
	P2 = 0x00;

	P2 = 0xe0;
	P0 = ~t_display[0];
	P2 = 0x00;

	while (1)
	{
		keyRead();
		if (trg & 0x01)
		{
			currentValue++;
			if (currentValue > 9)
			{
				currentValue = 9;
			}
			P2 = 0xe0;
			P0 = ~t_display[currentValue];
			P2 = 0x00;

			P2 = 0x80;
			P0 = ~0x02;
			P2 = 0x00;
			delay1000ms();
			P2 = 0x80;
			P0 = 0xFF;
			P2 = 0x00;
		}
		if (trg & 0x02)
		{
			currentValue--;
			if (currentValue < 0)
			{
				currentValue = 0;
			}
			P2 = 0xe0;
			P0 = ~t_display[currentValue];
			P2 = 0x00;

			P2 = 0x80;
			P0 = ~0x01;
			P2 = 0x00;
			delay1000ms();
			P2 = 0x80;
			P0 = 0xFF;
			P2 = 0x00;
		}
	}
}