//Incluimos librerías

#include <stdio.h>

const word PWM_FREQ_HZ = 25000; //Adjust this value to adjust the frequency
const word TCNT1_TOP = 16000000/(2*PWM_FREQ_HZ);

/
const word OCRA_TOP = 1;

void setup() {

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



  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {

  analogWrite(9, 185); //Funciona igual a 25kHz
  analogWrite(10, 185);
  analogWrite(3, 150); //Funciona igual a 25kHz
}
