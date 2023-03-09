//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "servo.h"
#include "user_interface.h"
#include "motion_sensor.h"
#include "ldr_sensor.h"
#include "lights.h"

#include "smart_bedroom_system.h"
#include "display.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000
#define DEBOUNCE_BUTTON_TIME_MS 40 

//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn lightsButton(PF_9);
DigitalIn shadesButton(PG_1);

DigitalIn shadesSwitch(PF_7);
DigitalIn lightsSwitch(PE_3);

//=====[Declaration of external public global variables]=======================

int accumulatedDebounceButtonTime = 0;
int numberOfEnterButtonReleasedEvents = 0;
buttonState_t lightsButtonState;
buttonState_t shadesButtonState;

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

bool lightsAutoMode = ON;
bool shadesAutoMode = ON;

bool lightsAreOn = OFF;
bool shadesAreOpen = OFF;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();
static void modeUpdate();
static void shadesButtonCallback();

//=====[Implementations of public functions]===================================

void debounceButtonInit()
{

lightsButton.mode(PullUp);
shadesButton.mode(PullUp);

if( !lightsButton ) {
    lightsButtonState = BUTTON_DOWN;
    } else {
    lightsButtonState = BUTTON_UP;
    }

if( !shadesButton ) {
    shadesButtonState = BUTTON_DOWN;
    } else {
    shadesButtonState = BUTTON_UP;
    }
}

bool lightsDebounceButtonUpdate()
{
    bool lightsButtonReleasedEvent = false;
    switch( lightsButtonState ) {
        case BUTTON_UP: 
            if( !lightsButton ) {
                lightsButtonState = BUTTON_FALLING;
                accumulatedDebounceButtonTime = 0;
                } 
        break;
        case BUTTON_FALLING:
            if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
                if( !lightsButton ) {
                    lightsButtonState = BUTTON_DOWN;
                } else {
                    lightsButtonState = BUTTON_UP;
                }
            }
            accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
            SYSTEM_TIME_INCREMENT_MS;
        break;
        case BUTTON_DOWN:
            if( lightsButton ) {
                lightsButtonState = BUTTON_RISING;
                accumulatedDebounceButtonTime = 0;
                }
        break;
        case BUTTON_RISING:
            if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
                if( lightsButton ) {
                    lightsButtonState = BUTTON_UP;
                    lightsButtonReleasedEvent = true;
                } else {
                    lightsButtonState = BUTTON_DOWN;
                }
            }
            accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
            SYSTEM_TIME_INCREMENT_MS;
        break;
    default:
        debounceButtonInit();
    break;
    }
    return lightsButtonReleasedEvent;
}

bool shadesDebounceButtonUpdate()
{
    bool shadesButtonReleasedEvent = false;
    switch( shadesButtonState ) {
        case BUTTON_UP: 
            if( !shadesButton ) {
                shadesButtonState = BUTTON_FALLING;
                accumulatedDebounceButtonTime = 0;
                } 
        break;
        case BUTTON_FALLING:
            if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
                if( !shadesButton ) {
                    shadesButtonState = BUTTON_DOWN;
                } else {
                    shadesButtonState = BUTTON_UP;
                }
            }
            accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
            SYSTEM_TIME_INCREMENT_MS;
        break;
        case BUTTON_DOWN:
            if( shadesButton ) {
                shadesButtonState = BUTTON_RISING;
                accumulatedDebounceButtonTime = 0;
                }
        break;
        case BUTTON_RISING:
            if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
                if( shadesButton ) {
                    shadesButtonState = BUTTON_UP;
                    shadesButtonReleasedEvent = true;
                } else {
                    shadesButtonState = BUTTON_DOWN;
                }
            }
            accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
            SYSTEM_TIME_INCREMENT_MS;
        break;
    default:
        debounceButtonInit();
    break;
    }
    return shadesButtonReleasedEvent;
}

void userInterfaceInit()
{
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    modeUpdate();
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]==================================

static void userInterfaceDisplayInit()
{
    displayInit();
    servoInit();
    motionSensorInit();
    motionSensorActivate();
     
    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "MOTION" );
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    
    if (!lightsAutoMode) {
        if ((!lightsAreOn) && (lightsDebounceButtonUpdate())) {
            lightsOn();
            lightsAreOn = ON;

        }
        if ((lightsAreOn) && (lightsDebounceButtonUpdate())) {
            lightsOff();
            lightsAreOn = OFF;
        }
    }

    if (!shadesAutoMode) {
        if ((!shadesAreOpen) && (shadesDebounceButtonUpdate())) {
            servoOpen();
            shadesAreOpen = ON;

        }
        if ((shadesAreOpen) && (shadesDebounceButtonUpdate())) {
            servoClose();
            shadesAreOpen = OFF;
        }
    }

    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        if( motionSensorRead() ) {
            displayCharPositionWrite ( 8,1 );
            displayStringWrite( "DETECTED" );
            if (lightsAutoMode) {
                lightsOn();
                lightsAreOn = ON;
            }
        } else {
            displayCharPositionWrite ( 8,1 );
            displayStringWrite( "CEASED  " );
            if (lightsAutoMode) {
                lightsOff();
                lightsAreOn = OFF;
            }
        }

        if( ldrSensorRead() > 0.7 ) {
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "DAY  " );
            if (shadesAutoMode){
                servoOpen();
                shadesAreOpen = ON;
            }
            
        } else {
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "NIGHT" );
            if (shadesAutoMode){
                servoClose();
                shadesAreOpen = OFF;
            }
            
        }

    } else {
        accumulatedDisplayTime = accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

static void modeUpdate() {
    if (lightsSwitch){
        lightsAutoMode = OFF;
    }
    else{
        lightsAutoMode = ON;
    }
    if (shadesSwitch){
        shadesAutoMode = OFF;
    }
    else {
        shadesAutoMode = ON;
    }
}