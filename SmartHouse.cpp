#define BLYNK_TEMPLATE_ID "TMPLxxxx"
#define BLYNK_TEMPLATE_NAME "SmartHome"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Nama_WiFi";
char pass[] = "Password_WiFi";

#define FLAME_PIN 5
#define PIR_PIN 4
#define BUZZER_PIN 14
#define LED_PIN 12

BlynkTimer timer;

void sendSensor() {
  int flameState = digitalRead(FLAME_PIN);
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  if (flameState == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  Blynk.virtualWrite(V0, flameState);
  Blynk.virtualWrite(V1, pirState);

  if (flameState == HIGH && pirState == HIGH) {
    Blynk.virtualWrite(V2, "API & GERAKAN TERDETEKSI");
  }
  else if (flameState == HIGH) {
    Blynk.virtualWrite(V2, "API TERDETEKSI");
  }
  else if (pirState == HIGH) {
    Blynk.virtualWrite(V2, "GERAKAN TERDETEKSI");
  }
  else {
    Blynk.virtualWrite(V2, "KONDISI NORMAL");
  }
}

void setup() {
  pinMode(FLAME_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}