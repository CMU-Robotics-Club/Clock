/* 
 * main.c: contains main() and signal handlers for doord.
 *
 * written by Aaron Solochek <aarons@aberrant.org> 
 * last modified: 26 Mar 2009 by Brad Neuman
 *
 */
#include <err.h>
#include "defs.h"


/* main */
int main(int argc, char** argv){
  int cont = TRUE;
  int ret = 0;

  /* open serial port and initialize shit */
  led_fd = openport(LEDBAR_DEVICE);

  /*
  if((ret=ledwrite("  ")<0)) //hack since first write produces crap
    err(ret, "failed on first write to ledbar");
  */
  ledclear();
  ledwrite("Initializing...");

  ledclear();

  /* main loop */   
  while(cont){
    if((ret=ledtime()) < 0) {
      err(ret, "failed writing time");
    }
    sleep(10);

    printf("loop\n");
  }
  
  /* close the ports and exit */
  close(led_fd);
  exit(0);
}

