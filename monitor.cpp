// monitor.cpp
#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

bool isOutOfRange(float value, const VitalThreshold& threshold) {
  return value < threshold.min || value > threshold.max;
}

VitalStatus checkVitals(float temperature, float pulseRate, float spo2) {
  if (isOutOfRange(temperature, {95.0, 102.0})) {
    return VitalStatus::TEMPERATURE_CRITICAL;
  }
  if (isOutOfRange(pulseRate, {60.0, 100.0})) {
    return VitalStatus::PULSE_CRITICAL;
  }
  if (spo2 < 90.0) {
    return VitalStatus::SPO2_CRITICAL;
  }
  return VitalStatus::OK;
}

void blinkAlert() {
  for (int i = 0; i < 6; ++i) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
}

void alert(VitalStatus status) {
  switch (status) {
    case VitalStatus::TEMPERATURE_CRITICAL:
      cout << "Temperature is critical!\n";
      blinkAlert();
      break;
    case VitalStatus::PULSE_CRITICAL:
      cout << "Pulse Rate is out of range!\n";
      blinkAlert();
      break;
    case VitalStatus::SPO2_CRITICAL:
      cout << "Oxygen Saturation out of range!\n";
      blinkAlert();
      break;
    default:
      break;
  }
}
