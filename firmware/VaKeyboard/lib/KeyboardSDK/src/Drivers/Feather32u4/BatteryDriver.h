#pragma once

#ifdef FEATHER32U4

#include <arduino.h>
#include "../IBatteryDriver.h"

class BatteryDriver : public IBatteryDriver
{
public:
    BatteryDriver();

    virtual uint8_t readBatteryLevel();
};

#endif