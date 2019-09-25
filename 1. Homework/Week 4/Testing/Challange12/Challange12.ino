/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */


// named constant for the switch pin
const int switchPin = 8;
const int startLed = 2;
const int maxLed = 7;

// 600000 = 10 minutes in milliseconds
long interval = 15000; // interval at which to light the next LED

unsigned long previousTime = 0; // store the last time an LED was updated

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int currLed = 2;

int switchState = 0; // the current switch state
int prevSwitchState = 0; // the previous switch state


// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  for (currLed = startLed; currLed <= maxLed; currLed++)
  {
   pinMode(currLed, OUTPUT);   
  }
  currLed = startLed;

  // set the tilt switch pin as input
  pinMode(switchPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop()
{
    // store the time since the Arduino started running in a variable
  unsigned long currentTime = millis();

  // compare the current time to the previous time an LED turned on
  // if it is greater than your interval, run the if statement
  if (currentTime - previousTime > interval) 
  {
    // save the current time as the last time you changed an LED
    previousTime = currentTime;
    digitalWrite(currLed, LOW);

    if (++currLed > maxLed)
    {
      currLed = startLed;
    }
    
    brightness = 0;

  }
   analogWrite(currLed, brightness);
   // wait for 30 milliseconds to see the dimming effect
    delay(30);
   brightness = ((brightness + fadeAmount) < 255) ? brightness += fadeAmount : 255;


     // read the switch value
  switchState = digitalRead(switchPin);

  // if the switch has changed
  if (switchState != prevSwitchState) 
  {
    // turn all the LEDs low
     for (int x = startLed; currLed <= maxLed; currLed++)
     {
      digitalWrite(x, LOW);
     }

     // reset the LED variable to the first one
     currLed = startLed;
    
     //reset the timer
     previousTime = currentTime;
  }
  
  // set the previous switch state to the current state
  prevSwitchState = switchState;
  
}


