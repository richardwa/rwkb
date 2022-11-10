# Keyboard with 2 color Programmable LEDs
![keyboard](https://raw.githubusercontent.com/richardwa/ledmatrix/main/pics/keyboard.jpg)

Years ago I had built my own keyboard made from 2 numpads, my goal being to have a mechanical keyboard with a grid layout. It worked fine and was my main home keyboard (though i do most my typing at work) for a long time. Then I stumbled upon Jack Humbert's Ortholinear keyboards - so i wasn't the only one after all :D I ordered a top plate and a milled bottom from Jack, and got started as soon as it arrived (which took a while).

My keyboard was hand wired using an chinese arduino (much cheaper than the teensy i had used on my numpad keyboard), and was using it fine. I got to thinking about the back light, I wanted individually controllable led's and preferably in more than 1 color. It would be cool to have the led change according to which layer I'm on. Turns out the usb micro port is not robust enough for a keyboard wire, it eventually broke off and motivated me to start on my second build with LEDs.

For my second build, I had salvaged teensy++ from the numpad keyboard - needed more pins for the LED matrix and key matrix together, and the usb mini port is a big plus, as I know that is strong enough to last a while. The only issue was the the teensy++ was slight too long, the milled bottom is very tight and only had a small cut out for the controller. I was able to squeeze it in by cutting the bottom knub off 2 keys.

I used 2 pin bi color leds and laid it out in a matrix. The idea is to power the matrix 1 row at a time, flip the current to show the second color, then move on the next row (of course this is done really fast so it looks like it is all lit and I am able to use get different shades of the 2 colors). The build and coding took some time, maybe 2 weeks each - working on it a few hours each day, and I finally finished it. Posted my led driver on github if anyone is interested.

# Wiring
![wiring](https://raw.githubusercontent.com/richardwa/ledmatrix/main/pics/wiring.jpg)

# LED test rig
![ledmatrix](https://raw.githubusercontent.com/richardwa/ledmatrix/main/pics/ledmatrix.jpg)
