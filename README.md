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

For Python program version of pimorse (pymorse), please refer to this [git repository](https://github.com/gabolander/pymorse)


**License**
This source is released under the terms of *GNU General Public License V. 3.0.*
Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license.
Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.

Please read __LICENSE.txt__ released with this code for further details.`
