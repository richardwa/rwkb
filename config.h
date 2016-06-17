//WIRING CONFIG

#define LED_MAT_ROWSIZE 3
#define LED_MAT_COLSIZE 3

//declare all pins used
#define LED_MAT_ALLP    F
#define LED_MAT_ALLMASK 0b11110011

//split the above into row and col groups
#define LED_MAT_ROWMASK 0b11100000
#define LED_MAT_COLMASK 0b00010011

//finally declare the individual pins of the rows and cols
#define LED_MAT_ROW0 0b10000000
#define LED_MAT_ROW1 0b01000000
#define LED_MAT_ROW2 0b00100000

#define LED_MAT_COL0 0b00010000
#define LED_MAT_COL1 0b00000010
#define LED_MAT_COL2 0b00000001
