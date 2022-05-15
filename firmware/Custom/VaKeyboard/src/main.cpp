#include <Arduino.h>

#include "KeyboardSDK.h"
#include "Drivers/UsbHidKeyboardDriver.h"
#include "Drivers/BluetoothKeyboardDriver.h"
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
IKeyboardDriver *keyboardDriver = NULL;
DisplayDriver *displayDriver = NULL;
MatrixScanner *matrixScanner = NULL;
MatrixEvaluator *matrixEvaluator = NULL;
KeyMapProvider *keymapProvider = NULL;
ActionEvaluator *actionEvaluator = NULL;
KeyboardSDK *keyboard = NULL;

void triggerBtReset()
{
	logger->logDebug("Resetting BT pairing...");
	delay(2000);
	keyboardDriver->ResetPairing();
}

void setup()
{
	Serial.begin(115200);
	Wire.begin();
	Wire.setClock(1700000);

	logger = new Logger();
	pinDriver = new PinDriver(logger);
	rgbLedDriver = new RgbLedDriver(logger);

	Adafruit_BluefruitLE_SPI *ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

	// keyboardDriver = new UsbHidKeyboardDriver(/*&Keyboard*/);
	keyboardDriver = new BluetoothKeyboardDriver(ble, logger);

	// displayDriver = new DisplayDriver(&SPI);
	matrixScanner = new MatrixScanner(pinDriver, numberOfRows, numberOfColumns, logger);
	matrixEvaluator = new MatrixEvaluator();
	keymapProvider = new KeyMapProvider(numberOfRows, numberOfColumns);
	actionEvaluator = new ActionEvaluator(keymapProvider, logger);
	keyboard = new KeyboardSDK(matrixScanner, matrixEvaluator, keyboardDriver, keymapProvider, actionEvaluator, logger);

	actionEvaluator->registerAction(triggerBtReset, 3, new KeyboardKeycode[3]{KEY_ESC, KEY_LEFT_CTRL, KEY_LEFT_GUI});

	logger->logDebug("\nSetup is done!");
}

void loop()
{
	keyboard->scan();
}