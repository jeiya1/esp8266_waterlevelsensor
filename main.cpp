#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Example";
const char* password = "Example";
const char* serverUrl = "http://Example:5000";

void setup() {
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

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
  while (digitalRead(D2)) {}

  long result = 0;
  for (int i = 0; i < 24; i++) {
    digitalWrite(D3, HIGH);
    digitalWrite(D3, LOW);
    result = result << 1;
    if (digitalRead(D2)) {
      result++;
    }
  }

  result = result ^ 0x800000;

  for (char i = 0; i < 3; i++) {
    digitalWrite(D3, HIGH);
    digitalWrite(D3, LOW);
  }

  sendPressureData(result);
  delay(1000);
}
