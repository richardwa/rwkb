#include <avr/io.h>

void ledMatrixInit(void);
void ledMatrixDraw(void);
void ledMatrixSetKeyState(uint8_t row, uint8_t col, uint8_t value);
void ledMatrixSetRowState(uint8_t row, uint8_t value[]);
void ledMatrixSetState(uint8_t value[]);
void ledMatrixToggle(void);

