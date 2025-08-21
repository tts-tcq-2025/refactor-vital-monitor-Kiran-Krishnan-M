
#include <gtest/gtest.h>
#include "./monitor.h"


TEST(MonitorTest, NotOkWhenAnyVitalIsOffRange) {
  EXPECT_NE(checkVitals(99, 102, 70), VitalStatus::OK);
  EXPECT_EQ(checkVitals(98.1, 70, 98), VitalStatus::OK);
}














