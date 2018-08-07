

/*************************************************** 
  This sketch reads the temperature and relative humidity and outputs the data to an LCD screen.
 ****************************************************/
 
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <LiquidCrystal.h>

Adafruit_SHT31 sht31 = Adafruit_SHT31();

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  Serial.begin(9600);  //open serial communication
  lcd.begin(16, 2);
  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Default address is 44, but can be sett to 0x45 for alternate i2c address
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
}


void loop() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.println(t);
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }
  Serial.println();

  lcd.setCursor(0,0);
  lcd.print("Temp. = ");
  lcd.print(t,2);

  lcd.setCursor(0,1);
  lcd.print("Humidity = ");
  lcd.print(h,2);
  delay(1000);
}
