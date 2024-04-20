#include "Fan.h"

/*******************************************************************************
 ** Initializations
 ******************************************************************************/

Fan::Fan(FanType_t type, uint8_t pin_rpm, uint8_t pin_fan, uint8_t pin_pwm = 0)
{ 
  type_    = type;
  pin_fan_ = pin_fan;
  pin_rpm_ = pin_rpm;
  pin_pwm_ = pin_pwm;

  last_pwm_value = 0;

  rpm_ = 0;
  start_time_ = 0;
  counting_  = false;  
}


void Fan::begin()
{
  pinMode(pin_rpm_, INPUT);
  pinMode(pin_fan_, OUTPUT);
  if( pin_pwm_ != 0 ){
    pinMode(pin_pwm_, OUTPUT); 
  }
}


/*
 *
 *
 */
void Fan::measureRPM(){

  // llegim l'entrada una única vegada enlloc de fer-ho dues vegades si no és compleix el primer if
  int current_value = digitalRead(pin_rpm_);

  if( current_value == LOW && counting_ == true ){
    counting_ = false;
    unsigned long end_time = micros();  // s'ha de tenir en compte que micros retorna un unsigned long
    // el temps final no fa falta sigui variable de classe, només s'empra aquí

    // si no és compleix es que ha coincidit amb el desbordament del comptador intern
    if ( end_time > start_time_ )
    {
      // la durada del pols tampoc fa falta que sigui variable de classe
      unsigned int pulse_width = micros() - start_time_;
      rpm_ = (60*1000000)/(4*pulse_width);
    }
  }else if(current_value == HIGH && counting_ == false){

    start_time_ = micros();
    counting_ = true;
  }
}

void Fan::setFanSpeed(Operation_Mode_t oper_mode, uint8_t temperature, uint8_t percent){
  int pwm_value;
  pwm_value = calculateFanSpeed(oper_mode, temperature, percent);
  if(oper_mode == MANUAL){
    if(pin_pwm_ != 0){
      analogWrite(pin_pwm_, pwm_value);
      digitalWrite(pin_fan_, HIGH);
    }else{
      analogWrite(pin_fan_, pwm_value);
    }
  }else{
    if(last_pwm_value >= (pwm_value + 5) || pwm_value >= (last_pwm_value + 5)){
      if(pin_pwm_ != 0){
        analogWrite(pin_pwm_, pwm_value);
        digitalWrite(pin_fan_, HIGH);
      }else{
        analogWrite(pin_fan_, pwm_value);
      }
    }
  }
  last_pwm_value = pwm_value;
}

uint8_t Fan::calculateFanSpeed(Operation_Mode_t oper_mode, uint8_t temperature, uint8_t percent){
  int pwm_value;
  switch ( oper_mode )
  {
    case MANUAL:
      pwm_value = map(percent, 0, 100, 101, 255);
      break;
    case SILENT:
      pwm_value = map(temperature, 55, 85, 101, 255);
      break;
    case NORMAL:
      pwm_value = map(temperature, 45, 85, 101, 255); //Com a valor minim de PWM establim 101 ja que sera el valor minim el qual fara que el venmtilador giri minimament
      break;
    case GAMING:
      pwm_value = map(temperature, 35, 75, 101, 255); //Baixam el rang de temperatura per a que s'activi abans ja que es suposa que estirem exigint molt a la computadora
      break;
    default:
      break;
  }
  return pwm_value;
  
}

