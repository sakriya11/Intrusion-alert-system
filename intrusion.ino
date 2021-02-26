#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 

char auth[] = "026dhuvFlbAOoTpuVzN7s4J4MEzb_t8Z"; //Blynk auth token
char ssid[] = "Samsungs10"; // WIFI Name
char pass[] = "nepal123"; // WIFI Password

 

int Buzzer=D1;
int IR_sensor = D0;
int object_detected;
int led=D3;

 

BlynkTimer timer;

 


void notifyOnObjectRemove(){
  object_detected=digitalRead(IR_sensor);
  Serial.println(object_detected);
  if(object_detected==0){ 
    Serial.println("object is in place");
    digitalWrite(Buzzer,LOW);
    digitalWrite(led,LOW);
    
  }else{
    
    Serial.println("object removed..!take action");
    Blynk.notify("alert: object removed");
    digitalWrite(Buzzer,HIGH);
    digitalWrite(led,HIGH);
    delay(500);
    
  }
}

 


void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(Buzzer, OUTPUT);
  pinMode(IR_sensor, INPUT_PULLUP);
  pinMode(led,OUTPUT);
  timer.setInterval(1000L, notifyOnObjectRemove);

 


}

 

void loop() {
  Blynk.run();
  timer.run();
}
