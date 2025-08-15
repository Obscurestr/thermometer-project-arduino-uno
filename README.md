# Multi-Room Arduino Thermometer with LCD, SD Logging, and Relay Control

## Overview
This project is a **multi-room thermometer** built with Arduino. It reads temperature and humidity from **two DHT11 sensors**, displays the data on an **I2C LCD**, logs readings to a **microSD card**, and controls a **relay** to turn on/off a heater based on a temperature threshold. The project also includes basic **low-power sleep mode** to save energy when deployed on battery power.

---

## Features
- **Dual DHT11 sensors**: Measures temperature and humidity in two separate rooms or zones.
- **16x2 I2C LCD**: Displays live readings for both rooms.
- **Relay control**: Automatically turns on/off a heater based on Room 1 temperature threshold.
- **Data logging**: Saves temperature and humidity readings to a microSD card (`data.txt`) for long-term tracking.
- **Low power mode**: Uses `LowPower` library to put Arduino to sleep between readings (simulation via `delay()` in Wokwi).

---

## Components Needed
- Arduino Uno (or ESP32/ESP8266 for Wi-Fi upgrade)
- 2 × DHT11 temperature & humidity sensors
- 16x2 I2C LCD display
- Relay module
- MicroSD card module
- Resistors (4.7kΩ for DHT sensors pull-up)
- Jumper wires and breadboard
- Optional: Battery pack for mobile power

---

## Pin Connections

### DHT Sensors
| Sensor | VCC | GND | Data |
|--------|-----|-----|------|
| DHT1   | 5V  | GND | D2   |
| DHT2   | 5V  | GND | D3   |
> Add a 4.7kΩ pull-up resistor between VCC and Data line for each sensor.

### LCD (I2C)
| Pin | Connection |
|-----|-----------|
| SDA | A4 (Arduino Uno) |
| SCL | A5 (Arduino Uno) |
| VCC | 5V |
| GND | GND |

### Relay
| Pin | Connection |
|-----|-----------|
| IN  | D8        |
| VCC | 5V        |
| GND | GND       |

### MicroSD Card Module
| Pin | Connection |
|-----|-----------|
| CS  | D4        |
| SCK | D13       |
| MOSI | D11      |
| MISO | D12      |
| VCC  | 5V       |
| GND  | GND      |

---

## Libraries Required
- [DHT sensor library by Adafruit](https://github.com/adafruit/DHT-sensor-library) (`DHT.h`)  
- [LiquidCrystal I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) (`LiquidCrystal_I2C.h`)  
- SD library (built-in Arduino IDE)  
- LowPower library by Rocketscream (`LowPower.h`) — optional; use `delay()` for Wokwi simulation.

---

## How to Use
1. Connect the components according to the pin connections above.
2. Upload the `sketch.ino` to your Arduino.
3. Open the **Serial Monitor** at 9600 baud to view readings.
4. The LCD will show live temperature and humidity for both rooms.
5. The relay will turn the heater **ON** when Room 1 temperature drops below 22°C.
6. Temperature and humidity readings are logged to `data.txt` on the SD card.

---

## Notes
- In **Wokwi**, the LowPower library is not supported. Replace `LowPower.powerDown()` with `delay()` for simulation.  
- For **real battery operation**, re-enable the LowPower sleep mode.  
