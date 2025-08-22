
#include "monitor.h"
#include <assert.h>
#include <iostream>
#include <limits>

using std::cout;

// ---------- Unit Tests ----------
void testVitals() {
  // ✅ All within range
  assert(vitalsOk(98.6, 72, 95) == true);

  // ❌ Temperature out of range
  assert(vitalsOk(104, 72, 95) == false);
  assert(vitalsOk(94, 72, 95) == false);

  // ❌ Pulse Rate out of range
  assert(vitalsOk(98.6, 55, 95) == false);
  assert(vitalsOk(98.6, 105, 95) == false);

  // ❌ Oxygen Saturation out of range (<90 only)
  assert(vitalsOk(98.6, 72, 85) == false);

  // ✅ Oxygen Saturation okay at 90+
  assert(vitalsOk(98.6, 72, 90) == true);
  assert(vitalsOk(98.6, 72, 100) == true);
}

// ---------- Component Tests ----------
void testIsOutOfRange() {
  VitalThreshold tempRange = {95, 102};
  assert(isOutOfRange(94, tempRange) == true);
  assert(isOutOfRange(98, tempRange) == false);
  assert(isOutOfRange(103, tempRange) == true);

  VitalThreshold spo2Range = {90, std::numeric_limits<float>::infinity()};
  assert(isOutOfRange(85, spo2Range) == true);
  assert(isOutOfRange(95, spo2Range) == false);
}

void testCheckVital() {
  VitalStatus pulse = {"Pulse Rate", 110, {60, 100}};
  VitalStatus spo2 = {"Oxygen Saturation", 95, {90, std::numeric_limits<float>::infinity()}};

  assert(checkVital(pulse) == "Pulse Rate is out of range!");
  assert(checkVital(spo2) == "");
}

// ---------- Main ----------
int main() {
  testVitals();
  testIsOutOfRange();
  testCheckVital();

  cout << "✅ All tests passed!\n";
  return 0;
}
















