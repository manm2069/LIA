#include "gyroscope.h"

gyroscopeClass::gyroscopeClass(int unused) {
  unused = 1;
}

void gyroscopeClass::setupMPU6050Registers() {
  // Configure MPU6050 registers for initialization
  Wire.beginTransmission(0x68);  // Start communication with MPU6050 at address 0x68
  Wire.write(0x6B);              // PWR_MGMT_1 register
  Wire.write(0x00);              // Set the register value to 0x00 (wake up MPU6050)
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x1C);  // ACCEL_CONFIG register
  Wire.write(0x10);  // Set the register value to 0x10 (enable 8g range)
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x1B);  // GYRO_CONFIG register
  Wire.write(0x08);  // Set the register value to 0x08 (set gyro sensitivity to +/- 500 degrees/s)
  Wire.endTransmission();
}

void gyroscopeClass::readMPU6050Data() {
  // Read raw data from MPU6050 registers
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);  // Starting register address for accelerometer data
  Wire.endTransmission();
  Wire.requestFrom(0x68, 14);  // Request 14 bytes of data from MPU6050
  while (Wire.available() < 14)
    ;  // Wait until all the bytes are available

  // Read accelerometer and gyro data from the registers
  acc_x = Wire.read() << 8 | Wire.read();
  acc_y = Wire.read() << 8 | Wire.read();
  acc_z = Wire.read() << 8 | Wire.read();
  temp = Wire.read() << 8 | Wire.read();
  gyro_x = Wire.read() << 8 | Wire.read();
  gyro_y = Wire.read() << 8 | Wire.read();
  gyro_z = Wire.read() << 8 | Wire.read();
}

void gyroscopeClass::init() {
  i2c_addr = 0x3F;

  setupMPU6050Registers();

  // Calibrate gyroscope
  for (int cal_int = 0; cal_int < 1000; cal_int++) {
    readMPU6050Data();
    gyro_x_cal += gyro_x;
    gyro_y_cal += gyro_y;
    gyro_z_cal += gyro_z;
    delay(3);
  }

  gyro_x_cal /= 1000;
  gyro_y_cal /= 1000;
  gyro_z_cal /= 1000;

  Serial.begin(115200);

  loop_timer = micros();
}

void gyroscopeClass::begin() {
  if (micros() - loop_timer > 4000) {
    loop_timer = micros();
    readMPU6050Data();
    gyro_x -= gyro_x_cal;
    gyro_y -= gyro_y_cal;
    gyro_z -= gyro_z_cal;

    // Calculate roll and pitch angles using gyroscope data
    angle_pitch += gyro_x * 0.0000611;
    angle_roll += gyro_y * 0.0000611;
    angle_pitch += angle_roll * sin(gyro_z * 0.000001066);
    angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);

    // Calculate roll and pitch angles using accelerometer data
    acc_total_vector = sqrt((acc_x * acc_x) + (acc_y * acc_y) + (acc_z * acc_z));
    angle_pitch_acc = asin((float)acc_y / acc_total_vector) * 57.296;
    angle_roll_acc = asin((float)acc_x / acc_total_vector) * -57.296;

    angle_pitch_acc -= 0.0;
    angle_roll_acc -= 0.0;

    // Combine gyroscope and accelerometer angles
    if (set_gyro_angles) {
      angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;
      angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;
    } else {
      angle_pitch = angle_pitch_acc;
      angle_roll = angle_roll_acc;
      set_gyro_angles = true;
    }

    // Calculate filtered output angles
    angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;
    angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;

    // Print the output angles
    Serial.print(" | Angle  = ");
    Serial.println(angle_pitch_output);
  }
}