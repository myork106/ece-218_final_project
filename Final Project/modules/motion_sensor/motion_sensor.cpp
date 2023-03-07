//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "motion_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

InterruptIn pirOutputSignal(PG_0);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool pirState;
static bool motionSensorActivated;

//=====[Declarations (prototypes) of private functions]========================

static void motionDetected();
static void motionCeased();

//=====[Implementations of public functions]===================================

void motionSensorInit()
{
    pirOutputSignal.rise(&motionDetected);
    pirState = OFF;
    motionSensorActivated = true;
}

bool motionSensorRead()
{
    return pirState;
}

void motionSensorActivate()
{
    motionSensorActivated = true;
    if ( !pirState ) {
        pirOutputSignal.rise(&motionDetected);
    }
}

void motionSensorDeactivate()
{
    motionSensorActivated = false;
    if ( !pirState ) {
        pirOutputSignal.rise(NULL);
    }
}

//=====[Implementations of private functions]==================================

static void motionDetected()
{
    pirState = ON;
    pirOutputSignal.rise(NULL);
    pirOutputSignal.fall(&motionCeased);
}

static void motionCeased()
{
    pirState = OFF;
    pirOutputSignal.fall(NULL);
    if ( motionSensorActivated ) {
        pirOutputSignal.rise(&motionDetected);
    }
}