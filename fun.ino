#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
/*#include "MQ135.h"
#define PIN_MQ135 A1
MQ135 mq135_sensor = MQ135(PIN_MQ135);*/
float sensor=A0;
float gas_value;
int Blue=8;
int Green=9;
int Red=10;
float temperature = 34.0; // assume current temperature. Recommended to measure with DHT22
float humidity = 27.0; // assume current humidity. Recommended to measure with DHT22
  const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


SoftwareSerial mySerial(11,12);  
int screenWidth = 16;
int screenHeight = 2;

void setup()
{
 lcd.begin(16, 2);  // initializes the 16x2 LCD
  mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.print("AT+CLIP=1\r\n");
 lcd.clear();
  lcd.setCursor(0,1); 
   lcd.print("GSM/GPRS DEVICE");
  lcd.setCursor(0,0); 
  lcd.print("Calibrating:");
 
//------------------------------Calibrate ---------------------------------------
    for(int i=0;i<100;i++)
  {
   
   delay(100);
   lcd.setCursor(13,0);
   lcd.print(i);
   lcd.print("%");
  }
  //------------------------------Calibrate ---------------------------------------
 lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Connecting");  
  lcd.setCursor(0,1); 
  lcd.print("GPRS");
  Connection();
  lcd.clear();
}

void loop()
{
  gas_value=analogRead(sensor);
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);

/*    float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
*/
int HCval = analogRead(1);
  HCval = map(HCval, 0, 1023, 10,1000);

  gas_value = map(gas_value, 0, 1023, 300, 9000);
/*  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");*/

  
  lcd.setCursor(0,0);           //sets the cursor at row 0 column 0
  lcd.print("HC:"); 
  lcd.print(HCval); 
    lcd.print(" PPM"); 
  lcd.setCursor(0,1);           //sets the cursor at row 1 column 2
  lcd.print("CO:");     // prints HELLO WORLD
 float covalue=(gas_value/9000);

 if(covalue<0.25||HCval<2500)
 
 RGB(0,255,0);
 else if((covalue>=0.25&&covalue<0.3)||(HCval>=2500&&HCval<3000))
 RGB(255,2,0); 
 else
 RGB(255,0,0); 
 
 
  
  lcd.print(covalue);
  lcd.print(" %"); 
Send2thingspeak(HCval,covalue);
   
  if (mySerial.available())
    Serial.write(mySerial.read());


}





void RGB(int R,int G,int B)
{
        digitalWrite(Blue, B);
        analogWrite(Red, R);
         digitalWrite(Green, G);
}
