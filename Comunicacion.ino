#include <stdio.h>
#include <ArduinoJson.h>

typedef enum {SILENT, NORMAL, GAMING, MANUAL} Operation_Mode_t;

Operation_Mode_t mode_fan = NORMAL;
float temp_sensor1 = 85.0;
float temp_sensor2 = 80.0;
float temp_sensor3 = 60.0;
volatile uint16_t rpm_fan1 = 1500;
volatile uint16_t rpm_fan2 = 1300;
volatile uint16_t rpm_fan3 = 1200;
volatile uint16_t rpm_fan4 = 1100;
volatile uint16_t rpm_fan5 = 1800;

char data[200];
int data_index = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) continue;
}

void loop() {

  sendData();
  
  //delay(2000);

  /*if((rpm_fan1 + 100 ) <= 2000){
    rpm_fan1 += 100;
  }else{
    rpm_fan1 -= 700;
  }

  if((rpm_fan2 + 100 ) <= 2000){
    rpm_fan2 += 100;
  }else{
    rpm_fan2 -= 700;
  }

  if((rpm_fan3 + 100 ) <= 2000){
    rpm_fan3 += 100;
  }else{
    rpm_fan3 -= 700;
  }

  if((rpm_fan4 + 100 ) <= 2000){
    rpm_fan4 += 100;
  }else{
    rpm_fan4 -= 700;
  }

  if((rpm_fan5 + 100 ) <= 2000){
    rpm_fan5 += 100;
  }else{
    rpm_fan5 -= 700;
  }

  if((temp_sensor1 + 10.0 ) <= 100.0){
    temp_sensor1 += 10.0;
  }else{
    temp_sensor1 -= 70.0;
  }

  if((temp_sensor2 + 10.0 ) <= 100.0){
    temp_sensor2 += 10.0;
  }else{
    temp_sensor2 -= 70.0;
  }

  if((temp_sensor3 + 10.0 ) <= 100.0){
    temp_sensor3 += 10.0;
  }else{
    temp_sensor3 -= 70.0;
  }*/

  /*while(Serial.available() > 0){
    rpm_fan1 = 2000;
    char character = Serial.read();
    if (character != '\n')
    {
      data[data_index] = character;
      data_index ++;
      rpm_fan4++;
    }else{
      Serial.print("El mensaje recibido es: ");
      Serial.println(data);
      //delay(5000);
      rpm_fan2 = 2000;
      receiveData(data, data_index);
      data_index = 0;
    }
  }*/

  // Check if there are any characters available to read
  if(Serial.available() > 0) {
    // Read the incoming byte
    char character = Serial.read();
    // Check if the character is the end of the message ('\n')
    if(character == '\n'){
      // Process the received data
      Serial.print("El mensaje recibido es: ");
      Serial.println(data);
      receiveData(data, data_index);
      // Reset the data index for the next message
      data_index = 0;
    }else{
      // Store the received character in the data buffer
      data[data_index] = character;
      data_index++;
      // Check if the data index exceeds the buffer size to avoid overflow
      if(data_index >= sizeof(data)){
        data_index = sizeof(data) - 1; // Ensure data_index stays within bounds
      }
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
  //char json3[] = {"mode":2,"rpm1":1400,"rpm2":1300,"rpm3":1400,"rpm4":1600,"rpm5":1500}; Formato que funciona para recibir
  char json[index + 1];

  //Amb el seguen bucle el que es vol aconseguir es llevar les comilles de l'inici i del final del string json que genera node red
  for(int i = 0; i < index; i++){
    /*if(data1[i+1] != '}'){
      json[i] = data1[i+1]; // corregir aixo
    }else{
      json[i] = data1[i+1];
      i++;
      json[i] = '\n';
    }*/
    
    json[i] = data1[i];

    /*Serial.print("Indice total: ");
    Serial.println(index);
    Serial.print("Indice: ");
    Serial.print(i);
    Serial.print(" tiene el caracter: ");
    Serial.println(data1[i]);
    delay(200);*/
    
    
  }
  
  for (int j = 0; j < index; j++) {
    if (json[j] == '\0') {
      // Si encontramos un carácter nulo, lo establecemos y salimos del ciclo
      json[j] = '\0';
      break;
    }
  }
  rpm_fan3= 2000;
  /*Serial.print("El mensaje JSON es    : ");
  Serial.println(json2);*/

  /*Serial.print("El mensaje JSON recibido es: ");
  Serial.println(json);
  delay(5000);*/

  DeserializationError error = deserializeJson(doc2, json);

  if (error) {
    /*Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());*/
    return;
  }

  mode_fan = doc2["mode"];
  rpm_fan1 = doc2["pc_rpm1"];
  rpm_fan2 = doc2["pc_rpm2"];
  rpm_fan3 = doc2["pc_rpm3"];
  rpm_fan4 = doc2["pc_rpm4"];
  rpm_fan5 = doc2["pc_rpm5"];



  // Print values.
  Serial.println("Received Data: ");
  Serial.println(mode_fan);
  Serial.println(rpm_fan1);
  Serial.println(rpm_fan2);
  Serial.println(rpm_fan3);
  Serial.println(rpm_fan4);
  Serial.println(rpm_fan5);
  delay(10000);
}
