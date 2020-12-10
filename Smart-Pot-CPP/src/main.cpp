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
#include "waterPump.h"

#define DHTTYPE DHT11

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
const int honderdWaarde = 100;
const int maxwaardeSensor = 4095;
const int DHTPIN = 14;
//String strLuchtVochtigheid;
//String strTemperatuur;

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
const char* serverName = "http://smartpot.nealgeilen.nl/api";

//const char* serverName = "https://collect2.com/api/02f27a5d-b70b-4cc2-b451-fd9e89be984f/datarecord/";

String parseDHTNaarString(double x)
{
  String y;
  y = y + x;

  return y;
}

String clearStringFunction(String x)
{
  x = "";

  return x;
}

void giveWaterServo()
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

void giveWaterPomp()
{
  int moisture = grondVochtigheidsSensor1.getMoisture();
  if (moisture < 50)
  {
    waterPump waterPump1(5);
    waterPump1.giveWater(10);
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

void printMessagesProcessedLichtSensor(int count)
{
  Serial.print("Processed data lichtsensor ");
  Serial.print(count);
  Serial.print(": ") ;
}

void printMessagesRawDataLichtSensor(int count)
{
  Serial.print("Raw data lichtsensor ");
  Serial.print(count);
  Serial.print(": ") ;
}
void setup() 
{
  Serial.begin(9600);
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
  giveWaterServo();

  if ((millis() - lastTime) > timerDelay) 
  {
   
    if(WiFi.status()== WL_CONNECTED)
    {
      //Lees alle sensoren uit

      //ultrasone sensor
      ultrasonicSensor1.getRawData();
      
      // DHT sensor
      double luchtVochtigheid = dht.readHumidity();
      double temperatuur = dht.readTemperature();

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
      printMessagesRawDataLichtSensor(1);
      lichtSensor1.printRawData();
      printMessagesRawDataLichtSensor(2);
      lichtSensor2.printRawData();
      printMessagesRawDataLichtSensor(3);
      lichtSensor3.printRawData();

      // Print alle waardes uit die gepost worden
      ultrasonicSensor1.printProcessedData();
      grondVochtigheidsSensor1.printProcessedData();
      printMessagesProcessedLichtSensor(1);
      lichtSensor1.printProcessedData();
      printMessagesProcessedLichtSensor(2);
      lichtSensor2.printProcessedData();
      printMessagesProcessedLichtSensor(3);
      lichtSensor3.printProcessedData();
      
      // Data naar string
      String distance1 = ultrasonicSensor1.dataToString();
      String strGrondVochtigheid1 = grondVochtigheidsSensor1.dataToString();
      String strLichtSterkte1 = lichtSensor1.dataToString();
      String strLichtSterkte2 = lichtSensor2.dataToString();
      String strLichtSterkte3 = lichtSensor3.dataToString();
      String strTemperatuur = parseDHTNaarString(temperatuur);
      String strLuchtVochtigheid = parseDHTNaarString(luchtVochtigheid);
      
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-AUTH-TOKEN", "TEST");
      http.addHeader("X-AUTH-ID", "wajdhlawkjhdlawjkdhawkjdh");      
      int httpResponseCode = http.POST("{ \"Temperatuur\": "+strTemperatuur+" , \"Luchtvochtigheid\": "+strLuchtVochtigheid+" , \"Grondvochtigheid\": "+strGrondVochtigheid1+" , \"Waterniveau\": "+distance1+" , \"Lichtsterkte1\": "+strLichtSterkte1+" , \"Lichtsterkte2\" : "+strLichtSterkte2+" , \"Lichtsterkte3\" : "+strLichtSterkte3+"}");
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      
      // Schoon alles op
      distance1 = ultrasonicSensor1.clearString();
      strGrondVochtigheid1 = grondVochtigheidsSensor1.clearString();
      strLichtSterkte1 = lichtSensor1.clearString();
      strLichtSterkte2 = lichtSensor2.clearString();
      strLichtSterkte3 = lichtSensor3.clearString();
      strTemperatuur = clearStringFunction(strTemperatuur);
      strLuchtVochtigheid = clearStringFunction(strLuchtVochtigheid);

      http.end();
    }
    
    else 
    {
      Serial.println("WiFi Disconnected");
    }   
    lastTime = millis();
  }
}