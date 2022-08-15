/*
 * board_utils.h
 * Copyright Joseph R. Freeston (MIT License)
 * 
 * Some utilities that assist with the portability of this library
 * 
 */



#ifndef CUBESERVER_BOARD_UTILS_H
#define CUBESERVER_BOARD_UTILS_H

// ESP8266 or ESP32?
// (From the latest boards.txt files as of 08-14-22)

#if \
    defined(ESP8266_GENERIC) || \
    defined(ESP8266_ESP01) || \
    defined(GEN4_IOD) || \
    defined(ESP8266_ADAFRUIT_HUZZAH) || \
    defined(AMPERKA_WIFI_SLOT) || \
    defined(ESP8266_ARDUINO) || \
    defined(ESP8266_ARDUINO_PRIMO) || \
    defined(ESP8266_ARDUINO_STAR_OTTO) || \
    defined(ESP8266_ARDUINO_UNOWIFI) || \
    defined(ESP8266_ESP01) || \
    defined(ESP8266_OAK) || \
    defined(ESP8266_ESP13) || \
    defined(ESP8266_ESPECTRO_CORE) || \
    defined(ESP8266_ESPINO_ESP12) || \
    defined(ESP8266_ESPRESSO_LITE_V1) || \
    defined(ESP8266_ESPRESSO_LITE_V2) || \
    defined(ESP8266_SONOFF_SV) || \
    defined(ESP8266_SONOFF_BASIC) || \
    defined(ESP8266_SONOFF_S20) || \
    defined(ESP8266_SONOFF_SV) || \
    defined(ESP8266_SONOFF_TH) || \
    defined(ESP8266_INVENT_ONE) || \
    defined(ESP8266_WEMOS_D1MINI) || \
    defined(ESP8266_WEMOS_D1MINI) || \
    defined(ESP8266_WEMOS_D1MINILITE) || \
    defined(ESP8266_WEMOS_D1MINIPRO) || \
    defined(ESP8266_WEMOS_D1R1) || \
    defined(ESP8266_AGRUMINO_LEMON_V4) || \
    defined(ESP8266_NODEMCU_ESP12) || \
    defined(ESP8266_NODEMCU_ESP12E) || \
    defined(MOD_WIFI_ESP8266) || \
    defined(ESP8266_PHOENIX_V1) || \
    defined(ESP8266_PHOENIX_V2) || \
    defined(ESP8266_SCHIRMILABS_EDUINO_WIFI) || \
    defined(ESP8266_WIO_LINK) || \
    defined(ESP8266_THING) || \
    defined(ESP8266_THING_DEV) || \
    defined(ESP8266_ESP210) || \
    defined(ESP8266_ESPINO_ESP13) || \
    defined(wifi_kit_8) || \
    defined(WIFIDUINO_ESP8266) || \
    defined(WIFINFO) || \
    defined(ESP8266_ESP07) || \
    defined(ESP8266_ESP12) || \
    defined(ESP8266_XINABOX_CW01)
#define SOC_ESP8266
#error "Yolodude"
#elif \
    defined(ESP32C3_DEV) || \
    defined(ESP32S2_DEV) || \
    defined(ESP32_DEV) || \
    defined(ESP32_WROOM_DA) || \
    defined(ESP32_DEV) || \
    defined(ESP32_PICO) || \
    defined(ESP32_S3_BOX) || \
    defined(ESP32_S3_USB_OTG) || \
    defined(ESP32S3_CAM_LCD) || \
    defined(ESP32S2_USB) || \
    defined(ESP32_WROVER_KIT) || \
    defined(TINYPICO) || \
    defined(FEATHERS2) || \
    defined(FEATHERS2NEO) || \
    defined(TINYS2) || \
    defined(RMP) || \
    defined(TINYS3) || \
    defined(PROS3) || \
    defined(FEATHERS3) || \
    defined(ESP32_DEV) || \
    defined(MICROS2) || \
    defined(ESP32_DEV) || \
    defined(ESP32_PICO) || \
    defined(TTGO_LoRa32) || \
    defined(TTGO_LoRa32_V1) || \
    defined(TTGO_LoRa32_V2) || \
    defined(TTGO_LoRa32_v21new) || \
    defined(TTGO_T1) || \
    defined(TTGO_T7_V13_Mini32) || \
    defined(TTGO_T7_V14_Mini32) || \
    defined(TTGO_T_OI_PLUS_DEV) || \
    defined(ESP32_DEV) || \
    defined(ESP32_THING) || \
    defined(ESP32_THING_PLUS) || \
    defined(ESP32_THING_PLUS_C) || \
    defined(ESP32S2_THING_PLUS) || \
    defined(ESP32_MICROMOD) || \
    defined(ESP32_DEV) || \
    defined(ESP32_IOT_REDBOARD) || \
    defined(UBLOX_NINA_W10) || \
    defined(WIDORA_AIR) || \
    defined(ESP320) || \
    defined(NANO32) || \
    defined(LOLIN_D32) || \
    defined(LOLIN_D32_PRO) || \
    defined(LOLIN_C3_MINI) || \
    defined(LOLIN_S2_MINI) || \
    defined(LOLIN_S2_PICO) || \
    defined(LOLIN_S3) || \
    defined(LOLIN32) || \
    defined(LOLIN32_LITE) || \
    defined(Pocket32) || \
    defined(Pocket32) || \
    defined(ESPea32) || \
    defined(QUANTUM) || \
    defined(Node32s) || \
    defined(HORNBILL_ESP32_DEV) || \
    defined(HORNBILL_ESP32_MINIMA) || \
    defined(DFROBOT_BEETLE_ESP32_C3) || \
    defined(ESP32C3_DEV) || \
    defined(ESP32S3_DEV) || \
    defined(DFROBOT_FIREBEETLE_2_ESP32S3) || \
    defined(ESP32_DEV) || \
    defined(INTOROBOT_ESP32_DEV) || \
    defined(ONEHORSE_ESP32_DEV) || \
    defined(FEATHER_ESP32) || \
    defined(METRO_ESP32S2) || \
    defined(MAGTAG29_ESP32S2) || \
    defined(FUNHOUSE_ESP32S2) || \
    defined(ADAFRUIT_FEATHER_ESP32S2) || \
    defined(ADAFRUIT_FEATHER_ESP32S2_TFT) || \
    defined(ADAFRUIT_QTPY_ESP32S2) || \
    defined(ADAFRUIT_QTPY_ESP32C3) || \
    defined(ADAFRUIT_QTPY_ESP32_PICO) || \
    defined(ADAFRUIT_FEATHER_ESP32_V2) || \
    defined(ADAFRUIT_FEATHER_ESP32S3) || \
    defined(ADAFRUIT_FEATHER_ESP32S3_NOPSRAM) || \
    defined(ADAFRUIT_FEATHER_ESP32S3_TFT) || \
    defined(ADAFRUIT_QTPY_ESP32S3_NOPSRAM) || \
    defined(NodeMCU_32S) || \
    defined(MH_ET_LIVE_ESP32DEVKIT) || \
    defined(MH_ET_LIVE_ESP32MINIKIT) || \
    defined(esp32vn_iot_uno) || \
    defined(ESP32_DEV) || \
    defined(ESP32_DEV) || \
    defined(ESP32_EVB) || \
    defined(ESP32_GATEWAY) || \
    defined(ESP32_GATEWAY_C) || \
    defined(ESP32_GATEWAY_E) || \
    defined(ESP32_GATEWAY_F) || \
    defined(ESP32_POE) || \
    defined(ESP32_POE_ISO) || \
    defined(ESP32_DEVKIT_LIPO) || \
    defined(ESPino32) || \
    defined(M5Stack_Core_ESP32) || \
    defined(M5STACK_FIRE) || \
    defined(M5Stick_C) || \
    defined(M5Stack_ATOM) || \
    defined(M5STACK_Core2) || \
    defined(M5Stack_Timer_CAM) || \
    defined(M5Stack_CoreInk) || \
    defined(ODROID_ESP32) || \
    defined(heltec_wifi_kit_32) || \
    defined(heltec_wifi_lora_32) || \
    defined(heltec_wifi_lora_32_V2) || \
    defined(heltec_wireless_stick) || \
    defined(heltec_wireless_stick_LITE) || \
    defined(ESPECTRO32) || \
    defined(CoreESP32) || \
    defined(ALKS) || \
    defined(WIPY3) || \
    defined(WT32_ETH01) || \
    defined(BPI_BIT) || \
    defined(WESP32) || \
    defined(TBeam) || \
    defined(D_Duino_32) || \
    defined(LoPy) || \
    defined(LoPy4) || \
    defined(OROCA_EDUBOT) || \
    defined(fm_devkit) || \
    defined(FROG_ESP32) || \
    defined(ESP32_DEV) || \
    defined(TWatch) || \
    defined(TWATCH_BASE) || \
    defined(TWATCH_2020_V1) || \
    defined(TWATCH_2020_V2) || \
    defined(TWATCH_2020_V3) || \
    defined(D1_MINI32) || \
    defined(D1_UNO32) || \
    defined(PYCOM_GPY) || \
    defined(ESP32_DEV) || \
    defined(HONEYLEMON) || \
    defined(MGBOT_IOTIK32A) || \
    defined(MGBOT_IOTIK32B) || \
    defined(Piranha) || \
    defined(Metro) || \
    defined(sensesiot_weizen) || \
    defined(ESP32_PICO) || \
    defined(ESP32_DEV) || \
    defined(openkb) || \
    defined(Wifiduino32) || \
    defined(IMBRIOS_LOGSENS_V1P1) || \
    defined(HEALTHYPI_4) || \
    defined(ET_Board) || \
    defined(DENKY) || \
    defined(DENKY_PICOV3) || \
    defined(DENKY_WROOM32) || \
    defined(uPesy_WROVER) || \
    defined(uPesy_WROOM) || \
    defined(ESP32_DEV) || \
    defined(DYDK) || \
    defined(Trueverit_ESP32_Universal_IoT_Driver) || \
    defined(Trueverit_ESP32_Universal_IoT_Driver_MK_II) || \
    defined(atmegazero_esp32s2) || \
    defined(DYM) || \
    defined(FRANZININHO_WIFI) || \
    defined(FRANZININHO_WIFI_MSC) || \
    defined(DPU_ESP32) || \
    defined(SONOFF_DUALR3) || \
    defined(Bit_Dev_Board) || \
    defined(WATCHY) || \
    defined(WATCHY_V10) || \
    defined(WATCHY_V15) || \
    defined(WATCHY_V20) || \
    defined(DYDK1A) || \
    defined(AirM2M_CORE_ESP32C3) || \
    defined(XIAO_ESP32C3) || \
    defined(connaxio_espoir) || \
    defined(ESP32_PICO) || \
    defined(DEPARTMENT_OF_ALCHEMY_MINIMAIN_ESP32S2) || \
    defined(BeeMotionS3) || \
    defined(Bee_Motion) || \
    defined(Bee_Motion_Mini) || \
    defined(Bee_S3) || \
    defined(FEATHER_ESP32) || \
    defined(unphone8) || \
    defined(unphone9)
# define SOC_ESP32
#else
#ifdef ESP8266_ADAFRUIT_HUZZAH
# error "Huh?"
#endif
#error "Unsupported platform."
#endif

#endif

