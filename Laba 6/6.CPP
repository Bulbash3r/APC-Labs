#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void interrupt (*old9)(...);
void interrupt new9(...)
{
	char buf[5];
	unsigned char c = inp(0x60);

	if (c != 0xFA)
	{
		puts("Button   ");
		itoa(c, buf, 16);
		cputs("0x");
		cputs(buf);
		cputs("\n\r");
	}
	(*old9)();
}

void blink(int a)
{
	int i = 0;
	while((inp(0x64) & 2) != 0);

	do
	{
		i++;
		outp(0x60, a);
	}while (inp(0x60) == 0xFE && i < 3);
}

void main()
{
	clrscr();
	old9 = getvect(0x09);
	setvect(0x09, new9);
	printf("\r\n(Press ESC to exit program)\n\rTap any key:");
	int i;

	while(1)
	{
		for (i = 0; i < 8; i++)
		{
			if(kbhit())
				if(getch() == 27)
				{
					setvect(0x09, old9);
					return;
				}
			blink(0xED);
			blink(i);
			delay(100);
		}
	}
}


