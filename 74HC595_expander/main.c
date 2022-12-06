#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include <stdint.h>

#define SH_CP PB2
#define ST_CP PB1
#define DS PB5

int main()
{
	DDRB |= (1<<DS) | (1<<ST_CP) | (1<<SH_CP);

	PORTB |= (1<<DS);

	for( ; ; )
	{


	}

	return 0;
}
