# 2 Pin Bi Color Led Matrix
C (avr-gcc) library to control 2 pin bi colored ledmatrix

bi colored leds with 2 pins are pretty cool.  Much fewer connections, and you still get 2 colors.  They work by having one color in one direction and different color when the current is flipped.  I did not find any libraries out there that would drive a matrix of these bad boys, so here it is.

Personally, I made this to include into my planck/tmk firmware keyboard to have individually controllable backlight.

# Dependencies
avr-gcc stack

# Configuration
config.h shows how to map your physical connections
keyboard config shows my keyboard setup, some hooks into the keyboard firmware is required
adjust Makefile to your hardware


# Installing the Example
make

make flash (this uses avrdude, ensure your the device and MCU is right for you)

