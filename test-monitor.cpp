#include <gtest/gtest.h>
#include "./monitor.h"

TEST(MonitorTest, DetectsTemperatureOutOfRange) {
  EXPECT_EQ(checkVitals(103.0, 75.0, 95.0), VitalStatus::TEMPERATURE_CRITICAL);
  EXPECT_EQ(checkVitals(94.0, 75.0, 95.0), VitalStatus::TEMPERATURE_CRITICAL);
}

TEST(MonitorTest, DetectsPulseOutOfRange) {
  EXPECT_EQ(checkVitals(98.0, 55.0, 95.0), VitalStatus::PULSE_CRITICAL);
  EXPECT_EQ(checkVitals(98.0, 105.0, 95.0), VitalStatus::PULSE_CRITICAL);
}

TEST(MonitorTest, DetectsSpo2OutOfRange) {
  EXPECT_EQ(checkVitals(98.0, 75.0, 85.0), VitalStatus::SPO2_CRITICAL);
}

TEST(MonitorTest, AllVitalsInRange) {
  EXPECT_EQ(checkVitals(98.6, 75.0, 98.0), VitalStatus::OK);
}

// Dummy usage to avoid unused function warning
namespace {
  void useAlertFunction() {
    if (false) {
      alert(VitalStatus::TEMPERATURE_CRITICAL);
    }
  }
}







