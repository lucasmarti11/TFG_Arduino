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

  sendData();
  
  while(Serial.available() > 0){
    char character = Serial.read();
    if (character != '\n')
    {
      data[data_index] = character;
      data_index ++;
    }else if(!Serial.available()){
      Serial.print("El mensaje recibido es: ");
      Serial.println(data);
      receiveData(data, data_index);
      data_index = 0;
    }
  }
}

void sendData(){
  StaticJsonDocument<200> doc1;
  
  doc1["Temp1"] = temp_sensor1;
  doc1["Temp2"] = temp_sensor2;
  doc1["Temp3"] = temp_sensor3;
  doc1["rpm1"] = rpm_fan1;
  doc1["rpm2"] = rpm_fan2;
  doc1["rpm3"] = rpm_fan3;  
  doc1["rpm4"] = rpm_fan4;
  doc1["rpm5"] = rpm_fan5;

  serializeJson(doc1, Serial);

  Serial.println();
}

void receiveData(char* data1, int index){

   StaticJsonDocument<300> doc2;

  //char json2[] = "{\"mode\":2,\"rpm1\":1400,\"rpm2\":1300,\"rpm3\":1400,\"rpm4\":1600,\"rpm5\":1500}"; Formato que no funciona
  //char json3[] = {"mode":2,"rpm1":1400,"rpm2":1300,"rpm3":1400,"rpm4":1600,"rpm5":1500}; Formato que funciona para recibir
  char json[index + 1];

  
  for(int i = 0; i < index; i++){
    json[i] = data1[i];
  }
  for (int j = 0; j < index; j++) {
    if (json[j] == '\0') {
      // Si encontramos un carácter nulo, lo establecemos y salimos del ciclo
      json[j] = '\0';
      break;
    }
  }

  /*Serial.print("El mensaje JSON es    : ");
  Serial.println(json2);*/


  DeserializationError error = deserializeJson(doc2, json);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  mode_fan = doc2["mode"];
  rpm_fan1 = doc2["rpm1"];
  rpm_fan2 = doc2["rpm2"];
  rpm_fan3 = doc2["rpm3"];
  rpm_fan4 = doc2["rpm4"];
  rpm_fan5 = doc2["rpm5"];

  // Print values.
  Serial.println("Received Data: ");
  Serial.println(mode_fan);
  Serial.println(rpm_fan1);
  Serial.println(rpm_fan2);
  Serial.println(rpm_fan3);
  Serial.println(rpm_fan4);
  Serial.println(rpm_fan5);
}
