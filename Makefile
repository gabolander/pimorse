#
# Semplice makefile per compilare i programmi necessari ..
#

# System environment
CC = gcc

CODEGEN =
OPTIMIZATION = -O0
# OPTIONS = -D_MG_BIG_ENDIAN_ -D_MG_NCURSES_
OPTIONS = 
DEBUG = -g
DEBUG_FLAG = -DDEBUG
SIMULATE_FLAG = -DNOPI
SIMDEBUG_FLAG = -DDEBUG -DNOPI
PRJ=pimorse.c
PRGS=pimorse

# CFLAGS = $(CODEGEN) $(OPTIMIZATION) $(OPTIONS) $(DEBUG)
CFLAGS = $(CODEGEN) $(OPTIMIZATION) $(OPTIONS)

#LIB = -lncurses -lwiringPi
LIB = -lwiringPi
# LIB = 

# COMPLINK = $(CC) $(CFLAGS) $(INCL) $(DEBUG) -Wall $(LIB)
# COMPILE = $(CC) $(CFLAGS) $(INCL) $(DEBUG) $(DEBUG_FLAG) $(SIMULATE_FLAG) $(SIMDEBUG_FLAG) -Wall -c
COMPLINK = $(CC) $(CFLAGS) $(INCL) -Wall $(LIB)
COMPILE = $(CC) $(CFLAGS) $(INCL) -Wall -c

#SOURCES = pimorse.c myutils.c
SOURCES = pimorse.c
# OBJ = presta.o senal.o strfunz.o
OBJ = ${SOURCES:.c=.o}

# all: presta senal
all: pimorse

## For debug,simulate,simdebug: Compile and link in one step.
debug: 
	$(CC) $(CFLAGS) $(INCL) $(DEBUG) $(DEBUG_FLAG) $(LIB) -Wall -o pimorse pimorse.c

simulate: 
	$(CC) $(CFLAGS) $(INCL) $(DEBUG) $(SIMULATE_FLAG) -Wall -o pimorse pimorse.c

simdebug: 
	$(CC) $(CFLAGS) $(INCL) $(DEBUG) $(SIMDEBUG_FLAG) -Wall -o pimorse pimorse.c

# presta: strfunz.o presta.o
# 	$(COMPLINK) -o $@ presta.o strfunz.o
# senal: strfunz.o senal.o
# 	$(COMPLINK) -o $@ senal.o strfunz.o

# pimorse: pimorse.o myutils.o strfunz.o
# 	$(COMPLINK) -o $@ pimorse.o
# 
#pimorse: pimorse.o myutils.o

pimorse: pimorse.o
	$(COMPLINK) -o $@ $^

#pimorse.o: pimorse.c pimorse.h myproto.h
pimorse.o: pimorse.c
	$(COMPILE) pimorse.c

#strfunz.o: strfunz.c strfunz.h
#	$(COMPILE) strfunz.c
#
#myutils.o: myutils.c
#	$(COMPILE) myutils.c

.PHONY: clean
clean:
	rm -f $(PRGS) $(OBJ) *~
