#include "motorClass.h"
int motors[] = { 5, 6, 7, 8 };
motorClass robotCar(motors);

#include <IRremote.h>
int receiver = 9;
IRrecv irrecv(receiver);
decode_results results;

#include "lineClass.h"
int lines[] = { A0, A1, A2 };
lineClass lineTrack(lines);

#include "obstacleClass.h"
int obstaclePins[] = { 13, 12, 10 };
obstacleClass obstacleAvoid(obstaclePins);

#include <Servo.h>
Servo ultrasonicServo;
Servo stickServo;

#include "gyroscope.h"
gyroscopeClass Gyroscope(1);

int mode = 1;
int speed;

void setup() {
  Serial.begin(9600);

  robotCar.init();  // Initialize robot car

  irrecv.enableIRIn();  // Enable IR receiver

  lineTrack.changeMotors(motors);  // Change motors for line tracking

  obstacleAvoid.init();                // Initialize obstacle avoidance
  obstacleAvoid.changeMotors(motors);  // Change motors for obstacle avoidance

  stickServo.attach(11);  // Attach stick servo to pin 11

  Gyroscope.init();  // Initialize gyroscope
}

void loop() {
  if (irrecv.decode(&results)) {    // Check if IR signal is received
    Serial.println(results.value);  // Print received IR signal value
    irrecv.resume();                // Resume receiving IR signals

    switch (results.value) {
      case 944967:                     // IR signal: 944967
        robotCar.setSpeed(255);        // Set robot car speed to maximum
        robotCar.stop();               // Stop robot car
        lineTrack.lineStop();          // Stop line tracking
        obstacleAvoid.obstacleStop();  // Stop obstacle avoidance
        mode = 1;                      // Set mode to 1
        break;

      case 92999:  // IR signal: 92999
        mode = 2;  // Set mode to 2
        break;

      case 420679:  // IR signal: 420679
        mode = 3;   // Set mode to 3
        break;

      case 641863:  // IR signal: 641863
        if (mode == 1) {
          mode = 1;
          robotCar.forward();  // Move robot car forward
        }
        break;

      case 904007:  // IR signal: 904007
        if (mode == 1) {
          mode = 1;
          robotCar.left();  // Turn robot car left
        }
        break;

      case 248647:  // IR signal: 248647
        if (mode == 1) {
          mode = 1;
          robotCar.right();  // Turn robot car right
        }
        break;

      case 379719:  // IR signal: 379719
        if (mode == 1) {
          mode = 1;
          robotCar.backward();  // Move robot car backward
        }
        break;

      case 772935:                     // IR signal: 772935
        robotCar.stop();               // Stop robot car
        lineTrack.lineStop();          // Stop line tracking
        obstacleAvoid.obstacleStop();  // Stop obstacle avoidance
        break;

      case 3216:                 // IR signal: 3216
        robotCar.setSpeed(128);  // Set robot car speed to medium
        break;

      case 1168:                 // IR signal: 1168
        robotCar.setSpeed(255);  // Set robot car speed to maximum
        break;

      case 715591:             // IR signal: 715591
        stickServo.write(90);  // Set stick servo position to 90 degrees
        break;

      case 453447:              // IR signal: 453447
        stickServo.write(360);  // Set stick servo position to 360 degrees
        break;
    }
  }

  if (mode == 2) {
    lineTrack.lineMove();          // Move according to line tracking algorithm
    obstacleAvoid.obstacleStop();  // Stop obstacle avoidance
  } else if (mode == 3) {
    obstacleAvoid.obstacleMove();  // Move according to obstacle avoidance algorithm
    lineTrack.lineStop();          // Stop line tracking
  }

  Gyroscope.begin();  // Read gyroscope data
}