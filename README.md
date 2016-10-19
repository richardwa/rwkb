# 2 Pin Bi Color Led Matrix
C (avr-gcc) library to control 2 pin bi colored ledmatrix

bi colored leds with 2 pins are pretty cool.  Fewer connections than a traditional 3 lead LED, the savings really add up when your keyboard has 50 LEDs.  They work by having one color in one direction and different color when the current is flipped.  I did not find any libraries out there that would drive a matrix of these bad boys, so here it is.

Personally, I made this to include into my planck/tmk firmware keyboard to have individually controllable backlight. See my
[Keyboard build](https://github.com/richardwa/ledmatrix/wiki).

## Dependencies
avr-gcc stack

## Configuration
config.h shows how to map your wires. keyboard config shows my keyboard setup, some hooks into the keyboard firmware is required.
adjust Makefile to your hardware.

## Code
The perl script generates a C Preprocessor definitions file, that can loop and map.  I know there is cpp magic which achieves a similar thing with a static CPP file, but the perl script.

The library let you define your LED state using on a higher level. Instead of doing logic at the switching level, just set the LED states on a row or coordinate basis, i.e. set(X,Y,COLOR);

## Build (builds the example only, this is meant to go into another project - like tmk keyboard)
make

make flash (this uses avrdude, ensure your the device and MCU is right for you)
