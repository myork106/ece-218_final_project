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

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

InterruptIn lightsButton(PF_9);
InterruptIn shadesButton(PG_1);

DigitalIn shadesSwitch(PF_7);
DigitalIn lightsSwitch(PE_3);

//=====[Declaration of external public global variables]=======================

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
static void lightsButtonCallback();
static void shadesButtonCallback();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    userInterfaceDisplayInit();

    lightsButton.mode(PullUp);
    shadesButton.mode(PullUp);
    
    lightsButton.fall(&lightsButtonCallback);
    shadesButton.fall(&shadesButtonCallback);
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
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;


        if (shadesAutoMode) {
            displayCharPositionWrite ( 5,0 );
            displayStringWrite( "SAuto" );
        }
        else{
            displayCharPositionWrite ( 5,0 );
            displayStringWrite( "SManl" );
        }

        if (lightsAutoMode) {
            displayCharPositionWrite ( 11,0 );
            displayStringWrite( "LAuto" );
        }
        else{
            displayCharPositionWrite ( 11,0 );
            displayStringWrite( "LManl" );
        }


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
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
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

static void lightsButtonCallback() {
    if (!lightsAutoMode){
        if (lightsAreOn){
            lightsOff();
            lightsAreOn = OFF;
        }
        else{
            lightsOn();
            lightsAreOn = ON;
        }
    }
}

static void shadesButtonCallback() {
    if (!shadesAutoMode){
        if (shadesAreOpen) {
            servoClose();
            shadesAreOpen = OFF;
        }
        else{
            servoOpen();
            shadesAreOpen = ON;
        }
    }
}