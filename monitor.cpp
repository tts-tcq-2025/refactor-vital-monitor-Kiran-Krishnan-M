#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;
constexpr float TEMP_LOW = 95.0f;
constexpr float TEMP_HIGH = 102.0f;
constexpr float PULSE_LOW = 60.0f;
constexpr float PULSE_HIGH = 100.0f;
constexpr float SPO2_MIN = 90.0f;
constexpr int OK = 1;
constexpr int NOT_OK = 0;
constexpr float tolerance = TEMP_HIGH * 0.015f;  // 1.5% of upper limit

void blinkAlert() {
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
  cout << "\r  \r" << flush;  // Clear line after alert
}

void temp_hypothermia(float temperature) {
    if ((temperature >= TEMP_LOW && temperature <= TEMP_LOW + tolerance)) {
        cout << "Warning: Approaching hypothermia\n";
    }
}
void temp_hyperthermia(float temperature) {
    if ((temperature >= TEMP_HIGH - tolerance && temperature <= TEMP_HIGH)) {
        cout << "Warning: Approaching hyperthermia\n";
    }
}

int tempOk(float temperature) {
    if (temperature > TEMP_HIGH || temperature < TEMP_LOW) {
        cout << "Temperature is critical!\n";
        blinkAlert();
        return NOT_OK;
    }
    temp_hypothermia(temperature);
    temp_hyperthermia(temperature);
    return OK;
}

int pulseRateOk(float pulseRate) {
  if (pulseRate < PULSE_LOW || pulseRate > PULSE_HIGH) {
    cout << "Pulse Rate is out of range!\n";
    blinkAlert();
    return NOT_OK;
  }
return OK;
}
int spo2Ok(float spo2) {
  if (spo2 < SPO2_MIN) {
    cout << "Oxygen Saturation out of range!\n";
    blinkAlert();
    return NOT_OK;
  }
return OK;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  return tempOk(temperature) && pulseRateOk(pulseRate) && spo2Ok(spo2);
}
