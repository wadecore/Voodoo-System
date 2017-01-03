/***********************************************************************************
 *                 Voodoo Control for RobotGeek Snapper Arm
 *                   Lesson 1: Let's Learn the Hard Way!
 * This sketch will cause a robot arm to flail wildly and twitch roughly where you
 * hold it in place. Don't run this sketch for too long, if at all. This is just
 * to show the most simplistic way of reasoning your way through code, and to give
 * a baseline for how much improvement is made in each iteration of the code.
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
#include <Servo.h>           //Include the Servo Library

const int ANALOG_0_PIN = 0;  // Analog Pin 0 is the first Rotation Knob in the system. This will be set to control the Base Rotation Servo on the Snapper.
const int ANALOG_1_PIN = 1;  // Analog Pin 1 is the second Rotation Knob in the system. This will be set to control the Shoulder Servo on the Snapper.
const int ANALOG_2_PIN = 2;  // Analog Pin 2 is the third Rotation Knob in the system. This will be set to control the Elbow Servo on the Snapper.
const int ANALOG_3_PIN = 3;  // Analog Pin 3 is the fourth Rotation Knob in the system. This will be set to control the Wrist Servo on the Snapper.
const int DIGITAL_4_PIN = 2; // Digital Pin 2 is the only Pushbutton in the system. This will be set to control the Gripper on the Snapper.

const int SERVO_0_PIN = 3;   // Servo 0 on Pin 3 is the Base Rotation Servo on the Snapper.
const int SERVO_1_PIN = 5;   // Servo 1 on Pin 5 is the Shoulder Servo on the Snapper.
const int SERVO_2_PIN = 6;   // Servo 2 on Pin 6 is the Elbow Servo on the Snapper.
const int SERVO_3_PIN = 9;   // Servo 3 on Pin 9 is the Wrist Servo on the Snapper.
const int SERVO_4_PIN = 10;  // Servo 4 on Pin 10 is the Gripper Servo on the Snapper.

const int SERVO_MIN_PULSE = 600;      // Here we are setting the minimum PWM pulse in microseconds to the Servo
const int SERVO_MAX_PULSE = 2400;     // Here we are setting the maximum PWM pulse in microseconds to the Servo
const int SERVO_CENTER_PULSE = 1500;  // A PWM pulse of 1500 will center the servo.

int analog0SensorValue;    // This is the raw value read from the first Rotation Knob.
int analog1SensorValue;    // This is the raw value read from the second Rotation Knob.
int analog2SensorValue;    // This is the raw value read from the third Rotation Knob.
int analog3SensorValue;    // This is the raw value read from the fourth Rotation Knob.
int digital4SensorValue;   // This is the raw value read from the Pushbutton.

int servo0Value;           // This holds the current PWM value (0-255).
int servo1Value;           // This holds the current PWM value (0-255).
int servo2Value;           // This holds the current PWM value (0-255).
int servo3Value;           // This holds the current PWM value (0-255).
int servo4Value;           // This holds the current PWM value (0-255).

int degree0Value;          // This holds the value in degrees (0-180).
int degree1Value;          // This holds the value in degrees (0-180).
int degree2Value;          // This holds the value in degrees (0-180).
int degree3Value;          // This holds the value in degrees (0-180).
int degree4Value;          // This holds the value in degrees (0-180).

Servo servo0;              //This creates an object for the Servo library, 'servo0'.
Servo servo1;              //This creates an object for the Servo library, 'servo1'.
Servo servo2;              //This creates an object for the Servo library, 'servo2'.
Servo servo3;              //This creates an object for the Servo library, 'servo3'.
Servo servo4;              //This creates an object for the Servo library, 'servo4'.

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  servo0.attach(SERVO_0_PIN); // This attaches the servo to the appropriate pin using the servo library.
  servo1.attach(SERVO_1_PIN); // This attaches the servo to the appropriate pin using the servo library.
  servo2.attach(SERVO_2_PIN); // This attaches the servo to the appropriate pin using the servo library.
  servo3.attach(SERVO_3_PIN); // This attaches the servo to the appropriate pin using the servo library.
  servo4.attach(SERVO_4_PIN); // This attaches the servo to the appropriate pin using the servo library.
  
  Serial.begin(9600);         // This begins sending Serial Output at a baud rate of 9600, which can be read in the Serial Monitor in your Arduino IDE
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  analog0SensorValue = analogRead(ANALOG_0_PIN);     // This reads the rotation knob and stores it in 'analog0SensorValue' 
  analog1SensorValue = analogRead(ANALOG_1_PIN);     // This reads the rotation knob and stores it in 'analog1SensorValue' 
  analog2SensorValue = analogRead(ANALOG_2_PIN);     // This reads the rotation knob and stores it in 'analog2SensorValue' 
  analog3SensorValue = analogRead(ANALOG_3_PIN);     // This reads the rotation knob and stores it in 'analog3SensorValue' 
  digital4SensorValue = digitalRead(DIGITAL_4_PIN);  // This reads the pushbutton and stores it in 'digital4SensorValue' 
  
  servo0Value = map(analog0SensorValue, 900, 120, SERVO_MIN_PULSE, SERVO_MAX_PULSE);  // The map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values.
  degree0Value = map(servo0Value, SERVO_MIN_PULSE, SERVO_MAX_PULSE, 0, 180);          // The map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values.
  servo0.write(degree0Value);                                                         // This sends the servo to the value in 'servoValue', thus adjusting the servo based on the analog input.

  servo1Value = map(analog1SensorValue, 120, 900, SERVO_MIN_PULSE, SERVO_MAX_PULSE);  // The map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values.
  degree1Value = map(servo1Value, SERVO_MIN_PULSE, SERVO_MAX_PULSE, 0, 180);          // The map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values.
  servo1.write(degree1Value);                                                         // This sends the servo to the value in 'servoValue', thus adjusting the servo based on the analog input.

  servo2Value = map(analog2SensorValue, 120, 900, SERVO_MIN_PULSE, SERVO_MAX_PULSE);  // The map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values.
  degree2Value = map(servo2Value, SERVO_MIN_PULSE, SERVO_MAX_PULSE, 0, 180);          // The map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values.
  servo2.write(degree2Value);                                                         // This sends the servo to the value in 'servoValue', thus adjusting the servo based on the analog input.

  servo3Value = map(analog3SensorValue, 120, 900, SERVO_MIN_PULSE, SERVO_MAX_PULSE);  // The map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values.
  degree3Value = map(servo3Value, SERVO_MIN_PULSE, SERVO_MAX_PULSE, 0, 180);          // The map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values.
  servo3.write(degree3Value);                                                         // This sends the servo to the value in 'servoValue', thus adjusting the servo based on the analog input.
  
  Serial.println("Raw Analog Values:");
  Serial.println(analog0SensorValue);
  Serial.println(analog1SensorValue);
  Serial.println(analog2SensorValue);
  Serial.println(analog3SensorValue);
  Serial.println("| Mapped Value for Servos:");
  Serial.println(servo0Value);
  Serial.println(servo1Value);
  Serial.println(servo2Value);
  Serial.println(servo3Value);
  Serial.println(servo4Value);
  Serial.println("uS ");
  Serial.println("| Mapped Values in degrees:");
  Serial.println(degree0Value);
  Serial.println(degree1Value);
  Serial.println(degree2Value);
  Serial.println(degree3Value);
  Serial.println(degree4Value);
  
  delay(15);  //short delay to account for servo movement
  
}//go back to the first line in loop()
