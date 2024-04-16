
#include <Arduino.h>
#include <stdint.h>

#ifndef Ventilador_H
#define Ventilador_H

typedef enum {ThreePins, FourPins_Soft, FourPins_Hard} FanType_t;
typedef enum {MANUAL, AUTOMATIC} Operation_Mode_t;
typedef enum {NORMAL, ECO, GAMING} Function_Mode_t;


class Ventilador {
  public:
    // Initializations

    Ventilador(FanType_t TipoVent, uint8_t pin_rpm, uint8_t pin_fan, uint8_t pin_pwm = 0);

    uint16_t medirRPM();

    
    void SetFan(Operation_Mode_t Oper_Mode, Function_Mode_t Func_Mode, uint8_t Temperature, uint8_t last_Temperature, uint8_t percent = 0);
    
    

  private:
    FanType_t FanType;
    uint8_t pin_revoluciones;
    uint8_t pin_pcFan;
    uint8_t pin_pcPWM;

    uint16_t tiempo_inicial;
    uint16_t tiempo_final;
    uint16_t tiempo_total;
    uint16_t ultima_medicionRPM;
    bool counting;
};

#endif
