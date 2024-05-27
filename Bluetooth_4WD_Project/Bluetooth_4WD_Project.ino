// Bluetooth Controlled 4WD with Automated Braking System
// This code allows an Arduino-based robot to be controlled via a smartphone over Bluetooth. 
// The robot can move forward, backward, left, and right, and it stops when an obstacle is detected within 40 cm.
// The distance to the obstacle is displayed on an LCD screen.
//
// Author: [Your Name]
// Date: [Date]
// License: [Choose a license, e.g., MIT]

#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 13, 9, 8, 3, 2); // Initialize the LCD with the specified pins

const int leftA = 5;  
const int leftB = 6;  
const int rightA = 4;  
const int rightB = 7; 
const int trigPin = 11; // Trigger pin for the ultrasonic sensor
const int echoPin = 12; // Echo pin for the ultrasonic sensor

long duration; // Variable to store the duration of the pulse
int distanceCm; // Variable to store the distance in centimeters
const int speed = 185; // Motor speed (0-255)
char state = 'g'; // Initial state is stopped

void setup() { 
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  Serial.begin(9600); // Start the serial communication at 9600 baud
  
  pinMode(rightA, OUTPUT); // Set rightA pin as an output
  pinMode(rightB, OUTPUT); // Set rightB pin as an output
  pinMode(leftA, OUTPUT); // Set leftA pin as an output
  pinMode(leftB, OUTPUT); // Set leftB pin as an output
  pinMode(trigPin, OUTPUT); // Set trigPin as an output
  pinMode(echoPin, INPUT); // Set echoPin as an input
}

void loop() { 
  lcd.print(millis() / 10); // Display elapsed time in deciseconds
  
  // Measure distance using the ultrasonic sensor
  digitalWrite(trigPin, LOW); // Set the trigPin low
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); // Set the trigPin high
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); // Set the trigPin low again
  duration = pulseIn(echoPin, HIGH); // Read the duration of the pulse from echoPin
  distanceCm = duration * 0.034 / 2; // Calculate the distance in centimeters

  // Stop the robot if an obstacle is detected within 40 cm
  if (distanceCm < 40) {
    stopMotors();
    delay(1500); // Stop for 1.5 seconds
  }

  // Display the distance on the LCD
  lcd.setCursor(0, 0); // Set the cursor to column 0, row 0
  lcd.print("Distance:"); // Print "Distance:"
  lcd.print(distanceCm); // Print the distance in centimeters
  lcd.print("cm"); // Print "cm"
  delay(10); // Pause for a short time
  lcd.setCursor(0, 1); // Set the cursor to column 0, row 1
  lcd.print("KLE E&C Deprtmnt"); // Print "KLE E&C Deprtmnt"
  delay(10); // Pause for a short time
  
  // Read Bluetooth input and control the robot accordingly
  if (Serial.available() > 0) { // If data is available from the Bluetooth module
    state = Serial.read(); // Read the data and store it in state
  } 

  // Control the robot based on the received command
  switch (state) {
    case 'a': // Move forward
      Serial.println(state); 
      moveForward();
      break;
    case 'd': // Turn right
      Serial.println(state); 
      turnRight();
      break;
    case 'c': // Stop
      Serial.println(state); 
      stopMotors();
      break;
    case 'b': // Turn left
      Serial.println(state); 
      turnLeft();
      break;
    case 'e': // Move backward
      Serial.println(state); 
      moveBackward();
      break;
    case 'f': // Distance sensing mode
      // Add functionality for distance sensing mode here
      break;
    case 'g': // Stop
      // Add functionality for stop mode here
      break;
  }
}

void moveForward() {
  analogWrite(rightB, 0);  
  analogWrite(leftB, 0);  
  analogWrite(rightA, speed);  
  analogWrite(leftA, speed);  
}

void turnRight() {
  analogWrite(rightB, speed);  
  analogWrite(leftB, 0);  
  analogWrite(rightA, 0);  
  analogWrite(leftA, speed);  
}

void stopMotors() {
  analogWrite(rightB, 0);  
  analogWrite(leftB, 0);  
  analogWrite(rightA, 0);  
  analogWrite(leftA, 0);  
}

void turnLeft() {
  analogWrite(rightB, 0);  
  analogWrite(leftB, speed); 
  analogWrite(leftA, 0); 
  analogWrite(rightA, speed);  
}

void moveBackward() {
  analogWrite(leftA, 0); 
  analogWrite(rightB, speed);  
  analogWrite(leftB, speed);  
}
