/**********************************************************************
* Filename    : pimorse.c
* Description : make a buzzer play a custom message in morse code
* Author      : Gabriele "Gabolander" Zappi
* E-mail      : gabodevelop@gmail.com
* website     : (not useful here)
* Date        : 2017/04/10
* License     : This source is released under the terms of GNU General
*               Public License V. 3.0. 
*               Permissions of this strong copyleft license are condi-
*               tioned on making available complete source code of 
*               licensed works and modifications, which include larger 
*               works using a licensed work, under the same license. 
*               Copyright and license notices must be preserved. Con-
*               tributors provide an express grant of patent rights.
*               Please read LICENSE.txt released with this code for 
*               further details.
**********************************************************************/
/**********************************************************************
* This program allow you to play a custom message on a Breadboard
* (https://en.wikipedia.org/wiki/Breadboard) connected to a RasperryPI
* (https://en.wikipedia.org/wiki/Raspberry_Pi) 1/2/3 on a circuit 
* already built on the Breadboard following this scheme: 
*    https://www.sunfounder.com/learn/Super_Kit_V2_for_RaspberryPi/
*     lesson-6-buzzer-super-kit-for-raspberrypi.html
* 
* To build this program under Raspbian in a Raspberry Pi environment,
* you fist need to have wiringPi library installed.
* To download and install wiringPi library, please follow this link:
* http://wiringpi.com/download-and-install/
* 
* To compile and run this program, do:
* 
* $ gcc pimorse.c -o pimorse -l wiringPi [ -DDEBUG ]
* (DEBUG is optional, just to have more verbosity during execution)
* 
* and run with:
* 
* $ ./pimorse
* 
* You may also want to run this program in a linux PC, out of a 
* Raspberry box just to test it and see how it works, even if you don't
* have the related hardware and accessories. 
* In this case you can compile program by entering:
* 
* $ gcc pimorse.c -o pimorse -DNOPI -DDEBUG
* ( DEBUG is optional here as well, but I suggest you to use it toge-
* ther with -DNOPI parameter, otherwise you can't realize the progress
* of program, since you don't have any audio output. At least, in this
* way you may see console output when program converts message to morse
* with the same timings as you had buzzer playback. )
* 
**********************************************************************/

#ifndef NOPI
#include <wiringPi.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include  <signal.h>
#include <unistd.h>

#define BeepPin 0
#define MAXMORSELENGTH 11
#define MAXMESSAGELENGTH 250

// Lettere, numeri e punteggiatura (with no TABs)
// 
// Lettere/Codice  Lettere/Codice  Numeri/Codice   Punteg./Codice
// A   • —         N   — •         0   — — — — —   •   • — • — • —
// B   — • • •     O   — — —       1   • — — — —   ,   — — • • — —
// C   — • — •     P   • — — •     2   • • — — —   :   — — — • • •
// D   — • •       Q   — — • —     3   • • • — —   ?   • • — — • •
// E   •           R   • — •       4   • • • • —   =   — • • • —
// F   • • — •     S   • • •       5   • • • • •   -   — • • • • —
// G   — — •       T   —           6   — • • • •   (   — • — — •
// H   • • • •     U   • • —       7   — — • • •   )   — • — — • —
// I   • •         V   • • • —     8   — — — • •   "   • — • • — •
// J   • — — —     W   • — —       9   — — — — •   '   • — — — — •
// K   — • —       X   — • • —                     /   — • • — •
// L   • — • •     Y   — • — —                     _   • • — — • —
// M   — —         Z   — — • •                     @   • — — • — •
//                                                 !   — • — • — —
//     $alfav=array("A","B","C","D","E","F","G","H","I","J",
//                 "K","L","M","N","O","P","Q","R","S","T",
//                 "U","V","W","X","Y","Z",
//                 "1","2","3","4","5","6","7","8","9","0",
//                 " "," "," ","è","é");
// 
//     $morsev=array(".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
//                 "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
//                 "..-","...-",".-- ","-..-","-.--","--..",
//                 ".----","..---","...--","....-",".....",
//                 "-....","--...","---..","----.","-----",
//                 "   ","  "," ",".-..-",".-..-");



const char default_msg[] = "Hello, world!";

const unsigned char Kalfav[] = { 'A','B','C','D','E','F','G','H','I','J',
            'K','L','M','N','O','P','Q','R','S','T',
            'U','V','W','X','Y','Z', // Alphabet chars
            '1','2','3','4','5','6','7','8','9','0',' ', // Numbers + space
            '.',',',':','?','=','-','(',')','"','\'','/','_','@','!' // Symbols
};

const char Kmorsev[][MAXMORSELENGTH] = {
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
    "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
    "..-","...-",".-- ","-..-","-.--","--..", // Alphabet chars
    ".----","..---","...--","....-",".....",
    "-....","--...","---..","----.","-----"," ", // Numbers + space
    ".-.-.-","--..--","---...","..--..","-...-","-....-","-.--.",
    "-.--.-",".-..-.",".----.","-..-.","..--.-",".--.-.","-.-.--" // Symbols
};
                         
                         
#define DOT_MS_LEN 80    // "BASE" DOT LENGTH: This is the main 'dot' length which all
                          // the other delay/durations are based on.
                          // Decrease it, to make it playing faster.
                          // Increase it, to make it slower.
                          // Don't touch other DASH_* DELAY_* values instead, because
                          // they are multipliers of DOT_MS_LEN.
#define DASH_MS_LEN (DOT_MS_LEN*3)
#define DELAY_MS_DOTS (DOT_MS_LEN*1)
#define DELAY_MS_LETTERS (DOT_MS_LEN*3)
#define DELAY_MS_WORDS (DOT_MS_LEN*5)
                         

#ifdef NOPI

#ifndef LOW
#define LOW 0
#endif
#ifndef HIGH
#define HIGH 1
#endif
#ifndef OUTPUT
#define OUTPUT 0
#endif
#ifndef INPUT
#define INPUT 1
#endif

void digitalWrite(int, int);
void delay(long);

#endif

void codiceMorse(const char *);
void INThandler(int);
void led_on(int);
void led_off(int);

void soundmorse(char);
void tomorse(char *,char);

#ifdef NOPI
void digitalWrite(int pin, int mode) {
}

void delay(long millis) {
    usleep((useconds_t)(millis*1000));
}
#endif

void  INThandler(int sig)
{
            
    int i;
    char  c;

    signal(sig, SIG_IGN);
    printf("You hit Ctrl-C?\n"
            "Switching off buzzer and exiting.\n "); // Gabo
    digitalWrite(BeepPin, HIGH);
    exit(0);
#if 0
    printf("OUCH, did you hit Ctrl-C?\n"
           "Do you really want to quit? [y/n] ");
    c = getchar();
    if (c == 'y' || c == 'Y') {
        digitalWrite(BeepPin, HIGH);
        exit(0);
    } else
        signal(SIGINT, INThandler);
    getchar(); // Get new line character
#endif
}

void soundmorse(char c) {
    int i;
    char dl;
    char retstring[MAXMORSELENGTH];
    
    strcpy(retstring,"");
    tomorse(retstring,c);
    
    if(strcmp(retstring,"")){
#ifdef DEBUG
        printf("Char: %c  Morse: %s\n", c, retstring);
#endif        
        
        if(!strcmp(retstring," ")) { // se è uguale a spazio faccio solo la pausa ...
            delay(DELAY_MS_WORDS); // if it's a space, it must place a pause delay at the end of word
        } else {
            
			for(i=0;i<strlen(retstring);i++){
				dl=retstring[i];
				digitalWrite(BeepPin, LOW);  //beep on
				delay( (dl=='-') ? DASH_MS_LEN : DOT_MS_LEN );
				digitalWrite(BeepPin, HIGH); //beep off
				delay(DELAY_MS_DOTS);        //delay at the and of dot or dash
			}
            delay(DELAY_MS_LETTERS-DELAY_MS_DOTS);  //delay at the end of letter
        }
    }
    
}

void tomorse(char * retstring, char c) {
    int i;
    int lenvect=sizeof(Kalfav);
    if (c >= 'a' && c <= 'z')
            c = c - 'a' + 'A';
    
    for(i=0;i<lenvect;i++) {
        if(c==Kalfav[i]) break;
    }
    
    strcpy(retstring,(i>=lenvect)?"":Kmorsev[i]);
}

void codiceMorse(const char * stringa) {
    int i;
    
    for(i=0;i<strlen(stringa);i++)
        soundmorse(stringa[i]);
    
}

void cleanup_message(char *strtopul) {
    int i;
    char c;
    for(i=strlen(strtopul)-1;i>=0;i--) {
        c=strtopul[i];
        if(c==0x0a||c==0x0d||c==0x09||c==0x20) strtopul[i]='\0'; else break;
    }
}


int main(void)
{
	int i;
        char szMessage[MAXMESSAGELENGTH+3];

    signal(SIGINT, INThandler); // GABO. inits INIThandler function on SIGINT

#ifndef NOPI
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}
#endif

#ifndef NOPI
	pinMode(BeepPin, OUTPUT);   //set GPIO0 output
#endif
        
#ifdef DEBUG
        printf("Sizeof Kalfav = %d \n",sizeof(Kalfav));
#endif

        while(1){
            putchar('\n');
        
            printf("Enter a message to transmit (\"%s\" default message, \"STOP\" to exit) : ", default_msg );
            fgets( szMessage, MAXMESSAGELENGTH, stdin );
            putchar('\n');
            
            cleanup_message(szMessage);
            
#if 0 
            // needed only to see ascii values of the input chars in message ..
            for(i=0;i<strlen(szMessage);i++){
                printf( "pos %d Car: %c asc: %d \n",i, szMessage[i], szMessage[i] );
            }
            putchar('\n');
#endif
            
            if( !strcmp(szMessage, "STOP") ) break;
            if( !strcmp(szMessage, "") ) strcpy( szMessage, default_msg);

            codiceMorse(szMessage);
        
        }

	return 0;
}
