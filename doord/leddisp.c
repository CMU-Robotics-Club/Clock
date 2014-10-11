/* 
 * leddisp.c: all functions for driving the LED display 
 *
 * written by Aaron Solochek <aarons@aberrant.org>
 * last modified: 11 Sep 2003
 *
 */

#include "defs.h"
#include <stdio.h>
unsigned int lasthour = 0;
unsigned int lastminute = 0;
/* write to the LED bar */
int ledwrite(char* str){
    int i, len;
    int errcount = 0;

    len = strlen(str);
    if(len > 19)
        len = 19; 
  
    for(i=0; i < len; i++){
        if((write(led_fd, &str[i], 1)) < 0){
            perror("write() failed for ledbar");
            printf("led write fail\n");
            if(errcount++ > MAX_WRITE_ERRS)
	            return -1;
            
            usleep(1000);
        }
            usleep(100000);
    }
  
    return 0;
}



/* clear the led */
int ledclear(){
    int ret;
    char buf[2];

    buf[0] = 0x0A;
    buf[1] = 0;

    if((ret = write(led_fd, buf, 1)) < 0)
        perror("write() failed for ledbar");

    ledsetpos(1);
    return 0; 
}

/* set the cursor to the specified position */
int ledsetpos(int pos){
  char buf[3];

  buf[0] = 0x1b;
  buf[1] = pos;
  buf[2] = 0;
  ledwrite(buf);

  return 0;
}

/* print the time */
int ledtime(void){
    int offset;
    char *timestring;
    char logostr[3];
    char timestr[20];
    char dow[4];
    char month[4];
    char ampm[3];
    unsigned int year;
    unsigned int date;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;

    int ret = 0;

    current_time = time(NULL);
    logostr[0] = 0x15;
    logostr[1] = 0x16;
    logostr[2] = 0;
    timestr[19] = 0;
    timestring = ctime(&current_time);
    sscanf(timestring, "%s %s %u %u:%u:%u %u", dow, month, &date, 
	        &hour, &minute, &second, &year);

    // This is where it checks to see if time changed
    if (minute == lastminute) {
        return 0;
    } else {
        lastminute = minute;
    }

    if(hour < 12) 
        ampm[0] = 0x17; //special small "A"
    else
        ampm[0] = 'p';

    hour = hour%12;
  
    if(hour < 10) //to make sure we overwrite old messages
        ampm[1] = 0x20;
    else 
        ampm[1] = 0;

    ampm[2] = 0;
  

    if(hour == 0)
        hour = 12;

    if(date > 9)
        offset = 1;
    else
        offset = 0;


    sprintf(timestr, "%s %s %u  %u:%.2u%s", dow, month, date, 
	        hour, minute, ampm);

    printf("%s\n", timestr);

    ledclear();
    ledsetpos(1);
    ret = ledwrite(timestr);
    ledsetpos(18);
    ret |= ledwrite(logostr);
    return(ret);
}
