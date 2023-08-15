#if defined(TKL) && defined(V2)

#pragma once

#include "HAL/Chips/Is31fl3743a.h"
#include "HAL/Chips/Tca9548a.h"
#include "HAL/IRGBLedDriver.h"

class RgbLedDriver : public IRGBLedDriver
{
private:
	Is31fl3743a **controllers = NULL;
	uint8_t controllersCount = 9;
	Tca9548a* tca = NULL;
	ILogger *logger = NULL;
	uint8_t rowsCount = 0;
	uint8_t columnCount = 0;

public:
	RgbLedDriver(ILogger *logger, uint8_t rowsCount, uint8_t columnCount, Tca9548a* tca);
	virtual void turnOn();
	virtual void turnOff();
	virtual bool toggle();
	virtual void blink(uint8_t animationPhase, uint8_t x, uint8_t y, uint32_t color);
	virtual void randomizeColors();
	virtual void setColor(uint8_t x, uint8_t y, uint8_t redIntensity, uint8_t greenIntensity, uint8_t blueIntensity);
};

#endif