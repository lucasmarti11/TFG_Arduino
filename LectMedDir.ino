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
byte sensor1[8] = {0x28, 0x18, 0xB4, 0x49, 0x0C, 0x00, 0x00, 0x7C}; //Aquí deberemos pones lad irecciones obtenidas con el otro programa
byte sensor2[8] = {0x28, 0xCC, 0x19, 0x49, 0x0C, 0x00, 0x00, 0xBB};
byte sensor3[8] = {0x28, 0x19, 0xEF, 0x48, 0x0C, 0x00, 0x00, 0x21};

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
  Serial.print("C");
}
