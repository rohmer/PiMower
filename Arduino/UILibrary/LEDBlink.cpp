#include <avr/io.h>

void Delay()
{
	long counter = 0;
	while (counter++ < 50000)
		asm("nop");
}

void MainLoop()
{
	DDRB |= (1 << 0);
	
	for (;;)
	{
		PORTB |= (1 << 0);
		Delay();
		PORTB &= ~(1 << 0);
		Delay();
	}
}

int main()
{
	MainLoop();
}