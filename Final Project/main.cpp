//=====[Libraries]=============================================================

#include "smart_bedroom_system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    smartBedroomSystemInit();
    while (true) {
        smartBedroomSystemUpdate();
    }
}