# Mission
To build a matrix layout keyboard with quality mechanical keys

# Materials
* 2 GoldTouch numpads (this one has 22 cherry mx brown keys)
* 1 teensy++ (regular teensy would have enough pins but configs would differ)

![keyboard](/pics/image9.jpg?raw=true)
![keyboard](/pics/image5.jpg?raw=true)

## Optional Materials
* 1 wasd 39 blank key set 
* 1 wasd row 1 key (i ended up 1 short, oops)
* 4 wasd 2x1 “zero” key 
* nail polish (if you want to paint the metal plate like i did)

## Tools:
* soldering set (iron, solder, flux, wires, solder sucker, etc)
* multimeter
* hacksaw
* drill
* razor cutting knife
* screw driver

<span style="color:red">This build assumes the user is familiar with the tools above, and uses them in a safe responsible manner.  Consult your manual and/or professional.  Always wear safety goggles when soldering, drilling, cutting, etc.  Exercise caution when working with sharp, hot, and electrical equipment.  The author is not responsible for any injuries or losses.</span>

# Procedure

First map out all the “groups” of connections on the circuit board - basically go through each switch (two pins each) and find which pin is already connect to which.  This would let us reuse the existing circuit board and keep the soldering to a minimum.  This process is quite tedious but should be simple enough.  Here are my results

![keyboard](/pics/image8.jpg?raw=true)

The pin groups are:

![keyboard](/pics/image14.png?raw=true)

The matrix that represents the keyboard based on the groupings

![keyboard](/pics/image3.png?raw=true)

double the virtual matrix (2 keypads) and fill in the corresponding key and we have finally the config.kspec (refer to humble hacker keyboard on building the firmware) of the matrix (filled in with the key position from the front perspective, i.e. upper left key is 1A) - this mapping part does require some thinking, I wrote some meta programs to help me out with the transformations.  All columns wire directly to the teensy but the rows only need to be connected to each other, and one set wired to the teensy.
```
/*    0  1  2  3  4  5  6  7  8  9 */
  Row:4L 3H 2H 4I 4K 4F 3B 2B 4C 4E 
  Row:-- 3L -- 3K -- -- 3F -- 3E -- 
  Row:-- -- 2L 2K -- -- -- 2F 2E -- 
  Row:1K -- -- 1L 4G 1E -- -- 1F 4A 
  Row:-- 3J 2J 1J -- -- 3D 2D 1D -- 
  Row:-- 3I 2I 1I -- -- 3C 2C 1C -- 
  Row:-- 3G 1G 1H 2G -- 3A 1A 1B 2A

/*  the rows and column pins will depend on your own wiring to the teensy, refer to the teensy website and the software’s reference for pin naming conventions */
  ColPins:PF6 PF3 PF1 PB1 PF5 PC2 PE1 PC0 PE0 PC1 
  RowPins:PF7 PF4 PF2 PB0 PC3 PC7 PF0

/* the matrix represented by this keypad has a lot of holes so “no” is alright here even though it does not have diodes */
  BlockGhostKeys:no
```
Then we need to cut the pcb board as shown above - this is for the side that will hold the teensy, the other side is much easier, just cut straight across.  I first drilled two holes at the corners of the red outline above, then use a hacksaw to cut from the edge to the holes.  Afterwards score between the holes and snap the pcb off.  Desolder and remove the usb connector indicated above, this section of pcb will secure the teensy, so don’t break it.  I kept the bottom usb and led intact in case i want to incorporate more functionality in the future.

Secure the teensy to the pcb board.  I thought about this for a while before arriving at a solution, as there’s no mounting spots on the teensy.  I took a small piece of metal (from a mini usb plug, not the plug itself but the housing that’s covered by the rubber - but any right size metal piece will do).  Secure the metal peice by soldering to teensy’s ground connections - this went over the teensy’s usb housing and connected to same ground patches of copper.  then bend the back of the metal piece upwards so that it can fit into the removed usb’s ground connections.  When making this connection make sure the teensy is forward enough so that it can receive a plug coming from the outside of the plastic case - and not too forward or it will keep the case from closing.

![keyboard](/pics/image6.jpg?raw=true)

![keyboard](/pics/image12.jpg?raw=true)

The case.  The import part to keep in mind is that each connection joint is at a different location, this adds strength as well as confusion.
i.e the top of the case is joins at different locations than the bottom and is different from the internal metal frame join.  All i can say is work carefully, i would sand it a bit then check the fit until it comes down to a perfect fit.  Also need to raise some of the legs so that the case rests flat on the table, do this first as it will make checking the fit easier.  i just used a ¼ inch wooden sheet cut into a circle.  Use a hack saw and cut along the red lines below.  Then use sand paper on a flat surface to fine tune all the peices.

![keyboard](/pics/image10.jpg?raw=true)

![keyboard](/pics/image1.jpg?raw=true)

with the top covers i sanded at a slight angle so that the left side covers over the right side, i actually took a bit too much angle here 45 degrees is too much. careful not to remove any of the parts that supports the frame or takes the screws.

![keyboard](/pics/image4.jpg?raw=true)

![keyboard](/pics/image2.jpg?raw=true)

Connect the two keypad together by crazy gluing the metal frame.  I also added a rigid piece of pcb to make the join stronger.   it is now secured on  two planes to form a box structure instead of just a sheet.  can also make your wire connections at this point.  Choose any pin on the teensy, many pins are dual purpose, but they are all at least digital IO - pick you pins wisely in case you want analog input at some point or pwm.
“virual columns” of the left board go directly to the teensy, the rows connect to the corresponding row of the right board.
both columns and rows of the right board goto the teensy.

![keyboard](/pics/image11.jpg?raw=true)

![keyboard](/pics/image15.jpg?raw=true)

![keyboard](/pics/image7.png?raw=true)

![keyboard](/pics/image13.jpg?raw=true)

# Other thoughts

I could have approached this, with a split keyboard design.  Would have saved on a lot of cutting and glueing.  Split is nice too but i thought combining it looked better - and I still have my third numpad that i can implement as a split design to be used in conjunction with this one.  Have fun be creative and stay safe.