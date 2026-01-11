#ifndef _MIT_APP_H
#define _MIT_APP_H

//#define MIT_DEBUG

extern void mit_app_requist_process(AsyncWebServerRequest *web); // Application_functions.h
void mit_app_cmd_setup();

 AsyncWebServer MIT_server(80);


extern String Global_IP;
extern String VERSION;
String MIT_INFO_DATA;

const char MIT_Basic_cmd[] PROGMEM =  /*stores in Flash memory*/
"Basic CMD's xx.xx.xx.xx/\n"
"========================\n"
"info\nversion\n"
"OTA_ON -> Enable_OTA\nOTA_OFF -> Disable_OTA\nrst -> Reset ESP\n"
"getwifiname\ngetwifipass\ngethotspotname\ngethotspotpass\n"
"setwifiname?setwifiname=RajeshJioFiber\n"
"setwifipass?setwifipass=Rajesh@0000\n"
"sethotspotname?sethotspotname=ESP_BOARD\n"
"sethotspotpass?sethotspotpass=0123456\n"
"WIFIUPDATE -> to copy wifi/hotspot details EEPROM to local\n"
"wifimode\nhotspotmode\n"


"\n";
extern String MIT_Appl_cmd;

String DATA; // Wifi_functions.h

 String Appl_mit_DATA = ""; // Application_functions.h
 int MIT_flag = 0;  // Application_functions.h

 void my_info()
 {
  String MYIP = "http://"+ MY_IP;
  MIT_INFO_DATA =
  
  " Hi Application User\nBOARD Details mentioned below\nBoard_Name : "+BOARD_NAME +"\nBoard_Number : "+BOARD_NUMBER +"\n"
  "Board_Local_IP : "+MYIP+"\nBoard Local DNS : "+"http://"+Local_DNS_Name+".local"+"\nBoard_Global_IP : "+Global_IP+ "\n"
  "For MIT Commands type "+MYIP+"/cmd" ;

 }


 void initLittleFS() {  // only for esp32
#if defined(ESP32)
 if (!LittleFS.begin(true)) {
#ifdef MIT_DEBUG
    Serial.println("An error has occurred while mounting LittleFS");
#endif    
 }
 else
 {
#ifdef MIT_DEBUG
    Serial.println("LittleFS mounted successfully");
#endif      
 }
#endif
}


void MIT_APP_Setup()
{
  initLittleFS(); // only for esp32

  mit_app_cmd_setup(); 
  MIT_server.begin();
}


void Enable_OTA()
{
  OTA_flag?OTA_flag = 0:OTA_flag = 1;
   
   EEPROM.write(OTA_addr, OTA_flag);
   EEPROM.commit();
   delay(5000);
   ESP.restart();
}

void mit_request_process(AsyncWebServerRequest *request)
{
  String R = "";
  String data = "";
#ifdef MIT_DEBUG
    Serial.print("URL : ");
    Serial.println(request->url()); 
#endif    
  R = request->url();

  if(R.indexOf("OTA_ON") > 0 ){ request->send(200, "text/plain", "OTA_Enabled");Enable_OTA();}
  else if(R.indexOf("rst") > 0 ){request->send(200, "text/plain", "ESP Restarted");delay(5000);ESP.restart();}
  else if(R.indexOf("getwifiname") > 0 ){request->send(200, "text/plain", AP_NameChar.c_str());}
  else if(R.indexOf("getwifipass") > 0 ){request->send(200, "text/plain", WiFiPassword.c_str());}
  else if(R.indexOf("gethotspotname") > 0 ){request->send(200, "text/plain", ssid.c_str());}
  else if(R.indexOf("gethotspotpass") > 0 ){request->send(200, "text/plain", password.c_str());}

  else if(R.indexOf("setwifiname") > 0 )
  { 
    data = request->getParam("setwifiname")->value();
    if(data == ""){request->send(200, "text/plain", "WIFI Name should not be empty!"); return;}
    Wifi_Hotspot_Write(data,1);request->send(200, "text/plain", "Wifi Name Updated as : " + data +"\nEEPROM writen : "+ DATA);
  }
  else if(R.indexOf("setwifipass") > 0 )
  {
    data = request->getParam("setwifipass")->value();
    if(data == ""){request->send(200, "text/plain", "WIFI Password should not be empty!"); return;}
    Wifi_Hotspot_Write(data,2);request->send(200, "text/plain", "Wifi Password Updated as : " + data +"\nEEPROM writen : "+ DATA);
  }
  else if(R.indexOf("sethotspotname") > 0 )
  {
    data = request->getParam("sethotspotname")->value();
    if(data == ""){request->send(200, "text/plain", "Hotspot Name should not be empty!"); return;}
    Wifi_Hotspot_Write(data,3);request->send(200, "text/plain", "Hotspot Name Updated as : " + data +"\nEEPROM writen : "+ DATA);
  }
  else if(R.indexOf("sethotspotpass") > 0 )
  {
    data = request->getParam("sethotspotpass")->value();
    if(data == ""){request->send(200, "text/plain", "Hotspot Password should not be empty!"); return;}
    Wifi_Hotspot_Write(data,4);request->send(200, "text/plain", "Hotspot Password Updated as : " + data +"\nEEPROM writen : "+ DATA);
  }
  
  else if(R.indexOf("wifiupdate") > 0 ){ReadWifiCredentials();request->send(200, "text/plain", "Wifi and Hotspot variables updated from EEPROM");}

  else if(R.indexOf("cmd") > 0 ){String MIT_cmd = MIT_Basic_cmd + MIT_Appl_cmd; request->send(200, "text/plain", MIT_cmd); }

  else if(R.indexOf("wifimode") > 0 ){Wifi_Only_Mode();request->send(200, "text/plain", "Wifi Mode was Activated Successfully....!");}

  else if(R.indexOf("hotspotmode") > 0 ){Hotspot_Only_Mode();request->send(200, "text/plain", "Hotspot Mode was Activated Successfully....!");}

  else if(R.indexOf("A") > 0 ){
         mit_app_requist_process(request);
         if(MIT_flag == 2 ) { request->send(200, "text/plain", Appl_mit_DATA);} 
         else { request->send(200, "text/plain", "ESP Application Invalid Request....!");  }
         }

  else{
        request->send(200, "text/plain", "ESP Invalid Request....!");
      }       
  
}


void mit_app_cmd_setup()
{
  MIT_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html",false);
    MIT_server.serveStatic("/", LittleFS, "/");
#ifdef MIT_DEBUG
      Serial.println("WEB SITE LOADED ....!");
#endif    
  });

  MIT_server.on("/info", HTTP_GET, [](AsyncWebServerRequest *request){ my_info();request->send(200, "text/plain", MIT_INFO_DATA); }); // Root //http://192.168.31.146/info
  MIT_server.on("/version", HTTP_GET, [](AsyncWebServerRequest *request){ request->send(200, "text/plain", VERSION); });

  MIT_server.on("/OTA_ON", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request); });
  MIT_server.on("/rst", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request); });
  MIT_server.on("/getwifiname", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/getwifipass", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/gethotspotname", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/gethotspotpass", HTTP_GET, [](AsyncWebServerRequest *request){ mit_request_process(request);});  // http://192.168.31.146/gethotspotpass
  MIT_server.on("/setwifiname", HTTP_GET, [](AsyncWebServerRequest *request){ mit_request_process(request);});  // http://192.168.31.146/setwifiname?setwifiname=RajeshJio
  MIT_server.on("/setwifipass", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/sethotspotname", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/sethotspotpass", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/wifiupdate", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/cmd", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/wifimode", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});
  MIT_server.on("/hotspotmode", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);});

  MIT_server.on("/A", HTTP_GET, [](AsyncWebServerRequest *request){mit_request_process(request);}); // Application  data

}



void MIT_loop()
{
  wifi_check_loop(); // every 20 min
}







#endif //_MIT_APP_H
