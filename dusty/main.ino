
/*
    First attempt at the Dusty firmware just use 
*/

#include <Arduino.h>
#include <stdio.h>
#include "IRremote.h"
#include "motor.h"

const int REMOTE_CONTROLLER_PIN = 12;

#define FORWARD_BUTTON 5316027		  // FORWARD
#define BACK_BUTTON 2747854299	// BACK
#define LEFT_BUTTON 1386468383	// LEFT
#define RIGHT_BUTTON 553536955		// RIGHT
#define OK_BUTTON 3622325019	// OK
#define CONTINUE 4294967295 // repeated press registered

// remote_control_t remoteControl(REMOTE_CONTROLLER_PIN);
IRrecv irrecv(REMOTE_CONTROLLER_PIN);  
decode_results results;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    
    pinMode(LED_BUILTIN, OUTPUT);
    
    irrecv.enableIRIn();  // Start receiving
}

// the loop function runs over and over again forever
void loop() {
    
    if (irrecv.decode(&results)) { 
        unsigned long val = results.value;
        Serial.println(val);

        
        
        irrecv.resume();      // Receive the next value
        delay(100);
    }
}
