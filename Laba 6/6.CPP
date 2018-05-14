#include <dos.h>
#include <conio.h>
#include <stdio.h>
void interrupt NewInterrupt(...);
void interrupt(*oldInterrupt)(...);
void UpdateHighlightFlag(unsigned char);
void SetMask(unsigned char mask);
int commandIsExecuted;
int quitFlag;
int needHighlight;
void main()
{
		commandIsExecuted = 0;
		quitFlag = 0;
		needHighlight = 0;
		oldInterrupt = getvect(9);
		setvect(9, NewInterrupt);
		while (!quitFlag)
		{
				if (needHighlight)
				{
						SetMask(0x02);
						delay(1000);
						SetMask(0x00);
						delay(1000);
						SetMask(0x02);
						delay(500);
						SetMask(0x00);
						delay(1000);
						needHighlight = 0;
				}
		}
		setvect(9, oldInterrupt);
		return;
}
void interrupt NewInterrupt(...)
{
		unsigned char value = 0;
		oldInterrupt();
		value = inp(0x60);
		if (value == 0x01) { quitFlag = 1; }
		UpdateHighlightFlag(value);
		commandIsExecuted = commandIsExecuted || (needHighlight == 0) || (value == 0xFA);
		printf("\t%x", value);
		outp(0x20, 0x20);
}
void UpdateHighlightFlag(unsigned char value)
{
		if (value != 0x1c) { return; }
		if (needHighlight)
		{
				needHighlight = 0;
		}
		else
		{
				needHighlight = 1;
		}
}
void SetMask(unsigned char mask)
{
		commandIsExecuted = 0;
		while (!commandIsExecuted)
		{
				while ((inp(0x64) & 0x02) != 0x00);
				outp(0x60, 0xED);
				outp(0x60, mask);
				delay(50);
		}
}
