# CubeServer-api-arduino
[![Maintainability](https://api.codeclimate.com/v1/badges/3637b71abcbcb0d8c30b/maintainability)](https://codeclimate.com/github/snorklerjoe/CubeServer-api-arduino/maintainability)


## :warning: This library is not currently supported :warning:

Only the [Python/CircuitPython API Wrapper](https://github.com/Windham-High-School/CubeServer-api-python) is currently supported for CubeServer.

Perhaps this will be revived in the future, but the demand is too low (very few students are comfortable with C or C++), and I (JRF) seem to be the only one who would maintain it, but I'm graduating and lack the bandwidth.

This library has not been tested since the *early* prerelease versions of CubeServer- there is a lot that is incompatible or unimplemented, as a warning to anyone who thinks they would like to casually fix this guy up. I encourage you to do so (feel free to contact me if you have any questions), but I will note that this is no task for the fainthearted.

:goberserk:





-------------------------------------------------------------------

An arduino-C implementation of the API wrapper for CubeServer

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
This library is intended to support ESP8266 and ESP32 microcontrollers.

This library has only yet been tested on the following boards:
* Adafruit Feather Huzzah ESP8266
* Unexpected Maker Feather S2 (ESP32)


## Installation/Usage:
1. Configure Arduino IDE for the board you are using
    - Go to File > Preferences
    - By "Additional boards manager URLs," paste in the following:
    ```
    https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
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

    CubeServer server(TEAM_NAME, TEAM_SECRET, SERVER_FINGERPRINT);  // Use SERVER_FINGERPRINT_SHA256 on ESP32
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

CubeServer server(TEAM_NAME, TEAM_SECRET, SERVER_FINGERPRINT);  // Use SERVER_FINGERPRINT_SHA256 on ESP32

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
  //code = server.postComment("Hello World!");  // Comments may only be 32 chars long!
  if(code == 201)
    Serial.println("Data posted successfully!");
  else
    Serial.println("There was a problem with posting the data.");
}

void loop() {
}
```
