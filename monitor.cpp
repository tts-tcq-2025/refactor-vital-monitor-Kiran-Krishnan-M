#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

bool isOutOfRange(float value, const VitalThreshold& threshold) {
  return value < threshold.min || value > threshold.max;
}

struct VitalCheck {
  float value;
  VitalThreshold threshold;
  VitalStatus status;
};

VitalStatus checkVitals(float temperature, float pulseRate, float spo2) {
  VitalCheck checks[] = {
    {temperature, {95.0, 102.0}, VitalStatus::TEMPERATURE_CRITICAL},
    {pulseRate,   {60.0, 100.0}, VitalStatus::PULSE_CRITICAL},
    {spo2,        {90.0, 150.0}, VitalStatus::SPO2_CRITICAL}  // upper bound arbitrary
  };

  for (const auto& check : checks) {
    if (isOutOfRange(check.value, check.threshold)) {
      return check.status;
    }
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

void printAlertMessage(VitalStatus status) {
  switch (status) {
    case VitalStatus::TEMPERATURE_CRITICAL:
      cout << "Temperature is critical!\n"; break;
    case VitalStatus::PULSE_CRITICAL:
      cout << "Pulse Rate is out of range!\n"; break;
    case VitalStatus::SPO2_CRITICAL:
      cout << "Oxygen Saturation out of range!\n"; break;
    default: break;
  }
}

void alert(VitalStatus status) {
  if (status != VitalStatus::OK) {
    printAlertMessage(status);
    blinkAlert();
  }
}
