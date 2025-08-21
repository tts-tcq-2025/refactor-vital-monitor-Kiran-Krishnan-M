#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <algorithm>

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
  const VitalCheck checks[] = {
    {temperature, {95.0, 102.0}, VitalStatus::TEMPERATURE_CRITICAL},
    {pulseRate,   {60.0, 100.0}, VitalStatus::PULSE_CRITICAL},
    {spo2,        {90.0, 150.0}, VitalStatus::SPO2_CRITICAL}
  };

    auto it = std::find_if(std::begin(checks), std::end(checks),
        [](const VitalCheck& check) {
            return isOutOfRange(check.value, check.threshold);
        });

    return (it != std::end(checks)) ? it->status : VitalStatus::OK;
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
  static const std::unordered_map<VitalStatus, const char*> messages = {
    {VitalStatus::TEMPERATURE_CRITICAL, "Temperature is critical!\n"},
    {VitalStatus::PULSE_CRITICAL, "Pulse Rate is out of range!\n"},
    {VitalStatus::SPO2_CRITICAL, "Oxygen Saturation out of range!\n"}
  };

  auto it = messages.find(status);
  if (it != messages.end()) {
    cout << it->second;
  }
}
bool alert(VitalStatus status) {
  bool alertTriggered = false;

  if (status != VitalStatus::OK) {
    printAlertMessage(status);
    blinkAlert();
    alertTriggered = true;
  }

  return alertTriggered;
}
/*
int main() {
  float temperature = 103.0;
  float pulseRate = 85.0;
  float spo2 = 95.0;

  VitalStatus status = checkVitals(temperature, pulseRate, spo2);
  alert(status);

  return 0;
} */
