#include <ESP8266WiFi.h>
#include <time.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "OakOLED.h"

#define OLED_RESET LED_BUILTIN  //4

OakOLED oled;

const char* ssid = "HIGH5 COFFEE T2 2.4G";
const char* password = "50ngothinham";

int ledPin = 16;

int timezone = 7 * 3600;
int dst = 0;


void setup() {

  oled.begin();

  // Clear the buffer.
 oled.clearDisplay();
  oled.display();
  
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);

  Serial.begin(115200);

  oled.setTextSize(1);
  oled.setTextColor(1);
  
  oled.setCursor(0,0);
  oled.println("Wifi connecting to ");
  oled.println( ssid );

  WiFi.begin(ssid,password);

 oled.println("\nConnecting");

 oled.display();

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      oled.print("."); 
      oled.display();       
  }

  // Clear the buffer.
  oled.clearDisplay();
  oled.display();
  oled.setCursor(0,0);
  oled.println("Wifi Connected!");
  oled.print("IP:");
  oled.println(WiFi.localIP() );
  oled.display();

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  oled.println("\nWaiting for NTP...");

  while(!time(nullptr)){
     Serial.print("*");
     
     delay(1000);
  }
  oled.println("\nTime response....OK"); 
  oled.display();  
  delay(1000);

  oled.clearDisplay();

  oled.setTextSize(2);
  oled.setCursor(3,24);
  oled.print("Hi Phuong!");
  oled.display();
  delay(1000);

  oled.clearDisplay();
  oled.display();
}

void loop() {
  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  
  Serial.print(p_tm->tm_mday);
  Serial.print("/");
  Serial.print(p_tm->tm_mon + 1);
  Serial.print("/");
  Serial.print(p_tm->tm_year + 1900);
  
  Serial.print(" ");
  
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.println(p_tm->tm_sec);
  
  // Clear the buffer.
 oled.clearDisplay();

  oled.setTextSize(3);
  oled.setTextColor(1);
  
  oled.setCursor(0,0);
  oled.print(p_tm->tm_hour);
  oled.print(":");
  if( p_tm->tm_min <10)
    oled.print("0"); 
  oled.print(p_tm->tm_min);
  
  oled.setTextSize(2);
  oled.setCursor(90,5);
  oled.print(".");
  if( p_tm->tm_sec <10)
  oled.print("0"); 
  oled.print(p_tm->tm_sec);

  oled.setTextSize(2);
  oled.setCursor(0,40);
  oled.print(p_tm->tm_mday);
  oled.print("/");
  oled.print(p_tm->tm_mon + 1);
  oled.print("/");
  oled.print(p_tm->tm_year + 1900);

  oled.display();

  delay(1000); // update every 1 sec

}
