#define BLYNK_TEMPLATE_ID "TMPLxxxx"
#define BLYNK_TEMPLATE_NAME "Peternakan Pintar"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char ssid[] = "WiFi";
char pass[] = "Password";

#define DHTPIN D4
#define DHTTYPE DHT11

#define LED D5

float batasSuhu = 30;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

void monitoring() {

  float suhu = dht.readTemperature();
  float hum = dht.readHumidity();

  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, hum);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(suhu);
  lcd.print("C");

  lcd.setCursor(8, 0);
  lcd.print("H:");
  lcd.print(hum);
  lcd.print("%");

  if (suhu > batasSuhu) {

    digitalWrite(LED, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("SUHU TINGGI!");

    Blynk.logEvent("suhu_tinggi",
                   "Suhu Kandang Tinggi");
  }
  else {

    digitalWrite(LED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Kondisi Aman");
  }
}

void setup() {

  pinMode(LED, OUTPUT);

  dht.begin();

  lcd.init();
  lcd.backlight();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, monitoring);
}

void loop() {
  Blynk.run();
  timer.run();
}