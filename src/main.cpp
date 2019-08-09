#include <Arduino.h>
#include <ArduinoJson.h>
#include <math.h>

StaticJsonDocument<200> doc;
#define PIN_ENABLE 8
#define PIN_STEP1 2
#define PIN_STEP2 4
#define DIR1 5
#define DIR2 7


void setup() {
  // Initialize serial port
  pinMode(PIN_ENABLE, OUTPUT);
  pinMode(PIN_STEP1, OUTPUT);
  pinMode(PIN_STEP2, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  Serial.begin(9600);
  while (!Serial) continue;
}
void loop() {
   while (Serial.available() > 0){
    digitalWrite(PIN_ENABLE, LOW);
    DeserializationError error = deserializeJson(doc, Serial);
    if (error) {
      Serial.print("deserializeMsgPack() failed: ");
      Serial.println(error.c_str());
      return;
    }
    long motor1 = doc["motor1"];
    boolean dir1 = doc["dir1"];
    long motor2 = doc["motor2"];
    boolean dir2 = doc["dir2"];
    //long motor3 = doc["motor3"];
    //boolean dir3 = doc["dir3"];
    //long motor4 = doc["motor4"];
    //boolean dir4 = doc["dir4"];


    digitalWrite(DIR1,(dir1));
    digitalWrite(DIR2,(dir2));

    motor1 = 2*motor1;
    motor2 = 2*motor2;
    boolean step2 = true;
    boolean step1 = true;



    while(motor1 > 0 || motor2 > 0) {
      if(Serial.available() > 0) {
        error = deserializeJson(doc,Serial);
        long motor1_v2 = doc["motor1"];
        boolean dir1_v2 = doc["dir1"];
        long motor2_v2 = doc["motor2"];
        boolean dir2_v2 = doc["dir2"];

        if(dir1 == dir1_v2) {
          long motor1 = motor1 + 2*motor1_v2;
        } else {
          dir1 = dir1_v2;
          long motor1 = abs(motor1 - 2*motor1_v2);
        }

        if(dir2 == dir2_v2) {
          long motor2 = motor2 + 2*motor2_v2;
        } else {
          dir2 = dir2_v2;
          long motor2 = abs(motor2 - 2*motor2_v2);
        }
      }
      if(motor2 > 0){
        digitalWrite(PIN_STEP2, step2);
        delay(10);
        step2 = !step2;
      }
      if(motor1 > 0){
        digitalWrite(PIN_STEP1, step1);
        delay(10);
        step1 = !step1;
      }

      motor2--;
      motor1--;
    }
    /*if (dir1 == 1)
        digitalWrite(DIR1, HIGH);
    else
        digitalWrite(DIR1, LOW);
    */
    /*
    for(int i = 0; i < motor1; i++){
        digitalWrite(PIN_STEP1, HIGH);
        delay(10);
        digitalWrite(PIN_STEP1, LOW);
        delay(10);
    }*/

    /*if (dir2 == 1)
        digitalWrite(DIR2, HIGH);
    else
        digitalWrite(DIR2, LOW);
    */
    /*
    for(int i = 0; i < motor2; i++){
        digitalWrite(PIN_STEP2, HIGH);
        delay(10);
        digitalWrite(PIN_STEP2, LOW);
        delay(10);
    }*/
    // Print values
    Serial.println(motor1);
    Serial.println(dir1);
    Serial.println(motor2);
    Serial.println(dir2);
    //Serial.println(motor3);
    //Serial.println(dir3);
    //Serial.println(motor4);
    //Serial.println(dir4);

   }
   digitalWrite(PIN_ENABLE, HIGH);
   delay(10);

}
