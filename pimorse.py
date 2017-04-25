#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

BeepPin = 11    # pin11
# MotorPin1   = 11    # pin11
# MotorPin2   = 12    # pin12
# MotorEnable = 13    # pin13


pins = [11, 12, 13, 15, 16, 18, 22, 7]
default_msg = "Hello, world!"

Kalfav = [ 'A','B','C','D','E','F','G','H','I','J',
            'K','L','M','N','O','P','Q','R','S','T',
            'U','V','W','X','Y','Z', ## Alphabet chars
            '1','2','3','4','5','6','7','8','9','0',' ', ## Numbers + space
            '.',',',':','?','=','-','(',')','"','\'','/','_','@','!' ## Symbols
        ]

Kmorsev = [
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
    "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
    "..-","...-",".-- ","-..-","-.--","--..", # Alphabet chars
    ".----","..---","...--","....-",".....",
    "-....","--...","---..","----.","-----"," ", # Numbers + space
    ".-.-.-","--..--","---...","..--..","-...-","-....-","-.--.",
    "-.--.-",".-..-.",".----.","-..-.","..--.-",".--.-.","-.-.--" # Symbols
    ]

def soundmorse(seq):
    return 1

def morse_decode(letter):
    Index=0
    maxindex=len(Kalfav)
    for kalfa in Kalfav:
        if kalfa == letter:
            break
        else:
            Index=Index+1
    if Index>=maxindex:
        return ""
    else:
        return Kmorsev[Index]



def setup():
        GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BOARD)        # Numbers GPIOs by physical location
	GPIO.setup(BeepPin, GPIO.OUT)   # Set BeepPin's mode is output
	GPIO.output(BeepPin, GPIO.HIGH) # Set BeepPin high(+3.3V) to off beep

def loop():
	while True:
#		GPIO.output(BeepPin, GPIO.LOW)
#		time.sleep(0.1)
#		GPIO.output(BeepPin, GPIO.HIGH)
#		time.sleep(0.1)
# 		for pin in pins:
# 			GPIO.output(pin, GPIO.LOW)	
# 			time.sleep(0.5)
# 			GPIO.output(pin, GPIO.HIGH)
            message = raw_input("Enter a message to transmit (\""+default_msg+"\" default message, \"STOP\" to exit) : " )
            if message == "STOP":
                break

            if message == "":
                message = default_msg

            # print "message: ", message
            Index=0
            while Index<len(message):
                letter=message.upper()[Index]
                morseseq=morse_decode(letter)
                print "letter: ", letter, " morse seq: ", morseseq
                soundmorse(morseseq)
                Index=Index+1
            print '\n'

def destroy():
	GPIO.output(BeepPin, GPIO.HIGH)    # beep off
	GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
        print 'Press Ctrl+C to end the program...'
	setup()
	try:
		loop()
                destroy()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
		destroy()

