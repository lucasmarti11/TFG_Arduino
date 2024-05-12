//Incluimos librerías

#include <stdio.h>
#include "Fan.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <FastLED.h>
#include <ArduinoJson.h>

//Definimos constantes

const uint8_t PIN_DTemp = A3;
const uint8_t PIN_LEDs = A2;
const uint8_t PIN_RPM2 = A1;
const uint8_t PIN_RPM1 = A0;
const uint8_t PIN_PWM1 = 3; //Freqüència PWM = 490Hz
const uint8_t PIN_FAN1 = 5; //Freqüència PWM = 980Hz
const uint8_t PIN_FAN2 = 6; //Freqüència PWM = 980Hz
const uint8_t PIN_FAN3 = 8; 
const uint8_t PIN_RPM3 = 9; //Freqüència PWM = 490Hz
const uint8_t PIN_FAN4 = 10; //Freqüència PWM = 490Hz
const uint8_t PIN_FAN5 = 11; //Freqüència PWM = 490Hz
const uint8_t PIN_RPM4 = 12;
const uint8_t PIN_RPM5 = 13;

const uint8_t NUM_LEDs = 60;

FanType_t type_fan1 = FourPins_Soft;
FanType_t type_fan2 = FourPins_Hard;
FanType_t type_fan3 = FourPins_Hard;
FanType_t type_fan4 = ThreePins;
FanType_t type_fan5 = ThreePins;

Operation_Mode_t mode_fan = NORMAL;

uint16_t rpm_fan1 = 0;
uint16_t rpm_fan2 = 0;
uint16_t rpm_fan3 = 0;
uint16_t rpm_fan4 = 0;
uint16_t rpm_fan5 = 0;

uint8_t rpm_fan1_percent = 0; //Per quan es rebi per part de l'interfície gràfica
uint8_t rpm_fan2_percent = 0;
uint8_t rpm_fan3_percent = 0;
uint8_t rpm_fan4_percent = 0;
uint8_t rpm_fan5_percent = 0;

Fan Fan1(type_fan1, PIN_RPM1, PIN_FAN1, PIN_PWM1);
Fan Fan2(type_fan2, PIN_RPM2, PIN_FAN2);
Fan Fan3(type_fan3, PIN_RPM3, PIN_FAN3);
Fan Fan4(type_fan4, PIN_RPM4, PIN_FAN4);
Fan Fan5(type_fan5, PIN_RPM5, PIN_FAN5);


void configura25kHzPWM(){
  // TIMER 1: afecta a pin PWM 9 i 10

  TCCR1A = 0b10000000;
  TCCR1B = 0b00010001;
  uint16_t  maximo = (16000000 / (2*25000)) - 1;
  ICR1 = maximo;
  OCR1A = maximo >> 1;


}

void setup() {
  // put your setup code here, to run once:

  configura25kHzPWM();

  Serial.begin(115200);
  while (!Serial) continue;

  Fan1.begin();
  Fan2.begin();
  Fan3.begin();
  Fan4.begin();
  Fan5.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Fan1.setFanSpeed(mode_fan, 85);
  analogWrite(9, 50);
  digitalWrite(PIN_FAN1, HIGH);
  analogWrite(PIN_FAN4, 255);
}
