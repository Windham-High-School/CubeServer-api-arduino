# CubeServer-api-arduino
[![Maintainability](https://api.codeclimate.com/v1/badges/3637b71abcbcb0d8c30b/maintainability)](https://codeclimate.com/github/snorklerjoe/CubeServer-api-arduino/maintainability)

An arduino-C implementation of the API wrapper for CubeServer

_This currently only supports ESP8266 (It's in development!)_

Minimum code to post a temperature value of 32 degrees F every 10 minutes:
``` C++
#include <Arduino.h>
#include <server.h>

CubeServer server;

void setup() {
  server.connect();
}

void loop() {
  server.postTemperature(32);
  delay(600000);
}

```

## Supported devices
This library currently supports only ESP8266 devices, with support coming soon for esp32.
This library has only yet been tested on the following devices:
* Adafruit Feather Huzzah ESP8266


## Installation/Usage:
1. Configure Arduino IDE for the board you are using
    - Go to File > Preferences
    - By "Additional boards manager URLs," paste in the following:
    ```
    https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
    ```
    - Click "ok"
    - Go to Tools > Board > Boards Manager
    - Search for "esp8266" or "esp32" depending on the microcontroller you are using
    - Install the package for the microcontroller you are using
    - Under Tools > Board, select the microcontroller board you are using
2. Install ArduinoJson
    - Go to Sketch > Include Library > Manage Libraries
    - Search "ArduinoJson"
    - Click "Install" underneath the item titled "ArduinoJson"
3. If you have registered your team with the CubeServer webapp, download the zip file that it provides. Otherwise, download the latest zip file of the library from the [releases page](https://github.com/snorklerjoe/CubeServer-api-arduino/releases).
4. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library and select the file you downloaded.
5. If you downloaded the library from the webapp, that's it! Try out the basic example above to get started. Otherwise, you will need to download the client_config.h file from the server, add that file to your sketch, and use the following code to initialize the connection with the server:
    ``` C++
    #include <Arduino.h>
    #include <server.h>
    #include "client_config.h"

    CubeServer server(TEAM_NAME, TEAM_SECRET, SERVER_FINGERPRINT);
    ```
      instead of:

      ``` C++
      #include <Arduino.h>
      #include <server.h>
      CubeServer server;
      ```

----------------------------------------------------------------

## More Examples:
(client_config.h is downloaded from the CubeServer webapp):

Advanced features demonstrated:
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
