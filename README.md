# CubeServer-api-arduino
[![Maintainability](https://api.codeclimate.com/v1/badges/3637b71abcbcb0d8c30b/maintainability)](https://codeclimate.com/github/snorklerjoe/CubeServer-api-arduino/maintainability)

An arduino-C implementation of the API wrapper for CubeServer

_This currently only supports ESP8266 (It's in development!)_

----------------------------------------------------------------

Example Sketch to demonstrate features
(client_config.h is downloaded from the CubeServer webapp):
``` C++
#include <Arduino.h>
#include <server.h>
#include "client_config.h"

CubeServer server(TEAM_NAME, TEAM_SECRET, SERVER_FINGERPRINT);

int code;
GameStatus stats;

bool connecting_loop() {
  delay(100);
  Serial.print(".");
  return true;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting...");
  code = server.connect(&connecting_loop);
  if(code >= 0)
    Serial.println("Connected!");
  else
    Serial.println("Could not connect to the server.");

  code = server.get_status(&stats);
  if(code == 200)
    Serial.printf("Time: %i; Score: %i; Strikes: %i;\n", stats.unix_time, stats.score, stats.strikes);
  else
    Serial.println("There was an issue connecting to the server.");


  Serial.println("Posting some data:");
  code = server.postHumidity(99.99);
  //code = server.postTemperature(32);
  //code = server.postLightIntensity(12.5);
  //code = server.postPressure(25.2);
  //code = server.postComment("Hello World!");
  if(code == 201)
    Serial.println("Data posted successfully!");
  else
    Serial.println("There was a problem with posting the data.");
}

void loop() {
}
```
