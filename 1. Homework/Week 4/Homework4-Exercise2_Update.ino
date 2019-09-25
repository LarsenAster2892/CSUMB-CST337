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

// library includes
//#include <stdio.h>
//#include <stdlib.h>
 
 

// named constant for the switch pin
const int startLed = 2;
const int maxLed = 7;

// 600000 = 10 minutes in milliseconds
long interval = 7500; 			// interval at which to light the next LED

unsigned long previousTime = 0; // store the last time an LED was updated

int brightness = 0;    			// how bright the LED is
int fadeAmount = 5;   			// how many points to fade the LED by
int currLed = 2;

int switchState = 0; 			// the current switch state
int prevSwitchState = 0; 		// the previous switch state


int tiltVal = 5;                // halfway value (wrap value) this is max num - 1 (since 0 to max)
int wrapValue = tiltVal * 2;    // Maximum value to reach
int tmpVal = 0;                 // tmp for calculation
int ledOffset = 2;              // Starting Pin
int val = 1;                    // current iteration value



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
    analogWrite(currLed, LOW);

    
    // wrap the value around the tilt (middle value) counting down from middle to zero
    //  and back up..
    //  this is done by subtracting the value from the tilt (middle) number
    //  this makes the value oscilate between 0 and the middle...
    //  5 - 0 = 5, 5 -1 = 4,...... 5 -5 = 0, 5 - 6 = -1 , 5 - 7 = -2
    tmpVal = tiltVal - val;
    //
    //  calculates the absoulte value of the pin
    //   done by multiplying the tmpVal with a -1 or 1 (value inside the parenthesis)
    //   the -1 or 1 is the calculated
    //   since a true is 1 and false is 0 then
    //    for tmpVal > 0:  tmpVal * ((0 * -1) + ( 1))
    //    for tmpVal < 0:  tmpVal * ((1 * -1) + (0))
    //    for tmpVal = 0:  tmpVal * ((0 * -1) + (0) -- all zeroes...
    tmpVal = tmpVal * ((tmpVal<0) * (-1) + (tmpVal>0));
    currLed = startLed + tiltVal - tmpVal;
    
    
    val = ++val % 10;
    
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

