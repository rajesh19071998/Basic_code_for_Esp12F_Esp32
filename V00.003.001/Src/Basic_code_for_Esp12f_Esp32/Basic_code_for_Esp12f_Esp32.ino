#ifndef _INO_
#define _INO_

//#define _INO_DEBUG

#include "BSW/Header_files.h"

const String APPL_VER = "V00.000.000";


String VERSION =
//const char VERSION[] PROGMEM =  /*stores in Flash memory*/
"BSW_VER  = " + BSW_VER + "\nAPPL_VER = " + APPL_VER + "\n\nSW_Compiled_Time = "+__TIME__+"\nSW_Compiled_Date = "+__DATE__;

void setup() {
#ifdef _INO_DEBUG  
 Serial.begin(115200);
#endif 
 EEPROM.begin(512); 

 WIFI_Setup();
 Application_Setup();

#ifdef _INO_DEBUG
  Serial.println("**** SW Versions *****");
  Serial.println(VERSION);

  Serial.println(AP_NameChar);
  Serial.println(WiFiPassword);
  Serial.println(ssid);
  Serial.println(password);
#endif 

  WriteWifiCredentials();
 
  ReadWifiCredentials();   
 
  OTA_flag = EEPROM.read(OTA_addr);
 
 if(OTA_flag)
  {
      OTA_Setup();
  }
 else
  {
    MIT_APP_Setup();
    google_sheet_setup();
#ifdef _INO_DEBUG    
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
#endif    
  }
  
  local_dns_setup();
}




void loop() {

  MIT_loop(); /* it will check wifi connected or not in every 20 min */
  local_dns_loop();
  Timer_loop(); // Millis_Timer.h
  Update_IP_On_Google_Sheet(); // only one time
  
  if(OTA_flag)
  {
     OTA_loop();
  }
  else
  {
    Application_loop();
  } 

}



#endif //_INO_
