#include <Arduino.h>

/**
 * Simple transistor circuit that activates a pump connected on an analog output
 * pin. Power is controlled via PWM that is controlled by a variable resistor.
 */
/* pump control */
int pumpPin = 2;
int onTimeMs = 15 * 1000; // pump for 15s
long offTimeMs = (86400 * 1000) / 2; // pump twice a day

/* power control */
int analogPin = 3;
// Pump power set to % power by PWM signal for onMs.
float dutyCyclePercent = 60;
float powerPercent = (255 / 100.0) * dutyCyclePercent;

void setupPump() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // wait 5 secs before starting
  // delay(5000);
  pinMode(pumpPin, OUTPUT);
  pinMode(analogPin, INPUT);
}

// read power for pump using analog in
float readPower() {
  int potValue = analogRead(analogPin); // range is 0-1024
  return potValue / 1024.0;   // normalize power between 0-1
}

// power is a percentage
void pump(int pumpTimeMs, int pumpPower) {
  digitalWrite(LED_BUILTIN, HIGH);
  int durationMs = 0;
  while (durationMs < pumpTimeMs) {
    analogWrite(pumpPin, pumpPower);   // pump on
    delay(100);
    durationMs += 100;
  }
  analogWrite(pumpPin, 0);     // pump off
  digitalWrite(LED_BUILTIN, LOW);
}
