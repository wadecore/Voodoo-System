/***********************************************************************************
 *                 Voodoo Control for RobotGeek Snapper Arm
 *                               Scroll Wheel
 * 
 * Voodoo Connections:
 * Analog 0  - RobotGeek Rotation Knob (Base)
 * Analog 1  - RobotGeek Rotation Knob (Shoulder)
 * Analog 2  - RobotGeek Rotation Knob (Elbow)
 * Analog 3  - RobotGeek Rotation Knob (Wrist)
 * Analog 4  - RobotGeek Rotation Knob (Gripper)
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
const int ANALOGPIN[] = { 0, 1, 2, 3, 4 };   // This is an array of each analog pin in the order that we wish to use them.

int currentValue[5];    // This creates an array of values to store the current position of the servo.
int nextValue[5];       // This creates an array of values to store the goal position of the servo.

void setup() 
{
  Serial.begin(9600); // start serial

  for(int i = 0; i < 5; i++) // Nothing changed here, check out the next for loop!
  {
    pinMode(ANALOGPIN[i], INPUT);
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

  for(int i = 1; i < 5; i++)
  {
    nextValue[i] = analogRead(ANALOGPIN[i]);
    nextValue[i] = map(nextValue[i], 120, 900, 0, 180);
  }

  for(int i = 0; i < 5; i++)
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
  
  for(int v = 0; v < 5; v++) // See lesson 3 for details
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

  //move the servos to the value
  for(int i = 0; i< 5; i++)
  {
    currentValue[i] = servo[i].read();
  }
  
  delay(2); //delay for 2 milliseconds
}
