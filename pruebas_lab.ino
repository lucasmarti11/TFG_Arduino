//Incluimos librerías

#include <stdio.h>
#include "Fan.h"

const uint8_t PIN_DTemp = A3;
const uint8_t PIN_LEDs = A2;
const uint8_t PIN_RPM2 = A1;
const uint8_t PIN_RPM1 = A0;
const uint8_t PIN_PWM1 = 3; //Freqüència PWM = 490Hz
const uint8_t PIN_FAN1 = 5; //Freqüència PWM = 980Hz
const uint8_t PIN_FAN2 = 6; //Freqüència PWM = 980Hz
const uint8_t PIN_RPM3 = 8; 
const uint8_t PIN_FAN3 = 9; //Freqüència PWM = 490Hz
const uint8_t PIN_FAN4 = 10; //Freqüència PWM = 490Hz
const uint8_t PIN_FAN5 = 11; //Freqüència PWM = 490Hz
const uint8_t PIN_RPM4 = 12;
const uint8_t PIN_RPM5 = 13;

FanType_t type_fan1 = FourPins_Soft;
FanType_t type_fan2 = FourPins_Hard;
FanType_t type_fan3 = FourPins_Hard;
FanType_t type_fan4 = ThreePins;
FanType_t type_fan5 = ThreePins;

Operation_Mode_t mode_fan = MANUAL;

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

float temp_sensor1 = 0.0;
float temp_sensor2 = 0.0;
float temp_sensor3 = 0.0;

Fan Fan1(type_fan1, PIN_RPM1, PIN_FAN1, PIN_PWM1);
Fan Fan2(type_fan2, PIN_RPM2, PIN_FAN2);
Fan Fan3(type_fan3, PIN_RPM3, PIN_FAN3);
Fan Fan4(type_fan4, PIN_RPM4, PIN_FAN4);
Fan Fan5(type_fan5, PIN_RPM5, PIN_FAN5);

const word PWM_FREQ_HZ = 25000; //Adjust this value to adjust the frequency
const word TCNT1_TOP = 16000000/(2*PWM_FREQ_HZ);


const word OCRA_TOP = 1;

void setup() {

  Serial.begin(115200);

  // Clear Timer1 control and count registers PHASE CORRECT PWM perque el calcul ho permet
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // Set Timer1 configuration
  // COM1A(1:0) = 0b10   (Output A clear rising/set falling)
  // COM1B(1:0) = 0b00   (Output B normal operation)
  // WGM(13:10) = 0b1010 (Phase correct PWM)
  // ICNC1      = 0b0    (Input capture noise canceler disabled)
  // ICES1      = 0b0    (Input capture edge select disabled)
  // CS(12:10)  = 0b001  (Input clock select = clock/1)
  
  TCCR1A |= (1 << COM1A1) | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << CS10);
  ICR1 = TCNT1_TOP;

  //PHASE CORRECT PWM Mod Perque el calcul ho permet

  TCCR2A = 0;
  TCCR2B = 0;
  OCR2A  = 0;
  TCNT2 = 0;

  TCCR2A |= (1 << COM2A1) | (1 << WGM20);
  TCCR2B |= (0 << WGM22) | (1 << CS20);
  OCR2A = OCRA_TOP;



  Fan1.begin();
  Fan2.begin();
  Fan3.begin();
  Fan4.begin();
  Fan5.begin();

}

void loop() {


  /*Fan1.setFanSpeed(mode_fan, temp_sensor1, rpm_fan1_percent);
  Fan2.setFanSpeed(mode_fan, temp_sensor2, rpm_fan2_percent);
  Fan3.setFanSpeed(mode_fan, temp_sensor2, rpm_fan3_percent);
  Fan4.setFanSpeed(mode_fan, temp_sensor3, rpm_fan4_percent);
  Fan5.setFanSpeed(mode_fan, temp_sensor3, rpm_fan5_percent);*/

  Fan1.measureRPM();
  Fan2.measureRPM();
  Fan3.measureRPM();
  Fan4.measureRPM();
  Fan5.measureRPM();

  rpm_fan1 = Fan1.getRPM();
  rpm_fan2 = Fan2.getRPM();
  rpm_fan3 = Fan3.getRPM();
  rpm_fan4 = Fan4.getRPM();
  rpm_fan5 = Fan5.getRPM();

  /*Serial.print("Revoluciones ventilador 3: ");
  Serial.println(rpm_fan3);*/

  /*Serial.print("Revoluciones ventilador 4: ");
  Serial.println(rpm_fan4);*/

  /*Serial.print("Revoluciones ventilador 5: ");
  Serial.println(rpm_fan5);*/


  analogWrite(9, 191); //Funciona igual a 25kHz
  analogWrite(10, 191); //Funciona igual a 25kHz
  analogWrite(3, 191); //Funciona igual a 31.33kHz
  analogWrite(11, 191); //Funciona igual a 31.33kHz
}
