/***********************************************************************************
 *                 Voodoo Control for RobotGeek Snapper Arm
 *                      Lesson 2: Let's Smooth it out!
 * This sketch will show you a way to smooth out the movement of the arm by way of
 * delaying the motion for a fraction of a second. To do this, we hold on to the
 * current position, look for a new position, and have the arm move between them
 * in an incremental motion instead of having the arm constantly keeping up with new
 * position data. We are starting to see the need to compress our code at this point,
 * as the pattern used to handle data keeps repeating. We'll handle that after we get
 * it working properly here.
 * 
 * Voodoo Connections:
 * Analog 0  - RobotGeek Rotation Knob (Base)
 * Analog 1  - RobotGeek Rotation Knob (Shoulder)
 * Analog 2  - RobotGeek Rotation Knob (Elbow)
 * Analog 3  - RobotGeek Rotation Knob (Wrist)
 * Digital 2 - RobotGeek Pushbutton    (Gripper)
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

#include <Servo.h>        //Include the Servo Library

Servo servo0;              //This creates an object for the Servo library, 'servo0'.
Servo servo1;              //This creates an object for the Servo library, 'servo1'.
Servo servo2;              //This creates an object for the Servo library, 'servo2'.
Servo servo3;              //This creates an object for the Servo library, 'servo3'.
Servo servo4;              //This creates an object for the Servo library, 'servo4'.

const int ANALOG_0_PIN = 0;  // Analog Pin 0 is the first Rotation Knob in the system. This will be set to control the Base Rotation Servo on the Snapper.
const int ANALOG_1_PIN = 1;  // Analog Pin 1 is the second Rotation Knob in the system. This will be set to control the Shoulder Servo on the Snapper.
const int ANALOG_2_PIN = 2;  // Analog Pin 2 is the third Rotation Knob in the system. This will be set to control the Elbow Servo on the Snapper.
const int ANALOG_3_PIN = 3;  // Analog Pin 3 is the fourth Rotation Knob in the system. This will be set to control the Wrist Servo on the Snapper.
const int DIGITAL_4_PIN = 2; // Digital Pin 2 is the only Pushbutton in the system. This will be set to control the Gripper on the Snapper.

int current0Value, next0Value; // This makes two variables for handling the values we'll be storing to smooth out the movement.
int current1Value, next1Value; // This makes two variables for handling the values we'll be storing to smooth out the movement.
int current2Value, next2Value; // This makes two variables for handling the values we'll be storing to smooth out the movement.
int current3Value, next3Value;    // This makes two variables for handling the values we'll be storing to smooth out the movement.
int buttonPress; // This makes two variables for handling the values we'll be storing to smooth out the movement.
boolean toggle = true;

void setup() 
{
  Serial.begin(9600); // This begins sending Serial Output at a baud rate of 9600, which can be read in the Serial Monitor in your Arduino IDE

  pinMode(ANALOG_0_PIN, INPUT);  // Setting Analog Pin 0 to Input
  pinMode(ANALOG_1_PIN, INPUT);  // Setting Analog Pin 1 to Input
  pinMode(ANALOG_2_PIN, INPUT);  // Setting Analog Pin 2 to Input
  pinMode(ANALOG_3_PIN, INPUT);  // Setting Analog Pin 3 to Input
  pinMode(DIGITAL_4_PIN, INPUT); // Setting Digital Pin 2 to Input

  servo0.attach(3);  // This attaches the servo to the appropriate pin using the servo library.
  servo1.attach(5);  // This attaches the servo to the appropriate pin using the servo library.
  servo2.attach(6);  // This attaches the servo to the appropriate pin using the servo library.
  servo3.attach(9);  // This attaches the servo to the appropriate pin using the servo library.
  servo4.attach(10); // This attaches the servo to the appropriate pin using the servo library.

  Serial.println("Starting Up..."); //Send some text over Serial
}

void loop() 
{

  next0Value = analogRead(ANALOG_0_PIN);           //Set Next0Value to the value read from Analog 0
  next0Value = map(next0Value, 900, 120, 0, 180);  //Map the value we just read from Analog 0 to a set of values that can be used for a servo.
  
  next1Value = analogRead(ANALOG_1_PIN);           //Set Next1Value to the value read from Analog 1
  next1Value = map(next1Value, 120, 900, 0, 180);  //Map the value we just read from Analog 1 to a set of values that can be used for a servo.

  next2Value = analogRead(ANALOG_2_PIN);           //Set Next2Value to the value read from Analog 2
  next2Value = map(next2Value, 120, 900, 0, 180);  //Map the value we just read from Analog 2 to a set of values that can be used for a servo.
  
  next3Value = analogRead(ANALOG_3_PIN);           //Set Next3Value to the value read from Analog 3
  next3Value = map(next3Value, 120, 900, 0, 180);  //Map the value we just read from Analog 3 to a set of values that can be used for a servo.

  buttonPress = digitalRead(DIGITAL_4_PIN);        //Set buttonPress to the value read from Digital 2

  //Send a readout of the angles of each servo over serial 
  Serial.print("Base Angle = ");
  Serial.print(next0Value);
  Serial.println("º");

  Serial.print("Shoulder Angle = ");
  Serial.print(next1Value);
  Serial.println("º");

  Serial.print("Elbow Angle = ");
  Serial.print(next2Value);
  Serial.println("º");

  Serial.print("Wrist Angle = ");
  Serial.print(next3Value);
  Serial.println("º");

  /*
   * Write Values to the Base Servo
   */
  if (next0Value > current0Value)                     // If the mapped value read at Analog 0 is higher than the value read by Servo 0
  {
    for (int i = current0Value; i <= next0Value; i++) // This makes a for loop where i is the value read by Servo 0. While it is less than or equal to the mapped value of Analog 0, add 1 to current0Value.
    {
      servo0.write(i);                                // Write current0Value to Servo 0
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, adding 1 to current0Value until it has the same value as next0Value.
  } 
  else if (next0Value < current0Value)                // If the mapped value read at Analog 0 is lower than the value read by Servo 0
  {
    for (int i = current0Value; i >= next0Value; i--) // This makes a for loop where i is the value read by Servo 0. While it is greater than or equal to the mapped value of Analog 0, subtract 1 from current0Value.
    {
      servo0.write(i);                                // Write current0Value to Servo 0
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, subtracting 1 from current0Value until it has the same value as next0Value.
  }

  /*
   * Write Values to the Shoulder Servo
   */
  if (next1Value > current1Value)                     // If the mapped value read at Analog 1 is higher than the value read by Servo 1
  {
    for (int i = current1Value; i <= next1Value; i++) // This makes a for loop where i is the value read by Servo 1. While it is less than or equal to the mapped value of Analog 1, add 1 to current1Value.
    {
      servo1.write(i);                                // Write current1Value to Servo 1
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, adding 1 to current1Value until it has the same value as next1Value.
  } 
  else if (next1Value < current1Value)                // If the mapped value read at Analog 1 is lower than the value read by Servo 1
  {
    for (int i = current1Value; i >= next1Value; i--) // This makes a for loop where i is the value read by Servo 1. While it is greater than or equal to the mapped value of Analog 1, subtract 1 from current1Value.
    {
      servo1.write(i);                                // Write current1Value to Servo 1
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, subtracting 1 from current1Value until it has the same value as next1Value.
  }

  /*
   * Write Values to the Elbow Servo
   */
  if (next2Value > current2Value)                     // If the mapped value read at Analog 2 is higher than the value read by Servo 2 
  {
    for (int i = current2Value; i <= next2Value; i++) // This makes a for loop where i is the value read by Servo 2. While it is less than or equal to the mapped value of Analog 2, add 1 to current2Value. 
    {
      servo2.write(i);                                // Write current2Value to Servo 2
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, adding 1 to current2Value until it has the same value as next2Value.
  } 
  else if (next2Value < current2Value)                // If the mapped value read at Analog 2 is lower than the value read by Servo 2
  {
    for (int i = current2Value; i >= next2Value; i--) // This makes a for loop where i is the value read by Servo 2. While it is greater than or equal to the mapped value of Analog 2, subtract 1 from current2Value. 
    {
      servo2.write(i);                                // Write current2Value to Servo 2
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, adding 1 to current2Value until it has the same value as next2Value.
  }

  /*
   * Write Values to the Wrist Servo
   */
  if (next3Value > current3Value)                     // If the mapped value read at Analog 3 is higher than the value read by Servo 3  
  {
    for (int i = current3Value; i <= next3Value; i++) // This makes a for loop where i is the value read by Servo 3. While it is less than or equal to the mapped value of Analog 3, add 1 to current3Value.  
    {
      servo3.write(i);                                // Write current3Value to Servo 3
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, adding 1 to current3Value until it has the same value as next3Value.
  } 
  else if (next3Value < current3Value)                // If the mapped value read at Analog 3 is lower than the value read by Servo 3
  {
    for (int i = current3Value; i >= next3Value; i--) // This makes a for loop where i is the value read by Servo 3. While it is greater than or equal to the mapped value of Analog 3, subtract 1 from current3Value.  
    {
      servo3.write(i);                                // Write current3Value to Servo 3
      delay(2);                                       // Delay for 2 milliseconds
    }                                                 // if the test condition hasn't been met, start this loop over, adding 1 to current3Value until it has the same value as next3Value.
  }

  /*
   * Write Values to the Gripper
   */

  if (buttonPress == HIGH) // If the pushbutton has been pressed
  {
    if(toggle)             // Do this if toggle is true
    {
      servo4.write(160);   // Set Servo 4 to 160 degrees
      toggle = !toggle;    // Invert toggle, making it false
    }
    else                   // Do this if toggle is false
    {
      servo4.write(20);    // Set Servo 4 to 20 degrees
      toggle = !toggle;    // Invert toggle, making it true
    }
  }

  /*
   * Set Current Values of the Servos
   */
  current0Value = servo0.read(); // Save the position of Servo 0 to current0Value
  current1Value = servo1.read(); // Save the position of Servo 1 to current1Value
  current2Value = servo2.read(); // Save the position of Servo 2 to current2Value
  current3Value = servo3.read(); // Save the position of Servo 3 to current3Value
  delay(2); //delay for 2 milliseconds
}
