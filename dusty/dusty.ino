
/*
    First attempt at the Dusty firmware just use 
*/

#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>
#include "IRremote.h"
#include "motor.h"

const int REMOTE_CONTROLLER_PIN = 12;

#define FORWARD_BUTTON 5316027		  // FORWARD
#define BACK_BUTTON 2747854299	// BACK
#define LEFT_BUTTON 1386468383	// LEFT
#define RIGHT_BUTTON 553536955		// RIGHT
#define OK_BUTTON 3622325019	// OK
#define CONTINUE 4294967295 // repeated press registered

/*define channel enable output pins*/
#define ENA 5	  // Left  wheel speed
#define ENB 10	  // Right wheel speed
/*define logic control output pins*/
#define IN1 6   // Left  wheel forward
#define IN2 7   // Left  wheel reverse
#define IN3 8   // Right wheel reverse
#define IN4 9   // Right wheel forward
#define carSpeed 150	// initial speed of car >=0 to <=255

// the rangefinder's pins
#define ECHO A0
#define TRIGGER A1

// remote_control_t remoteControl(REMOTE_CONTROLLER_PIN);
IRrecv irrecv(REMOTE_CONTROLLER_PIN);  
decode_results results;

motor_t rightMotor(ENB, IN1, IN2);
motor_t leftMotor(ENA, IN3, IN4);   

Servo rangefinderNeck;
int servoPlacement = 45;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    
    pinMode(LED_BUILTIN, OUTPUT);
    leftMotor.stop();
    rightMotor.stop();
    
    irrecv.enableIRIn();  // Start receiving

    rangefinderNeck.attach(4);

    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
}

void forward() {
    leftMotor.forward();
    rightMotor.forward();
}

void reverse() {
    leftMotor.reverse();
    rightMotor.reverse();
}

void stop() {
    leftMotor.stop();
    rightMotor.stop();
}

void left() {
    leftMotor.forward();
    rightMotor.reverse();
}

void right() {
    leftMotor.reverse();
    rightMotor.forward();
}

// the loop function runs over and over again forever
void loop() {
    
    if (irrecv.decode(&results)) { 
        unsigned long val = results.value;

        // TODO: need a state maachine
        // in the final codebase the raspi will handle the state machine component but for now just shove it in the arduino
        if (val == FORWARD_BUTTON) {
            Serial.println("forward");
            stop();
            forward();
        }

        if (val == BACK_BUTTON) {
            Serial.println("reverse");
            stop();
            reverse();
        }

        if (val == LEFT_BUTTON) {
            Serial.println("left");
            stop();
            left();
        }
        
        if (val == RIGHT_BUTTON) {
            Serial.println("right");
            stop();
            right();
        }

        if (val == OK_BUTTON) {
            Serial.println("stop");
            stop();
        }
        
        irrecv.resume();      // Receive the next value
    }

    // if (servoPlacement == 45) {
    //     servoPlacement = 135;
    // } else {
    //     servoPlacement = 45;
    // }
    // rangefinderNeck.write(servoPlacement);
    // delay(100);
}
