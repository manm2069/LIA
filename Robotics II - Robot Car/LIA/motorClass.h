#ifndef MOTORCLASS_H
#define MOTORCLASS_H

#include <Arduino.h>

class motorClass {
private:
  int PWMA;   // Pin for controlling Motor A's speed
  int PWMB;   // Pin for controlling Motor B's speed
  int AIN1;   // Pin for controlling Motor A's direction
  int BIN1;   // Pin for controlling Motor B's direction
  int speed;  // Current speed of the motors

public:
  motorClass(){};               // Default constructor
  motorClass(int multiPins[]);  // Constructor with pin initialization

  void init();                              // Initialize the motor class
  void changeMotors(int multiPins[]);       // Change the pin configuration of the motors
  void move(bool a, int x, bool b, int y);  // Move the robot car by specifying direction and speed for both motors
  void setSpeed(int speed);                 // Set the speed of the motors
  void forward();                           // Move the robot car forward
  void backward();                          // Move the robot car backward
  void left();                              // Turn the robot car left
  void right();                             // Turn the robot car right
  void forwardLeft();                       // Move the robot car forward and slightly to the left
  void forwardRight();                      // Move the robot car forward and slightly to the right
  void backwardLeft();                      // Move the robot car backward and slightly to the left
  void backwardRight();                     // Move the robot car backward and slightly to the right
  void stop();                              // Stop the robot car
};

#endif