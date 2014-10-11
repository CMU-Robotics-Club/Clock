
#include "defs.h"

/* global variables */
struct timeb lclose, lopen;
int serbuf[8];
int serbuf_size = 0;
int readbuf = FALSE;
int verbose = 2;
int debug = FALSE;
int led_fd;
// int num_members;
int num_groups;
int lastauth;
int deadbabies = FALSE;
int led_lock = FALSE;
int time_redraw = TRUE;
int time_refresh = TRUE;
time_t current_time;

