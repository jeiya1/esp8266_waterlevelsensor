#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Example";
const char* password = "Example";
const char* serverUrl = "http://Example:5000";

void setup() {
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);

  delay(1000);
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void sendPressureData(long pressure) {
  static unsigned long lastSendTime = 0;

  if (millis() - lastSendTime >= 500) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverUrl);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "message=" + String(pressure);

    int httpCode = http.POST(postData);

    if (httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    lastSendTime = millis();
  }
}

void loop() {
  while (digitalRead(D1)) {}

  long result = 0;
  for (int i = 0; i < 24; i++) {
    digitalWrite(D2, HIGH);
    digitalWrite(D2, LOW);
    result = result << 1;
    if (digitalRead(D1)) {
      result++;
    }
  }

  result = result ^ 0x800000;

  for (char i = 0; i < 3; i++) {
    digitalWrite(D2, HIGH);
    digitalWrite(D2, LOW);
  }

  sendPressureData(result);
  delay(1000);
}
