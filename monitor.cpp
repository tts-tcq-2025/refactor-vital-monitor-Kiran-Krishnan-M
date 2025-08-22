#include "monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <limits>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// ---------- Pure Functions ----------
bool isOutOfRange(float value, const VitalThreshold& threshold) {
  return value < threshold.min || value > threshold.max;
}

std::string checkVital(const VitalStatus& vital) {
  if (isOutOfRange(vital.value, vital.threshold)) {
    return vital.name + " is out of range!";
  }
  return "";
}

// ---------- I/O Functions ----------
#ifndef UNIT_TEST
// Production version: blinking alert with delays
void blinkAlert(const std::string& message) {
  cout << message << "\n";
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
  cout << "\n";
}
#else
// Unit test version: no sleep (fast execution)
void blinkAlert(const std::string& message) {
  cout << "[ALERT] " << message << "\n";
}
#endif

// ---------- Monitoring Function ----------
bool vitalsOk(float temperature, float pulseRate, float spo2) {
  std::unordered_map<std::string, VitalThreshold> thresholds = {
      {"Temperature", {95, 102}},
      {"Pulse Rate", {60, 100}},
      {"Oxygen Saturation", {90, std::numeric_limits<float>::infinity()}} // only min check
  };

  VitalStatus vitals[] = {
      {"Temperature", temperature, thresholds["Temperature"]},
      {"Pulse Rate", pulseRate, thresholds["Pulse Rate"]},
      {"Oxygen Saturation", spo2, thresholds["Oxygen Saturation"]}
  };

  for (const auto& vital : vitals) {
    std::string msg = checkVital(vital);
    if (!msg.empty()) {
      blinkAlert(msg);
      return false;
    }
  }
  return true;
}
