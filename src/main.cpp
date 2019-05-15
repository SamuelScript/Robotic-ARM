#include <Arduino.h>
#include <ArduinoJson.h>

StaticJsonDocument<200> doc;
#define PIN_ENABLE 8
#define PIN_STEP 2

void setup() {
  // Initialize serial port
  pinMode(PIN_ENABLE, OUTPUT);
  pinMode(PIN_STEP, OUTPUT);
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
    long motor2 = doc["motor2"];
    long motor3 = doc["motor3"];

    for(int i = 0; i < motor1; i++){
        digitalWrite(PIN_STEP, HIGH);
        delay(10);
        digitalWrite(PIN_STEP, LOW);
        delay(10);
    }
    // Print values
    Serial.println(motor1);
    Serial.println(motor2);
    Serial.println(motor3);
   }
   digitalWrite(PIN_ENABLE, HIGH);
   delay(10);
}
