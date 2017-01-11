/***********************************************************************************
 *                 Voodoo Control for RobotGeek Snapper Arm
 *                   Lesson 3: Let's Compress this Mess!
 * In the last sketch, you may have noticed that there were sections that were
 * repeated several times over. When you find yourself repeating a line of code
 * to work with several variables, you can save yourself the tedium with some
 * arrays and for loops. Arrays and for loops play very nicely together. Arrays
 * store several variables in an easy to call fashion, and for loops can be used
 * to call each variable and run the same code with each without having to write
 * that code several times over. Notice that this code does the exact same thing
 * as the last lesson, but make sure to take a second to compare how many lines
 * of code it took to achieve the same results.
 * 
 * Voodoo Connections:
 * Analog 0  - RobotGeek Rotation Knob (Base)
 * Analog 1  - RobotGeek Rotation Knob (Shoulder)
 * Analog 2  - RobotGeek Rotation Knob (Elbow)
 * Analog 3  - RobotGeek Rotation Knob (Wrist)
 * Analog 4  - RobotGeek Rotation Knob (Gripper OPTION)
 * Digital 4 - RobotGeek Pushbutton    (Gripper OPTION)
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
 
#include <Servo.h>  //Include the Servo Library

Servo servo[5];     // This creates an array of five objects for the Servo library, servo[0], servo[1], servo[2], servo[3], servo[4].
const int SERVOPIN[] = { 3, 5, 6, 9, 10}; // This is an array of each servo pin in the order that we wish to use them. Note we are defining them here because they are non sequential
//calling SERVOPIN[0] will subsitute 3, calling SERVOPIN[4] will substitute 10.

const int ANALOGPIN[] = { 0, 1, 2, 3 };   // This is an array of each analog input in the order that we wish to use them. This code doesn't account for the scroll wheel. Can you think of a way to add it here?
const int DIGITAL_4_PIN = 4;              // A variable the way we're used to seeing them.

int currentValue[4]; // This creates an array of values to store the current position of the servo. When the values are sequential starting at zero, we can skip over defining them.
int nextValue[4];    // This creates an array of values to store the goal position of the servo.

//button things you should be familiar with.
int buttonPress;
boolean toggle = true;

void setup() 
{
  Serial.begin(9600); // start serial

  for(int i = 0; i < 4; i++) // Here's our first for loop. We initialize a variable, set our limit, and give it some math to move our way to that limit.
  {
    pinMode(ANALOGPIN[i], INPUT); // The for loop will run this code, replacing the [i] each time it has run, starting with 0, until it reaches 3.
  }
  
  pinMode(DIGITAL_4_PIN, INPUT); // Set digital 4 to input.

  for(int i = 0; i < 5; i++) // Here's our next for loop. Same deal as the first, only the limit is different.
  {
    servo[i].attach(SERVOPIN[i]); // We're using this one to attach the servos to their respective pins. Notice we're using [i] with the SERVOPIN array. Think about why this works.
  }

  Serial.println("YOOOOOO");
}

void loop() 
{
  
  nextValue[0] = analogRead(ANALOGPIN[0]);              // You can call up one value of an array with the number in the brackets.
  nextValue[0] = map(nextValue[0], 900, 120, 0, 180);   // Here, we need the mapped values reversed for the base knob due to physical orientation.

  for(int i = 1; i < 4; i++) // Notice that we're starting this at 1 and working our way up. 0 is handled by the previous two lines of code.
  {
    nextValue[i] = analogRead(ANALOGPIN[i]);            //Set NextValue[1 through 3] to the value read from ANALOGPIN[1 through 3]
    nextValue[i] = map(nextValue[i], 120, 900, 0, 180); //Map the value we just read from ANALOGPIN[1 through 3] to a set of values that can be used for the servos.
  }

  buttonPress = digitalRead(DIGITAL_4_PIN); //Set buttonPress to the value read from Digital 4

  for(int i = 0; i < 4; i++) //You know the drill, this time for Serial.
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
  
  for(int v = 0; v < 4; v++) // Notice we're using v instead of i here. You never actually had to use i at all! Haha, it was a clever ruse!
  {
    if (nextValue[v] > currentValue[v]) // If the mapped value read at Analog 0-3 is higher than the value read by Servo 0-3
    {
      for (int i = currentValue[v]; i <= nextValue[v]; i++) // Oh gosh, now we're using [v] AND i. Make sure to keep these straight. Notice that this is still subject to the rules of the for loop it is contained within.
      {
        servo[v].write(i); // Write currentValue[0 through 3] to Servo[0 through 3]
        delay(2);          // Delay for 2 milliseconds
      }
    } 
    else if (nextValue[v] < currentValue[v])  // If the mapped value read at Analog 0-3 is lower than the value read by Servo 0-3
    {
      for (int i = currentValue[v]; i >= nextValue[v]; i--) // This makes a for loop where i is the value read by Servo 0-3. While it is greater than or equal to the mapped value of Analog 0-3, subtract 1 from currentValue[0-3].
      {
        servo[v].write(i); // Write currentValue[0 through 3] to Servo[0 through 3]
        delay(2);          // Delay for 2 milliseconds
      }
    }
  }

  /*
   * Toggle the button
   */

  if (buttonPress == HIGH) // if the button has been pressed
  {
    if(toggle)             // if toggle is true when the button is pressed
    {
      servo[4].write(160); // write 160 degrees to servo 4 (open the gripper)
      toggle = !toggle;    // invert toggle, setting toggle to false
    }
    else                   //if toggle is false when the button is pressed
    {
      servo[4].write(20);  // write 20 degrees to servo 4 (close the gripper)
      toggle = !toggle;    // invert toggle, setting toggle to true
    }
  }

  /*
   * Set Current Values of the Servos
   */
  for(int i = 0; i< 5; i++)
  {
    currentValue[i] = servo[i].read(); // Save the position of Servo 0-4 to current0Value
  }
  delay(2); //delay for 2 milliseconds
}
