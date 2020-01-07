//
// Common imports and definitions. Mostly to make the code for Arduino compatible with Zephyr.
//
#include <stdlib.h>
#include <stdio.h>
#include <kernel.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <Arduino.h>

// missing standard functions
char* itoa(int value, char* buffer, int base);
char* utoa(unsigned int val, char * s, int radix);
char* ultoa(unsigned long val, char * s, int radix);
char* ltoa(long val, char * s, int radix);

