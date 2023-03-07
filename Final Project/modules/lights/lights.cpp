//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include "lights.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut led(PF_1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void lightsInit()
{
    led = OFF;
}

void lightsOn()
{
    led = ON;
}

void lightsOff()
{
    led = OFF;
}

//=====[Implementations of private functions]==================================
