#include <Servo.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
 
#define FIREBASE_HOST "prohek-4c689-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "4VznHQ2vtO0Gu2PQYZAcZarcDiCBmYxzjtCxY7VI"
#define WIFI_SSID "Muka datar"
#define WIFI_PASSWORD "Pandelva1!"


int fireSensorOnePin = D1;
int fireSensorTwoPin = D6;
int fireSensorThreePin = D5;
int waterSensorPin = A0;
int relayPin = D2;
int fireSensorOneValue = 0;
int fireSensorTwoValue = 0;
int fireSensorThreeValue = 0;
int waterSensorValue = 0;
int fireThreshold = 500;
int waterThreshold = 100;
int ledPin = D0;
int angle = 0;
Servo myservo;

void setup() {

  myservo.attach(D8);
  pinMode(fireSensorOnePin,INPUT);
  pinMode(fireSensorTwoPin,INPUT);
  pinMode(fireSensorThreePin,INPUT);
  pinMode(waterSensorPin,INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  myservo.write(180);
  Serial.begin(115200);

 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 Serial.print("connecting");
 while (WiFi.status() != WL_CONNECTED)
 {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 Serial.print("connected: ");
 Serial.println(WiFi.localIP());
 
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 if(Firebase.failed())
  {
  Serial.print(Firebase.error());
  }
  else{
  
  Serial.print("Firebase Connected");
  }
}

void loop() {
  fireSensorOneValue = analogRead(fireSensorOnePin);
  fireSensorTwoValue = analogRead(fireSensorTwoPin);
  fireSensorThreeValue = analogRead(fireSensorThreePin);
  waterSensorValue = analogRead(waterSensorPin);
  Serial.print("Fire Sensor One Value: ");
  Serial.print(fireSensorOneValue);
  Serial.print("Fire Sensor Two Value: ");
  Serial.print(fireSensorTwoValue);
  Serial.print("Fire Sensor Three Value: ");
  Serial.print(fireSensorThreeValue);
  if (waterSensorValue > waterThreshold) { 
    digitalWrite(ledPin, LOW); 
  } else {
    digitalWrite(ledPin, HIGH);
  }
  Serial.print(" Water Sensor Value: ");
  Serial.println(waterSensorValue);
  if (fireSensorOneValue > fireThreshold) {
    myservo.write(0);
    delay(1000);
    digitalWrite(relayPin, LOW);
  } else if (fireSensorTwoValue > fireThreshold) {
    myservo.write(90);
    delay(1000);
    digitalWrite(relayPin, LOW);
  } else if (fireSensorThreeValue > fireThreshold) {
    myservo.write(180);
    delay(1000);
    digitalWrite(relayPin, LOW);
  } else {
    digitalWrite(relayPin,HIGH);
  }
  int fire1 = analogRead(D1);
  Firebase.setInt("fire sensor 1", fire1);

  int fire2 = analogRead(D6);
  Firebase.setInt("fire sensor 2", fire2);

  int fire3 = analogRead(D5);
  Firebase.setInt("fire sensor 3", fire3);

  int water = analogRead(A0);

    Firebase.setInt("water sensor", water);
}