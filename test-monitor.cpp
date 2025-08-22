#include <gtest/gtest.h>
#include "./monitor.h"

// --- Individual vital checks ---
TEST(TemperatureTest, BoundaryAndOutOfRange) {
  EXPECT_EQ(tempOk(95), 1);     // Lower bound valid
  EXPECT_EQ(tempOk(102), 1);    // Upper bound valid
  EXPECT_EQ(tempOk(94.9), 0);   // Below range
  EXPECT_EQ(tempOk(102.1), 0);  // Above range
}

TEST(PulseRateTest, BoundaryAndOutOfRange) {
  EXPECT_EQ(pulseRateOk(60), 1);     // Lower bound valid
  EXPECT_EQ(pulseRateOk(100), 1);    // Upper bound valid
  EXPECT_EQ(pulseRateOk(59), 0);     // Below range
  EXPECT_EQ(pulseRateOk(101), 0);    // Above range
}

TEST(SpO2Test, MinimumCheck) {
  EXPECT_EQ(spo2Ok(90), 1);     // Minimum valid
  EXPECT_EQ(spo2Ok(95), 1);     // Normal valid
  EXPECT_EQ(spo2Ok(89.9), 0);   // Below valid
}

// --- Combined vital checks ---
TEST(Monitor, CombinedVitals) {
  EXPECT_FALSE(vitalsOk(99, 102, 70));     // Pulse high + SpO2 low
  EXPECT_TRUE(vitalsOk(98.1, 70, 98));     // All good
  EXPECT_TRUE(vitalsOk(95, 60, 90));       // Boundary valid
  EXPECT_TRUE(vitalsOk(102, 100, 90));     // Boundary valid
  EXPECT_FALSE(vitalsOk(94, 59, 89));      // All low
  EXPECT_FALSE(vitalsOk(103, 101, 91));    // Temp & pulse high
  EXPECT_TRUE(vitalsOk(101, 100, 90));     // High boundary ok
  EXPECT_TRUE(vitalsOk(96, 100, 90));      // Edge valid
}





