#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "char.h"
#include "time.h"

#define CLOCKPIN _BV(PORTD4)    // Pin we use for the clock
#define LOAD_COLUMN 0x01        // This is the mask to enable the column
#define BUFF_SIZE 19            // Maximum number of characters in a row

#define TRUE 1
#define FALSE 0

uint8_t     s_buffer[95];   // Current state of the screen
uint8_t     c_buffer[5];    // Character write to the s_buffer
uint16_t    in_buff_index;  // Current location in the s_buffer to write
uint8_t     escaped;        // We escaped the next character

/* shift the shift registers */
inline void clock(void){
    PORTD |= CLOCKPIN;
    PORTD &= ~CLOCKPIN;
}

/* write the current buffer */
void write(uint8_t incoming){
    uint16_t index = 5 * in_buff_index + 1;
    uint16_t offset = 5 * incoming;

    s_buffer[index] = CHAR_MAP_ADDRESS[offset];
    s_buffer[index+1] = CHAR_MAP_ADDRESS[offset+1];
    s_buffer[index+2] = CHAR_MAP_ADDRESS[offset+2];
    s_buffer[index+3] = CHAR_MAP_ADDRESS[offset+3];
    s_buffer[index+4] = CHAR_MAP_ADDRESS[offset+4];
}

/* blank the screen */
void blank(void){
    uint8_t i;

    for(i = 0; i < 95; i++) {
        s_buffer[i] = 0x00;
    }
    
    in_buff_index = 0;
}

/* read incoming characters */
ISR(USART_RX_vect) {  
    uint8_t incoming;
                    
    incoming = UDR0;

    if(escaped){ //escapes set the cursor position
        in_buff_index = incoming-1;
        escaped = FALSE;
        return;
    }
   
    // Special cases
    switch(incoming){
        case 0x08: //backspace
        case 0x7F: //del
            if(in_buff_index > 0) {
	            in_buff_index--;
	            write(0x00);
            }
            return;
        case 0x0A: //newline
        case 0x0D: //carriage return
            blank();
            return;
        case 0x1B: //escape
            escaped = TRUE;
            return;
    }
    
    // Add character to the buffer
    if(in_buff_index < BUFF_SIZE){
        write(incoming);
      
        in_buff_index++;
      
        if(in_buff_index > BUFF_SIZE) {
	        in_buff_index = BUFF_SIZE;
        }
    }
}

/* Initialize to 9600 baud, no parity, 8 bits */
void init_uart(void) {
    UCSR0B = _BV(RXCIE0) | _BV(RXEN0);
    UBRR0H = 0x00;
    UBRR0L = 129;
}

int main(void) {
    uint8_t i, j;
    uint8_t mask;
    uint8_t data;
    escaped = FALSE;
    in_buff_index = 0;

    sei();
    init_uart();

    // Init pins
    DDRB = 0x0F;
    DDRC = 0x0F;
    DDRD |= _BV(DDD4) | _BV(DDD3);
    PORTD &= ~CLOCKPIN;
    PORTD &= ~_BV(PORTD3);  // Debug pin
    
    // Clear Display
    blank();    

    while(1) {
        
        /** 
         * Enable each column in the row if the row we are on
         * is supposed to be on. Iterate through each row.
         **/
        mask = 0x80;
        for (i = 0; i < 7; i++) {
            for(j = 0; j < 95; j++) {
                if (s_buffer[j] & mask) {
                    data = 0x01;
                } else {
                    data = 0x00;
                }

                PORTB = data;
                PORTC = 0x00;
                clock();
            }

            PORTB = mask & 0x0F;
            PORTC = (mask >> 4);
            clock();

            delay_ms(1);
            mask = mask >> 1;
        }
        
        /* 
        // Sanity Check Code
        // Edit mask to change the pattern
        mask = 0xAF;
        PORTB = mask & 0x0F;
        PORTC = (mask >> 4) & 0x0F;
        clock();
        */
    }
}
