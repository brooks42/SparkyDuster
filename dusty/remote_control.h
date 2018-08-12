#include "Arduino.h"

const int NO_COMMAND = -1;

#define F 16736925	// FORWARD
#define B 16754775	// BACK
#define L 16720605	// LEFT
#define R 16761405	// RIGHT
#define S 16712445	// STOP

#define UNKNOWN_F 5316027		  // FORWARD
#define UNKNOWN_B 2747854299	// BACK
#define UNKNOWN_L 1386468383	// LEFT
#define UNKNOWN_R 553536955		// RIGHT
#define UNKNOWN_S 3622325019	// STOP

// #define L         16738455
#define UNKNOWN_L 1386468383

struct remote_control_t {

    // current command from the remote control, or -1 if there isn't one
    int _command;

    uint8_t _pin;

    remote_control_t(const int & pin) : _pin(pin) {
    }

    int hasCommand() {
        return _command != NO_COMMAND;
    }

    void update() {
        int tempValue = analogRead(_pin);
        // TODO: check - if it's a non-known command, we should return 0 or LOW

        // switch (tempValue) {
        //     case F:
        //     case B:
        //     case L:
        //     case R:
        //     case S:
        //     _command = tempValue % 100;
        //     break;
        //     default:
        //     _command = NO_COMMAND;
        // }
        _command = tempValue;
    }

    int poll() {
        int tempCommand = _command;
        _command = NO_COMMAND;
        return tempCommand;
    }
};