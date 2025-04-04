#include <DHT.h>

// Sensor Pins
#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_MOISTURE_PIN 34
#define RAIN_SENSOR_PIN 35  // Menggunakan D0 (Digital Output)
#define BUZZER_PIN 23       // Buzzer aktif

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);  // Matikan buzzer saat awal
}

void loop() {
  readSensors();
  delay(2000);
}

void readSensors() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int rain = digitalRead(RAIN_SENSOR_PIN);  // 0 = hujan, 1 = tidak hujan

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.print(", Rain: ");
  Serial.println(rain == 0 ? "Raining" : "No Rain");

  checkWeatherConditions(temperature, soilMoisture, rain);
}

void checkWeatherConditions(float temperature, int soilMoisture, int rain) {
  Serial.print("Checking Conditions... ");
  Serial.print("Rain: ");
  Serial.print(rain);
  Serial.print(", Soil Moisture: ");
  Serial.println(soilMoisture);

  if (rain == 0 && soilMoisture < 500) {
    Serial.println("🚨 WARNING: Flood Risk Detected! Buzzer ON");
    digitalWrite(BUZZER_PIN, LOW);  // ON untuk active-low buzzer
  } else if (temperature > 35 && soilMoisture > 2000) {
    Serial.println("🔥 WARNING: Drought Risk Detected! Buzzer ON");
    digitalWrite(BUZZER_PIN, LOW);  // ON untuk active-low buzzer
  } else {
    Serial.println("✅ Conditions Normal. Buzzer OFF");
    digitalWrite(BUZZER_PIN, HIGH);  // OFF untuk active-low buzzer
  }
}
