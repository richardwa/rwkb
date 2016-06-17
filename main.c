#include <avr/io.h>
#include <util/delay.h>
#include "interval.h"
#include "ledmatrix.h"

#define led 7

int count = 0;
int main(void)
{
    
    ledMatrixInit();
    initInterval(100);
    DDRC |= (1 << led);

    while (1) {
        PORTC ^= (1 << led);
        _delay_ms(500);
    }
}

intervalFunction()
{
    ledMatrixDraw();
}

