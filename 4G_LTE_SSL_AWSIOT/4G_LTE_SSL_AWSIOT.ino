#include <SSLClient.h>
#define TINY_GSM_MODEM_SIM7600
#define TINY_GSM_RX_BUFFER 1024
#include <TinyGsmClient.h>
#include <PubSubClient.h>
#include "certs.h"

#define SerialAT Serial2


TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);
SSLClient secureclient(&gsmClient);
PubSubClient mqtt(secureclient);


#define MODEM_PWKEY          4
#define MODEM_TX             26
#define MODEM_RX             27

const char MQTT_HOST[]       = "a13p7xnji7t9a5-ats.iot.me-central-1.amazonaws.com";
const char topic_publish[]   = "$aws/rules/Ingest_pipeline_rule";
const char topic_subscribe[] = "Rakaz_IoT_c2d/f5f6b765-4e51-49be-93b1-81d9b73cce12";
const char connect_topic[]   = "$aws/rules/device_connectivity_tracker";

#define NTP_SERVER "pool.ntp.org"

#define AT_WAIT_TIME_MSECS 12000L
const char* ntpServer = "pool.ntp.org";


void mqttCallback(char* topic, byte* payload, unsigned int len) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<len;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void reconnect() {
  // Loop until we're reconnected
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqtt.connect("SrreetLightClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqtt.publish(topic_publish,"hello world");
      // ... and resubscribe
      mqtt.subscribe(topic_subscribe);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void setup(){

  Serial.begin(115200);
  SerialAT.begin(115200);
  
  modemPowerKeyToggle();

  secureclient.setCACert(cacert);
  secureclient.setCertificate(clientcert);
  secureclient.setPrivateKey(clientkey);
  
  mqtt.setServer(MQTT_HOST, 8883);
  mqtt.setCallback(mqttCallback);

  
  restartModem(&modem);
  initialiseModem(&modem);

  while(!modem.isNetworkConnected()){
      Serial.println("Network not available");
      modem.waitForNetwork();
  }
  while(!modem.isGprsConnected()){
      Serial.println("GPRS not connected");
      modem.gprsConnect("airtelgprs.com","","");
  }
}
 int i = 0;
 
 void loop(){

  if (!mqtt.connected()) {
    reconnect();
  }
    if(i == 100){
    mqtt.publish(topic_publish,"connected");
    i = i - 100;
  }
  mqtt.loop();

  delay(100);
  i++;Serial.println(i);
  }

  bool initialiseModem(TinyGsm *modem)
  {
    Serial.println("initialising Modem");
    int ret = modem->init();
    String modemInfo = modem->getModemInfo();
    Serial.printf("modemInfo: %s\n SimStatus: %d\n", modemInfo.c_str(), modem->getSimStatus());
    return ret;
  }


  bool restartModem(TinyGsm *modem)
  {
    int ret = modem->restart();
    String modemInfo = modem->getModemInfo();
    Serial.printf("modemInfo: %s\n SimStatue: %d\n", modemInfo.c_str(), modem->getSimStatus());
    return ret;
  }

void modemPowerKeyToggle() {
  pinMode(MODEM_PWKEY,OUTPUT);
  Serial.println("Power On modem");
  digitalWrite(MODEM_PWKEY, LOW);
  delay(100);
  digitalWrite(MODEM_PWKEY, HIGH);
  delay(1000);
  digitalWrite(MODEM_PWKEY, LOW);
}


 bool updateNTPTime(TinyGsm *modem)
  {
    Serial.println("Update NTP Time");
    modem->sendAT("+CNTP=\"" NTP_SERVER "\",32");
    int res = modem->waitResponse(AT_WAIT_TIME_MSECS);
    return res;
  }
