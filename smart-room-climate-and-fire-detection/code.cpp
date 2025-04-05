#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define FLAME_SENSOR_PIN 15
#define FAN_INA 22
#define FAN_INB 23
#define BUZZER_PIN 5

float suhu;
float kelembaban;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(FLAME_SENSOR_PIN, INPUT_PULLUP);
  pinMode(FAN_INA, OUTPUT);
  pinMode(FAN_INB, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(FAN_INA, LOW);
  digitalWrite(FAN_INB, LOW);
  digitalWrite(BUZZER_PIN, HIGH); // Buzzer aktif LOW
}

void loop() {
  suhu = dht.readTemperature();
  kelembaban = dht.readHumidity();
  
  int flameRaw = digitalRead(FLAME_SENSOR_PIN);
  bool adaApi = flameRaw == LOW;

  Serial.print("Suhu: "); Serial.print(suhu);
  Serial.print("°C | Kelembaban: "); Serial.print(kelembaban);
  Serial.print("% | Flame Sensor: "); Serial.print(flameRaw);
  Serial.print(" | Api: "); Serial.println(adaApi ? "TERDETEKSI" : "Tidak");

  // Logika kontrol
  bool kipasNyala = false;
  bool buzzerNyala = false;

  if (suhu > 33) {
    kipasNyala = true;
  }

  if (adaApi) {
    kipasNyala = true;
    buzzerNyala = true;
  }

  // Aktifkan kipas
  digitalWrite(FAN_INA, kipasNyala ? HIGH : LOW);
  digitalWrite(FAN_INB, LOW); // arah searah, LOW/LOW = off

  // Aktifkan buzzer (aktif LOW)
  digitalWrite(BUZZER_PIN, buzzerNyala ? LOW : HIGH);

  delay(2000);
}
