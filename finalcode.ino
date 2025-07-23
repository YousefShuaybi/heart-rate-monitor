#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

// معدل النبض
const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute = 0;
int beatAvg = 0;

// المكونات الإضافية
const int ledPin = 8;         // ضوء LED عند كل نبضة
const int buttonPin = 7;      // زر إعادة التصفير

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // لأن الكبسة توصل الأرضي عند الضغط

  if (!particleSensor.begin()) {
    Serial.println("✖️ فشل في الاتصال بالحساس");
    while (1);
  }

  particleSensor.setup(0x1F, 4, 2, 100, 411, 4096);
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeIR(0x0A);
}

void loop() {
  // ✅ التحقق من زر إعادة التهيئة
  if (digitalRead(buttonPin) == LOW) {
    resetBPM();  // إعادة التصفير
  }

  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue)) {
    long now = millis();
    long delta = now - lastBeat;
    lastBeat = now;

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute > 20 && beatsPerMinute < 200) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (byte i = 0; i < RATE_SIZE; i++) {
        beatAvg += rates[i];
      }
      beatAvg /= RATE_SIZE;

      // ✅ تشغيل الضوء مؤقتًا عند كل نبضة
      digitalWrite(ledPin, HIGH);
      delay(20);  // نبضة قصيرة
      digitalWrite(ledPin, LOW);

      Serial.println(beatsPerMinute, 1);  // إرسال BPM لـ Processing
    }
  }

  delay(20);
}

// تابع لتصفير المتغيرات عند الضغط على الزر
void resetBPM() {
  beatsPerMinute = 0;
  beatAvg = 0;
  rateSpot = 0;
  lastBeat = 0;
  for (byte i = 0; i < RATE_SIZE; i++) {
    rates[i] = 0;
  }
  Serial.println("0");  // إرسال 0 لمسح الشاشة في Processing
  delay(500);  // انتظار لتجنب التكرار عند الضغط المستمر
}
