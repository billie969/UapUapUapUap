#define BLYNK_TEMPLATE_ID "TMPLxxxx"
#define BLYNK_TEMPLATE_NAME "Pertanian Pintar"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "WiFi";
char pass[] = "Password";

#define DHTPIN D4
#define DHTTYPE DHT11

#define SOIL_PIN A0
#define BUZZER D5

DHT dht(DHTPIN, DHTTYPE);

int batasSoil = 500;

BlynkTimer timer;

void kirimData() {
  float suhu = dht.readTemperature();
  float hum = dht.readHumidity();
  int soil = analogRead(SOIL_PIN);

  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, soil);

  if (soil > batasSoil) {
    digitalWrite(BUZZER, HIGH);
    Blynk.logEvent("tanah_kering", "Tanah Terlalu Kering!");
  } else {
    digitalWrite(BUZZER, LOW);
  }
}

void setup() {
  pinMode(BUZZER, OUTPUT);

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, kirimData);
}

void loop() {
  Blynk.run();
  timer.run();
}