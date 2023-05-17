#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <Arduino.h>
#include <Wire.h>

class gyroscopeClass {
private:
  int I2CAddress;                               // I2C address of the gyroscope
  int gyro_x, gyro_y, gyro_z;                   // Gyroscope readings
  long gyro_x_cal, gyro_y_cal, gyro_z_cal;      // Calibration values for gyroscope
  boolean set_gyro_angles;                      // Flag to indicate if gyro angles should be set
  long acc_x, acc_y, acc_z, acc_total_vector;   // Accelerometer readings
  float angle_roll_acc, angle_pitch_acc;        // Roll and pitch angles calculated from accelerometer
  float angle_pitch, angle_roll;                // Roll and pitch angles
  int angle_pitch_buffer, angle_roll_buffer;    // Buffer for storing previous roll and pitch angles
  float angle_pitch_output, angle_roll_output;  // Output roll and pitch angles
  long loop_timer;                              // Timer for controlling the loop rate
  int temp;                                     // Temperature reading

public:
  gyroscopeClass(){};
  gyroscopeClass(int unused);

  void setupMPU6050Registers();  // Setup MPU6050 registers
  void readMPU6050Data();        // Read data from MPU6050
  void init();                   // Initialize the gyroscope
  void begin();                  // Begin gyroscope operation
};

#endif