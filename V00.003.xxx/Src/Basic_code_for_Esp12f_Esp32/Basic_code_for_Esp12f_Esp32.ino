#ifndef _INO_
#define _INO_

#define _INO_DEBUG

#include "BSW/Header_files.h"

String APPL_VER = "V00.000.000";
String SW_Compiled_Date = __DATE__ ;

String VERSION =
//const char VERSION[] PROGMEM =  /*stores in Flash memory*/
"BSW_VER  = " + BSW_VER + "\nAPPL_VER = " + APPL_VER + "\n\nSW_Compiled_Time = "+__TIME__+"\nSW_Compiled_Date = "+__DATE__;

void setup() 
{
  EEPROM.begin(512); 
  OTA_flag = EEPROM.read(OTA_addr);

#ifdef _INO_DEBUG  
  Serial.begin(115200);

 if(OTA_flag)
   Serial.println("\nBOOTING OTA .....!");
 else
   Serial.println("\nBOOTING APPLICATION ....!");
#endif //_INO_DEBUG

  WriteWifiCredentials();
  ReadWifiCredentials();
   
  WIFI_Setup();
  Application_Setup();
  google_sheet_setup();

#ifdef _INO_DEBUG
  Serial.println("**** SW Versions *****");
  Serial.println(VERSION);

  Serial.println(AP_NameChar);
  Serial.println(WiFiPassword);
  Serial.println(ssid);
  Serial.println(password);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif 
 
 if(OTA_flag)
  {
      OTA_Setup();
  }
 else
  {
    MIT_APP_Setup();
  }
  
  local_dns_setup();
  Update_IP_On_Google_Sheet(); // only one time
}



void loop() 
{

  MIT_loop(); /* it will check wifi connected or not in every 20 min */
  local_dns_loop();
  Timer_loop(); // Millis_Timer.h
  
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
