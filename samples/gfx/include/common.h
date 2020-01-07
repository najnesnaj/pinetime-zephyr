
#include <stdlib.h>
#include <stdio.h>
#include <kernel.h>
#include <string.h>
#include <ctype.h>

#define boolean bool

char* itoa(int value, char* buffer, int base);
char* utoa(unsigned int val, char * s, int radix);
char* ultoa(unsigned long val, char * s, int radix);
char* ltoa(long val, char * s, int radix);

char *dtostrf(double val, signed char width, unsigned char prec, char *sout);
