
#include <gtest/gtest.h>
#include "./monitor.h"

extern bool testMode;  // Declare the flag

TEST(MonitorTest, NotOkWhenAnyVitalIsOffRange) {

  testMode = true;  // Disable blinking
  // Pulse rate is out of range (102)
  EXPECT_NE(checkVitals(99, 102, 70), VitalStatus::OK);

  // All vitals are within range
  EXPECT_EQ(checkVitals(98.1, 70, 98), VitalStatus::OK);
}











