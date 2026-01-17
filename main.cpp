#include <Arduino.h>

const int PIN_CAR_RED = 25;
const int PIN_CAR_YELLOW = 26;
const int PIN_CAR_GREEN = 27;
const int PIN_PED_RED = 14;
const int PIN_PED_GREEN = 12;

unsigned long timer = 0;

enum State {
  CARS_GO,
  YELLOW,
  PED_GO,
  SAFETY
};

State CURRENT_STATE = CARS_GO;

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_CAR_RED, OUTPUT);
  pinMode(PIN_CAR_YELLOW, OUTPUT);
  pinMode(PIN_CAR_GREEN, OUTPUT);
  pinMode(PIN_PED_RED, OUTPUT);
  pinMode(PIN_PED_GREEN, OUTPUT);
}

void loop() {
  
  switch (CURRENT_STATE) {
    
    case CARS_GO:
      digitalWrite(PIN_CAR_GREEN, HIGH);
      digitalWrite(PIN_PED_RED, HIGH);
      digitalWrite(PIN_CAR_RED, LOW); 
      digitalWrite(PIN_CAR_YELLOW, LOW); 
      digitalWrite(PIN_PED_GREEN, LOW);
      
      if(millis() - timer > 5000) {
        timer = millis();
        CURRENT_STATE = YELLOW;
      }
      break;

    case YELLOW:
      digitalWrite(PIN_CAR_GREEN, LOW);
      digitalWrite(PIN_PED_RED, HIGH);
      digitalWrite(PIN_CAR_RED, LOW); 
      digitalWrite(PIN_CAR_YELLOW, HIGH); 
      digitalWrite(PIN_PED_GREEN, LOW);
      
      if(millis() - timer > 2000) { 
        timer = millis();
        CURRENT_STATE = PED_GO;
      }
      break;

    case PED_GO:
      digitalWrite(PIN_CAR_GREEN, LOW);
      digitalWrite(PIN_PED_RED, LOW);
      digitalWrite(PIN_CAR_RED, HIGH); 
      digitalWrite(PIN_CAR_YELLOW, LOW); 
      digitalWrite(PIN_PED_GREEN, HIGH);
      
      if(millis() - timer > 5000) { 
        timer = millis();
        CURRENT_STATE = SAFETY;
      }
      break;

    case SAFETY:
      digitalWrite(PIN_CAR_GREEN, LOW);
      digitalWrite(PIN_PED_RED, HIGH);
      digitalWrite(PIN_CAR_RED, HIGH); 
      digitalWrite(PIN_CAR_YELLOW, LOW); 
      digitalWrite(PIN_PED_GREEN, LOW);
      
      if(millis() - timer > 2000) { 
        timer = millis();
        CURRENT_STATE = CARS_GO; 
      }
      break;
  } 
}
