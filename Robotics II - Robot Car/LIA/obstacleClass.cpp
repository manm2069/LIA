#include "obstacleClass.h"

obstacleClass::obstacleClass(int multiPins[]) {
  trigPin = multiPins[0];     // Assign the first element of multiPins to trigPin
  echoPin = multiPins[1];     // Assign the second element of multiPins to echoPin
  servo = multiPins[2];       // Assign the third element of multiPins to servo
  activated = 0;              // Set activated flag to 0 (not activated)
  obstacleCar.init();         // Initialize the motorClass for the obstacleCar
  obstacleCar.setSpeed(255);  // Set the speed of the obstacleCar motors to 255
}

void obstacleClass::init() {
  pinMode(trigPin, OUTPUT);  // Set trigPin as OUTPUT
  pinMode(echoPin, INPUT);   // Set echoPin as INPUT
  myservo.attach(servo);     // Attach the servo motor to the specified pin
}

void obstacleClass::read() {
  digitalWrite(trigPin, LOW);  // Set trigPin LOW
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Set trigPin HIGH
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  // Set trigPin LOW

  duration = pulseIn(echoPin, HIGH);   // Read the duration of the echo pulse
  distance = (duration / 2) * 0.0343;  // Calculate the distance based on the duration
}

void obstacleClass::changeMotors(int multiPins[]) {
  obstacleCar.changeMotors(multiPins);  // Call the changeMotors function of the obstacleCar motorClass instance
}

void obstacleClass::obstacleMove() {
  obstacleCar.move(1, 128, 1, 128);  // Move the obstacleCar forward at a medium speed
  myservo.write(90);                 // Set the servo motor to the middle position
  read();                            // Read the distance from the ultrasonic sensor

  if (activated == 1) {              // If obstacle detection is activated
    if (distance <= 100) {           // If an obstacle is detected within 100 cm
      obstacleCar.move(0, 0, 0, 0);  // Stop the obstacleCar
      myservo.write(180);            // Turn the servo motor to the right
      delay(750);                    // Delay for 750 milliseconds
      read();                        // Read the distance again
      myservo.write(90);             // Set the servo motor to the middle position

      if (distance <= 30) {            // If an obstacle is detected within 30 cm
        obstacleCar.move(0, 0, 0, 0);  // Stop the obstacleCar
        myservo.write(0);              // Turn the servo motor to the left
        delay(750);                    // Delay for 750 milliseconds
        read();                        // Read the distance again
        myservo.write(90);             // Set the servo motor to the middle position

        if (distance <= 30) {                        // If an obstacle is still detected within 30 cm
          obstacleCar.move(1, 255 / 3, 0, 255 / 3);  // Move the obstacleCar forward and slightly to the right
          delay(1500);                               // Delay for 1500 milliseconds
          return;                                    // Exit the function
        } else {
          obstacleCar.move(0, 255 / 3, 1, 255 / 3);  // Move the obstacleCar forward and slightly to the left
          delay(750);                                // Delay for 750 milliseconds
          return;                                    // Exit the function
        }
      } else {
        obstacleCar.move(1, 255 / 3, 0, 255 / 3);  // Move the obstacleCar forward and slightly to the right
        delay(750);                                // Delay for 750 milliseconds
        return;                                    // Exit the function
      }
    }
  } else {
    return;  // Exit the function
  }
}

void obstacleClass::obstacleStop() {
  activated = 0;  // Set activated flag to 0 (not activated)
}