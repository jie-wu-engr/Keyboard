#include <Arduino.h>

#include "KeyboardSDK.h"
#include "Drivers/UsbHidKeyboardDriver.h"
#include "Drivers/BluetoothKeyboardDriver.h"
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/DisplayDriver.h"
#include "Drivers/PinDriver.h"
#include "KeyMapProvider.h"
#include "Drivers/RgbLedDriver.h"
#include "Logger.h"

#include "Adafruit_BluefruitLE_SPI.h"

#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 // Optional but recommended, set to -1 if unused

const uint8_t numberOfRows = 6;
const uint8_t numberOfColumns = 17;

ILogger *logger = NULL;
IPinDriver *pinDriver = NULL;
RgbLedDriver *rgbLedDriver = NULL;
SelectiveKeyboardDriver *keyboardDriver = NULL;
DisplayDriver *displayDriver = NULL;
MatrixScanner *matrixScanner = NULL;
MatrixEvaluator *matrixEvaluator = NULL;
KeyMapProvider *keymapProvider = NULL;
ActionEvaluator *actionEvaluator = NULL;
KeyboardSDK *keyboard = NULL;

IKeyboardDriver *btKeyboardDriver = NULL;
IKeyboardDriver *usbKeyboardDriver = NULL;

bool enforcedDisabledLeds = false;

void triggerBtReset()
{
	logger->logDebug("Resetting BT pairing...");
	keyboardDriver->ResetPairing();
}

void toggleLeds()
{
	logger->logDebug("Toggling LEDs...");
	enforcedDisabledLeds = !rgbLedDriver->toggle();
}

void toggleConnection()
{
	keyboardDriver->SwapKeyboards();
}

void randomizeColors()
{
	rgbLedDriver->randomizeColors(numberOfRows, numberOfColumns);
}

void turnOnLeds()
{
	if (enforcedDisabledLeds)
	{
		return;
	}

	rgbLedDriver->turnOn();
}

void turnOffLeds()
{
	rgbLedDriver->turnOff();
}

void setup()
{
	Serial.begin(115200);
	Wire.begin();
	Wire.setClock(1700000L);

	logger = new Logger();
	pinDriver = new PinDriver(&Wire, logger);
	rgbLedDriver = new RgbLedDriver(logger);

	Adafruit_BluefruitLE_SPI *ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

	usbKeyboardDriver = new UsbHidKeyboardDriver();
	btKeyboardDriver = new BluetoothKeyboardDriver(ble, logger);

	keyboardDriver = new SelectiveKeyboardDriver(usbKeyboardDriver, btKeyboardDriver);

	// displayDriver = new DisplayDriver(&SPI);
	matrixScanner = new MatrixScanner(pinDriver, numberOfRows, numberOfColumns, logger);
	matrixEvaluator = new MatrixEvaluator();
	keymapProvider = new KeyMapProvider(numberOfRows, numberOfColumns);
	actionEvaluator = new ActionEvaluator(keymapProvider, logger);
	keyboard = new KeyboardSDK(matrixScanner, matrixEvaluator, keyboardDriver, keymapProvider, actionEvaluator, logger);

	actionEvaluator->registerMatrixAction(triggerBtReset, 3, new KeyboardKeycode[3]{KEY_ESC, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(toggleLeds, 3, new KeyboardKeycode[3]{KEY_F1, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(toggleConnection, 3, new KeyboardKeycode[3]{KEY_F2, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(randomizeColors, 3, new KeyboardKeycode[3]{KEY_F3, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerTimerAction(90000UL, 0UL, turnOffLeds, turnOnLeds);

	logger->logDebug("\nSetup is done!");
}

void loop()
{
	keyboard->scan();
}