//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "smart_bedroom_system.h"

#include "lights.h"
#include "ldr_sensor.h"
#include "servo.h"
#include "user_interface.h"
#include "motion_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void smartBedroomSystemInit()
{
    debounceButtonInit();
    lightsInit();
    servoInit();
    userInterfaceInit();
}

void smartBedroomSystemUpdate()
{
    userInterfaceUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
