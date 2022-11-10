#include "interval.h"

//CSn2 CSn1 CSn0 Description
//0 0 0 No clock source. (Timer/Counter stopped)
//0 0 1 clkI/O/1 (No prescaling
//0 1 0 clkI/O/8 (From prescaler)
//0 1 1 clkI/O/64 (From prescaler)
//1 0 0 clkI/O/256 (From prescaler)
//1 0 1 clkI/O/1024 (From prescaler)
//1 1 0 External clock source on Tn pin. Clock on falling edge
//1 1 1 External clock source on Tn pin. Clock on rising edge
//
//F CPU Scaling Step Size (micros)  Timer Size  Max Time (micros)
//16    1,1       0.0625  65536   4,096.00
//16    2,8       0.5     65536   32,768.00
//16    3,64      4       65536   262,144.00
//16    4,256     16      65536   1,048,576.00
//16    5,1024    64      65536   4,194,304.00
//
#define setPrescaler(x) TCCR1B = (1 << WGM12)|(x)
void initInterval(uint32_t microSeconds){
    cli();

    if (microSeconds < 32000){
        setPrescaler(2);
        OCR1A = (microSeconds << 1) - 1;
    } else if (microSeconds < 250000){
        setPrescaler(3);
        OCR1A = (microSeconds >> 2) - 1;
    } else if (microSeconds < 1000000){
        setPrescaler(4);
        OCR1A = (microSeconds >> 4) - 1;
    } else {
        setPrescaler(5);
        OCR1A = (microSeconds >> 6) - 1;
    }

    TIMSK1 = (1 << OCIE1A);
    
    TCNT1 = 0;
    sei();
}
