#include <Arduino.h>

struct motor_t {
    int _enablePin;
    int _forwardPin;
    int _reversePin;
    int _currentSpeed = 0;

    motor_t(int enablePin, int forwardPin, int reversePin): _enablePin(enablePin), _forwardPin(forwardPin), _reversePin(reversePin) {

        // enable write mode
        pinMode(_enablePin, OUTPUT);
        pinMode(_forwardPin, OUTPUT);
        pinMode(_reversePin, OUTPUT);

        // stop the motor entirely
        digitalWrite(_enablePin, LOW);
        digitalWrite(_forwardPin, LOW);
        digitalWrite(_reversePin, LOW);
    }

    void forward() {
        digitalWrite(_enablePin, HIGH);
        digitalWrite(_forwardPin, HIGH);
        digitalWrite(_reversePin, LOW);
    }

    void reverse() {
        digitalWrite(_enablePin, HIGH);
        digitalWrite(_forwardPin, LOW);
        digitalWrite(_reversePin, HIGH);
    }

    void stop() {
        digitalWrite(_enablePin, LOW);
        digitalWrite(_forwardPin, LOW);
        digitalWrite(_reversePin, LOW);
    }
};