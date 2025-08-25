#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// MPU-6050 setup
Adafruit_MPU6050 mpu;

// GPS setup
static const int RXPin = 4, TXPin = 3; // GPS RX, TX pins
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  // Start serial communication to PC
  Serial.begin(115200);

  // Initialize MPU-6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.println("MPU6050 Found!");

  // Start serial communication to GPS
  ss.begin(GPSBaud);
  Serial.println("GPS Initialized!");
}

void loop() {
  // Read from GPS module
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  // Get sensor events from MPU-6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Check if we have a valid GPS location
  if (gps.location.isValid() && gps.location.isUpdated()) {
    // Print all data in a single comma-separated line
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print(a.acceleration.z);
    Serial.print(",");
    Serial.print(gps.location.lat(), 6); // latitude with 6 decimal places
    Serial.print(",");
    Serial.print(gps.location.lng(), 6); // longitude with 6 decimal places
    Serial.print(",");
    Serial.println(gps.speed.mps()); // speed in meters per second
  }
}
