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
			if (mode == 0)
			{
				mode = 1;
			}
			else
			{
				mode = 0;
			}
		}

		P2 = 0x80;
		P0 = ~(0x80 >> i);
		P2 = 0x00;
		if (mode == 0)
		{
			i++;
			if (i == 8)
			{
				i = 0;
			}
		}
		else
		{
			i--;
			if (i == -1)
			{
				i = 7;
			}
		}
		delay1000ms();
	}
}