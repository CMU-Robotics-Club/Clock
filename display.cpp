#include "display.h"
#include "char.h"

#define ROW_WIDTH 95

// Display buffer
volatile static char buffer[ROW_WIDTH];
volatile static int bufferIndex = 0;

// Used by displayFlush()
// i is current row
volatile int i = 0;
// i is the mask that represents the row
volatile uint8_t mask = 0x80;

// Clears buffer
void displayClearBuffer();


/*
 * Writes a char to the display buffer;
 */
void displayWriteChar(char c);

/*
 * Clock the display's shift register.
 */
inline void displayClock();

/*
 * Called by display.
 * Does the actual work of displaying a String
 * but s.length() <= 19 as does not handle display
 * overflow(that is handled by display(s)).
 */
void displayFull(String s);


void display(String s) {
  // Display String in 19 character sections
  for(int i = 0; i < s.length(); i++) {
    displayFull(s.substring(i, i+19));
    delay(800);
    
    // Break if all remaining characters were
    // just displayed
    if(i + 19 >= s.length()) {
      break; 
    }
  }
}

void displayFlush()
{
  uint8_t data;
  
  // write data for row i
  for(int j = 0; j < ROW_WIDTH; j++) {
    if (buffer[j] & mask) {
      data = 0x01;
    } else {
      data = 0x00;
    }

    PORTF = data;
      
    displayClock();
  }

  PORTF = mask;
    
  displayClock();

  mask = mask >> 1;

  i++;
    
  if(i == 7) {
    mask = 0x80;
    i = 0; 
  }
}



// Private Methods

void displayFull(String s) {
  // clear the buffer and reset the index
  displayClearBuffer();

  // write all characters in String to buffer
  for(int i = 0; i < s.length(); i++) {
    char c = s.charAt(i);
    displayWriteChar(c);
  }
}

void displayClearBuffer() {
  for(int j = 0; j < ROW_WIDTH; j++) {
    buffer[j] = 0;
  }
  
  bufferIndex = 0;
}

void displayWriteChar(char c)
{
  int index = 5 * bufferIndex + 1;
  int offset = 5 * c;

  // Lookup character to LED bit mapping
  // and store that in the buffer
  buffer[index] = CHAR_MAP_ADDRESS[offset];
  buffer[index+1] = CHAR_MAP_ADDRESS[offset+1];
  buffer[index+2] = CHAR_MAP_ADDRESS[offset+2];
  buffer[index+3] = CHAR_MAP_ADDRESS[offset+3];
  buffer[index+4] = CHAR_MAP_ADDRESS[offset+4];
  
  bufferIndex++;  
}

inline void displayClock() {
  // Clock is PortK LSB (A8 on Mega)
  PORTK &= ~1;
  PORTK |= 1;
}
