#include <STC15F2K60S2.h>
#include "intrins.h"

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

unsigned char mode = 0; //0 -> right to left, 1 -> left to right

void main()
{
	char i;

	P2 = 0xA0;
	P0 = 0x00;
	P2 = 0x00;

	while (1)
	{
		keyRead();
		if (trg & 0x01)
		{
			mode = (mode == 0) ? 1 : 0;
		}

		P2 = 0x80;
		P0 = ~(0x80 >> i);
		P2 = 0x00;

		if (mode == 0)
		{
			i++;
			i = (i == 8) ? 0 : i;
		}
		else
		{
			i--;
			i = (i == -1) ? 7 : i;
		}

		delay1000ms();
	}
}