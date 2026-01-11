#ifndef _LED_BLINK_H
#define _LED_BLINK_H

bool status = 0;

void led_setup()
{
 pinMode(LED1_PIN, OUTPUT);
 pinMode(LED2_PIN, OUTPUT);
 init_timer_delay_sec( LED_BLINK_TIMER , LED_BLINK_DELAY_SEC );
 activate_timer(LED_BLINK_TIMER);
}

void led_delay(int Delay)
{
  LED_BLINK_DELAY_SEC = Delay;
  init_timer_delay_sec( LED_BLINK_TIMER , LED_BLINK_DELAY_SEC );
}

void led_loop()
{

 if(is_timer_timeout(LED_BLINK_TIMER))
 {
   if(status)
   {
    digitalWrite(LED1_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED2_PIN, HIGH);
    status = 0;
   } 
   else 
   {
    digitalWrite(LED1_PIN, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(LED2_PIN, LOW);
    status = 1;
   }
 } 

}




#endif // _LED_BLINK_H