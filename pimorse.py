#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

BeepPin = 11    # pin11
# MotorPin1   = 11    # pin11
# MotorPin2   = 12    # pin12
# MotorEnable = 13    # pin13


pins = [11, 12, 13, 15, 16, 18, 22, 7]

def setup():
        GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BOARD)        # Numbers GPIOs by physical location
	GPIO.setup(BeepPin, GPIO.OUT)   # Set BeepPin's mode is output
	GPIO.output(BeepPin, GPIO.HIGH) # Set BeepPin high(+3.3V) to off beep

def loop():
	while True:
		GPIO.output(BeepPin, GPIO.LOW)
		time.sleep(0.1)
		GPIO.output(BeepPin, GPIO.HIGH)
		time.sleep(0.1)
# 		for pin in pins:
# 			GPIO.output(pin, GPIO.LOW)	
# 			time.sleep(0.5)
# 			GPIO.output(pin, GPIO.HIGH)

def destroy():
	GPIO.output(BeepPin, GPIO.HIGH)    # beep off
	GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
        print 'Press Ctrl+C to end the program...'
	setup()
	try:
		loop()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
		destroy()

