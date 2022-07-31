#include <MKRWAN_v2.h>

LoRaModem modem;

#include "arduino_secrets.h"
String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

bool canResume = false;

String receivedIds[10];

bool isDuplicated = false;

int receivedCount = 0;

#define _DEBUG_

void setup() {
  #ifdef _DEBUG_
    Serial.begin(9600);
    while (!Serial);
  #endif
  
  Serial1.begin(9600);
  while (!Serial1);
  
  if (!modem.begin(AS923)) {
    while (1) {}
  };

  if (!modem.joinOTAA(appEui, appKey)) {
    while (1) {}
  }

  modem.minPollInterval(60);

  for (int i = 0; i < 10; i++) {
    receivedIds[i] = "0000";
  }
}

void loop() {

  while (!Serial1.available());
  
  String userId = Serial1.readStringUntil('\n');

  if (userId.equals("end")) {
    #ifdef _DEBUG_
      Serial.println("Beacon ended sending Data.");
    #endif
    for (int i = 0; i < 10; i++) {
      receivedIds[i] = "0000";
    }
    receivedCount = 0;
    Serial1.print("ack\n");
    #ifdef _DEBUG_
      Serial.println("Sending ack completed");
    #endif
  } else {
    #ifdef _DEBUG_
      Serial.print("Received userId : ");
      Serial.println(userId);
    #endif
    
    receivedCount += 1;

    isDuplicated = false;
    for (int i = 0; i < 10; i++) {
      if(receivedIds[i].equals(userId)) {
        isDuplicated = true;
        break;
      }
    }

    if (!isDuplicated) {
      receivedIds[receivedCount - 1] = userId; 
      int err = 0;
      while (err <= 0) {
        modem.setPort(1);
        modem.beginPacket();
        modem.print(userId);
        err = modem.endPacket(true);
        if (err <= 0) {
          #ifdef _DEBUG_
            Serial.println("Send failed.. Retry sending");
          #endif
          delay(3000);
        } else {
          #ifdef _DEBUG_
            Serial.println("Send Success!");
          #endif
        }
        delay(500);
      } 
    } else {
      #ifdef _DEBUG_
        Serial.println("received Data is Duplicated. Pass sending.");
      #endif
    }
  }  
}
