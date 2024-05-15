#ifndef TEMP_H
#define TEMP_H

#include <Arduino.h>
#include <stdint.h>

#include "OneWire.h"
#include "DallasTemperature.h"

class Temp {
  public:
    // Initializations

    Temp(uint8_t pin_dtemp, byte sensor1[8], byte sensor2[8], byte sensor3[8]);

    // Les inicialitzacions dels pins s'han de fer dins el setup(), poden donar problemes si es fan al constructor ja que s'executarà abans del setup()
    void begin();

    void measureTemp();

    float getTemp(uint8_t dir);

  private:
    // afegeixo _ al final a les variables de classe. Es una pràctica habitual perquè al codi quedi més clar quines són variables de classe i quines no
    // també s'eviten problemes quan els argument s'anomenen igual, com per exemple al constructor
    uint8_t   pin_data_temp;

    byte dir_sensor1[8]; //Aquí deberemos pones lad irecciones obtenidas con el otro programa
    byte dir_sensor2[8];
    byte dir_sensor3[8];

    float temp_sensor_1;
    float temp_sensor_2;
    float temp_sensor_3;

    OneWire oneWire;

    // Pass the oneWire reference to DallasTemperature library:
    DallasTemperature sensorT;

};

#endif

