#include "monitor.h"
#include <assert.h>
#include <iostream>

using std::cout;

// ---------- Unit Tests ----------

// Temperature Tests
void testTemperature() {
  // Within safe range
  assert(tempOk(98.6f) == true);

  // Critical high/low
  assert(tempOk(104.0f) == false);
  assert(tempOk(94.0f) == false);

  // Approaching hypothermia (just above min)
  temp_hypothermia(95.5f);

  // Approaching hyperthermia (just below max)
  temp_hyperthermia(101.8f);
}

// Pulse Tests
void testPulse() {
  assert(pulseRateOk(72.0f) == true);   // Normal
  assert(pulseRateOk(55.0f) == false);  // Low
  assert(pulseRateOk(105.0f) == false); // High
}

// SpO2 Tests
void testSpO2() {
  assert(spo2Ok(95.0f) == true);   // Normal
  assert(spo2Ok(90.0f) == true);   // Lower bound okay
  assert(spo2Ok(85.0f) == false);  // Below safe
}

// Combined Vitals Tests
void testVitals() {
  // All good
  assert(vitalsOk(98.6f, 72.0f, 95.0f) == true);

  // Temperature fails
  assert(vitalsOk(104.0f, 72.0f, 95.0f) == false);

  // Pulse fails
  assert(vitalsOk(98.6f, 55.0f, 95.0f) == false);

  // SpO2 fails
  assert(vitalsOk(98.6f, 72.0f, 85.0f) == false);
}

int main() {
  testTemperature();
  testPulse();
  testSpO2();
  testVitals();

  cout << "✅ All unit tests passed!\n";
  return 0;
}
