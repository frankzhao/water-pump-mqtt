#include "wifi.h"
#include <WiFiNINA_Generic.h>

int status = WL_IDLE_STATUS;      //connection status

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("Status: ");
  switch (status) {
    case WL_IDLE_STATUS:
      Serial.println("Idle");
      break;
    case WL_CONNECTED:
      Serial.println("Connected");
      break;
    case WL_CONNECT_FAILED:
      Serial.println("Failed");
      break;
    case WL_CONNECTION_LOST:
      Serial.println("Lost");
      break;
  }

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void enable_WiFi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
}

void connect_WiFi(const char* ssid, const char* pass) {
  WiFi.begin(ssid, pass);
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println("Waiting on time sync...");
  while (WiFi.getTime() < 1510644967) {
    delay(10);
  }

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
}
