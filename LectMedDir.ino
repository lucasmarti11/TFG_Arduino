/* Read multiple DS18B20 1-Wire digital temperature sensors by address. 
   More info: https://www.makerguides.com */

// Include the required Arduino libraries:
#include "OneWire.h"
#include "DallasTemperature.h"

// Define to which pin of the Arduino the 1-Wire bus is connected:
const uint8_t PIN_DTemp = A3;

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(PIN_DTemp);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensorT(&oneWire);

// Addresses of DS18B20 sensors connected to the 1-Wire bus

/*Direcciones de nuestros sensores:

14:08:23.842 -> Sensor 1 : 0x28, 0x61, 0x64, 0x09, 0x54, 0x3B, 0xC8, 0x94
14:08:23.875 -> Sensor 2 : 0x28, 0xFF, 0x64, 0x1D, 0xF2, 0x7C, 0xDD, 0x70
14:08:23.940 -> Sensor 3 : 0x28, 0xFF, 0x64, 0x1D, 0xFD, 0x97, 0x70, 0x2B

*/

byte sensor1[8] = {0x28, 0x61, 0x64, 0x09, 0x54, 0x3B, 0xC8, 0x94}; //Aquí deberemos pones lad irecciones obtenidas con el otro programa
byte sensor2[8] = {0x28, 0xFF, 0x64, 0x1D, 0xF2, 0x7C, 0xDD, 0x70};
byte sensor3[8] = {0x28, 0xFF, 0x64, 0x1D, 0xFD, 0x97, 0x70, 0x2B};

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(115200);
  // Start up the library:
  sensorT.begin();
}

void loop() {
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensorT.requestTemperatures();

  Serial.print("Sensor 1: ");
  printTemperature(sensor1); // call the printTemperature function with the address of sensor1 as input
  Serial.print("Sensor 2: ");
  printTemperature(sensor2);
  Serial.print("Sensor 3: ");
  printTemperature(sensor3);

  Serial.println(); // prints an empty line
  //delay(1000);
}

void printTemperature(DeviceAddress address) {
  // Fetch the temperature in degrees Celsius for device address:
  float tempC = sensorT.getTempC(address);
  Serial.print(tempC);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.print("C ");
}
