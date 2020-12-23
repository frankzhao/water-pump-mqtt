#include <Arduino.h>
#include <WiFiNINA_Generic.h>
#include <MQTT.h>
#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>
#include "wifi.h"
#include "credentials.h"
#include "water_pump.h"

Client *netClient;
CloudIoTCoreDevice *device;
CloudIoTCoreMqtt *mqtt;
MQTTClient *mqttClient;
unsigned long iat = 0;
String jwt;
char logMsg[50];

String getJwt() {
  // Disable software watchdog as these operations can take a while.
  Serial.println("Refreshing JWT");
  iat = WiFi.getTime();
  jwt = device->createJWT(iat, jwt_exp_secs);
  return jwt;
}

void messageReceived(String &topic, String &payload) {
  if (payload.length() == 0) {
    return;
  }
  Serial.println("Received message on topic - " + topic + " - " + payload);
  // Format "015 255" means pump for 15s at full power
  const char* command = payload.c_str();
  char* value = strtok((char*) command, " ");
  int durationSeconds = atoi(value);
  value = strtok(NULL, " ");
  int pumpPower = atoi(value);
  sprintf(logMsg, "Duration: %ds, Power: %d", durationSeconds, pumpPower);
  Serial.println(logMsg);

  // Pump on
  pump(durationSeconds * 1000, pumpPower);
}

void setupCloudIoT() {
  device = new CloudIoTCoreDevice(
      project_id, location, registry_id, device_id,
      private_key_str);

  netClient = new WiFiSSLClient();

  mqttClient = new MQTTClient(512);
  mqttClient->setOptions(180, true, 1000); // keepAlive, cleanSession, timeout
  mqtt = new CloudIoTCoreMqtt(mqttClient, netClient, device);
  mqtt->startMQTT();
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // Setup pump
  setupPump();

  // Connect to wifi
  enable_WiFi();
  connect_WiFi(ssid, password);

  // Connect to mqtt
  setupCloudIoT();
}

void loop() {
  // put your main code here, to run repeatedly:
  mqtt->loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!mqttClient->connected()) {
    connect_WiFi(ssid, password);
    mqtt->mqttConnect();
  }
}
