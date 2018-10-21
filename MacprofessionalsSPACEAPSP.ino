/* Code Written By Team MACPROFESSIONALS (Narti G. & Bleron Zh.) For NASA Space Apps Challange 2018
 *  Pinout : 
 *  Temperature (Out) (Middle pin) =>> Pin 2 Arduino
 *  FlameSensor (D0) (Middle pin) =>> Pin 12 Arduino
 *  SmokeSensor (A0) (Left Pin) =>> Pin A0 Arduino
 *  BLuetooth : RX (11) TX (10) 
 *  Real Time Clock : CLK (6) DAT (7) RST (8)
 *  SD CARD : MOSI (51) MISO (50) SCK (52) CS (53)
 *  Drone LED Red =>> Pin 22
 *  Drone LED Green =>> Pin 23
 *  Drone LED Blue =>> Pin 24
 */


#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <virtuabotixRTC.h>
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT22 

SoftwareSerial btSerial (10, 11); //RX dhe TX UART

DHT dht(DHTPIN, DHTTYPE); 

virtuabotixRTC myRTC(6, 7, 8);
//MOSI (51) MISO (50) SCK (52) SS (53)
//Temperature Variables
float h;
float t;
float f;
String _Humidity;
String _Temperature;
String _HeatIndex;
//End Temperature Variables

//Start Flame Sensor Variables
int value_Flame;
int pin_Flame = 12;
String _FlameValue;
//End Flame Sensor Variables

//Start Smoke Sensor
int average;
int SmokeSensor_val;
int SmokeSensor_pin = A0;
String SmokeSensor_Output;
//End Smoke Sensor

//SD Card 
File myFile;
String final_val;
//End Sd Card
String read_bluetooth;
int red_led = 22;
int blue_led = 23;
int green_led = 24;

bool joinRecording;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  dht.begin();
  pinMode(pin_Flame, INPUT);
  
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  digitalWrite(red_led, HIGH);
  digitalWrite(blue_led, HIGH);
  digitalWrite(green_led, HIGH);
}
//  myRTC.updateTime(); myRTC.hours myRTC.minutes
void loop() {
  delay(1500);
  
if (btSerial.available() > 0) {
    read_bluetooth = btSerial.read();
    Serial.println(read_bluetooth);
 }
    btSerial.println("$idle");
    Serial.println("Idle");
    ReadSerial();
    
     if (read_bluetooth == "49") {
      joinRecording = true;
      read_bluetooth = "";
      Recorder();
     }
  
//delay(2000);

//GetTemperatureValues();
//delay(50);
//DetectFire();
//delay(50);
//DetectSmoke();

//WriteSdCard();
  read_bluetooth = "";
}

void Recorder() {
  while (joinRecording == true) {
    Serial.println("Looped :)");
    btSerial.println("%recording");
    delay(2000);

    GetTemperatureValues();
    delay(50);
    DetectFire();
    delay(50);
    DetectSmoke();
    delay(50);
    myRTC.updateTime();
    String TimeTotal = String(myRTC.dayofmonth) + "/" + String(myRTC.month) + "/" + String(myRTC.year) + " " + String(myRTC.hours) + ":" + String(myRTC.minutes) + ":" + String(myRTC.seconds);

    final_val = TimeTotal + "," + _Temperature + "," + _Humidity + ","+ _HeatIndex + "," + _FlameValue + "," + SmokeSensor_Output;

    WriteSdCard();
    
    Serial.print("Final Val : ");
    Serial.println(final_val);
    
    ReadSerial();

    
    if (read_bluetooth == "50") {
      //EXIT RECORDING
     joinRecording = false;
//      digitalWrite(drone_led, LOW);
      break;
    }

    if (read_bluetooth == "52") {
      btSerial.println("fetch_start");
      joinRecording = false;
      FetchSDCard();
      break;
    }

    read_bluetooth = "";
  }
}

void ReadSerial() {
   if (btSerial.available() > 0) {
   read_bluetooth = btSerial.read();
    Serial.write(btSerial.read());
   }
   if (Serial.available() > 0) {
    btSerial.write(Serial.read());
   }
   btSerial.flush();
   Serial.flush();
}



void WriteSdCard() {
 Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (0);
  }
  Serial.println("initialization done.");
  Serial.println(" ");

  myFile = SD.open("log.txt", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing to log.txt...");
    Serial.println(" ");
    myFile.println(final_val);
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening test.txt");
  }

  delay(1000);
  }

  

 void FetchSDCard() {
   Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (0);
  } 

  myFile = SD.open("log.txt");

  if (myFile) {
    Serial.println("log.txt:");
    btSerial.println("_");
    
    while (myFile.available()) {
      Serial.write(myFile.read());
      btSerial.write(myFile.read());
      delay(5);
    }
    myFile.close();
    btSerial.println("]");
  } else {
    Serial.println("error opening log.txt");
  }
    
 }

void DetectFire() {
value_Flame = digitalRead(pin_Flame);
 if (value_Flame == 0) {
  _FlameValue = "Fire DETECTED!";
 }else {
  _FlameValue = "No Signs Of Fire";
 }
}

void GetTemperatureValues() {
 h = dht.readHumidity();
 t = dht.readTemperature();
 f = dht.readTemperature(true);

 if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
  }
   float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

   _Humidity = String(h);
   _Temperature = String(t);
   _HeatIndex = String(hic);
 }

void DetectSmoke() {
  SmokeSensor_val = analogRead(SmokeSensor_pin);
  int tot_avg;
  tot_avg = average + 30;
  if (SmokeSensor_val > tot_avg) {
    SmokeSensor_Output = "Smoke Has Been Detected!";
  }else {
    SmokeSensor_Output = "No Signs Of Smoke"; 
 
  }
}


