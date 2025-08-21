// monitor.h
#pragma once

enum class VitalStatus {
  OK,
  TEMPERATURE_CRITICAL,
  PULSE_CRITICAL,
  SPO2_CRITICAL
};

struct VitalThreshold {
  float min;
  float max;
};

bool isOutOfRange(float value, const VitalThreshold& threshold);
VitalStatus checkVitals(float temperature, float pulseRate, float spo2);
bool alert(VitalStatus status);




