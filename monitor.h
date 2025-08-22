#ifndef MONITOR_H
#define MONITOR_H

// ---------- Vital Ranges ----------
constexpr float TEMP_LOW   = 95.0f;
constexpr float TEMP_HIGH  = 102.0f;
constexpr float PULSE_LOW  = 60.0f;
constexpr float PULSE_HIGH = 100.0f;
constexpr float SPO2_MIN   = 90.0f;

constexpr float tolerance  = TEMP_HIGH * 0.015f;  // 1.5% of upper limit

// ---------- Function Declarations ----------

// Alert function (different in UNIT_TEST vs Production)
void blinkAlert();

// Temperature checks
void temp_hypothermia(float temperature);
void temp_hyperthermia(float temperature);
bool tempOk(float temperature);

// Pulse check
bool pulseRateOk(float pulseRate);

// SpO2 check
bool spo2Ok(float spo2);

// Combined monitoring
bool vitalsOk(float temperature, float pulseRate, float spo2);

#endif // MONITOR_H








