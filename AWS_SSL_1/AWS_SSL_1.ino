#define TINY_GSM_RX_BUFFER          1024 // Set RX buffer to 1Kb
#define TINY_GSM_MODEM_A7670
#define DUMP_AT_COMMANDS
#define TINY_GSM_TEST_SSL true
#define SerialAT   Serial2
#include <TinyGsmClient.h>
#include "certs/AWSClientCertificate.h"
#include "certs/AWSClientPrivateKey.h"
#include "certs/AmazonRootCA.h"
#include <ArduinoJson.h>
#ifdef DUMP_AT_COMMANDS  
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, Serial);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

#define NETWORK_APN     "airtelgprs.com"             //CHN-CT: China Telecom

const char *broker = "a13p7xnji7t9a5-ats.iot.me-central-1.amazonaws.com";
const uint16_t broker_port = 8883;
const char *clien_id = "StreetlightCleint";

// Replace the topic you want to subscribe to
const char *subscribe_topic = "Rakaz_IoT_c2d/f5f6b765-4e51-49be-93b1-81d9b73cce12";
// Replace the theme you want to publish
const char *publish_topic = "$aws/rules/Ingest_pipeline_rule";
const char *connect_topic = "$aws/rules/device_connectivity_tracker";
// Current connection index, range 0~1
const uint8_t mqtt_client_id = 0;
uint32_t check_connect_millis = 0;

void mqtt_callback(const char *topic, const uint8_t *payload, uint32_t len)
{
    Serial.println();
    Serial.println("======mqtt_callback======");
    Serial.print("Topic:"); Serial.println(topic);
    Serial.println("Payload:");
    for (int i = 0; i < len; ++i) {
        Serial.print(payload[i], HEX); Serial.print(",");
    }
    Serial.println();
    Serial.println("=========================");
}

bool mqtt_connect()
{
    Serial.print("Connecting to ");
    Serial.print(broker);

    bool ret = modem.mqtt_connect(mqtt_client_id, broker, broker_port, clien_id);
    if (!ret) {
        Serial.println("Failed!"); return false;
    }
    Serial.println("successed.");

    if (modem.mqtt_connected()) {
        Serial.println("MQTT has connected!");
    } else {
        return false;
    }
    // Set MQTT processing callback
    modem.mqtt_set_callback(mqtt_callback);
    // Subscribe to topic
    modem.mqtt_subscribe(mqtt_client_id, subscribe_topic);

    return true;
}


void setup()
{
    Serial.begin(115200); // Set console baud rate

    Serial.println("Start Sketch");

    SerialAT.begin(115200);
   
    Serial.println();

    delay(100);
    modem.restart();
    delay(3000);
    // Check if SIM card is online
    SimStatus sim = SIM_ERROR;
    while (sim != SIM_READY) {
        sim = modem.getSimStatus();
        switch (sim) {
        case SIM_READY:
            Serial.println("SIM card online");
            break;
        case SIM_LOCKED:
            Serial.println("The SIM card is locked. Please unlock the SIM card first.");
            // const char *SIMCARD_PIN_CODE = "123456";
            // modem.simUnlock(SIMCARD_PIN_CODE);
            break;
        default:
            break;
        }
        delay(1000);
    }



#ifdef NETWORK_APN
    Serial.printf("Set network apn : %s\n", NETWORK_APN);
    modem.sendAT(GF("+CGDCONT=1,\"IP\",\""), NETWORK_APN, "\"");
    if (modem.waitResponse() != 1) {
        Serial.println("Set network apn error !");
    }
#endif

    // Check network registration status and network signal status
    int16_t sq ;
    Serial.print("Wait for the modem to register with the network.");
    RegStatus status = REG_NO_RESULT;
    while (status == REG_NO_RESULT || status == REG_SEARCHING || status == REG_UNREGISTERED) {
        status = modem.getRegistrationStatus();
        switch (status) {
        case REG_UNREGISTERED:
        case REG_SEARCHING:
            sq = modem.getSignalQuality();
            Serial.printf("[%lu] Signal Quality:%d\n", millis() / 1000, sq);
            delay(1000);
            break;
        case REG_DENIED:
            Serial.println("Network registration was rejected, please check if the APN is correct");
            return ;
        case REG_OK_HOME:
            Serial.println("Online registration successful");
            break;
        case REG_OK_ROAMING:
            Serial.println("Network registration successful, currently in roaming mode");
            break;
        default:
            Serial.printf("Registration Status:%d\n", status);
            delay(1000);
            break;
        }
    }
    Serial.println();


    Serial.printf("Registration Status:%d\n", status);
    delay(1000);

    String ueInfo;
    if (modem.getSystemInformation(ueInfo)) {
        Serial.print("Inquiring UE system information:");
        Serial.println(ueInfo);
    }

    if (!modem.enableNetwork()) {
        Serial.println("Enable network failed!");
    }

    delay(5000);

    String ipAddress = modem.getLocalIP();
    Serial.print("Network IP:"); Serial.println(ipAddress);

    // Initialize MQTT, use SSL
    modem.mqtt_begin(true);

    // Set Amazon Certificate
    modem.mqtt_set_certificate(AmazonRootCA, AWSClientCertificate, AWSClientPrivateKey);
    
    // Connecting to AWS IOT Core
    if (!mqtt_connect()) {
        return ;
    }

    while (1) {
        // Check the connection every ten seconds
        if (millis() > check_connect_millis) {
            check_connect_millis = millis() + 3600000UL;
            if (!modem.mqtt_connected()) {
                mqtt_connect();
            } else {
                 StaticJsonDocument<200> doc;
                doc["deviceId"] = "StreetlightPOC";
                doc["timestamp"] ="timestamp";
                JsonObject data = doc.createNestedObject("data");
                data["volatage_r"] = 230;
                data["current_r"]  = 2;
                data["volatage_y"] = 231;
                data["current_y"]  = 5;
                data["volatage_b"] = 190;
                data["current_b"]  = 4;
                char jsonBuffer[512];
                serializeJson(doc, jsonBuffer);
                // If connected, send information once every ten seconds
                String payload = "RunTime:" + String(millis() / 1000);
                modem.mqtt_publish(0, publish_topic, jsonBuffer);
            }
        }
        // MQTT handling
        modem.mqtt_handle();
        delay(5);
    }
}

void loop()
{
    // Debug AT
    if (SerialAT.available()) {
        Serial.write(SerialAT.read());
    }
    if (Serial.available()) {
        SerialAT.write(Serial.read());
    }
    
    delay(1);
}
