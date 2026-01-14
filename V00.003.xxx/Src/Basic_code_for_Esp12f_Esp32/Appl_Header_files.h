#ifndef _APPL_HEADER_FILES_H
#define _APPL_HEADER_FILES_H

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


/* Appl requeired files */

#include "Led_blink.h"










#endif // _APPL_HEADER_FILES_H