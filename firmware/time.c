/**
 * Copyright (c) 2007 Colony Project
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 **/

#include <avr/interrupt.h>
#include <util/delay.h>
#include <time.h>

/* Calculate how many cycles to delay for to get 1 ms. Based on F_CPU which should be defined by the makefile */
#ifdef F_CPU
#define WAIT_CYCLES ((F_CPU / 1000) / 10)
#else
#define WAIT_CYCLES (8000 / 10)
#endif

/**
 * Delays for the specified number of milliseconds.
 * It depends on F_CPU to be defined in order to calculate how many cycles
 * it should delay. If it is not defined, a default clock of 8MHz is assumed.
 * 
 * We use _delay_loop_2 which will run assembly instructions that should be
 * 4 cycles long. Optimizations must be enabled for this to be true.
 * That function is called to ensure around 1ms per execution. To generate
 * multiple ms we run a for loop of how many milliseconds are desired.
 *
 * The error should be just the skew on the oscillator as the formula to 
 * calculate delay cycles should always be a whole number. The is some skew
 * in practice though it is unavoidable. Delaying for less than 1s should make
 * the error negligable.
 *
 * @param ms the number of milliseconds to delay for
 **/
void delay_ms(int ms) {
    for (; ms > 0; ms--) {
        _delay_loop_2(WAIT_CYCLES);
    }
}

