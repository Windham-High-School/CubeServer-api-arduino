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
  int connStatus = client.connect(this->_conf.API_HOST, this->_conf.API_PORT);
  if(connStatus >= 0) {
    //if(client.verify(server_fingerprint, this->_conf.API_HOST)) {
      Serial.println(this->_conf.API_HOST + ':' + this->_conf.API_PORT + path);
      http.begin(client, this->_conf.API_HOST + ':' + this->_conf.API_PORT + path);
      http.setAuthorization(this->_team_name, this->_team_secret);
      return VERIFICATION_OK;
    //} return VERIFICATION_FAILED;
  }
  return connStatus;
}


CubeServer::CubeServer(const char * team_name, const char * team_secret, const char * server_fingerprint, long unsigned int timestamp, CubeServerConfig conf) {
  this->_team_name = team_name;
  this->_team_secret = team_secret;
  this->_conf = conf;
  client.setX509Time(timestamp);  // Use the build timestamp since we don't have NTP access
  client.setFingerprint(server_fingerprint);
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
      Serial.println("getString...");
      String payload = http.getString();
      Serial.println(payload);
      Serial.println("Making json doc...");
      StaticJsonDocument<128> doc;
      Serial.println("Deserializing...");
      DeserializationError error = deserializeJson(doc, payload);
      Serial.println("Splitting...");
      Serial.println("Time...");
      stats_var->unix_time = doc["unix_time"].as<int>();
      Serial.println(doc["unix_time"].as<int>());
      Serial.println("Score as int...");
      stats_var->score = doc["status"]["score"].as<int>();
      Serial.println("Strikes as int...");
      stats_var->strikes = doc["status"]["strikes"].as<int>();
    }
      Serial.println("Closing...");
    http.end();
    return httpCode;
  }
  return verification_status;
}

//    // get status:
//    GameStatus status();

