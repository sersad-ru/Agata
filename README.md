# Agata
Agata. The splitted mouse.

** Main Image **

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
*  Six latch-switches `8.5x8.5 mm`
*  12 capacitors to prevent the chatter. `0.1uF`

<p align="center"><img src="img/schematic.png"/>

<p align="center"><img src="img/without-case.jpg" widht="400"/>


## Software
This device emulates a HID keyboard and HID mouse. When you rotate the encoder, the mouse pointer moves along the selected axis. The `X axis` for the `left` encoder and the `Y axis` for the `right` encoder by default.

If you hold the encoder key while rotating, the mouse pointer will move slowly.

Pressing one of the six additional keys will send a `KeyDown` event. Pressing it again will send a `KeyUp` event. So you don't need to hold these buttons down.

In addition to emulating HID devices, Agata also sends and receives messages via a COM port. You can connect to it using any COM terminal program. Port specification: `9600 8N1`. This connection can be used to configure devise settings.

Available configuration commands are:

|Command|Params|Description|
|:---:|:---:|:---|
|`?` or `h`|none|Get the list of available commands|
|`i`|none|Get the version information and current configuration|
|`&`|`F`|Reset the configuration to defaults. Example: `&F`|
|`d`|none|Turn on or off debug messages to the COM-port|

