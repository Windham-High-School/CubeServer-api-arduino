/*
 * server.h
 * Copyright Joseph R. Freeston (MIT License)
 * 
 * API Wrapper for CubeServer
 * 
 */

#ifndef CUBESERVER_SERVER_H
#define CUBESERVER_SERVER_H

#include <Arduino.h>

#ifdef ARDUINO_ARCH_ESP8266  // ESP8266 version--
# include <ESP8266WiFi.h>
# include <ESP8266HTTPClient.h>
#elif ARDUINO_ARCH_ESP32  // ESP32 version--
#include <WiFi.h>
#include <HTTPClient.h>
#else
# error "Unsupported Architecture."
#endif

#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#include "server_options.h"

#include "compile_time.h"


#define VERIFICATION_OK 1
#define VERIFICATION_FAILED -1



extern WiFiClientSecure client;
extern HTTPClient http;

typedef struct CubeServerConfig {
  const char *AP_SSID;
  const char *API_CN;
  const char *API_HOST;
  int API_PORT;
} CubeServerConfig;


const CubeServerConfig CUBESERVER_DEFAULT_CONFIG = {
  "CubeServer-API",
  "api.local",
  "https://api.local",
  8081
};


typedef struct GameStatus {
  unsigned long int unix_time;
  int score;
  int strikes;
} GameStatus;

class CubeServer {
  private:
    const char * _team_name;
    const char * _team_secret;
    CubeServerConfig _conf;
    const char *_server_fingerprint;
    unsigned int _timestamp;


    int _begin_client(String path);

  public:
    CubeServer(const char * team_name, const char * team_secret, const char * server_fingerprint, long unsigned int timestamp, CubeServerConfig conf);
    CubeServer(const char * team_name, const char * team_secret, const char * server_fingerprint, CubeServerConfig conf) : CubeServer(team_name, team_secret, server_fingerprint, UNIX_TIMESTAMP, CUBESERVER_DEFAULT_CONFIG) {};
    CubeServer(const char * team_name, const char * team_secret, const char * server_fingerprint) : CubeServer(team_name, team_secret, server_fingerprint, CUBESERVER_DEFAULT_CONFIG) {};

#ifdef CLIENT_CONF_H
#ifdef ARDUINO_ARCH_ESP32  // Only ESP32 can handle the sha256 fingerprint:
  CubeServer() : CubeServer(TEAM_NAME, TEAM_SECRET, SERVER_FINGERPRINT_SHA256) {};
#else
  CubeServer() : CubeServer(TEAM_NAME, TEAM_SECRET, SERVER_FINGERPRINT) {};
#endif
#endif

    // connect to the wifi access point:
    int connect(bool (*connection_wait_loop)());
    int connect();

    // get status:
    int get_status(GameStatus* stats_var);

    // post some data:
    int post(char *json);

    int postTemperature(int value);
    int postTemperature(double value);

    int postHumidity(int value);
    int postHumidity(double value);

    int postPressure(int value);
    int postPressure(double value);

    int postLightIntensity(int value);
    int postLightIntensity(double value);

    int postComment(String value);
    int postComment(char *value);
    int postComment(const char *value);

};


#endif

