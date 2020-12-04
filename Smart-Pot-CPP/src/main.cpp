// Includen van alle benodigde libraries
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <ESP32Servo.h>

#include "ultrasonicSensor.h"
#include "grondVochtigheid.h"
#include "lichtSterkte.h"
#include "ledController.h"

// Definitions


/*
// Const int's van pins
const int DHTPIN = 14;
const int servopin = 15;
const int echoPin = 26;
const int grondPin = 33;
const int lichtPin1 = 32;
const int lichtPin2 = 35;
const int lichtPin3 = 34;
const int greenpin = 2;
const int redpin = 4;
const int trigPin = 27;
*/

// magic number handlers
const int DHTTYPE = DHT11;
const int honderdWaarde = 100;
const int maxwaardeSensor = 4095;
const int DHTPIN = 14;
// Class declaraties
DHT dht(DHTPIN, DHTTYPE);
ultrasonicSensor ultrasonicSensor1(27, 26);
grondVochtigheid grondVochtigheidsSensor1(33);
ledController RGBLed1(2,4);
lichtSterkte lichtSensor1(32);
lichtSterkte lichtSensor2(35);
lichtSterkte lichtSensor3(34);

StaticJsonDocument<200> doc;


// Declaratie van WiFi netwerken die gebruikt kunnen worden

//const char* ssid = "schenktol";
//const char* password = "TLE143TLE";

//const char* ssid = "wjavandertol";
//const char* password = "WT3030wt";

const char* ssid = "12connect";
const char* password = "";

// Declaratie van de eindbestemming
const char* serverName = "http://smartpot.nealgeilen.nl/api/addData";

//const char* serverName = "https://collect2.com/api/02f27a5d-b70b-4cc2-b451-fd9e89be984f/datarecord/";

void giveWater()
{
  int servoPin = 15;
  int moisture = grondVochtigheidsSensor1.getMoisture();
  if (moisture < 50)
  {
    Servo myservo;
    myservo.attach(servoPin);
    myservo.write(180);
    delay(1000);
    myservo.write(90);
  }
}

void setLedStatus()
{
  int distance = ultrasonicSensor1.getRawData();
  
  if (distance > 25)
  {
    RGBLed1.setLedStatusVol();
  }

  if (distance < 5)
  {
    RGBLed1.setLedStatusLeeg();
  }
}

void setup() 
{
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Verbonden met WiFi, met Ip adres: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  const int timerDelaywaarde = 1000;
  unsigned long lastTime = 0;
  unsigned long timerDelay = timerDelaywaarde;
  setLedStatus();
  giveWater();

  if ((millis() - lastTime) > timerDelay) 
  {
   
    if(WiFi.status()== WL_CONNECTED)
    {
      //Lees alle sensoren uit

      //ultrasone sensor
      ultrasonicSensor1.getRawData();
      
      // DHT sensor
      dht.readHumidity();
      dht.readTemperature();

      // Grondvochtigheids sensor
      grondVochtigheidsSensor1.getMoisture();

      // Lichtsterkte sensoren
      lichtSensor1.pullData();
      lichtSensor2.pullData();
      lichtSensor2.pullData();

      // Procentuele omrekening van sensorwaardes
      ultrasonicSensor1.processData();
      grondVochtigheidsSensor1.processMoistureToPercent();
      lichtSensor1.processData();
      lichtSensor2.processData();
      lichtSensor3.processData();

      // Printen van alle onbewerkte variabelen
      ultrasonicSensor1.printRawData();
      grondVochtigheidsSensor1.printRawData();
      lichtSensor1.printRawData();
      lichtSensor2.printRawData();
      lichtSensor3.printRawData();

      // Print alle waardes uit die gepost worden
      ultrasonicSensor1.printProcessedData();
      grondVochtigheidsSensor1.printProcessedData();
      lichtSensor1.printProcessedData();
      lichtSensor2.printProcessedData();
      lichtSensor3.printProcessedData();

      // Data naar string
      String distance1 = ultrasonicSensor1.dataToString();
      String strGrondVochtigheid1 = grondVochtigheidsSensor1.dataToString();
      String strLichtSterkte1 = lichtSensor1.dataToString();
      String strLichtSterkte2 = lichtSensor2.dataToString();
      String strLichtSterkte3 = lichtSensor3.dataToString();

      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-AUTH-TOKEN", "TEST");
      http.addHeader("X-AUTH-ID", "wajdhlawkjhdlawjkdhawkjdh");

      /*http.addHeader("Temperatuur", strtemperatuur);
      http.addHeader("Luchtvochtigheid", strluchtvochtigheid);
      http.addHeader("Grondvochtigheid", strgrondvochtigheid);
      http.addHeader("Waterniveau", strwaterniveau);
      http.addHeader("Lichtsterkte1", strlichtSterkte1);
      http.addHeader("Lichtsterkte2", strlichtSterkte2);
      http.addHeader("Lichststerkte3", strlichtSterkte3); */
      
      int httpResponseCode = http.POST("{ \"Temperatuur\": "+strtemperatuur+" , \"Luchtvochtigheid\": "+humidity hier+" , \"Grondvochtigheid\": "+strGrondVochtigheid1+" , \"Waterniveau\": "+distance1+" , \"Lichtsterkte1\": "+strLichtSterkte1+" , \"Lichtsterkte2\" : "+strLichtSterkte2+" , \"Lichtsterkte3\" : "+strLichtSterkte3+"}");
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      //Serial.print("Test: ");
      //Serial.println(response);      
      //Serial.println(strwaterniveau);

      // Schoon alles op
      
      http.end();
    }
    
    else 
    {
      Serial.println("WiFi Disconnected");
    }   
    lastTime = millis();

    
  }
 
    
}

int hoi()
{
  int distance = ultrasonicSensor1.getRawdata();
  if (distance == 0)
  {
    pinMode(pinG, HIGH);

  }

}

if (rawData < 50)
    {
        Servo myservo;
        myservo.attach(servopin); 
        myservo.write(180);
        delay(1000);
        myservo.write(90);
    }