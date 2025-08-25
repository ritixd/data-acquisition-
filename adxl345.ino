#include <Wire.h>

int ADXL345 = 0x53; // ADXL345 I2C address

float X_out, Y_out, Z_out;  
float roll, pitch;
float rollF = 0, pitchF = 0; // filtered values

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);  
  Wire.endTransmission();
  delay(10);
}

void loop() {
  // === Read accelerometer data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); 
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  
  X_out = (Wire.read() | Wire.read() << 8);
  X_out = X_out / 256.0;
  Y_out = (Wire.read() | Wire.read() << 8);
  Y_out = Y_out / 256.0;
  Z_out = (Wire.read() | Wire.read() << 8);
  Z_out = Z_out / 256.0;

  // --- Compute roll and pitch (in degrees) ---
  roll  = atan2(Y_out, Z_out) * 180.0 / PI;
  pitch = atan2(-X_out, sqrt(Y_out*Y_out + Z_out*Z_out)) * 180.0 / PI;

  // --- Apply low-pass filter ---
  rollF  = 0.94 * rollF  + 0.06 * roll;
  pitchF = 0.94 * pitchF + 0.06 * pitch;

  // --- Send filtered values to Processing ---
  Serial.print(rollF);
  Serial.print("/");
  Serial.println(pitchF);

  delay(50);
}
