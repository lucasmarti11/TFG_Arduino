/* Multiple DS18B20 1-Wire digital temperature sensors with Arduino example code. More info: https://www.makerguides.com */
//ESTE CÓDIGO ES PARA LA LECTURA DE DIRECCIONES DE LOS SENSORES

// Include the required Arduino libraries:
#include "OneWire.h"
#include "DallasTemperature.h"

// Define to which pin of the Arduino the 1-Wire bus is connected:
const uint8_t PIN_DTemp = A3;

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(PIN_DTemp);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensorT(&oneWire);

// Create variables:
int deviceCount = 0; // variable to store the number of devices connected
DeviceAddress deviceAddress; // variable to store the device address

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  // Start up the library:
  sensorT.begin();

  // Locate the devices on the bus:
  Serial.println("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensorT.getDeviceCount();
  Serial.print(deviceCount);
  Serial.println(" devices");

  Serial.println("Printing addresses...");
  for (int i = 0;  i < deviceCount;  i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" : ");
    sensorT.getAddress(deviceAddress, i);
    printAddress(deviceAddress);
  }
}

void loop() {
}

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) {
      Serial.print(", ");
    }
  }
  Serial.println();
}

/*
14:08:23.842 -> Sensor 1 : 0x28, 0x61, 0x64, 0x09, 0x54, 0x3B, 0xC8, 0x94
14:08:23.875 -> Sensor 2 : 0x28, 0xFF, 0x64, 0x1D, 0xF2, 0x7C, 0xDD, 0x70
14:08:23.940 -> Sensor 3 : 0x28, 0xFF, 0x64, 0x1D, 0xFD, 0x97, 0x70, 0x2B
*/
