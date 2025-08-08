#include <LiquidCrystal.h>
#include <DHT.h>

// LCD setup: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// DHT11 setup
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Sensors and relay
#define LDR_PIN A0
#define SOIL_PIN A1
#define RELAY_PIN 4

// State tracking
bool isDay = false;
bool wasDay = false;

bool isSoilDry = false;
bool wasSoilDry = false;

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read sensors
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN);
  int soilValue = analogRead(SOIL_PIN);

  // ✅ Inverted logic: lower light value = Day
  isDay = ldrValue < 500;       // Inverted threshold
  isSoilDry = soilValue > 600;  // Adjust as needed

  // --- LDR State Change ---
  if (isDay != wasDay) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(isDay ? "It's Day" : "It's Night");
    wasDay = isDay;
    delay(2000);
  }

  // --- Soil State Change ---
  if (isSoilDry != wasSoilDry) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(isSoilDry ? "Soil is Dry" : "Soil is Moist");

    digitalWrite(RELAY_PIN, isSoilDry ? HIGH : LOW);
    wasSoilDry = isSoilDry;
    delay(2000);
  }

  // --- Default Screen: Temp + Humidity ---
  lcd.clear();
  lcd.setCursor(0, 0);
  if (isnan(temp) || isnan(hum)) {
    lcd.print("Sensor Error");
  } else {
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Humid: ");
    lcd.print(hum);
    lcd.print(" %");
  }

  delay(2000);
}
