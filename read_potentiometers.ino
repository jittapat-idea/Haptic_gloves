#include "M5StickCPlus.h"
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_ADS1X15.h>
#include <Wire.h>

Adafruit_ADS1115 ads;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

int check = 0;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.IMU.Init();  // Init IMU.  

  
  Wire.begin(32,33);
  pwm.begin();
  pwm.setPWMFreq(60);
  
  ads.begin();
  ads.setGain(GAIN_TWOTHIRDS);

  Serial.begin(115200);
  Serial.println();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("IMU TEST");
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("   X       Y       Z");
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.println("  Pitch   Roll    Yaw");

  pwm.setPWM(0,0,300);
  pwm.setPWM(1,0,300);
  pwm.setPWM(2,0,300);
  pwm.setPWM(3,0,400);

  float thumb = 75.00;
  float firstfinger = 65.00;
  float middlefinger = 50.00;
  float ringfinger = 50.00;

}

void loop() {
  float jX = 0.00;
  float jY = 0.00;
  float jZ = 0.00;

  int16_t  adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  //Convert Back
  volts0 = (adc0*0.000188)*100/4.7;
  volts1 = (adc1*0.000188)*100/4.7;
  volts2 = (adc2*0.000188)*100/4.7;
  volts3 = (adc3*0.000188)*100/4.7;

  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);

  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("%6.2f  %6.2f  %6.2f o/s\n", gyroX, gyroY, gyroZ);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f G\n", accX, accY, accZ);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f\n", pitch, roll, yaw);

  Serial.println("-----------------------------------------------------------");
  Serial.print(" AIN0:  "); Serial.print(adc0); 
  Serial.print(" AIN1:  "); Serial.print(adc1); 
  Serial.print(" AIN2:  "); Serial.print(adc2); 
  Serial.print(" AIN3:  "); Serial.print(adc3); 
  Serial.println(" ");
  Serial.println("-----------------------------------------------------------");
  Serial.print(" volt0:  "); Serial.print(volts0); 
  Serial.print(" volt1:  "); Serial.print(volts1); 
  Serial.print(" volt2:  "); Serial.print(volts2); 
  Serial.print(" volt3:  "); Serial.print(volts3); 
  Serial.println(" ");

  delay(1000);

  
  
}


