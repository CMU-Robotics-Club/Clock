#include <SPI.h>
#include <Ethernet.h>
#include <RC.h>
#include <TimerThree.h>
#include <delay_basic.h>

#include "display.h"

// SET THESE
#define PUBLIC_KEY ""
#define PRIVATE_KEY ""
byte mac[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

#define CLOCK_PIN A8

EthernetClient ethernetClient;

APIClient api(ethernetClient, PUBLIC_KEY, PRIVATE_KEY);

#define CLOCK_CHANNEL 5

Channel channel;

// Special byte sequence to show Roboclub Logo
char logo[3];


void setup() {
  Serial.begin(9600);
  Serial.println(F("Welcome to the Clock Project"));
  
  if(!Ethernet.begin(mac)) {
    Serial.println(F("Failed to initialize ethernet shield"));
    return; 
  }
  
  Serial.println(F("Connected to Internet"));
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
 
  // Roboclub Logo
  logo[0] = 0x15;
  logo[1] = 0x16;
  logo[2] = 0x00;
 
  // Timer to flush display
  Timer3.initialize(1000);
  Timer3.attachInterrupt(displayFlush);
 
  display("Initializing...");
  
  // Read initial value of channel
  while(!api.channel(CLOCK_CHANNEL, channel))
  {
    Serial.println("Initial channel reading failed");
  }
}


void loop() {  
  String datetime;
  
  if(!api.datetime("%a %b %d %I:%M%p", datetime)) {
    Serial.println("Datetime failed"); 
  } else {
    Serial.println(datetime);
    
    datetime.replace("AM", "a");
    datetime.replace("PM", "p");
        
    datetime += logo;
    
    display(datetime);
  }
  
  Channel newChannel;
  
  if(!api.channel(CLOCK_CHANNEL, newChannel)) {
    Serial.println("Channel failed");
  } else {
    if(CHANNEL_UPDATED(channel, newChannel)) {
      Serial.println(newChannel.value);
      
      display(newChannel.value);
      
      // show message for 5 seconds
      delay(5000);
      
      channel = newChannel;
    }
  }
}

