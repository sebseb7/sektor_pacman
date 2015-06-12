#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "font5x3.h"
#include "../main.h"
#include "text_5x3.h"

void print_5x3_at (int x,int y, char *text, unsigned char r, unsigned char g, unsigned char b)
{
	while (*text)
	{
		putc_5x3_at(x,y,*text,r,g,b);
		x+=4;
		text++;
	}

}

void putc_5x3_at (int x,int y, char text, unsigned char r, unsigned char g, unsigned char b)
{
	text -= 32;

	int i;
	for (i = 0; i < 3; i++)
	{
		char ch = font5x3[(int)text][i];

		int j;
		for (j = 0; j < 5; j++)
		{
			if(ch & (1<<j))
			{
				setLedXY(x+i,LED_HEIGHT-(y-j+4),r,g,b);
			}
			else
			{
				//setLedXY(x+i,y-j+4,0,0,0);
			}
		}
	}
}

void print_unsigned_5x3_at(int x, int y, unsigned int number, int length, char pad,unsigned char r, unsigned char g, unsigned char b)
{
	x += length * 4 - 1;
	int i;
	for(i = 0; i < length; i++) {
		int d = number % 10;
		putc_5x3_at(
			x -= 4, y,
			!i || number > 0 ? '0' + d : pad,
			r,g,b);
		number /= 10;
	}
}


void print_num_5x3_at (int x, int y, int number, int length, int pad, unsigned char r, unsigned char g, unsigned char b)
{

	char s[10];
	sprintf(s, "%i", number);
	int len = strlen(s);

	if (length < len) {
		int i;
		for (i = 0; i < length; i++) {
			putc_5x3_at (x += 4, y, '*', r,g,b);
		}
		return;
	}
	int i;
	for (i = 0; i < length - len; i++) {
		putc_5x3_at (x += 4, y, pad, r,g,b);
	}
	print_5x3_at(x, y, (char*)s, r,g,b);

}


