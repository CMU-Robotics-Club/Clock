/* 
 * init.c: function to open and setup the serial port for PIC 
 *         and card reader communication.
 *
 * written by Aaron Solochek <aarons@aberrant.org>
 * last modified: 8 May 2003
 *
 */

#include "defs.h"


/* open and configure the port */
int openport(char *portname){
  struct termios oldtio, newtio;
  char *error = 0;
  int fd;

  /* open read/write, non-controlling, non-blocking */   
  fd = open(portname, O_RDWR | O_NOCTTY | O_NONBLOCK);
  if (fd == -1){
    //    sprintf(error, "openport: Unable to open %s", portname);
    fprintf(stderr, "Unable to open %s: ", portname);
    perror(error);
    exit(-1);
  }

  tcgetattr(fd, &oldtio);          //save current port settings
  bzero(&newtio, sizeof(newtio));  //clear struct for new settings
  
  if(!strcmp(portname, LEDBAR_DEVICE)){
    newtio.c_cflag = LEDBAR_BAUDRATE | CS8 | CLOCAL | CREAD | HUPCL;
    newtio.c_iflag = IGNBRK | IGNPAR;
  }else{
    if(verbose > 1) 
      fprintf(stderr, "Unknown device opened.  Using default port settings.\n");
    newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR | ICRNL;
  }
  
  newtio.c_oflag = 0;
  newtio.c_lflag = 0;
   
  newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
  newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
  newtio.c_cc[VERASE]   = 0;     /* del */
  newtio.c_cc[VKILL]    = 0;     /* @ */
  newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
  newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
  newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
  newtio.c_cc[VSWTC]    = 0;     /* '\0' */
  newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
  newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
  newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
  newtio.c_cc[VEOL]     = 0;     /* '\0' */
  newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
  newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
  newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
  newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
  newtio.c_cc[VEOL2]    = 0;     /* '\0' */
   
  /* flush the port, and apply the new settings now */
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &newtio);
   
  return (fd);
}


