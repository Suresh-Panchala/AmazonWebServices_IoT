#include <Wire.h>
#include "I2C_Anything.h"
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
const byte MY_ADDRESS = 42;
const byte relay = 15;
const byte dayLight = 25;   
int lightValue ; 
String lightState;                      
volatile boolean haveData = false;
volatile float voltage_1,current_1;//,power_1,energy_1,pf_1,frequency_1;
volatile float voltage_2,current_2;//,power_2,energy_2,pf_2,frequency_2;
volatile float voltage_3,current_3;//,power_3,energy_3,pf_3,frequency_3;
// The MQTT topics that this device should publish/subscribe



#define AWS_IOT_PUBLISH_TOPIC   "$aws/rules/Ingest_pipeline_rule"
#define AWS_IOT_SUBSCRIBE_TOPIC "Rakaz_IoT_c2d/f5f6b765-4e51-49be-93b1-81d9b73cce12"



WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["deviceId"] = "POC_Street_Light";
  doc["volatage_r"] = voltage_1;
  doc["current_r"]  = current_1;
  doc["volatage_y"] = voltage_2;
  doc["current_y"]  = current_2;
  doc["volatage_b"] = voltage_3;
  doc["current_b"]  = current_3;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
  Serial.println("Done  Publish");
}

void messageHandler(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  lightState= payload;
//  StaticJsonDocument<200> doc;
//  deserializeJson(doc, payload);
//  const char* message = doc["message"];
}

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(dayLight, INPUT);
  Wire.begin (MY_ADDRESS);
  Wire.onReceive (receiveEvent);
  Serial.begin(9600);
  connectAWS();
}

void loop() {
   if (haveData)
    {
    Serial.print ("R Voltage = ");
    Serial.println (voltage_1);
    Serial.print ("R Current = ");
    Serial.println (current_1);
    Serial.print ("Y Voltage = ");
    Serial.println (voltage_2);
    Serial.print ("Y Current = ");
    Serial.println (current_2);
    Serial.print ("B Voltage = ");
    Serial.println (voltage_3);
    Serial.print ("B Current = ");
    Serial.println (current_3);
    haveData = false;
    }
  publishMessage();
  client.loop();
  delay(1000);
  lightValue = digitalRead(dayLight);
  if(lightValue == 1 || lightState == "ON"){
    digitalWrite(relay,1);
  }
  else if(lightValue == 0 || lightState == "OFF"){
    digitalWrite(relay,0);
  }
  
}
void receiveEvent (int howMany)
 {
 if (howMany >= (sizeof voltage_1) + (sizeof current_1)+(sizeof voltage_2) + (sizeof current_2)+(sizeof voltage_3) + (sizeof current_3))
   {
   I2C_readAnything (voltage_1);
   I2C_readAnything (current_1);
   I2C_readAnything (voltage_2);
   I2C_readAnything (current_2);
   I2C_readAnything (voltage_3);
   I2C_readAnything (current_3);
   haveData = true;
   }  // end if have enough data
 }  // en
