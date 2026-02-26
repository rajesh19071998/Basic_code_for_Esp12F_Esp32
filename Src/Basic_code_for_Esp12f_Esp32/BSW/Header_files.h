#ifndef _HEADER_FILES_H
#define _HEADER_FILES_H


const String BSW_VER  = "V00.004.000"; // Date : 25-02-2026

String SW_Compiled_Date = __DATE__ ;
String SW_Compiled_Time = __TIME__ ;

extern String APPL_VER; // Application_var.h

String VERSION = "";

/* Board specific libraries */
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
  #include <ESPAsyncTCP.h>
  #include <ESP8266mDNS.h>
  #include <ESP8266HTTPClient.h>

#elif defined(ESP32)
  #include <WiFi.h> 
  #include <AsyncTCP.h>
  #include "LittleFS.h"
  #include <WiFiClient.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
  #include <HTTPClient.h>
#endif

/* Common libraries */

#include <EEPROM.h> 
#include <Arduino_JSON.h> // website.h
#include <WiFiClientSecure.h> //google sheets
#include <ElegantOTA.h>
#include <ESPAsyncWebServer.h>


#define BSW_TIMERS 4 // BSW using first 4 timers

/* timer init */

#define OTA_TIMER         0 // 10 min
#define G_SHEET_TIMER     1 //  6 sec 
#define WIFI_CHECK_TIMER  2 // 20 min
#define SLEEP_TIMER1      3 // 5 sec timer

/* timer delay in seconds*/
#define OTA_DELAY_SEC        600   // 10 min
#define G_SHEET_DELAY_SEC    6     // 6 sec
#define SLEEP1_DELAY_SEC     5     // 5 sec 
int     WIFI_CHECK_DELAY_SEC = 1200 ; // 20 min 

/* Common Macros */
#define OFF          0
#define ON           1
#define DISABLE      0
#define ENABLE       1
#define DISCONNECTED 0
#define CONNECTED    1
#define DISCONNECT   0
#define CONNECT      1

/* Basic Local files */

#include "../PIN_CONFIG.h"
#include "Millis_Timer.h"
#include "../WIFI_CONFIG.h"
#include "Wifi_functions.h"
#include "MIT_APP.h"
#include "local_DNS.h"
#include "google_sheet.h"
#include "web_site.h"
#include "OTA_V5.h"
#include "http_url.h"
#include "../Application_var.h"
#include "../Appl_Header_files.h"
#include "../Application_functions.h"



#endif //_HEADER_FILES_H