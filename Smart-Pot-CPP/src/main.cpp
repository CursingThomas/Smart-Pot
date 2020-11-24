// Includen van alle benodigde libraries
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <ESP32Servo.h>

// Definitions
#define DHTTYPE DHT11

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

// magic number handlers
const int procentHulpwaarde = -1;
const int nulWaarde = 0;
const int potDiepte = 30;
const int grensWaardepostUpdate = 10;
const int procentRekenwaarde = 100;
const int sensorRekenwaarde = 4095;
const int timerDelaywaarde = 1000;

// Declaratie variabeles
String strluchtvochtigheid;
String strtemperatuur;
String strgrondvochtigheid;
String strlichtsterkte1;
String strlichtsterkte2;
String strlichtsterkte3;
String strwaterniveau;

double lichtSterkte1;
double lichtSterkte2;
double lichtSterkte3;


int sensorValueGrond; 
int postCounter;

long duration;
unsigned long lastTime = nulWaarde;
unsigned long timerDelay = timerDelaywaarde;

// Aanroepen van benodigdheden voor miscellaneous functies binnen de code
DHT dht(DHTPIN, DHTTYPE);
StaticJsonDocument<200> doc;
Servo myservo;

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

int potLed(int distance)
{
  if (distance < 5)
  {
    digitalWrite(greenpin, HIGH);
    digitalWrite(redpin,LOW);
    
  }

  if (distance > 25)
  {
    digitalWrite(greenpin, LOW);
    digitalWrite(redpin, HIGH);
  }
  return 0;
}

int ultraSensor()
{
  // Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // Natuurkundige berekening voor de hoeveelheid water in het reservoir
  int distance = duration * 0.034 / 2;

  return distance;
}

String parsingProcesstring(String x, int y)
{
  x = x + y;

  return x;
}

int lichtSterktenaarProcenten(int x)
{
  int honderdWaarde = 100;
  int lichtdeler = 4095;
  (x * honderdWaarde) / lichtdeler;

  return x;
}

int printOpdrachten(int distance, double dbltemperatuur, double dblluchtvochtigheid, int sensorValueGrond, int procentlichtSterkte1, int procentlichtSterkte2, int procentlichtSterkte3)
{
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Temperatuur: ");
  Serial.println(dbltemperatuur);
  Serial.print("Luchtvochtigheid: ");
  Serial.println(dblluchtvochtigheid);
  Serial.print("Grondvochtigheid: ");
  Serial.println(sensorValueGrond);
  Serial.print("Lichtsterkte sensor 1: ");
  Serial.println(procentlichtSterkte1);
  Serial.print("Lichtsterkte sensor 2: ");
  Serial.println(procentlichtSterkte2);
  Serial.print("Lichtsterkte sensor 3: ");
  Serial.println(procentlichtSterkte3);

  return 0;
}

int distanceNaarprocenten(int distance)
{ 
  int potDiepte = 30;
  int honderdWaarde = 100;
  int procentDistance = ((distance * honderdWaarde) / potDiepte) - honderdWaarde;

  return procentDistance;
}

int grondVochtigheidNaarprocenten(int sensorValueGrond)
{
  int grondsensorRekenwaarde = 4095;
  int negatiefRekenwaarde = -1;
  int honderdWaarde = 100;
  int procentGrondvochtigheid = ((((sensorValueGrond - grondsensorRekenwaarde) * negatiefRekenwaarde) * honderdWaarde) / honderdWaarde);

  return procentGrondvochtigheid;
}

int grenswaardeGrondvochtigheid()
{
  if (sensorValueGrond < 50)
  {
    myservo.write(180);
    delay(1000);
    myservo.write(90);
  }

  return 0;
}


  



void setup() 
{
  Serial.begin(115200);
  myservo.attach(servopin);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(greenpin, OUTPUT);
  pinMode(redpin, OUTPUT);
  //pinMode(redPin, OUTPUT);
  //pinMode(greenPin, OUTPUT);

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
  int distance = ultraSensor();
  potLed(distance);

  if ((millis() - lastTime) > timerDelay) 
  {
   
    if(WiFi.status()== WL_CONNECTED)
    {
      //Lees alle sensoren uit
      distance = ultraSensor();

      // DHT sensor
      double dblluchtvochtigheid = dht.readHumidity();
      double dbltemperatuur = dht.readTemperature();

      // Grondvochtigheids sensor
      int sensorValueGrond = analogRead(grondPin); 

      // Lichtsterkte sensoren
      int lichtSterkte1 = analogRead(lichtPin1);
      int lichtSterkte2 = analogRead(lichtPin2);
      int lichtSterkte3 = analogRead(lichtPin3);
      int procentDistance = distanceNaarprocenten(distance);
      int procentGrondvochtigheid = grondVochtigheidNaarprocenten(sensorValueGrond);
      int procentlichtSterkte1 = lichtSterktenaarProcenten(lichtSterkte1);
      int procentlichtSterkte2 = lichtSterktenaarProcenten(lichtSterkte2);
      int procentlichtSterkte3 = lichtSterktenaarProcenten(lichtSterkte3);
      

    
      // Print alle waardes uit (voor debugging)
      printOpdrachten(distance, dbltemperatuur, dblluchtvochtigheid, procentlichtSterkte1, procentlichtSterkte2, procentlichtSterkte3);

      

      // Procentuele omrekening van alle getallen

      
      // Omzetten van alle getallen naar strings, zo kunnen ze worden meegegeven in de JSON string
      String strlichtSterkte1 = parsingProcesstring(strlichtsterkte1, procentlichtSterkte1);
      String strlichtSterkte2 = parsingProcesstring(strlichtsterkte2, procentlichtSterkte2);
      String strlichtSterkte3 = parsingProcesstring(strlichtsterkte3, procentlichtSterkte3);
      String strtemperatuur = parsingProcesstring(strtemperatuur, dbltemperatuur);
      String strluchtvochtigheid = parsingProcesstring(strluchtvochtigheid, dblluchtvochtigheid);
      String strwaterniveau = parsingProcesstring(strwaterniveau, procentDistance);
      String strgrondvochtigheid = parsingProcesstring(strgrondvochtigheid, procentGrondvochtigheid);

      // Grenswaarde van de servo
      grenswaardeGrondvochtigheid();
      
      
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-AUTH-TOKEN", "TEST");
      http.addHeader("X-AUTH-ID", "wajdhlawkjhdlawjkdhawkjdh");
      http.addHeader("Temperatuur", strtemperatuur);
      http.addHeader("Luchtvochtigheid", strluchtvochtigheid);
      http.addHeader("Grondvochtigheid", strgrondvochtigheid);
      http.addHeader("Waterniveau", strwaterniveau);
      http.addHeader("Lichtsterkte1", strlichtsterkte1);
      http.addHeader("Lichtsterkte2", strlichtsterkte2);
      http.addHeader("Lichststerkte3", strlichtsterkte3);
      
  int httpResponseCode = http.POST("{ \"Temperatuur\": "+strtemperatuur+" , \"Luchtvochtigheid\": "+strluchtvochtigheid+" , \"Grondvochtigheid\": "+strgrondvochtigheid+" , \"Waterniveau\": "+strwaterniveau+" , \"Lichtsterkte1\": "+strlichtsterkte1+" , \"Lichtsterkte2\" : "+strlichtsterkte2+" , \"Lichtsterkte3\" : "+strlichtsterkte3+"}");
  String response = http.getString();
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

      //Serial.print("Test: ");
      //Serial.println(response);      
      //Serial.println(strwaterniveau);

        
      // Schoon alles op
      
      strtemperatuur = "";
      strluchtvochtigheid = "";
      strgrondvochtigheid = "";
      strlichtsterkte1 = "";
      strwaterniveau = "";
      strlichtsterkte1  = "";
      strlichtsterkte2 = "";
      strlichtsterkte3 = "";
      postCounter = nulWaarde;
      http.end();
    }
    
    else 
    {
      Serial.println("WiFi Disconnected");
    }   
    lastTime = millis();

    
  }
 
 

}