#ifndef _INO_
#define _INO_

#define _INO_DEBUG
#define _G_DEBUG
#define MIT_DEBUG

#include "BSW/Header_files.h"

void setup() 
{
  EEPROM.begin(512); 
  OTA_flag = EEPROM.read(OTA_addr);

#ifdef _INO_DEBUG  
  Serial.begin(115200);
#endif //_INO_DEBUG

  WriteWifiCredentials();
  ReadWifiCredentials();
   
  WIFI_Setup();
  Application_Setup();
  
 if(OTA_flag == ENABLE)
  {
      OTA_Setup();
  }
 else
  {
    MIT_APP_Setup();
  }
  
  local_dns_setup();
  delay(100);

  if(WIFI_Status == CONNECTED)
  {
     google_sheet_setup();
     Update_IP_On_Google_Sheet(); // only one time
  }   

  //wifi_ckeck_delay_update(600); // every 600 sec= 10 MIN , check wifi
  String responce = http_url("http://sw1.rajeshv.in/info");
  Serial.println("http://sw1.rajeshv.in/info -> Rsponce");
  Serial.println(responce);
}



void loop() 
{

  MIT_loop(); /* it will check wifi connected or not in every 20 min */
  local_dns_loop();
  Timer_loop(); // Millis_Timer.h
  
  if(OTA_flag == ENABLE)
  {
     OTA_loop();
  }
  else
  {
    Application_loop();
  } 

}



#endif //_INO_
