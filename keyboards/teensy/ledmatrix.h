#include <avr/io.h>

void ledMatrixInit(void);
void ledMatrixDraw(void);
void ledMatrixSetKeyState(uint8_t row, uint8_t col, uint8_t value);
void ledMatrixSetRowState(uint8_t row, uint8_t value[]);
void ledMatrixSetState(uint8_t value[]);
void ledMatrixToggle(void);
void ledMatrixSetOn(uint8_t on);
void ledMatrixSetLayer(uint8_t layer);

//WIRING CONFIG
#define LED_MAT_ROWSIZE 4
#define LED_MAT_COLSIZE 12
#define LED_NUM_LAYERS 5

//declar all ports and pins 
#define LED_MAT_ALLP    F,C,E
#define LED_MAT_ALLMASK 0b11111111, 0b10111011, 0b00000011

//split the above into row and col groups
#define LED_MAT_ROWMASK 0b00000000, 0b10110000, 0b00000001
#define LED_MAT_COLMASK 0b11111111, 0b00001011, 0b00000010

//finall declare the individual pins of the rows and cols
#define LED_MAT_ROW0    0b00000000, 0b00010000, 0b00000000
#define LED_MAT_ROW1    0b00000000, 0b00100000, 0b00000000
#define LED_MAT_ROW2    0b00000000, 0b00000000, 0b00000001
#define LED_MAT_ROW3    0b00000000, 0b10000000, 0b00000000

#define LED_MAT_COL0    0b00000000, 0b00001000, 0b00000000
#define LED_MAT_COL1    0b00000000, 0b00000000, 0b00000010
#define LED_MAT_COL2    0b00000000, 0b00000010, 0b00000000
#define LED_MAT_COL3    0b00000000, 0b00000001, 0b00000000
#define LED_MAT_COL4    0b10000000, 0b00000000, 0b00000000
#define LED_MAT_COL5    0b01000000, 0b00000000, 0b00000000
#define LED_MAT_COL6    0b00100000, 0b00000000, 0b00000000 
#define LED_MAT_COL7    0b00010000, 0b00000000, 0b00000000 
#define LED_MAT_COL8    0b00001000, 0b00000000, 0b00000000
#define LED_MAT_COL9    0b00000100, 0b00000000, 0b00000000
#define LED_MAT_COL10   0b00000010, 0b00000000, 0b00000000
#define LED_MAT_COL11   0b00000001, 0b00000000, 0b00000000

#define _OFF 0x00
#define _IND 0xFF
#define _BLU 0xF0
#define _RED 0x0F

extern uint8_t layerLED[LED_NUM_LAYERS][LED_MAT_ROWSIZE * LED_MAT_COLSIZE];