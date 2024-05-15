#include "Temp.h"

/*******************************************************************************
 ** Initializations
 ******************************************************************************/

Temp::Temp(uint8_t pin_dtemp, byte sensor1[8], byte sensor2[8], byte sensor3[8])
: pin_data_temp(pin_dtemp), oneWire(pin_data_temp), sensorT(&oneWire){ 

  /*dir_sensor1 = sensor1; //Aquí deberemos pones lad irecciones obtenidas con el otro programa
  dir_sensor2 = sensor2;
  dir_sensor3 = sensor3;*/

  memcpy(dir_sensor1, sensor1, 8);
  memcpy(dir_sensor2, sensor2, 8);
  memcpy(dir_sensor3, sensor3, 8);


}


void Temp::begin()
{
  pinMode(pin_data_temp, INPUT);

  sensorT.begin();
}


void Temp::measureTemp(){
  sensorT.requestTemperatures();

  temp_sensor_1 = sensorT.getTempC(dir_sensor1);
  temp_sensor_2 = sensorT.getTempC(dir_sensor2);
  temp_sensor_3 = sensorT.getTempC(dir_sensor3);
}

float Temp::getTemp(uint8_t dir){
  float send_temp;
  switch(dir){
    case 1:
      send_temp = temp_sensor_1;
      break;
    case 2:
      send_temp = temp_sensor_2;
      break;
    case 3:
      send_temp = temp_sensor_3;
      break;
    default:
      break;
  }
  return send_temp;
}


