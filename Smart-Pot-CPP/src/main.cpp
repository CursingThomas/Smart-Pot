//* Include Third-party libraries.
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

//* Include my classes.
#include <MyDHT.h>
#include <ultrasonicSensor.h>
#include <grondVochtigheid.h>
#include <lichtSterkte.h>
#include <ledController.h>
#include <waterPump.h>
#include <PotentioMeter.h>

//* Define type of DHT sensor (define instead of const because library asks for a define).
#define DHTTYPE DHT11

//* Magic number variables.
const int honderdWaarde = 100;
const int maxwaardeSensor = 4095;
const int DHTPIN = 14;
const int echoPin = 27;
const int trigPin = 26;
const int grondPin = 33;
const int redPin = 2;
const int greenPin = 4;
const int lichtPin1 = 32;
const int lichtPin2 = 35;
const int lichtPin3 = 34;
const int dhtHelpwaarde = 6;
const int potPin = 10;

//* Initializing all objects.
UltrasonicSensor ultrasonicSensor1(echoPin, trigPin);
GrondVochtigheid grondVochtigheidsSensor1(grondPin);
LedController RGBLed1(redPin,greenPin);
LichtSterkte lichtSensor1(lichtPin1, "Lichtsensor 1");
LichtSterkte lichtSensor2(lichtPin2, "Lichtsensor 2");
LichtSterkte lichtSensor3(lichtPin3, "Lichtsensor 3");
MyDHT dht(DHTPIN, DHTTYPE, dhtHelpwaarde);
PotentioMeter potMeter1(potPin); 

//* Declaring usable Wi-Fi networks.
//const char* ssid = "schenktol";
//const char* password = "TLE143TLE";

const char* ssid = "wjavandertol";
const char* password = "WT3030wt";

//const char* ssid = "12connect";
//const char* password = "";

//* Declaring the endpoint of the HTTP Post Request.
const char* serverName = "https://smartpot.nealgeilen.nl/api/pot/addData";

//* Function made to control a pump which has dependencies with the grondVochtigheid class.
void giveWaterPomp()
{
  const int pompPin = 5;
  const int timerWaarde = 10;

  int moisture = grondVochtigheidsSensor1.getMoisture();
  moisture = grondVochtigheidsSensor1.processMoistureToPercent();
  int grenswaarde = potMeter1.readValuePot();
  grenswaarde = potMeter1.getProcessedData();
  if (moisture < grenswaarde)
  {
    WaterPump waterPump1(pompPin);
    waterPump1.giveWater(timerWaarde);
  }  
}

//* Function made to control a RGB LED which has dependencies with the UltrasonicSensor class.
void setLedStatus()
{
  int distance = ultrasonicSensor1.getRawData();
  const int volReservoir = 25;
  const int leegReservoir = 5;
  
  if (distance > volReservoir)
  {
    RGBLed1.setLedStatusVol();
  }

  if (distance < leegReservoir)
  {
    RGBLed1.setLedStatusLeeg();
  }
}

void getDatafromsensors()
{
  //* Gathers raw data of all sensors.
  ultrasonicSensor1.getRawData(); // Gathers raw data of ultrasonic sensor.
      


  grondVochtigheidsSensor1.getMoisture(); // Gathers raw data of soil moisture sensor.

  lichtSensor1.pullData(); // Gathers raw data of LDR1.
  lichtSensor2.pullData(); // Gathers raw data of LDR2.
  lichtSensor2.pullData(); // Gathers raw data of LDR3.
}

void processDatafromsensors()
{
  //* Compute raw data gathered before to processed data which is representative.
  ultrasonicSensor1.processData(); // Computes raw data to processed data from ultrasonic sensor.

  grondVochtigheidsSensor1.processMoistureToPercent(); // Computes raw data to processed data from soil moisture sensor.

  lichtSensor1.processData(); // Computes raw data to processed data from LDR1.
  lichtSensor2.processData(); // Computes raw data to processed data from LDR2.
  lichtSensor3.processData(); // Computes raw data to processed data from LDR3.
}

void printDatafromsensors()
{
  //* Print out all the raw data gathered.
  dht.printTemperatuur(); // Prints raw data from DHT11.
  dht.printLuchtVochtigheid(); // Prints raw data from DHT11.

  ultrasonicSensor1.printRawData(); // Prints raw data from ultrasonic sensor.

  grondVochtigheidsSensor1.printRawData(); // Prints raw data from soil moisture sensor.

  lichtSensor1.printRawData(); // Prints raw data from LDR1.
  lichtSensor2.printRawData(); // Prints raw data from LDR2.
  lichtSensor3.printRawData(); // Prints raw data from LDR3.
}

void printProcesseddatafromsensors()
{
  //* Print all final computed data which will be posted to the website.
  ultrasonicSensor1.printProcessedData(); // Prints processed data from ultrasonic sensor.

  grondVochtigheidsSensor1.printProcessedData(); // Prints processed data from soil moisture sensor.

  lichtSensor1.printProcessedData(); // Prints processed data from LDR1.
  lichtSensor2.printProcessedData(); // Prints processed data from LDR2.
  lichtSensor3.printProcessedData(); // Prints processed data from LDR3.
}

//* Normal void setup()
void setup() 
{
  Serial.begin(9600); // Set baudrate to 9600.
  dht.begin();
  WiFi.begin(ssid, password); // Call to class function .begin with parameters ssid and password.
  Serial.println("Connecting"); // When the above line of code is executed, print that the MC is connecting to WiFi.
  while(WiFi.status() != WL_CONNECTED) // While WiFi is not connected, print out a . to indicate the microcontroller is trying to connect to the WiFi
  {
    Serial.print(".");
  }
  Serial.println(""); // Print a clear line in the console
  Serial.print("Verbonden met WiFi, met Ip adres: "); // Print that the microcontroller has succesfully connected to the internet with the following ip address.
  Serial.println(WiFi.localIP());
}

//* Normal void loop()
void loop()
{
  const int timerDelaywaarde = 1000; // Sets the amount of time the interval between two HTTP Post Request.
  unsigned long lastTime = 0; // Sets variable used to calculate if timing has been met.
  unsigned long timerDelay = timerDelaywaarde; // Check two variables.
  setLedStatus(); // Executes this function.
  giveWaterPomp(); // Executes this function.

  if ((millis() - lastTime) > timerDelay) // Sets if statement to check if requirements are met.
  {
   
    if(WiFi.status()== WL_CONNECTED) // Sets if statement to check if requirements are met.
    {
      double luchtVochtigheid = dht.readHumidity(); // Gathers raw data of DHT11 sensor.
      double temperatuur = dht.readTemperature(); // Gathers raw data of DHT11 sensor.
      getDatafromsensors();
      processDatafromsensors();
      printDatafromsensors();
      printProcesseddatafromsensors();   
     
      //* Converts processed data to a datatype of String.
      String distance1 = ultrasonicSensor1.dataToString(); // Converts processed data from ultrasonic sensor to datatype String.
      String strGrondVochtigheid1 = grondVochtigheidsSensor1.dataToString(); // Converts processed data from soil moisture sensor to datatype String.
      String strLichtSterkte1 = lichtSensor1.dataToString(); // Converts processed data from LDR1 to datatype String.
      String strLichtSterkte2 = lichtSensor2.dataToString(); // Converts processed data from LDR2 to datatype String.
      String strLichtSterkte3 = lichtSensor3.dataToString(); // Converts processed data from LDR3 to datatype String.
      String strTemperatuur = dht.dataToString(temperatuur); // Converts processed data from DHT11 to datatype String.
      String strLuchtVochtigheid = dht.dataToString(luchtVochtigheid); // Converts processed data from DHT11 to datatype String.

      //* HTTP Post Request
      HTTPClient http; // Initializes object.
      http.begin(serverName); // Calls to function. begin with parameter serverName.
      http.addHeader("Content-Type", "application/json"); // Adds a header to the HTTP Post Request.
      http.addHeader("X-AUTH-TOKEN", "TEST"); // Adds a header to the HTTP Post Request.
      http.addHeader("X-AUTH-ID", "wajdhlawkjhdlawjkdhawkjdh"); // Adds a header to the HTTP Post Request.  
      int httpResponseCode = http.POST("{ \"Temperatuur\": "+strTemperatuur+" , \"Luchtvochtigheid\": "+strLuchtVochtigheid+" , \"Grondvochtigheid\": "+strGrondVochtigheid1+" , \"Waterniveau\": "+distance1+" , \"Lichtsterkte1\": "+strLichtSterkte1+" , \"Lichtsterkte2\" : "+strLichtSterkte2+" , \"Lichtsterkte3\" : "+strLichtSterkte3+"}"); // Send the actual HTTP Post Request.
      String response = http.getString(); // Gather the response the website gives.
      Serial.print(response);
      Serial.print("HTTP Response code: "); // Print message.
      Serial.println(httpResponseCode); // print the actual response the website gives.
      
      //* Clear all strings to use them next time.
      distance1 = ultrasonicSensor1.clearString();
      strGrondVochtigheid1 = grondVochtigheidsSensor1.clearString();
      strLichtSterkte1 = lichtSensor1.clearString();
      strLichtSterkte2 = lichtSensor2.clearString();
      strLichtSterkte3 = lichtSensor3.clearString();
      strTemperatuur = dht.clearString();
      strLuchtVochtigheid = dht.clearString();
      http.end(); // End the HTTP Post Request.
    }
    
    else 
    {
      Serial.println("WiFi Disconnected"); // Prints message if WiFi gets disconnected.
    }   
    lastTime = millis(); // Make sure if statement for all code above stays valid.

    while(WiFi.status() != WL_CONNECTED) // While WiFi is not connected, print out a . to indicate the microcontroller is trying to connect to the WiFi
  {
    Serial.print(".");
  }
  }
}