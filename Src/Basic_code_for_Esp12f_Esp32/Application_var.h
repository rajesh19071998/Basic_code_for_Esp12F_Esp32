#ifndef _APPLICATION_VARIABLES_H
#define _APPLICATION_VARIABLES_H

String APPL_VER = "V00.000.000";

/* init Timers */
#if 0
 #define MAX_TIMERS 4  ( increment this macro in PIN_CONFIG.h)
 #endif
/*0 to 3 reserved , so use from 4 */

#define LED_BLINK_TIMER 4 

/* timer delay in seconds */
/*if fixed value use macro , else use variable */

//#define LED_BLINK_DELAY_SEC 1 // 1 sec
int LED_BLINK_DELAY_SEC = 1;




String MIT_Appl_cmd = 
//const char MIT_Appl_cmd[] PROGMEM =  /*stores in Flash memory*/
"Appl CMD's  xx.xx.xx.xx/A?\n"
"==========================\n"

"sleep -> esp will go to sleep\n"
"led=2 -> led will blink 2 sec delay\n"
"\n";















#endif //_APPLICATION_VARIABLES_H