/* 
 *  -----------------------------------------------------------------
 *  Course     : CST337
 *  Instrcutor : Dr. Eckhardt
 *  Homework   : 4 Exercise 2
 *  Student    : Clarence Mitchell
 *  Description: KnightRider Lights
 *               Cycles through lights on board
 *  -----------------------------------------------------------------
 */


// named constant for the switch pin
const int startLed = 2;
const int maxLed = 7;

// 600000 = 10 minutes in milliseconds
long interval = 7500; // interval at which to light the next LED

unsigned long previousTime = 0; // store the last time an LED was updated

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int currLed = 2;

int switchState = 0; // the current switch state
int prevSwitchState = 0; // the previous switch state


// the setup routine runs once when you press reset:
void setup() 
{
  //
  // Loop through pins 2 through 7 and declare them as output
  //
  for (currLed = startLed; currLed <= maxLed; currLed++)
  {
   pinMode(currLed, OUTPUT);   
  }
  currLed = startLed;

}

// the loop routine runs over and over again forever:
void loop()
{
    //
    // store the time since the Arduino started running in a variable
    //
    unsigned long currentTime = millis();

   //
   // Compare the current time to the previous time an LED was turned on
   // if it is greater than interval, reset led and store time
   //
   if (currentTime - previousTime > interval) 
   {
    //
    // save the current time as the last time the LED changed
    //
    previousTime = currentTime;
    //
    //  turn off current led
    //
    digitalWrite(currLed, LOW);

   //
   //  increment current led number and check if greater than max number
   //  if so, reset to start number
   //
    if (++currLed > maxLed)
    {
      currLed = startLed;
    }

    //
    //  reset brightness to low
    //
    brightness = 0;

   }
   //
   //  Fade on brightness of led to full
   //
      analogWrite(currLed, brightness);
  
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
    brightness = ((brightness + fadeAmount) < 255) ? brightness += fadeAmount : 255;
   
}


