
#include "Ventilador.h"

/*******************************************************************************
 ** Initializations
 ******************************************************************************/

Ventilador::Ventilador(FanType_t TipoVent, uint8_t pin_rpm, uint8_t pin_fan, uint8_t pin_pwm = 0)
{ 
  FanType = TipoVent;
  pin_revoluciones = pin_rpm;
  pin_pcFan = pin_fan;
  pin_pcPWM = pin_pwm;

  tiempo_inicial = 0;
  tiempo_final = 0;
  tiempo_total = 0;
  ultima_medicionRPM = 0;
  counting  = false;

  pinMode(pin_revoluciones, INPUT);
  pinMode(pin_pcFan, OUTPUT);
  if(pin_pcPWM != 0){
    pinMode(pin_pcPWM, OUTPUT); 
  }
  
}

uint16_t Ventilador::medirRPM(){
  uint16_t revoluciones = 0;
  if(digitalRead(pin_revolciones) == LOW && counting == true){
    tiempo_final = micros();
    counting = false;
    tiempo_total = tiempo_final - tiempo_inicial;

  }else if(digitalRead(pin_revoluciones) == HIGH && counting == false){

    tiempo_inicio = micros();
    start_counting = true;
    
  }
  if(tiempo_total != 0){
    revoluciones = (tiempo_total / (2 * 60));
  }
  return revoluciones;
}

void Ventilador::SetFan(Operation_Mode_t Oper_Mode, Function_Mode_t Func_Mode, uint8_t Temperature, uint8_t last_Temperature, uint8_t percent = 0){
  if(Oper_Mode == AUTOMATIC){
    if(abs(Temperature - last_Temperature >= 5){
      if(Func_Mode == NORMAL){
        PWM_value = map(Temperature, 45, 85, 101, 255); //Com a valor minim de PWM establim 101 ja que sera el valor minim el qual fara que el venmtilador giri minimament
      }else if(Func_Mode == ECO){
        PWM_value = map(Temperature, 55, 85, 101, 255);
      }else if(Func_Mode == GAMING){
        PWM_value = map(Temperature, 35, 75, 101, 255); //Baixam el rang de temperatura per a que s'activi abans ja que es suposa que estirem exigint molt a la computadora
      }
    }
  }else if(Oper_Mode == MANUAL){
    PWM_value = map(percent, 0, 100, 101, 255);
  }
  if(pin_pcPWM != 0){
    analogWrite(pin_pcPWM, PWM_value);
    digitalWrite(pin_pcFan, HIGH);
  }else{
    analogWrite(pin_pcFan, PWM_value);
  }
}

