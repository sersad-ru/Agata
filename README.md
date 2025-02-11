# Agata
Agata. The splitted mouse.

## Table of contents
* [Overview](#overview)
* [Hardware](#hardware)
* [Software](#software)
* [History](#history)


## Overview
Back in the 1980's, the famous russian personal computer ["Agat"](http://agatcomp.ru/agat/index.shtml) has very unusual cursor control system: two independent controllers for the X and Y axes. This was convenient for games if you played with a partner, but was completely useless for other software. However, there were almost no programs that used the graphics mode.
<p align="center"><img src="img/agat.jpg"/><br>
<sup><a href="https://ru.pc-history.com/">Image from https://ru.pc-history.com/</a></sup>
</p>

But nowadays independent axis control may be very useful for working with CAD or graphics software. So this simple project brings us back to good old technology.

This device has two encoders for independent axis control and six keys. Each key has a latched state, so you don't have to hold them down while operating the encoders.

You can switch between fine and coarse mode by holding encoders key while rotating.

The devise implements HID protocol and needs no drivers for your OS.



## Hardware
The device is based on:
*  `Arduino Pro Micro ATMega32U4` 
*  Two encoders `EC-11`
*  Six latches `8.5x8.5 mm`
*  12 capacitors to prevent the chatter. `0.1uF`

<p align="center"><img src="img/schematic.png"/>

