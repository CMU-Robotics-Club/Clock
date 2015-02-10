#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>

/*
 * Writes the String s to the display.
 * s can be any length, as display scrolls
 * across one character at a time for Strings
 * large than display width(19 characters).
 */
void display(String s);

/*
 * Flushes display buffer to display.
 * Must be called frequently by a timer interrupt
 * as display can only show 1 row at a time.
 * Illusion of all rows being set at once
 * is caused by persistence of vision.
 */
void displayFlush();

#endif
