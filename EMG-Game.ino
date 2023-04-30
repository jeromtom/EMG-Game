/*
  EMG-controlled Pick and Place Game
*/
//Libraries for display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#include <Servo.h>
Servo claw;
int pos = 30; 
int randtime;

void setup() {
  Serial.begin(9600);
  claw.attach(9);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(20,2);
  display.print("Welcome to the");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,15);
  display.print("EMG Game");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1.75);
  display.setTextColor(WHITE);
  display.setCursor(55,2);
  display.print("By");
  display.setTextSize(2.5);
  display.setTextColor(WHITE);
  display.setCursor(15,15);
  display.print("jeromtom");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(55,5);
  display.print("3");
  display.display();
  delay(1000);
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(55,5);
  display.print("2");
  display.display();
  delay(1000);
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(55,5);
  display.print("1");
  display.display();
  delay(1000);
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.print("FLEX!!!");
  display.display();
  delay (500);
  
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Detecting spike...");
  display.display();
  int sensorValue = analogRead(A0);
  // Converts the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
  float spike = voltage;

  //Higher the spike higher the random time range
  if (spike >= 1.0){
    Serial.println("Spike detected");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(spike);
    
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(50,0);
    display.print("V");
    
    display.display();
    
    randtime = random(1000,2000);
    
    if (spike >=2.0) {
      randtime = random(2000,3000);
    }
    if (spike >=3.0) {
      randtime = random(3000,4000);
    }
    Serial.println(round(randtime/100));
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,18);
    display.print(randtime);

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(50,18);
    display.print("ms");
    
    display.display();
    //If spike is detected, servo will close the claw and hold after the random time,
    //it will release the claw and the sensor takes readings again
    for (pos = 30; pos <= 107; pos += 1){
      claw.write(pos);
      delay(15);
     }
    delay(randtime);
    for (pos = 107; pos >= 30; pos -= 1){
      claw.write(pos);
      delay(15);
    }
  }
}
