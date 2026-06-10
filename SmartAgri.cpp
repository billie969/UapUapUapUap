#define BLYNK_TEMPLATE_ID "TMPLxxxx"
#define BLYNK_TEMPLATE_NAME "Pertanian Pintar"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "NamaWifi";
char pass[] = "PasswordWifi";

#define SOIL_PIN A0
#define DHTPIN D4
#define DHTTYPE DHT22
#define RELAY_PIN D1
#define LED_HIJAU D5
#define LED_MERAH D6
#define BUZZER D7

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void kirimData() {
  int soilValue = analogRead(SOIL_PIN);

  float suhu = dht.readTemperature();
  float humidity = dht.readHumidity();

  Blynk.virtualWrite(V0, soilValue);
  Blynk.virtualWrite(V1, suhu);
  Blynk.virtualWrite(V2, humidity);

  if (soilValue > 700) {
    digitalWrite(RELAY_PIN, LOW); 
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    digitalWrite(BUZZER, HIGH);

    Blynk.virtualWrite(V3, "POMPA MENYALA");
  } else{
    digitalWrite(RELAY_PIN, HIGH); 
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(BUZZER, LOW);
    Blynk.virtualWrite(V3, "POMPA MATI");
  }

  if (suhu > 35) { 
    digitalWrite(BUZZER, HIGH);
  }

  Serial.println("===== PERTANIAN PINTAR =====");
  Serial.print("Soil : ");
  Serial.println(soilValue);
  Serial.print("Suhu : ");
  Serial.println(suhu);
  Serial.print("Humidity : ");
  Serial.println(humidity);
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);

  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, kirimData);
}

void loop(){
  Blynk.run();
  timer.run();
}
