/* 
 *  -----------------------------------------------------------------
 *  Course     : CST337
 *  Instrcutor : Dr. Eckhardt
 *  Homework   : 4 Exercise 1
 *  Student    : Clarence Mitchell
 *  Description: Or Gaate
 *               Cycles through binary combinations displaying OR gate
 *  ------------------------------------------------------------------
 */


// named constant for the OR Pins
const int Pin2 = 2;
const int Pin4 = 4;
const int MaxCountValue = 4;


// 600000 = 10 minutes in milliseconds
long interval = 2000; // interval for cycle

int currCount = 0; // the current number counter (should never exceed 4)
int pin2Val = 0;
int pin4Val = 0;
int brightness = 255;

// the setup routine runs once when you press reset:
void setup() 
{
  //
  // Set both pins to output
  //
   pinMode(Pin2, OUTPUT);   
   pinMode(Pin4, OUTPUT);   
  currCount = 0;
}

// the loop routine runs over and over again forever:
void loop()
{
    //
    // Set 1 digit led  
    //
    if ((currCount % 2) == 1) 
    {
     //
     //  FTurn on led to full and send value to OR gate
     //
       analogWrite(Pin2, brightness);
    }
    else
    {     
      //
      //  turn off current led
      //
       analogWrite(Pin2, LOW);
   }
   
    //
    // Set 2 digit led  
    //
    if ((currCount / 2) == 1)
    {
     //
     //  Turn on led to full and send value to OR gate
     //
       analogWrite(Pin4, brightness);
    }
    else
    {     
      //
      //  turn off current led
      //
        analogWrite(Pin4, LOW);
   }

  //
  // increment current count and wrap value modulus division makes it between 0 and 3  (0 - 00, 1 - 01, 2 - 10, 3 - 11) 
  //
  currCount = (++currCount) % 4;
   delay(interval);
}


