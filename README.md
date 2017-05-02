# PIMORSE

## A morse code player with Raspberry PI and a Breadboard with a buzzer-circuit scheme

This program allow you to play a custom message on a [Breadboard](https://en.wikipedia.org/wiki/Breadboard) 
connected to a [RasperryPI](https://en.wikipedia.org/wiki/Raspberry_Pi) 1/2/3 on a circuit already built on the Breadboard following this scheme: 
	[Super Kit V2 for RaspberyPi by Sunfounder](https://www.sunfounder.com/learn/Super_Kit_V2_for_RaspberryPi/lesson-6-buzzer-super-kit-for-raspberrypi.html)
  
Circuit to mount on the breadboard is right this one:

![Buzzer](https://www.sunfounder.com/media/wysiwyg/swatches/Super_kit_v2_for_raspberrypi/6_Buzzer/5.png)

## C Source - pimorse.c

### Build program to run with Raspberry PI and the buzzer scheme on the breadboard
To build this program under Raspbian in a Raspberry Pi environment, you fist need to have wiringPi library installed.
To download and install wiringPi library, please follow this link: [WiringPi Library - download and install](http://wiringpi.com/download-and-install/)

To compile and run this program, do:

 `$ gcc pimorse.c -o pimorse -l wiringPi [ -DDEBUG ]`

or just run:

 `make [ debug ]`

(DEBUG is optional, just to have more verbosity during execution)

and run with:

 `$ ./pimorse`


### Build program to run in a PC for simulation
You may also want to run this program in a linux PC, out of a 
Raspberry box just to test it and see how it works, even if you don't
have the related hardware and accessories. 
In this case you can compile program by entering:

 `$ gcc pimorse.c -o pimorse -DNOPI -DDEBUG`

or just run:

 `make simdebug`

( DEBUG is optional here as well, but I suggest you to use it together with -DNOPI parameter, otherwise you can't realize the progress of program, since you don't have any audio output. At least, in this way you may see console output when program converts message to morse, with the same timings as you had buzzer playback. )

## Python program - pimorse.py

It has just almost the same behaviour of corresponding C program mentioned above.

Run with

	./pimorse.py

_NOTE: You may check the first line `#!/usr/bin/env python` and eventually change env path according to your system configuration._

If you want to test program with no breadboard or circuit attached or just run in your PC, you could just run it with:

`./pimorse.py -s` or `./pimorse.py --simulate`

In this way, no GPIO library will be called as imported modules.

You may also change dot beep duration by issuing _--dot=NN_ parameter, where _NN_ stands for seconds (**NOTE**: enter a fraction of second. Accepted value range is between 0.05 and 0.2 [default is 0.08])

Anyway, you may always run `./pimorse.py -h` to see an help screen for command parameters.



**License**
This source is released under the terms of *GNU General Public License V. 3.0.*
Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license.
Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.

Please read __LICENSE.txt__ released with this code for further details.`
