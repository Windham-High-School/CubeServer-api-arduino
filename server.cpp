/*
 * server.cpp
 * Copyright Joseph R. Freeston (MIT License)
 * 
 * API Wrapper for CubeServer
 * 
 */

#include "server.h"

WiFiClientSecure client;
HTTPClient http;

int CubeServer::_begin_client(String path) {
#ifdef ARDUINO_ARCH_ESP32  // ESP32 version only (8266 automatically verifies)--
  client.setInsecure(); // Not an issue since we'll manually verify the certificate:
#else   // ESP8266 version only  (BearSSL)--
  //client.allowSelfSignedCerts();
  client.setX509Time(this->_timestamp);
  client.setFingerprint(this->_server_fingerprint);
#endif
  int connStatus = client.connect(this->_conf.API_HOST, this->_conf.API_PORT);
#ifdef ARDUINO_ARCH_ESP8266
  ++connStatus;
#endif
  if(connStatus > 0) {
#ifdef ARDUINO_ARCH_ESP32  // ESP32 version only (8266 automatically verifies)--
    if(!client.verify(this->_server_fingerprint, this->_conf.API_CN))
      return VERIFICATION_FAILED;
#endif
      // TODO: Make this more efficient by avoiding Strings:
      http.begin(client, String(this->_conf.API_HOST) + ':' + this->_conf.API_PORT + path);
      http.setAuthorization(this->_team_name, this->_team_secret);
      return VERIFICATION_OK;
  }
  return connStatus;
}


CubeServer::CubeServer(const char * team_name, const char * team_secret, const char * server_fingerprint, long unsigned int timestamp, CubeServerConfig conf) {
  this->_team_name = team_name;
  this->_team_secret = team_secret;
  this->_conf = conf;
  this->_server_fingerprint = server_fingerprint;
  this->_timestamp = timestamp;
}

int CubeServer::connect(bool (*connection_wait_loop)()) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(this->_conf.AP_SSID);
  while(WiFi.status() != WL_CONNECTED) {
    if(!connection_wait_loop()) return false;
  }

  return client.connect(this->_conf.API_HOST, this->_conf.API_PORT);
}

bool def_conn_loop() {
  delay(100);
  return true;
}

int CubeServer::connect() {
  return this->connect(&def_conn_loop);
}

int CubeServer::get_status(GameStatus* stats_var) {
  int verification_status = this->_begin_client("/status");
  if(verification_status == VERIFICATION_OK) {
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, http.getStream());
      if(error) {
        http.end();
        return -1;
      }
      stats_var->unix_time = doc["unix_time"];
      stats_var->score = doc["status"]["score"];
      stats_var->strikes = doc["status"]["strikes"];
    }
    http.end();
    return httpCode;
  }
  http.end();
  return verification_status;
}


int CubeServer::post(char *json) {
  int verification_status = this->_begin_client("/data");
  if(verification_status == VERIFICATION_OK) {
    http.addHeader("Content-Type", "application/json", false, true);
    int httpCode = http.POST(json);
    http.end();
    return httpCode;
  }
  http.end();
  return verification_status;
}

int CubeServer::postTemperature(int value) {
  char data[64];
  sprintf(data, "{\"type\": \"temperature\", \"value\": %i}", value);
  return this->post(data);
}
int CubeServer::postTemperature(double value) {
  char data[64];
  sprintf(data, "{\"type\": \"temperature\", \"value\": %f}", value);
  return this->post(data);
}

int CubeServer::postHumidity(int value) {
  char data[64];
  sprintf(data, "{\"type\": \"humidity\", \"value\": %i}", value);
  return this->post(data);
}
int CubeServer::postHumidity(double value) {
  char data[64];
  sprintf(data, "{\"type\": \"humidity\", \"value\": %f}", value);
  return this->post(data);
}

int CubeServer::postPressure(int value) {
  char data[64];
  sprintf(data, "{\"type\": \"pressure\", \"value\": %i}", value);
  return this->post(data);
}
int CubeServer::postPressure(double value) {
  char data[64];
  sprintf(data, "{\"type\": \"pressure\", \"value\": %f}", value);
  return this->post(data);
}

int CubeServer::postLightIntensity(int value) {
  char data[64];
  sprintf(data, "{\"type\": \"light intensity\", \"value\": %i}", value);
  return this->post(data);
}
int CubeServer::postLightIntensity(double value) {
  char data[64];
  sprintf(data, "{\"type\": \"light intensity\", \"value\": %f}", value);
  return this->post(data);
}

int CubeServer::postComment(String value) {  // 32 chars max!
  char data[64];
  sprintf(data, "{\"type\": \"comment\", \"value\": \"%s\"}", value);
  return this->post(data);
}
int CubeServer::postComment(char *value) {
  char data[64];
  sprintf(data, "{\"type\": \"comment\", \"value\": \"%s\"}", value);
  return this->post(data);
}
int CubeServer::postComment(const char *value) {
  char data[64];
  sprintf(data, "{\"type\": \"comment\", \"value\": \"%s\"}", value);
  return this->post(data);
}
