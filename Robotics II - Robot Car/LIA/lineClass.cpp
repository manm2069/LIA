#include "lineClass.h"

lineClass::lineClass(int multiPins[]) {
  rightPin = multiPins[0];   // Assign the pin number for the right line sensor
  middlePin = multiPins[1];  // Assign the pin number for the middle line sensor
  leftPin = multiPins[2];    // Assign the pin number for the left line sensor
  right = 0;                 // Initialize the reading from the right line sensor
  middle = 0;                // Initialize the reading from the middle line sensor
  left = 0;                  // Initialize the reading from the left line sensor
  activated = 0;             // Set the line tracking flag to not activated
  lineCar.init();            // Initialize the motor class
  lineCar.setSpeed(255);     // Set the speed of the motors to maximum
}

void lineClass::lineTrack() {
  right = analogRead(rightPin);    // Read the value from the right line sensor
  middle = analogRead(middlePin);  // Read the value from the middle line sensor
  left = analogRead(leftPin);      // Read the value from the left line sensor
}

void lineClass::lineMove() {
  activated = 1;                   // Activate line tracking
  right = analogRead(rightPin);    // Read the value from the right line sensor
  middle = analogRead(middlePin);  // Read the value from the middle line sensor
  left = analogRead(leftPin);      // Read the value from the left line sensor

  if (activated == 1) {
    if (right > 40) {
      lineCar.move(0, 43, 1, 43);  // Move the robot car slightly to the right
    } else if (middle > 40) {
      lineCar.move(1, 85, 1, 85);  // Move the robot car forward
    } else if (left > 40) {
      lineCar.move(1, 43, 0, 43);  // Move the robot car slightly to the left
    } else {
      lineCar.move(1, 85, 0, 85);  // Move the robot car forward

      if (middle > 40) {
        return;  // Return if the middle line sensor detects the line
      }
    }
  } else {
    lineCar.stop();  // Stop the robot car if line tracking is not activated
    return;
  }
}

void lineClass::changeMotors(int multiPins[]) {
  lineCar.changeMotors(multiPins);  // Change the pin configuration of the motors
}

void lineClass::whatTrack() {
  Serial.print("Right = ");  // Print the reading from the right line sensor
  Serial.println(right);
  Serial.print("Middle = ");  // Print the reading from the middle line sensor
  Serial.println(middle);
  Serial.print("Left = ");  // Print the reading from the left line sensor
  Serial.println(left);
}

void lineClass::lineStop() {
  activated = 0;  // Deactivate line tracking
}