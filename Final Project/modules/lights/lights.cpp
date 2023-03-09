//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include "lights.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut led1(D10);
DigitalOut led2(D11);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void lightsInit()
{
    led1 = OFF;
    led2 = OFF;
}

void lightsOn()
{
    led1 = ON;
    led2 = ON;
}

void lightsOff()
{
    led1 = OFF;
    led2 = OFF;
}

//=====[Implementations of private functions]==================================
