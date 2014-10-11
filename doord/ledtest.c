/* 
 * ledtest.c: simple program to test the led display
 *
 * written by Aaron Solochek <aarons@aberrant.org> 
 * last modified: 8 May 2003
 *
 */

#include "defs.h"

int led_fd;

int main(){
  int i = 0;
  char buf[5];
  led_fd = openport(LEDBAR_DEVICE);
  
  buf[4] = 0;
  i = 0;

  time_redraw = TRUE;
  ledwrite("a");
  ledwrite("a");
  ledwrite("a");
  ledwrite("a");

  ledclear();
  ledwrite("a");
  ledwrite("c");
  ledwrite("c");
  sleep(10);
  exit(0);
}
