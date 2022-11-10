#include <avr/io.h>
#include <util/atomic.h>
#include <string.h>
#include "ledmatrix.h"
#include "cpp-utility.h"
#include "config.h"

//period of 7 can be described with 3 bits
#define LED_MAT_PERIOD 7
#define LED_MAT_PERIOD_BITS 0b00000111

#define LED_MAT_NUMCOLORS 2
#define LED_MAT_PORT(x) PORT##x 
#define LED_MAT_CTRL(x) DDR##x 

//memory map of led states
// instead of holding physical state (row x cols), we are holding 
// pin state per cycle to minimize transformations on reading 
#define LED_MAT_SIZE (LED_MAT_PERIOD * LED_MAT_ROWSIZE * LED_MAT_NUMCOLORS)
#define LED_MAT_IDX(p,r,c) \
    ((p) * LED_MAT_ROWSIZE * LED_MAT_NUMCOLORS) +\
    ((r) * LED_MAT_NUMCOLORS) + (c)

static uint8_t state[LED_MAT_SIZE][SIZE(LED_MAT_ALLP)] = {{0}};
static uint8_t cycle = 0;
static uint8_t ledOn = 0b00000001;
void ledMatrixInit(){

    //set row states, these show remain constant after being set here
    for (int j=0;j<(LED_MAT_PERIOD);j++){
#define nested(pinmask,i,row) \
    state[LED_MAT_IDX(j,row,0)][i] = pinmask; \
    state[LED_MAT_IDX(j,row,1)][i] = pinmask; 

#define lambda(index) \
    MAP3(nested,EMPTY,LED_MAT_ROW##index,IDX(LED_MAT_ALLP),REPEAT(index,LED_MAT_ALLP))
    MAP(lambda,EMPTY,IDXNUM(LED_MAT_ROWSIZE))
#undef lambda 
#undef nested 
    }
}

//buffer for holding physical color of each key
static uint8_t  physicalState[LED_MAT_ROWSIZE * LED_MAT_COLSIZE] = {0xFF};
static volatile uint32_t physicalStateRowChanged = 0;

//value is 0-7 indicating intensity, first half is for blue then red
// 0 - off
// 1 - 1 out of 7 cycles
// 2 - 2 out of 7 cycles (spread evenly) and so on
// 7 - all on
void ledMatrixSetKeyState(uint8_t row, uint8_t col, uint8_t value){
    physicalState[row * LED_MAT_COLSIZE + col] = value;
    physicalStateRowChanged |= (1UL<<row);
}
void ledMatrixSetRowState(uint8_t row,  uint8_t value[]){
    memcpy(physicalState + (row * LED_MAT_COLSIZE), value , LED_MAT_COLSIZE * sizeof(uint8_t));
    physicalStateRowChanged |= (1UL<<row);
}
void ledMatrixSetState(uint8_t value[]){
    memcpy(physicalState, value , LED_MAT_ROWSIZE * LED_MAT_COLSIZE * sizeof(uint8_t));
    physicalStateRowChanged |= 0xFFFFFF;
}
void ledMatrixToggle(){
    ledOn ^= 1; //toggle left bit
    ledOn |= 1<<1; //set next bit to true for changed
}


void applyBuffer(uint8_t row){
    physicalStateRowChanged &= ~(1UL<<row);

    //ranges from 1 to PERIOD + 1
    for (int j=0;j<LED_MAT_PERIOD;j++){
#define nested(pinmask,i,col) \
    if (blue##col) state[LED_MAT_IDX(j,row,0)][i] &= ~(pinmask);\
        else       state[LED_MAT_IDX(j,row,0)][i] |=   pinmask; \
    if (red##col)  state[LED_MAT_IDX(j,row,1)][i] &= ~(pinmask);\
        else       state[LED_MAT_IDX(j,row,1)][i] |=   pinmask; 

#define lambda(col) \
    uint8_t value##col= ~(physicalState[row * LED_MAT_COLSIZE + col]);\
    uint8_t blue##col = (j+1) % (((LED_MAT_PERIOD_BITS) & value##col) + 1);\
    uint8_t red##col  = (j+1) % (((((LED_MAT_PERIOD_BITS)<<4) & value##col)>>4) + 1);\
    MAP3(nested,EMPTY,LED_MAT_COL##col,IDX(LED_MAT_ALLP),REPEAT(col,LED_MAT_ALLP)) 

    MAP(lambda,EMPTY,IDXNUM(LED_MAT_COLSIZE))
#undef lambda 
#undef nested 
    }
}


void draw(uint8_t on){
    //flag for current color in cycle
    uint8_t color = (cycle % LED_MAT_NUMCOLORS) == 1;

    //apply buffer on current row if first color in cycle
    if (color == 0){
        uint8_t currentRow = (cycle/LED_MAT_NUMCOLORS) % LED_MAT_ROWSIZE;
        if (physicalStateRowChanged & (1UL<<currentRow)){
            applyBuffer(currentRow);
        }
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    //declare holders for all ports
    //apply mask on holders
    //also need control port to set all low values to input/disconnected state
    // (and active pins to output)
#define lambda(mask,p,i) \
    uint8_t port_##p = LED_MAT_PORT(p); \
    uint8_t ctrl_##p = (~(mask) & LED_MAT_CTRL(p)) | ((mask) & state[cycle][i]);
    MAP3(lambda,EMPTY,LED_MAT_ALLMASK,LED_MAT_ALLP,IDX(LED_MAT_ALLP))
#undef lambda


    if (on) {
        //flag for setting row pins off if no columns are on
        uint8_t someColumnOn = 0;
        //set columns
#define lambda(mask,p,i) \
        someColumnOn |= (mask) & state[cycle][i]; \
        port_##p = (~(mask) & port_##p) | ((mask) & (color ? \
                ~(state[cycle][i]):(state[cycle][i])));
        MAP3(lambda,EMPTY,LED_MAT_COLMASK,LED_MAT_ALLP,IDX(LED_MAT_ALLP))
#undef lambda
       
        //set rows
#define lambda(mask,p,i) \
        if (!someColumnOn) ctrl_##p &= ~(mask); \
        port_##p = (~(mask) & port_##p) | ((mask) & (color ? \
                (state[cycle][i]):~(state[cycle][i])));
        MAP3(lambda,EMPTY,LED_MAT_ROWMASK,LED_MAT_ALLP,IDX(LED_MAT_ALLP))
#undef lambda
    }else{
#define lambda(mask,p,i) \
        port_##p &= ~(mask);\
        ctrl_##p &= ~(mask); 
        MAP3(lambda,EMPTY,LED_MAT_ALLMASK,LED_MAT_ALLP,IDX(LED_MAT_ALLP))
#undef lambda
    }
    //assign holders into ports
#define lambda(p) \
    LED_MAT_PORT(p) = port_##p;
    MAP(lambda,EMPTY,LED_MAT_ALLP)
#undef lambda

#define lambda(p) \
    LED_MAT_CTRL(p) = ctrl_##p;
    MAP(lambda,EMPTY,LED_MAT_ALLP)
#undef lambda
    }

    cycle++;
    if (cycle >= LED_MAT_SIZE){
        cycle = 0;
    }

}

void ledMatrixDraw(){
    if (ledOn & 1){
        draw(1);
    }else if (ledOn & (1<<1)){
        draw(0);
        ledOn &= ~(1<<1);
    }
}
