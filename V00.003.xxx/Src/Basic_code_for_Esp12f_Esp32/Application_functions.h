#ifndef _APPLICATION_FUNCTIONS_H
#define _APPLICATION_FUNCTIONS_H

// This file related Macros , variables , structures must be declared in  "Application_var.h" file

//#define APPL_DEBUG // for debug

void Application_Setup()
{

  if(OTA_flag == 0)
  { 
    web_site_setup();
  }
  init_timer_delay_sec( SLEEP_TIMER1 , SLEEP1_DELAY_SEC ); // 5 sec
  
  /* Appliction files setups */

  led_setup();

} //Application_Setup



void All_sleep()
{
  activate_timer(SLEEP_TIMER1);
  Appl_mit_DATA = "Sleep Activated in 5 sec...!";
}

void Timer_timeout_check()
{

  if(is_timer_timeout( SLEEP_TIMER1 )) // 5 sec timer
  {
    deactivate_timer(SLEEP_TIMER1);
#ifdef APPL_DEBUG    
    Serial.println("SLEEP Timer 1 Expired! Going to Sleep...!");
#endif    
    delay(1000);
    ESP.deepSleep(0); 
  } 


  

}







void Application_loop()
{
  // keep watching the push button:
  
  web_site_loop();
  Timer_timeout_check();
  

 /* Application loops */

  led_loop();

}

void set_led_delay(String time)
{
  int delay_time = time.toInt();
  led_delay(delay_time);  
  Appl_mit_DATA = "Led Time delay was set = "+time+" sec's";
}

void mit_commn(String request)
{
  MIT_flag = 2; 
  #ifdef APPL_DEBUG 
  Serial.println(request); 
  #endif 
}

void mit_app_requist_process(AsyncWebServerRequest *web) // refer MIT_APP.h
{
  MIT_flag = 0;
  //int paramsNr = web->params(); // number of param

  if(web->params() == 0){return;}
  String request = web->getParam(0)->name(); // first param only // http://192.168.31.146/A?Sleep  // /A?Sleep=1  // /A?Sleep=1&l1on=2
  
  // Serial.print("Parm num : ");Serial.println(web->params());Serial.print("Request : ");Serial.println(request);

  if      ( request == "sleep" ) {mit_commn(request); All_sleep(); }
  
  else if ( request == "led" ) { mit_commn(request); set_led_delay( web->getParam(0)->value() ); }
  


}



















#endif //_APPLICATION_FUNCTIONS_H
