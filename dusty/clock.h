
typedef unsigned short timerRegistrationResult;
typedef unsigned short timerJobId;

const timerRegistrationResult WORKED = 0;
const timerRegistrationResult TOO_MANY_EVENTS = 1;

const unsigned short TIMER_COUNT = 8;

struct timer_t {

    timerJobId _name;
    unsigned long _triggerTime;
    void (*_callback)(unsigned long);
};

struct clock_t {

    // 
    timer_t timerList[TIMER_COUNT];

    // registers a new timer for the past distance from now, in time
    timerRegistrationResult registerEvent(timerJobId name, unsigned long millisFromNow, void (*callback)(unsigned long)) {
        for (int i = 0; i < TIMER_COUNT; i++) {
            if (timerList[i]._name == NULL) {
                timerList[i]._name = name;
                timerList[i]._triggerTime = millis() + millisFromNow;
                timerList[i]._callback = callback;
                return WORKED;
            }
        }
        return TOO_MANY_EVENTS;
    }

    // update can be a super expensive call
    // updates each of the items in our timer list, and if any have a time beyond 
    // the current time millis(), executes its callback function with the current
    // time millis and then removes it from the list
    void update() {
        
        unsigned long currentTime = millis();

        for (int i = 0; i < TIMER_COUNT; i++) {
            if (timerList[i]._name != NULL) {
                if (timerList[i]._triggerTime < currentTime) {
                    
                    void (*callback)(unsigned long) = timerList[i]._callback;

                    timerList[i]._name = NULL;

                    callback(currentTime);
                }
            }
        }
    }
};