#include <avr/interrupt.h>

#define intervalFunction() ISR(TIMER1_COMPA_vect)

void initInterval(uint32_t microSeconds);

