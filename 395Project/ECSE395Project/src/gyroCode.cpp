/*
#include <Arduino.h>
#include <Wire.h>

// ---- ESP32 board settings (classic ESP32 DevKit defaults) ----
#define SDA_PIN 21
#define SCL_PIN 22
#define MPU_ADDR 0x68
#define USE_DEFAULT_PINS 1 // 1 = use the board's default I2C pins (Wire.begin()), 0 = use SDA_PIN/SCL_PIN above
#define I2C_CLOCK 400000   // try 100000 if you still see errors
#define PRINT_EVERY 1000     // print every 10th loop (25 Hz)

float RateRoll, RatePitch, RateYaw;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
int RateCalibrationNumber;
float AccX, AccY, AccZ;
float AngleRoll, AnglePitch;
uint32_t LoopTimer;
uint8_t PrintCounter = 0;
uint32_t LastErrorPrint = 0;
float KalmanAngleRoll=0, KalmanUncertaintyAngleRoll=2*2;
float KalmanAnglePitch=0, KalmanUncertaintyAnglePitch=2*2;
float Kalman1DOutput[]={0,0};

void kalman_1d(float KalmanState, float KalmanUncertainty, float KalmanInput, float KalmanMeasurement) {
  KalmanState=KalmanState+0.004f*KalmanInput;
  KalmanUncertainty=KalmanUncertainty + 0.004f * 0.004f * 4 * 4;
  float KalmanGain=KalmanUncertainty * 1/(1*KalmanUncertainty + 3 * 3);
  KalmanState=KalmanState+KalmanGain * (KalmanMeasurement-KalmanState);
  KalmanUncertainty=(1-KalmanGain) * KalmanUncertainty;
  Kalman1DOutput[0]=KalmanState; 
  Kalman1DOutput[1]=KalmanUncertainty;
}

// Restart the I2C peripheral (recovers from a stuck/timed-out bus)
void i2c_start(void) {
#if USE_DEFAULT_PINS
  Wire.begin();
#else
  Wire.begin(SDA_PIN, SCL_PIN);
#endif
  Wire.setClock(I2C_CLOCK);
  Wire.setTimeOut(100);   // ms
}

void i2c_restart(void) {
  Wire.end();
  delay(5);
  i2c_start();
}

// endTransmission() codes: 0 ok, 1 too long, 2 NACK on address, 3 NACK on data, 4 other, 5 timeout
bool writeReg(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  uint8_t err = Wire.endTransmission();
  if (err) {
    Serial.printf("writeReg(0x%02X) failed, endTransmission error %u\n", reg, err);
    return false;
  }
  return true;
}

// Reads len bytes starting at reg, using a repeated start between the
// register-select write and the read (standard MPU6050 access pattern)
bool readRegs(uint8_t reg, uint8_t *buf, uint8_t len) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  uint8_t err = Wire.endTransmission(false);
  if (err) {
    if (millis() - LastErrorPrint > 500) {
      Serial.printf("readRegs(0x%02X): select failed, endTransmission error %u\n", reg, err);
      LastErrorPrint = millis();
    }
    return false;
  }
  uint8_t got = Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)len);
  if (got != len) {
    if (millis() - LastErrorPrint > 500) {
      Serial.printf("readRegs(0x%02X): wanted %u bytes, got %u\n", reg, len, got);
      LastErrorPrint = millis();
    }
    return false;
  }
  for (uint8_t i = 0; i < len; i++) buf[i] = Wire.read();
  return true;
}

// Returns false if the read failed (values are left unchanged in that case)
bool gyro_signals(void) {
  uint8_t acc[6], gyro[6];
  if (!readRegs(0x3B, acc, 6) || !readRegs(0x43, gyro, 6)) {
    i2c_restart();
    return false;
  }
  int16_t AccXLSB = (int16_t)((acc[0] << 8) | acc[1]);
  int16_t AccYLSB = (int16_t)((acc[2] << 8) | acc[3]);
  int16_t AccZLSB = (int16_t)((acc[4] << 8) | acc[5]);
  int16_t GyroX   = (int16_t)((gyro[0] << 8) | gyro[1]);
  int16_t GyroY   = (int16_t)((gyro[2] << 8) | gyro[3]);
  int16_t GyroZ   = (int16_t)((gyro[4] << 8) | gyro[5]);

  RateRoll=(float)GyroX/65.5f;
  RatePitch=(float)GyroY/65.5f;
  RateYaw=(float)GyroZ/65.5f;
  AccX=(float)AccXLSB/4096.0f;
  AccY=(float)AccYLSB/4096.0f;
  AccZ=(float)AccZLSB/4096.0f;
  AngleRoll=atanf(AccY/sqrtf(AccX*AccX+AccZ*AccZ))*RAD_TO_DEG;
  AnglePitch=-atanf(AccX/sqrtf(AccY*AccY+AccZ*AccZ))*RAD_TO_DEG;
  return true;
}

void setup() {
Serial.begin(115200);
//SETUP FOR ANGLE MEASUREMENT
  delay(3000);   // gives you time to open the serial monitor and see the startup messages
  i2c_start();
  #if USE_DEFAULT_PINS
    Serial.printf("I2C using board default pins: SDA=%d SCL=%d\n", (int)SDA, (int)SCL);
  #else
    Serial.printf("I2C using pins: SDA=%d SCL=%d\n", SDA_PIN, SCL_PIN);
  #endif
    delay(250);

  // Diagnostic: is the sensor answering, and what is it?
  uint8_t who = 0;
  if (readRegs(0x75, &who, 1)) {
    Serial.printf("WHO_AM_I = 0x%02X (expected 0x68 for MPU6050; some clones differ)\n", who);
  } else {
    Serial.println("Could not read WHO_AM_I - see error code above");
  }

  // Wake up, then configure: LPF ~10 Hz, accel +/-8g, gyro +/-500 deg/s
  writeReg(0x6B, 0x00);
  delay(100);
  writeReg(0x1A, 0x05);
  writeReg(0x1C, 0x10);
  writeReg(0x1B, 0x08);
  delay(50);

  // Gyro calibration: average 2000 good samples (give up after 6000 attempts)
  int good = 0;
  for (int attempts = 0; good < 2000 && attempts < 6000; attempts++) {
    if (gyro_signals()) {
      RateCalibrationRoll+=RateRoll;
      RateCalibrationPitch+=RatePitch;
      RateCalibrationYaw+=RateYaw;
      good++;
    }
    delay(1);
  }
  if (good > 0) {
    RateCalibrationRoll/=good;
    RateCalibrationPitch/=good;
    RateCalibrationYaw/=good;
  }
  Serial.printf("Calibration done with %d good samples\n", good);
  LoopTimer=micros();
}

void loop() {
  if (gyro_signals()) {
    RateRoll-=RateCalibrationRoll;
    RatePitch-=RateCalibrationPitch;
    RateYaw-=RateCalibrationYaw;
    kalman_1d(KalmanAngleRoll, KalmanUncertaintyAngleRoll, RateRoll, AngleRoll);
    KalmanAngleRoll=Kalman1DOutput[0]; 
    KalmanUncertaintyAngleRoll=Kalman1DOutput[1];
    kalman_1d(KalmanAnglePitch, KalmanUncertaintyAnglePitch, RatePitch, AnglePitch);
    KalmanAnglePitch=Kalman1DOutput[0]; 
    KalmanUncertaintyAnglePitch=Kalman1DOutput[1];

    if (++PrintCounter >= PRINT_EVERY) {
      PrintCounter = 0;
      Serial.print("Roll Angle [°] ");
      Serial.print(KalmanAngleRoll);
      Serial.print(" Pitch Angle [°] ");
      Serial.println(KalmanAnglePitch);
    }
  }

  while (micros() - LoopTimer < 4000);
  LoopTimer=micros();
}
*/
/*
#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu(0x68);

// DMP state
bool dmpReady = false;
uint16_t packetSize;
uint8_t fifoBuffer[64];

Quaternion q;
VectorFloat gravity;
float ypr[3];

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.begin(21, 22);
  Wire.setClock(400000);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  Serial.println("Initializing DMP...");
  uint8_t devStatus = mpu.dmpInitialize();

  // Replace these with your own offsets (see note below)
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  mpu.setXAccelOffset(0);
  mpu.setYAccelOffset(0);
  mpu.setZAccelOffset(0);

  if (devStatus == 0) {
    mpu.CalibrateAccel(6);   // quick auto-calibration; keep sensor still & flat
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();

    mpu.setDMPEnabled(true);
    packetSize = mpu.dmpGetFIFOPacketSize();
    dmpReady = true;
    Serial.println("DMP ready!");
  } else {
    // 1 = initial memory load failed, 2 = DMP config updates failed
    Serial.print("DMP init failed, code ");
    Serial.println(devStatus);
    while (1);
  }
}

void loop() {
  if (!dmpReady) return;

  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    Serial.print("YPR:\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.println(ypr[2] * 180 / M_PI);
  }
}
*/

#include <Wire.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <MPU6050.h>

MPU6050 mpu(0x68);

void setup(void) {
  Wire.begin(22, 20);
  Wire.setClock(400000);
  Serial.begin(115200);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  // Verify connection
  if (!mpu.testConnection()) {
      Serial.println("MPU6050 connection failed!");
      while(1);
  }

  // Initialize DMP
  uint8_t devStatus = mpu.dmpInitialize();
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("MPU6050 Test Commence!");

}

void loop() {
  // Containers for sensor data
  uint8_t fifoBuffer[64]; // FIFO storage buffer
  Quaternion q;           // [w, x, y, z] quaternion container
  VectorFloat gravity;    // [x, y, z] gravity vector
  float ypr[3];           // [yaw, pitch, roll] container

  // Check if a full packet is ready to be fetched from the FIFO
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { 
      
      // 1. Get Quaternions
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      
      // 2. Get gravity vector (necessary for isolating pure tilt from linear motion)
      mpu.dmpGetGravity(&gravity, &q);
      
      // 3. Calculate Euler angles (Yaw/Pitch/Roll) in radians
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

      // Print values (Convert radians to degrees)
      Serial.print("YPR:\t");
      Serial.print(ypr[0] * 180/M_PI);
      Serial.print("\t");
      Serial.print(ypr[1] * 180/M_PI);
      Serial.print("\t");
      Serial.println(ypr[2] * 180/M_PI);
  }
}

