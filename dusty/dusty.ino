
/*
    First attempt at the Dusty firmware just use 
*/

#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>
#include "IRremote.h"
#include "motor.h"
#include "clock.h"

#define DEBUG 1

#define REMOTE_CONTROLLER_PIN 12

#define FORWARD_BUTTON 5316027		  // FORWARD
#define BACK_BUTTON 2747854299	// BACK
#define LEFT_BUTTON 1386468383	// LEFT
#define RIGHT_BUTTON 553536955		// RIGHT
#define OK_BUTTON 3622325019	// OK
#define CONTINUE 4294967295 // repeated press registered

// job Id for 
#define CHECK_DISTANCE_JOB_ID 1

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
#define TRIGGER 2
#define ECHO 3

// remote_control_t remoteControl(REMOTE_CONTROLLER_PIN);
IRrecv irrecv(REMOTE_CONTROLLER_PIN);  
decode_results results;

motor_t rightMotor(ENB, IN1, IN2);
motor_t leftMotor(ENA, IN3, IN4);   

Servo rangefinderNeck;
int servoPlacement = 45;

clock_t clock;

// rangefinder-related variables
volatile bool rangefinderTriggered = false;
volatile bool rangefinderEchoed = false;
unsigned long rangefinderPulseInMicros = 0l;
volatile unsigned long rangefinderPulseDoneMicros = 0l;

unsigned long lastMillis = 0l;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    
    pinMode(LED_BUILTIN, OUTPUT);
    leftMotor.stop();
    rightMotor.stop();
    
    irrecv.enableIRIn();  // Start receiving

    rangefinderNeck.attach(4);

    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ECHO), pingReturn_ISR, CHANGE);

    clock.registerEvent(CHECK_DISTANCE_JOB_ID, 100, &pingDistanceJobCallback);

    forward();
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

        switch (val) {
            case FORWARD_BUTTON:
                moveForward();
                break;
            case BACK_BUTTON:
                moveBackward();
                break;
            case LEFT_BUTTON:
                turnLeft();
                break;
            case RIGHT_BUTTON:
                turnRight();
                break;
            case OK_BUTTON:
                Serial.println("stop");
                stop();
                break;
        }
        
        irrecv.resume();      // Receive the next value
    }

    rangefinderLogicUpdate();
    clock.update();
}

// this is the job that runs at 10hz, just pings the rangefinder and then reschedules itself
void pingDistanceJobCallback(unsigned long currentTime) {

    triggerRangefinder();

    // reschedule this job
    clock.registerEvent(CHECK_DISTANCE_JOB_ID, 100, &pingDistanceJobCallback);
}

// triggers the rangefinder
void triggerRangefinder() {

    // power the TRIGGER pin for 10 microseconds to cause the rangefinder to pulse
    digitalWrite(TRIGGER, LOW); 
    delayMicroseconds(2);
 
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIGGER, LOW);

    rangefinderTriggered = true;
}

// the rangefinder raises echo based on the time spent so we actually want to read the time echo is high, not the time from ping to echo
void pingReturn_ISR() {
    if (rangefinderTriggered) {
        switch (digitalRead(ECHO)) {
            case HIGH:                                      
                rangefinderPulseInMicros = micros();                                 
                break;
            
            case LOW:                    
                rangefinderTriggered = false;
                rangefinderEchoed = true;
                rangefinderPulseDoneMicros = micros();
                break;
        }
    }
}

void rangefinderLogicUpdate() {

    if (rangefinderEchoed) {

        long duration = rangefinderPulseDoneMicros - rangefinderPulseInMicros;

        if (duration < 0) {
            return;
        }

        float obstacleDistance = duration / 58;

        // 0.0344 is just a multiplier for transforming ping time to distance
        // float obstacleDistance = (duration / 2) * 0.0344; 
        
    #ifdef DEBUG
        unsigned long currentMillis = millis();
        Serial.print("distance: (");
        Serial.print(currentMillis - lastMillis);
        Serial.print(") ");
        Serial.println(obstacleDistance);
        lastMillis = currentMillis;
    #endif

        // for now just stop the car if we see an obstacle
        if (obstacleDistance < 30) { 
            stop();
        } 
    } 

    rangefinderEchoed = false;
}

void lookLeft() {

}

void lookRight() {

}

void moveForward() {
    
#ifdef DEBUG
    Serial.println("forward");
#endif
    stop();
    forward();
}

void moveBackward() {
    Serial.println("reverse");
    stop();
    reverse();
}

void turnLeft() {
    Serial.println("left");
    stop();
    left();
}

void turnRight() {
    Serial.println("right");
    stop();
    right();
}

void print(const char *str) {
#ifdef DEBUG
    Serial.println(str);
#endif
}