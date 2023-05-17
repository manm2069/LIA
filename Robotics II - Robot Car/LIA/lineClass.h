#ifndef LINECLASS_H
#define LINECLASS_H

#include <Arduino.h>
#include "motorClass.h"

class lineClass {
private:
  int rightPin;        // Pin for the right line sensor
  int middlePin;       // Pin for the middle line sensor
  int leftPin;         // Pin for the left line sensor
  int right;           // Reading from the right line sensor
  int middle;          // Reading from the middle line sensor
  int left;            // Reading from the left line sensor
  int motorPins;       // Number of pins used for the motors
  int activated;       // Flag indicating whether the line tracking is activated or not
  motorClass lineCar;  // Object of the motorClass for controlling the robot car

public:
  lineClass(){};               // Default constructor
  lineClass(int multiPins[]);  // Constructor with pin initialization

  void lineTrack();                    // Perform line tracking
  void lineMove();                     // Move the robot car based on the line tracking results
  void changeMotors(int multiPins[]);  // Change the pin configuration of the motors
  void whatTrack();                    // Determine the line tracking state
  void lineStop();                     // Stop the line tracking
};

#endif