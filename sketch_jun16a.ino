#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ---------- OLED setup (I²C) ---------- */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ---------- BMP280 setup ---------- */
Adafruit_BMP280 bmp;    // I²C address 0x76 or 0x77
bool bmpOK = false;

/* ---------- Project pins ---------- */
#define PIR_PIN D5
#define LED_PIN D6
#define LDR_PIN A0

int  ldrValue          = 0;
const int ldrThreshold = 500;   // dark if < 500
bool lightIsOn         = false;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  /* OLED init */
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("❌ OLED not found"));
    while (true);
  }

  /* BMP280 init */
  if (bmp.begin(0x76)) {        // use 0x77 if your board is 0x77
    bmpOK = true;
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X8,   // temp
                    Adafruit_BMP280::SAMPLING_X16,  // pressure
                    Adafruit_BMP280::FILTER_X4,
                    Adafruit_BMP280::STANDBY_MS_250);
  } else {
    Serial.println(F("⚠️  BMP280 not found"));
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  /* ---- sensors ---- */
  ldrValue = analogRead(LDR_PIN);          // 0=bright … 1023=dark
  int motion = digitalRead(PIR_PIN);       // HIGH when motion

  /* ---- LED control (original logic) ---- */
  if (!lightIsOn && ldrValue < ldrThreshold && motion == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    lightIsOn = true;
  }
  if (lightIsOn && ldrValue > ldrThreshold) {
    digitalWrite(LED_PIN, LOW);
    lightIsOn = false;
  }

  /* ---- BMP280 reading ---- */
  float temp = NAN, press = NAN;
  if (bmpOK) {
    temp  = bmp.readTemperature();         // °C
    press = bmp.readPressure() / 100.0F;   // hPa
  }

  /* ---- Serial output ---- */
  Serial.print("LDR: "); Serial.print(ldrValue);
  Serial.print(" | Motion: "); Serial.print(motion);
  Serial.print(" | Light: "); Serial.print(lightIsOn ? "ON" : "OFF");
  if (bmpOK) {
    Serial.print(" | Temp: "); Serial.print(temp); Serial.print("°C");
    Serial.print(" P: ");     Serial.print(press); Serial.println(" hPa");
  } else {
    Serial.println(" | BMP280 missing");
  }

  /* ---- OLED display ---- */
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("LDR: "));   display.println(ldrValue);
  display.print(F("Motion: "));display.println(motion ? "YES" : "NO");
  display.print(F("Light: ")); display.println(lightIsOn ? "ON" : "OFF");

  if (bmpOK) {
    display.setCursor(0, 32);
    display.print(F("T: ")); display.print(temp, 1); display.print(F(" C"));
    display.setCursor(0, 46);
    display.print(F("P: ")); display.print(press, 1); display.print(F(" hPa"));
  } else {
    display.setCursor(0, 40);
    display.println(F("BMP280 missing"));
  }
  display.display();

  delay(500);
}
 
