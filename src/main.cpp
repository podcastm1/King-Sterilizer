#include <Arduino.h>

const int lampPin = 1; // Sterilizer Lamp
const int doorPin = 0; // Cover Check Button - LOW is open HIGHis close

const int lampTime = 60; //The time of Sterilizer on-time (second)

bool openCheck = true;

void setup() {
    // put your setup code here, to run once:
    pinMode(lampPin, OUTPUT);
    pinMode(doorPin, INPUT);
}

void loop() {
    if (digitalRead(doorPin)) { //when the cover open - HIGH
      openCheck = true;
      digitalWrite(lampPin, LOW); //lamp off
    }

    if (!digitalRead(doorPin)) { //when the cover open - LOW
      if(openCheck == true) {
        openCheck = false;

        for(int count = 0; count <= lampTime; count++) { //loop with waiting 1sec during lampTime
          if (digitalRead(doorPin)) { //when the cover is open during Sterilizer on-time
            digitalWrite(lampPin, LOW);
            break;
          }

          digitalWrite(lampPin, HIGH); //lamp on
          delay(1000); //wait 1sec

          if (count >= lampTime) { //time out check
            digitalWrite(lampPin, LOW); //lamp off
          }
        }
      }
    }
}
