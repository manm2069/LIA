#ifndef OBSTACLECLASS_H
#define OBSTACLECLASS_H

#include <Arduino.h>
#include "motorClass.h"
#include <Servo.h>

class obstacleClass {
private:
  int trigPin;             // Pin number for the ultrasonic sensor's trigger pin
  int echoPin;             // Pin number for the ultrasonic sensor's echo pin
  int servo;               // Pin number for the servo motor
  float duration;          // Duration of the echo pulse from the ultrasonic sensor
  float distance;          // Calculated distance based on the echo duration
  int activated;           // Flag to indicate if obstacle detection is activated
  motorClass obstacleCar;  // Instance of the motorClass for controlling the robot car's motors
  Servo myservo;           // Instance of the Servo library for controlling the servo motor

public:
  obstacleClass(){};               // Default constructor
  obstacleClass(int multiPins[]);  // Constructor with parameter for initializing pin numbers

  void init();                         // Initialize the obstacleClass
  void read();                         // Read the distance from the ultrasonic sensor
  void changeMotors(int multiPins[]);  // Change the pin configuration of the motors
  void obstacleMove();                 // Perform obstacle avoidance movement
  void obstacleStop();                 // Stop obstacle detection
};

#endif