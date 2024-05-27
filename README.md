# Bluetooth_Controlled_4WD_with_Automated_Braking_System

This project allows an Arduino-based robot to be controlled via a smartphone over Bluetooth. The robot can move forward, backward, left, and right, and it stops when an obstacle is detected within 40 cm. The distance to the obstacle is displayed on an LCD screen.

## Components Used
- Arduino Uno
- Bluetooth module (HC-05)
- Ultrasonic sensor (HC-SR04)
- L298N Motor Driver
- DC Motors
- LCD Display
- Miscellaneous components (wires, breadboard, power supply)

## Setup Instructions
1. Upload the `main.ino` file to the Arduino.
2. Pair the Bluetooth module with your smartphone.
3. Use a Bluetooth terminal app to send commands to the robot.

## Commands
- `a`: Move forward
- `b`: Turn left
- `c`: Stop
- `d`: Turn right
- `e`: Move backward
- `f`: Distance sensing mode
- `g`: Stop

