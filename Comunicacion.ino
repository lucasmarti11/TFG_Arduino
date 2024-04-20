#include <stdio.h>
#include <ArduinoJson.h>

typedef enum {SILENT, NORMAL, GAMING, MANUAL} Operation_Mode_t;

Operation_Mode_t mode_fan = NORMAL;
float temp_sensor1 = 85.0;
float temp_sensor2 = 80.0;
float temp_sensor3 = 60.0;
uint16_t rpm_fan1 = 1500;
uint16_t rpm_fan2 = 1300;
uint16_t rpm_fan3 = 1200;
uint16_t rpm_fan4 = 1100;
uint16_t rpm_fan5 = 1800;

char data[200];
int data_index = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) continue;
}

void loop() {

  //sendData();
  
  while(Serial.available() > 0){
    char character = Serial.read();
    if (character != '}')
    {
      data[data_index] = character;
      data_index ++;
    }else{
      data[data_index] = character;
      data_index ++;
      Serial.print("El mensaje recibido es: ");
      Serial.println(data);
      receiveData(data, data_index);
    }
  }
}

void sendData(){
  StaticJsonDocument<200> doc;
  
  doc["Temp1"] = temp_sensor1;
  doc["Temp2"] = temp_sensor2;
  doc["Temp3"] = temp_sensor3;
  doc["rpm1"] = rpm_fan1;
  doc["rpm2"] = rpm_fan2;
  doc["rpm3"] = rpm_fan3;  
  doc["rpm4"] = rpm_fan4;
  doc["rpm5"] = rpm_fan5;

  serializeJson(doc, Serial);

  Serial.println();
}

void receiveData(char* data1, int index){

   StaticJsonDocument<200> doc;

  //char json[] = "{\"mode\":2,\"rpm1\":1400,\"rpm2\":1300,\"rpm3\":1400,\"rpm4\":1600,\"rpm5\":1500}";

  char json[index + 1];

  
  for(int i = 0; i < index; i++){
    json[i] = data1[i];
  }
  json[index] = '\0'; 

  DeserializationError error = deserializeJson(doc, data1);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  mode_fan = doc["mode"];
  rpm_fan1 = doc["rpm1"];
  rpm_fan2 = doc["rpm2"];
  rpm_fan3 = doc["rpm3"];
  rpm_fan4 = doc["rpm4"];
  rpm_fan5 = doc["rpm5"];

  // Print values.
  Serial.println("Received Data: ");
  Serial.println(mode_fan);
  Serial.println(rpm_fan1);
  Serial.println(rpm_fan2);
  Serial.println(rpm_fan3);
  Serial.println(rpm_fan4);
  Serial.println(rpm_fan5);
}
