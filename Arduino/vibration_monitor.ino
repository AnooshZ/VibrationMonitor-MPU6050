#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

const int OUT_PIN = 8;

const float SAMPLE_HZ = 100;

const int WINDOW_N = 50;

const float ALPHA = 0.01;

const float THRESH_G = 0.8;

int16_t ax, ay, az, gx, gy, gz;

float avgAx = 0, avgAy = 0, avgAz = 0;

float sqBuf[WINDOW_N];
int idx = 0;
int filled = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(OUT_PIN, OUTPUT);
  Serial.begin(115200);
  Wire.begin();

  mpu.initialize();
  if(!mpu.testConnection()){
    Serial.println("MPU6050 not found!");
    while(1); //Stops the program if not MPU6050 is found.
  }
  Serial.println("MPU6050 connected.");

  // Configure sensor ranges and filters
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
  mpu.setDLPFMode(MPU6050_DLPF_BW_42);
  mpu.setRate(9);
}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long tStart = micros();

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  const float SCALE = 8192.0;
  float xg =ax / SCALE;
  float yg = ay / SCALE;
  float zg = az / SCALE;

  // ----------------- High-pass Filter ----------------- 
  avgAx = (1.0f -  ALPHA) * avgAx + ALPHA * xg;
  avgAy = (1.0f - ALPHA) * avgAy + ALPHA * yg;
  avgAz = (1.0f - ALPHA) * avgAz + ALPHA * zg;

  float hx = xg - avgAx;
  float hy = yg - avgAy;
  float hz = zg - avgAz;

  // Instantenous magnitude of the vibrations (using pythagoras theorem)
  float mag = sqrt(hx*hx + hy*hy + hz*hz);

  // ----------------- RMS Calculations ----------------- 
  // Smooth out fluctuations by averaging last WINDOW_N samples
  sqBuf[idx] = mag * mag;
  idx = (idx + 1) % WINDOW_N;
  if(filled < WINDOW_N) filled++;

  float sum = 0.0f;
  for(int i = 0; i< filled; i++){
    sum += sqBuf[i];
  }

  float rms = sqrt(sum/filled);

  // ----------------- Trigger Detection ----------------- 
  bool trigger = (rms> THRESH_G);
  digitalWrite(OUT_PIN, trigger ? HIGH : LOW);

  // ----------------- Arduino Serial Plotter Output -----------------
  static int counter = 0;
  if (++counter % 5 == 0) {   // print 1 out of 5 samples → 20 Hz instead of 100 Hz
    Serial.print("rms:"); Serial.print(rms, 4);
    Serial.print("\tmag:"); Serial.print(mag, 4);
    Serial.print("\tth:");  Serial.println(THRESH_G, 4);

    // ---- CSV for Python ----
    Serial.print(millis()); Serial.print(',');
    Serial.print(mag, 6);   Serial.print(',');
    Serial.println(rms, 6);
  }


  // ----------------- Keep ~100 Hz sample rate ----------------- 
  const float period_us = 1000000.0f / SAMPLE_HZ; // target period in us (microsecond)
  unsigned long elapsed = micros() - tStart;
  if(elapsed < period_us){
    delayMicroseconds(period_us - elapsed);
  }
}

