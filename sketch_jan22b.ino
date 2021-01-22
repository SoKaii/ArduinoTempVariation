#include <DHTesp.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT11 

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 255;
const int colorB = 255;
const int BUTTON_PIN = 7;
int currentState;
int lastTemp;
int temp = 0;
bool clicked = false;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  dht.begin();  
  Serial.println("Here we go !");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
    
  lcd.setRGB(colorR, colorG, colorB);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readHumidity();
  currentState = digitalRead(BUTTON_PIN);
  if (currentState == 1 ) {
    clicked = false; 
    Serial.println(temperature);
  }
    if(temp == 0) {
      lcd.setCursor(0,0);
      lcd.print("");
      lastTemp = temperature;
      temp++;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Variation : ");
    if ( temperature - lastTemp > 0) {
      lcd.print("+");
      lcd.setRGB(255, 0, 0);
    } else if (temperature - lastTemp == 0) {
       lcd.setRGB(0, 255, 0);
    } else {
      lcd.setRGB(0, 0, 255);
    }
  
    lcd.println(temperature - lastTemp);
  
    lcd.setCursor(0, 1);
  
    lcd.print("PRESET : ");
    lcd.print(lastTemp);

  //BUTTON PART
   // read the state of the switch/button:
  
  if(currentState == 0 && clicked == false) {
    clicked = true;
    lcd.setCursor(0,0);
    lcd.print("");
    lastTemp = temperature;
    Serial.println("ACTION BOUTON");
  }
}
