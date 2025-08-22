#include "monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

#ifndef UNIT_TEST
// ---------- Production Alert ----------
void blinkAlert() {
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
  cout << "\r  \r" << flush;  // Clear line after alert
}
#else
// ---------- Test Alert (no delay) ----------
void blinkAlert() {
  cout << "[ALERT triggered]\n";
}
#endif

// ---------- Temperature Check ----------
void temp_hypothermia(float temperature) {
  if (temperature >= TEMP_LOW && temperature <= TEMP_LOW + tolerance) {
    cout << "Warning: Approaching hypothermia\n";
  }
}

void temp_hyperthermia(float temperature) {
  if (temperature >= TEMP_HIGH - tolerance && temperature <= TEMP_HIGH) {
    cout << "Warning: Approaching hyperthermia\n";
  }
}

bool tempOk(float temperature) {
  if (temperature > TEMP_HIGH || temperature < TEMP_LOW) {
    cout << "Temperature is critical!\n";
    blinkAlert();
    return false;
  }
  temp_hypothermia(temperature);
  temp_hyperthermia(temperature);
  return true;
}

// ---------- Pulse Check ----------
bool pulseRateOk(float pulseRate) {
  if (pulseRate < PULSE_LOW || pulseRate > PULSE_HIGH) {
    cout << "Pulse Rate is out of range!\n";
    blinkAlert();
    return false;
  }
  return true;
}

// ---------- SpO2 Check ----------
bool spo2Ok(float spo2) {
  if (spo2 < SPO2_MIN) {
    cout << "Oxygen Saturation out of range!\n";
    blinkAlert();
    return false;
  }
  return true;
}

// ---------- Combined Monitoring ----------
bool vitalsOk(float temperature, float pulseRate, float spo2) {
  return tempOk(temperature) && pulseRateOk(pulseRate) && spo2Ok(spo2);
}
