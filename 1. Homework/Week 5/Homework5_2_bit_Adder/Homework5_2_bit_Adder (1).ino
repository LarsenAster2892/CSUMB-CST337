/* 
 *  -----------------------------------------------------------------
 *  Course     : CST337
 *  Instrcutor : Dr. Eckhardt
 *  Homework   : 5
 *  Student    : Clarence Mitchell
 *  Description: 2 Bit Adder
 *               Uses 4 switches to simulate a 2 bit adder
 *               Pins 1-4 Input from switches
 *                    5-8 output to led to represent switch state (on/off)
 *                    9 bit 1 of sum
 *                    10 bit 2 f sum
 *                    11 carry of sum
 *  ------------------------------------------------------------------
 */

// -------------------------------------
// Define Constants
// -------------------------------------
const int startLED = 5;			// PIN for First LED for numbers (in sequence)
const int startBUTTON = 1;		// PIN for first Button (in sequence)
const int totalDigit1Pin = 9;	// PIN for LED for 1 digit on results
const int totalDigit2Pin = 10;  // PIN for LED for 2 digit on results
const int carryLedPin = 11;		// PIN for LED for carry on results

//
//  ---   Arrays (consecutive memory)
//
int ledOn[] = {false, false, false, false};
boolean lastPress[] = {false, false, false, false};

//
//  -- Current state  
//
int currLED = 5;
int currBUTTON = 1;
boolean currPress = false;

//
// --- Result digits
//
int digit = 0;
int bit = 0;
int carry = 0;
//
// --- Temporary storage
//

int iLoop = 0;
int value1 = 0;
int value2 = 0;

int ledSetValue = LOW;

//void setPin(boolean ledOn, int pinNum);

// -----------------------------------------------
//
// debounce routine
//    Get button press but limit the rate at 
//    which press can fire
//
// -----------------------------------------------
boolean debounce(int buttonPin, boolean presslast)
{
  //
  //  get button press
  //  
  boolean pressCurrent = digitalRead(buttonPin);
  //
  //  -- if not the same as last press then give user time
  //
  if (presslast != pressCurrent)
  {
   delay(5);
   pressCurrent = digitalRead(buttonPin);
  }
  //
  //
  return pressCurrent;
} // -- exit debounce routine


//----------------------------------------------------
//
//  setup Routine
//   routine runs once when you press reset:
//
// --------------------------------------------------
void setup() 
{
  //
  // Loop and set number LEDs and Buttons
  //
  //
  // Define Output PINs for Number Buttons and LEDs
  //
  for (iLoop = 0; iLoop < 4; iLoop++)
  {
    //
	// -- Calculate pin as start plus offset (iLoop)
	//
	currLED = startLED + iLoop;
    currBUTTON = startBUTTON + iLoop;
	//
	// --- Set LED and Button PINs
	//
  	pinMode(currLED, OUTPUT);
  	pinMode(currBUTTON, INPUT);
    //
	// --- Initialize Arrays
	//
	ledOn[iLoop] = false;
    lastPress[iLoop] = false;
	
  } // -- end for
  
  pinMode(totalDigit1Pin, OUTPUT);
  pinMode(totalDigit2Pin, OUTPUT);
  pinMode(carryLedPin, OUTPUT);
  
  currBUTTON = 1;
  currLED = 5;
  
} // -- end setup

//----------------------------------------------------
//
//  loop Routine
//   runs over and over again forever:
//
// --------------------------------------------------
void loop() 
{

    //
  // Loop and set number LEDs and Buttons
  //
  
	//
	// -- First calculate PIN numbers based on start plus  offset (iLoop)
	//
    currLED = startLED + iLoop;
    currBUTTON = startBUTTON + iLoop;
 	
	//
	// -- Get button press but limit the rate at which press can fire
	//
    currPress = debounce(currBUTTON,lastPress[iLoop]);     // try to eliminate button fire time
	//
	//  -- Now check if button for current offset has been pressed
	//     This is determined by last being low current being high....
	//
    if (lastPress[iLoop] == LOW && currPress == HIGH)
  	{
		//
		//  -- invert state of LED for button
		//
		ledOn[iLoop] = !ledOn[iLoop]; 
  	
	} // -- end of if
	
	//
	//   --- Store current pressed value into array
	//
    lastPress[iLoop] = currPress;
	//
	//  --- Send value to LED 
	//
   digitalWrite(currLED, ledOn[iLoop]);
	//
	// -- Calculate results 
	//  Note could have used ledOn[] directly but would be less clear....
	//
	//  -- First Bit
	//   add the two bits and set carry (if needed)
	//
   value1 = (ledOn[0]?1:0);   
   value2 = (ledOn[2]?1:0);
   digit = value1 + value2;   
   bit = digit % 2;
   carry = digit / 2;
   ledSetValue = (bit == 1?HIGH:LOW);
   digitalWrite(totalDigit1Pin, ledSetValue);  

   	//
	//  -- Second Bit
	//  -- Same as first bit but include carry in addition
	//  

   value1 = (ledOn[1]?1:0);
   value2 = (ledOn[3]?1:0);
   digit = value1 + value2 + carry;
   bit = digit % 2;
   carry = digit / 2;
   ledSetValue = (bit == 1?HIGH:LOW);
   digitalWrite(totalDigit2Pin, ledSetValue);  
  
   ledSetValue = (carry == 1?HIGH:LOW);
   digitalWrite(carryLedPin, ledSetValue);  
  
	//
	//  increment for next button (wrap using modulus division)
	//
   iLoop = ++iLoop % 4;
   
}  // -- end loop routine

