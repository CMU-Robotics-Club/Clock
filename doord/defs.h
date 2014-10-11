/* 
 * defs.h: headerfile included by all .c's.  defines some globals
 *         and system specific variables, as well as provides all 
 *         prototypes.
 *
 * written by Aaron Solochek <aarons@aberrant.org>
 * last modified: 4 Nov 2008 - Barkin Aygun - Cleaned up
 *
 */

/* all the includes here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/* system specific defines */
#define LEDBAR_BAUDRATE B9600
#define LEDBAR_DEVICE "/dev/ttyUSB0"
#define LEDLENGTH 19

#define MAX_WRITE_ERRS 2

/* general defines */
#define TRUE  1
#define FALSE 0

/* global variables */
extern unsigned int lastminute;
extern int verbose;
extern int debug;
extern int led_fd;
extern int time_redraw;
extern int time_refresh;
extern time_t current_time;
extern int led_lock;
extern int deadbabies;

/* some prototypes */
int printusage(void);
int printbuf(void);
int openport(char *portname);
int sendcommand(int fd, char command);
int readcommand(int fd, struct timeval* tv);
int expected_return(char command);
inline int setstatus(char stat);
int updatestatus(int pic_fd);
int printstatus(void);
int buttonaction(int pic_fd);
int sendzephyr(char command);
int writelog(char command);
int updatefinger(void);
inline int picpong(void);
int bufadd(int command);
int bufpop(void);
int ledwrite(char *str);
int ledclear(void);
int ledsetpos(int pos);
int ledtime(void);
char *reducedate(char *datestr);
unsigned int timediff(struct timeb t1, struct timeb t2);
