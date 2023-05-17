#include "motorClass.h"

motorClass::motorClass(int multiPins[]) {
  PWMA = multiPins[0];  // Assign the first element of multiPins array to PWMA
  PWMB = multiPins[1];  // Assign the second element of multiPins array to PWMB
  AIN1 = multiPins[2];  // Assign the third element of multiPins array to AIN1
  BIN1 = multiPins[3];  // Assign the fourth element of multiPins array to BIN1
}

void motorClass::init() {
  pinMode(PWMA, OUTPUT);  // Set PWMA pin as an output
  pinMode(PWMB, OUTPUT);  // Set PWMB pin as an output
  pinMode(AIN1, OUTPUT);  // Set AIN1 pin as an output
  pinMode(BIN1, OUTPUT);  // Set BIN1 pin as an output
  pinMode(3, OUTPUT);     // Set pin 3 as an output
  digitalWrite(3, 1);     // Set pin 3 to HIGH (logic level 1)
}

void motorClass::changeMotors(int multiPins[]) {
  PWMA = multiPins[0];  // Assign the first element of multiPins array to PWMA
  PWMB = multiPins[1];  // Assign the second element of multiPins array to PWMB
  AIN1 = multiPins[2];  // Assign the third element of multiPins array to AIN1
  BIN1 = multiPins[3];  // Assign the fourth element of multiPins array to BIN1
}

void motorClass::move(bool a, int x, bool b, int y) {
  digitalWrite(AIN1, a);  // Set the AIN1 pin based on the value of the 'a' parameter (HIGH or LOW)
  analogWrite(PWMA, x);   // Set the PWM value of PWMA pin based on the value of the 'x' parameter (0-255)
  digitalWrite(BIN1, b);  // Set the BIN1 pin based on the value of the 'b' parameter (HIGH or LOW)
  analogWrite(PWMB, y);   // Set the PWM value of PWMB pin based on the value of the 'y' parameter (0-255)
}

void motorClass::setSpeed(int speed) {
  this->speed = speed;  // Set the speed member variable to the value of the 'speed' parameter
}

void motorClass::forward() {
  move(1, speed / 2, 1, speed / 2);  // Move the robot car forward with equal speed for both motors
}

void motorClass::backward() {
  move(0, speed / 2, 0, speed / 2);  // Move the robot car backward with equal speed for both motors
}

void motorClass::left() {
  move(1, speed / 3, 0, speed / 3);  // Turn the robot car to the left by reducing the speed of the right motor
}

void motorClass::right() {
  move(0, speed / 3, 1, speed / 3);  // Turn the robot car to the right by reducing the speed of the left motor
}

void motorClass::forwardLeft() {
  move(1, speed / 2, 1, speed / 4);  // Move the robot car forward and slightly to the left
}

void motorClass::forwardRight() {
  move(1, speed / 4, 1, speed / 2);  // Move the robot car forward and slightly to the right
}

void motorClass::backwardLeft() {
  move(0, speed / 2, 0, speed / 4);  // Move the robot car backward and slightly to the left
}

void motorClass::backwardRight() {
  move(0, speed / 4, 0, speed / 2);  // Move the robot car backward and slightly to the right
}

void motorClass::stop() {
  move(0, 0, 0, 0);  // Stop the robot car by setting the speed of both motors to 0
}