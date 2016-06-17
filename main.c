#include <avr/io.h>
#include <util/delay.h>
#include "interval.h"
#include "ledmatrix.h"

#define led 7

int main(void)
{
    
    ledMatrixInit();
    initInterval(1000);
    DDRC |= (1 << led);

    ledMatrixSetState((uint8_t[]){
        0xFF,0x0F,0xFF,
        0xF0,0xFF,0xF0,
        0xFF,0x0F,0xFF
    });

    uint8_t toggle = 0xFF;

    while (1) {
        PORTC ^= (1 << led);
        ledMatrixSetKeyState(1,1,toggle);
        toggle = ~toggle;
        _delay_ms(1000);
    }
}

intervalFunction()
{
    ledMatrixDraw();
}

