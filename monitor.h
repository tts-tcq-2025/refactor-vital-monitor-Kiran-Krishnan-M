#ifndef MONITOR_H
#define MONITOR_H

#include <string>

// ---------- Structures ----------
struct VitalThreshold {
  float min;
  float max;  // use +infinity if no max check needed
};

struct VitalStatus {
  std::string name;
  float value;
  VitalThreshold threshold;
};

// ---------- Pure Functions ----------
bool isOutOfRange(float value, const VitalThreshold& threshold);
std::string checkVital(const VitalStatus& vital);

// ---------- I/O Functions ----------
void blinkAlert(const std::string& message);

// ---------- Monitoring Function ----------
bool vitalsOk(float temperature, float pulseRate, float spo2);

#endif // MONITOR_H






