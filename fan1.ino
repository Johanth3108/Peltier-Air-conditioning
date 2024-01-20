#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"

//DS18B20 libs
#include <OneWire.h>
#include <DallasTemperature.h>

//mq135 libs
#include <SPI.h>
#include <Wire.h>
#include "MQ135.h"

//dht11 libs
#include <DFRobot_DHT11.h>

DFRobot_DHT11 DHT;
#define DHT11ONE_PIN 16
#define DHT11TWO_PIN 5

const char* ssid = "SURESH_HOME4G";
const char* password = "krishnakumari";

#define ONE_WIRE_BUS 4

#define RELAY_NO true
#define NUM_RELAYS 6
int relayGPIOs[NUM_RELAYS] = {14, 12, 13, 10, 1, 3};
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//airpurifier -> 14 -> D5
//fan -> 12 -> D6
//water pump -> 13 -> D7
//peltier -> 15 -> D8

int airpurifier = 14; //D5
int fan = 12; // D6
int water_pump = 13; // D7
int peltier_onoff = 10; // D5
int peltier_one = 3; // RX
int peltier_two = 1; // TX

int ap_con = 0;
int fan_con = 0;
int wp_con = 0;
int p_con = 0;

//ppm

int readD1;
int readD2;
int r_ppm = 0;
int p_ppm = 2;

ESP8266WebServer server(80);

void handleRoot() 
{
 String s = webpage;
 server.send(200, "text/html", s);
}

void ppm() 
{
  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();
  String ppm = String(air_quality);
  server.send(200, "text/plane", ppm);
}

void sens(){
  digitalWrite(r_ppm, HIGH); // Turn D1 On
  digitalWrite(p_ppm, LOW); // Turn D2 Off
  MQ135 rppm = MQ135(A0);
  String roomppm = String(rppm.getPPM());
  delay(1000);
  Serial.print(roomppm);

  digitalWrite(r_ppm, LOW); // Turn D1 On
  digitalWrite(p_ppm, HIGH); // Turn D2 Off
  MQ135 pppm = MQ135(A0);
  String purippm = String(pppm.getPPM());
  delay(200);
  Serial.print(purippm);

  DHT.read(DHT11ONE_PIN);
  String roomtmp = String(DHT.temperature);
  delay(200);

  DHT.read(DHT11TWO_PIN);
  String airtmp = String(DHT.temperature);
  delay(200);

  DHT.read(DHT11ONE_PIN);
  String roomhum = String(DHT.humidity);
  delay(200);

  DHT.read(DHT11TWO_PIN);
  String airhum = String(DHT.humidity);
  delay(200);

  sensors.requestTemperatures();
  String peltmp = String(sensors.getTempCByIndex(0));

  String values = roomtmp+","+airtmp+","+roomhum+","+airhum+","+peltmp+","+roomppm+","+purippm;
  server.send(200, "text/plane", values);
}

void ap_control() 
{
 if(ap_con == 1)
 {
  digitalWrite(airpurifier, HIGH);  //purifier ON
  ap_con = 0;
 }
 else if (ap_con == 0)
 {
  digitalWrite(airpurifier, LOW);  //purifier OFF
  ap_con = 1;
 }
 server.send(200, "text/plane", String(ap_con)); //state
}


void fan_control() 
{
 if(fan_con == 1)
 {
  digitalWrite(fan, HIGH);  //purifier ON
  fan_con = 0;
 }
 else if (fan_con == 0)
 {
  digitalWrite(fan, LOW);  //purifier OFF
  fan_con = 1;
 }
 server.send(200, "text/plane", String(fan_con)); //state
}

void water_pumpc() 
{
 if(wp_con == 1)
 {
  digitalWrite(water_pump, HIGH);  //waterpump ON
  wp_con = 0;
 }
 else if (wp_con == 0)
 {
  digitalWrite(water_pump, LOW);  //waterpump OFF
  wp_con = 1;
 }
 server.send(200, "text/plane", String(wp_con)); //state
}


void peltierc(){
  if(p_con == 1)
 {
  digitalWrite(peltier_onoff, HIGH);  //peltier ON
  p_con = 0;
 }
 else if (p_con == 0)
 {
  digitalWrite(peltier_onoff, LOW);  //peltier OFF
  p_con = 1;
 }
 server.send(200, "text/plane", String(wp_con)); //state
}

void peltierauto(){
  digitalWrite(peltier_onoff, LOW);
  digitalWrite(peltier_one, LOW);
  digitalWrite(peltier_two, LOW);
  p_con = 1;
  server.send(200, "text/plane", String(p_con)); //state
}

void peltierheat(){
  digitalWrite(peltier_onoff, HIGH);
  digitalWrite(peltier_one, HIGH);
  digitalWrite(peltier_two, HIGH);
  p_con = 1;
  server.send(200, "text/plane", String(p_con));
}

void peltiercold(){
  digitalWrite(peltier_onoff, HIGH);
  digitalWrite(peltier_one, LOW);
  digitalWrite(peltier_two, LOW);
  p_con = 1;
  server.send(200, "text/plane", String(p_con));
}

void setup(void)
{
  Serial.begin(115200);
  sensors.begin();
  pinMode(r_ppm, OUTPUT);
  pinMode(p_ppm, OUTPUT);
  for(int i=1; i<=NUM_RELAYS; i++){
    pinMode(relayGPIOs[i-1], OUTPUT);
    if(RELAY_NO){
      digitalWrite(relayGPIOs[i-1], HIGH);
    }
    else{
      digitalWrite(relayGPIOs[i-1], LOW);
    }
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

//  relays
//  pinMode(airpurifier, OUTPUT);
//  pinMode(fan, OUTPUT);
//  pinMode(water_pump, OUTPUT);
//  pinMode(peltier, OUTPUT);
  Serial.print("connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);

//  control
  server.on("/apcontrol", ap_control);
  server.on("/fancontrol", fan_control);
  server.on("/waterpump", water_pumpc);
  server.on("/peltier", peltierc);
  server.on("/peltierauto", peltierauto);
  server.on("/peltierheat", peltierheat);
  server.on("/peltiercold", peltiercold);

//  sensors
  server.on("/ppm", ppm);
  server.on("/sens", sens);
  server.begin();

  delay(500);
}

void loop(void)
{  
    server.handleClient();
    
//  delay(500);
//  float hic = dht.computeHeatIndex(t, h, false);
}
