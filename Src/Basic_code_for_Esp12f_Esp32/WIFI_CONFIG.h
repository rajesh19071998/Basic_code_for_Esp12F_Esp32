#ifndef _WIFI_CONFIG_H
#define _WIFI_CONFIG_H

#if defined(ESP8266)
  String BOARD_NUMBER = "100";
  String BOARD_NAME = "ESP12F_BASIC";
  String Local_DNS_Name = "esp12f";
  String  AP_NameChar = "ESP12F_BASIC" ;
  String MODULE_TYPE = "ESP12F" ;

#elif defined(ESP32)
  String BOARD_NUMBER = "100";
  String BOARD_NAME = "ESP32_BASIC";
  String Local_DNS_Name = "esp32";
  String  AP_NameChar = "ESP32_BASIC" ;
  String MODULE_TYPE = "ESP32" ;
#endif

String WiFiPassword = "123456789";

String     ssid = "RajeshJioFiber";
String password = "Rajesh@1998";
/*
String     ssid = "Rajesh iPhone";
String password = "123456789";
*/

String WIFI_HOTSPOT_MODE = "BOTH"; // WIFI / HOTSPOT / BOTH 
String Global_IP = "https://basic.rajeshv.in";


String STATIC_IP = "";
String GATEWAY_IP = "";

/*
String STATIC_IP = "192.168.31.181";
String GATEWAY_IP = "192.168.31.1";
*/




#endif //_WIFI_CONFIG_H
