/***********************************************************************************
 *                 Voodoo Control for RobotGeek Snapper Arm
 *                   Lesson 4: Let's Fix that dang Button!
 * In all the sketches leading up to this, if you used the code for the button, it
 * was real twitchy. That's not great! You were probably inclined to find a way to
 * make the scroll wheel work. Buttons are important for activating predefined bits
 * of code, so let's make it work right. We'll be using a debouncing library named
 * Bounce2. You can learn about debouncing with a google search, but for now just
 * know that it fixes the issue we've been having with the button thus far.
 * 
 * Voodoo Connections:
 * Analog 0  - RobotGeek Rotation Knob (Base)
 * Analog 1  - RobotGeek Rotation Knob (Shoulder)
 * Analog 2  - RobotGeek Rotation Knob (Elbow)
 * Analog 3  - RobotGeek Rotation Knob (Wrist)
 * Digital 4 - RobotGeek Pushbutton    (Gripper)
 * 
 * RobotGeek Snapper Connections:
 * Digital 3  - RobotGeek 180 Servo (Base)
 * Digital 5  - RobotGeek 180 Servo (Shoulder)
 * Digital 6  - RobotGeek 180 Servo (Elbow)
 * Digital 9  - RobotGeek 180 Servo (Wrist)
 * Digital 10 - RobotGeek 180 Servo (Gripper)
 * 
 * Set both of the jumpers on the RobotGeek Sensor Shield to VIN.
 * 
 ***********************************************************************************/
 
#include <Servo.h>   //Include the Servo Library
#include <Bounce2.h> //Include the Debouncing Library

Servo servo[5]; // This creates an array of five objects for the Servo library, servo[0], servo[1], servo[2], servo[3], servo[4].
Bounce debounce[1] = Bounce(); // This creates an array containing just a single item for the debouncing library. This isn't normal, but if you wanted to add more buttons, this would make it easier to use them.

const int SERVOPIN[] = { 3, 5, 6, 9, 10}; // This is an array of each servo pin in the order that we wish to use them.
const int ANALOGPIN[] = { 0, 1, 2, 3 };   // This is an array of each analog pin in the order that we wish to use them.
const int BUTTONPIN[] = { 4 };            // This is an array of each button pin in the order that we wish to use them. Again, abnormal case having a single item in the array.

int currentValue[4];    // This creates an array of values to store the current position of the servo.
int nextValue[4];       // This creates an array of values to store the goal position of the servo.
int btnValue[] = { 4 }; // This is an array to hold on to the pin we have buttons on for use with the debouncing library.

boolean toggle = true;  // Still togglin'.

void setup() 
{
  Serial.begin(9600); // start serial

  for(int i = 0; i < 4; i++) // Nothing changed here, check out the next for loop!
  {
    pinMode(ANALOGPIN[i], INPUT);
  }
  
  for (int i = 0; i < 1; i++) // Count up from 0 to 0 because we only have one button. Very strange!
  {
    pinMode(BUTTONPIN[i],INPUT);      // Set BUTTONPIN[0] (Digital 4) to input
    debounce[i].attach(BUTTONPIN[i]); // Attach Digital 4 to debounce[0] for the debounce library
    debounce[i].interval(5);          // Set the interval for debounce[0] to 5
  }

  for(int i = 0; i < 5; i++) // Same as in Lesson 3
  {
    servo[i].attach(SERVOPIN[i]);
  }

  Serial.println("YOOOOOO");
}

void loop() 
{
  //This should all look familiar
  nextValue[0] = analogRead(ANALOGPIN[0]);
  nextValue[0] = map(nextValue[0], 900, 120, 0, 180);

  for(int i = 1; i < 4; i++)
  {
    nextValue[i] = analogRead(ANALOGPIN[i]);
    nextValue[i] = map(nextValue[i], 120, 900, 0, 180);
  }

  for(int i = 0; i < 4; i++)
  {
    Serial.print("Angle ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(nextValue[i]);
    Serial.println("º");
  }


  /*
    Write Values to all of the Servos
  */
  
  for(int v = 0; v < 4; v++) // See lesson 3 for details
  {
    if (nextValue[v] > currentValue[v]) 
    {
      for (int i = currentValue[v]; i <= nextValue[v]; i++) 
      {
        servo[v].write(i);
        delay(2);
      }
    } 
    else if (nextValue[v] < currentValue[v]) 
    {
      for (int i = currentValue[v]; i >= nextValue[v]; i--) 
      {
        servo[v].write(i);
        delay(2);
      }
    }
  }

  /*
   * Toggle button with Debounce
   */

  if ( debounce[0].fell() ) // Notice the way we're interacting with the button is different. instead of buttonPress == HIGH, we're using the debounce library to handle when the button is pressed.
  {
    if(toggle) // toggling the button handled in Lesson 3
    {
      servo[4].write(160);
      toggle = !toggle;
    }
    else
    {
      servo[4].write(20);
      toggle = !toggle;
    }
  }

  //move the servos to the value
  for(int i = 0; i< 5; i++)
  {
    currentValue[i] = servo[i].read();
  }

  //update button press using debounce library
  for (int i = 0; i < 1; i++) 
  {
    debounce[i].update();
    btnValue[i] = debounce[i].read();
  }
  
  delay(2); //delay for 2 milliseconds
}
