#include <DHT.h>

// Konfigurasi DHT22
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Pin Sensor Soil
const int soilPin = A0;

// Aktuator
const int ledPin = 8;
const int buzzerPin = 9;

// Nilai ambang
float suhuThreshold = 20.0;      // °C
int kelembapanThreshold = 50;    // %

void setup() {
  Serial.begin(9600);

  dht.begin();

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledPin, LOW);
}

void loop() {

  // Membaca suhu
  float suhu = dht.readTemperature();

  // Membaca soil moisture
  int soilValue = analogRead(soilPin);

  // Konversi ke persen
  int soilPercent = map(soilValue, 1023, 0, 0, 100);

  if (isnan(suhu)) {
    Serial.println("Gagal membaca DHT22!");
    delay(2000);
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" °C");

  Serial.print("Kelembapan Tanah: ");
  Serial.print(soilPercent);
  Serial.println(" %");

  // Jika kedua sensor di atas threshold
  if (suhu > suhuThreshold && soilPercent > kelembapanThreshold) {

    digitalWrite(ledPin, HIGH);

    // Nada buzzer 1000 Hz
    tone(buzzerPin, 1000);

    Serial.println("PERINGATAN -> LED & BUZZER MENYALA");
  }
  else {

    digitalWrite(ledPin, LOW);

    // Matikan buzzer
    noTone(buzzerPin);

    Serial.println("NORMAL -> LED & BUZZER MATI");
  }

  Serial.println("---------------------");

  delay(2000);
}