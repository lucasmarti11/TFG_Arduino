#include "Temp.h"

const uint8_t PIN_DTemp = A3;

byte sensor1[8] = {0x28, 0x61, 0x64, 0x09, 0x54, 0x3B, 0xC8, 0x94}; //Aquí deberemos pones lad irecciones obtenidas con el otro programa
byte sensor2[8] = {0x28, 0xFF, 0x64, 0x1D, 0xF2, 0x7C, 0xDD, 0x70};
byte sensor3[8] = {0x28, 0xFF, 0x64, 0x1D, 0xFD, 0x97, 0x70, 0x2B};

float temp_sensor1;
float temp_sensor2;
float temp_sensor3;

Temp Temp1(PIN_DTemp, sensor1, sensor2, sensor3);

void setup(){
  Serial.begin(115200);

  Temp1.begin();


}

void loop(){

  Temp1.measureTemp();

  temp_sensor1 = Temp1.getTemp(1);
  temp_sensor2 = Temp1.getTemp(2);
  temp_sensor3 = Temp1.getTemp(3);

  Serial.print("Sensor 1: ");
  Serial.print(temp_sensor1);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.print("C ");

  Serial.print("Sensor 2: ");
  Serial.print(temp_sensor2);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.print("C ");


  Serial.print("Sensor 3: ");
  Serial.print(temp_sensor3);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.print("C ");
  Serial.println();


}


