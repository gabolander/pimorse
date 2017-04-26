#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

BeepPin = 11    # pin11
# MotorPin1   = 11    # pin11
# MotorPin2   = 12    # pin12
# MotorEnable = 13    # pin13

# I define some vars that I treat as constants ...

DOT_MS_LEN=0.08     # "BASE" DOT LENGTH: This is the main 'dot' length which all
                    # the other delay/durations are based on.
                    # Decrease it, to make it playing faster.
                    # Increase it, to make it slower.
                    # Don't touch other DASH_* DELAY_* values instead, because
                    # they are multipliers of DOT_MS_LEN.
DASH_MS_LEN=(DOT_MS_LEN*3)
DELAY_MS_DOTS=(DOT_MS_LEN*1)
DELAY_MS_LETTERS=(DOT_MS_LEN*3)
DELAY_MS_WORDS=(DOT_MS_LEN*5)

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
    Index=0
    while Index<len(seq):
        sign=seq[Index]
        GPIO.output(BeepPin, GPIO.LOW)
        if sign=='-':
            time.sleep(DASH_MS_LEN)
        else:
            time.sleep(DOT_MS_LEN)

        GPIO.output(BeepPin, GPIO.HIGH)
        time.sleep(DELAY_MS_DOTS)

    # Delay at end of letter
    time.sleep(DELAY_MS_LETTERS-DELAY_MS_DOTS)
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
                print "letter: ", letter, " morse seq: ", morseseq # GABODebug
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

# ex: ts=4 sts=4 sw=4 ai nohls mouse-=a ft=python et:
# ex: tabstop=4 softtabstop=4 shiftwidth=4 autoindent mouse-=a filetype=python expandtab:
