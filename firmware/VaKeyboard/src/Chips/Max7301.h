#pragma once
#include <Arduino.h>
#include <SPI.h>

class Max7301
{
private:
    uint8_t csPin;
    SPISettings spiSettings;
    uint8_t transferWord(uint8_t higherByte, uint8_t lowerByte);

public: 
    Max7301(uint8_t csPin);
    void begin();
    uint8_t read(uint8_t address);
    void write(uint8_t address, uint8_t value);
    void enable();
};