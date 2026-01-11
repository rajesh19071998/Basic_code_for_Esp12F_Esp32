#ifndef _HEADER_FILES_H
#define _HEADER_FILES_H

/* Board specific libraries */
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
  #include <ESPAsyncTCP.h>
  #include <ESP8266mDNS.h>

#elif defined(ESP32)
  #include <WiFi.h> 
  #include <AsyncTCP.h>
  #include "LittleFS.h"
  #include <WiFiClient.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
#endif

/* Common libraries */

#include <EEPROM.h> 
#include <Arduino_JSON.h> // website.h
#include <WiFiClientSecure.h> //google sheets
#include <ElegantOTA.h>
#include <ESPAsyncWebServer.h>



/* max timers */
#define MAX_TIMERS 5

/* timer init */

#define OTA_TIMER         0 // 10 min
#define G_SHEET_TIMER     1 //  6 sec 
#define WIFI_CHECK_TIMER  2 // 20 min
#define SLEEP_TIMER1      3 // 5 sec timer

/* timer delay in seconds*/
#define OTA_DELAY_SEC        600   // 10 min
#define G_SHEET_DELAY_SEC    6     // 6 sec
#define SLEEP1_DELAY_SEC     5     // 5 sec 
#define WIFI_CHECK_DELAY_SEC 1200  // 20 min









/* Basic Local files */

#include "Millis_Timer.h"
#include "PIN_CONFIG.h"
#include "WIFI_CONFIG.h"
#include "Wifi_functions.h"
#include "MIT_APP.h"
#include "local_DNS.h"
#include "google_sheet.h"
#include "web_site.h"
#include "OTA_V5.h"
#include "Application_var.h"
#include "Application_functions.h"



#endif //_HEADER_FILES_H