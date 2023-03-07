//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include "servo.h"
#include "smart_bedroom_system.h"

//=====[Declaration of private defines]========================================

#define DUTY_MIN 0.03
#define DUTY_MAX 0.12
#define PERIOD 0.02
#define DELAY_TIME 10000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

PwmOut servo(PF_9);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void servoInit()
{
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
}

void servoOpen()
{
    servo.write(DUTY_MAX/1.75);
}

void servoClose()
{
    servo.write(DUTY_MIN);
}

//=====[Implementations of private functions]==================================
