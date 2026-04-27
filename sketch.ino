// Task3.1Trigger_SecurityLight.ino
// SIT210 - Task 3.1P — Automatic Security Light (Calibrated)
//
// CALIBRATION RESULTS:
//   0.1 lux  (very dark)   = reading ~1015
//   100000 lux (very bright) = reading ~8
//
// Threshold set at 900 = approximately dusk (~55 lux)
// Security light turns ON  when reading > 900 (getting dark)
// Security light turns OFF when reading <= 900 (bright enough)

// ─── PIN DEFINITIONS ────────────────────────────────────────────────────────
const int LIGHT_PIN    = A0;  // LDR analogue input
const int SECURITY_LED = 4;   // Security light — ON in darkness
const int STATUS_LED   = 5;   // Status indicator — mirrors security light

// ─── CALIBRATED THRESHOLD ───────────────────────────────────────────────────
const int DARK_THRESHOLD = 900;  // reading above this = dark = lights ON

// ─── TIMING ─────────────────────────────────────────────────────────────────
const unsigned long CHECK_INTERVAL = 3000;
unsigned long lastCheckTime = 0;

// ─── STATE ──────────────────────────────────────────────────────────────────
bool securityLightOn = false;

// ─── COMMENTED OUT: WiFi and MQTT (uncomment for real hardware) ─────────────
// #include <WiFiNINA.h>
// #include <ArduinoMqttClient.h>
// const char* WIFI_SSID     = "YOUR_SSID";
// const char* WIFI_PASSWORD = "YOUR_PASSWORD";
// const char* MQTT_BROKER   = "broker.hivemq.com";
// const int   MQTT_PORT     = 1883;
// const char* TOPIC_LIGHT   = "sit210/terrarium/light";
// WiFiClient wifiClient;
// MqttClient mqttClient(wifiClient);

// ─── SETUP ──────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  setupPins();
  Serial.println("=== terrarium auto light ===");
  Serial.println("Threshold: 900 (above = dark, below = bright)");
  Serial.println("Drag slider RIGHT (toward dark) to turn light ON");
  Serial.println("Drag slider LEFT  (toward bright) to turn light OFF");
  Serial.println("===================================");
}

// ─── MAIN LOOP ──────────────────────────────────────────────────────────────
void loop() {
  if (millis() - lastCheckTime >= CHECK_INTERVAL) {
    int lightValue = readLightLevel();
    checkAndTrigger(lightValue);
    lastCheckTime = millis();
  }
}

// ─── MODULE: Pin Setup ───────────────────────────────────────────────────────
void setupPins() {
  pinMode(SECURITY_LED, OUTPUT);
  pinMode(STATUS_LED,   OUTPUT);
  digitalWrite(SECURITY_LED, LOW);
  digitalWrite(STATUS_LED,   LOW);
}

// ─── MODULE: Light Level Reading ────────────────────────────────────────────
int readLightLevel() {
  int level = analogRead(LIGHT_PIN);
  Serial.print("Reading: " + String(level));
  Serial.print(" | Status: ");
  Serial.println(level > DARK_THRESHOLD ? "DARK" : "BRIGHT");
  return level;
}

// ─── MODULE: Trigger + Security Light Handler ───────────────────────────────
void checkAndTrigger(int lightValue) {

  // Reading HIGH = dark — turn security light ON
  if (lightValue > DARK_THRESHOLD && !securityLightOn) {
    securityLightOn = true;
    digitalWrite(SECURITY_LED, HIGH);
    digitalWrite(STATUS_LED,   HIGH);
    Serial.println(">>> SUNLIGHT STOPPED —  light ON");
    // publishNotification("SUNLIGHT_STOP");
  }

  // Reading LOW = bright — turn security light OFF
  else if (lightValue <= DARK_THRESHOLD && securityLightOn) {
    securityLightOn = false;
    digitalWrite(SECURITY_LED, LOW);
    digitalWrite(STATUS_LED,   LOW);
    Serial.println(">>> SUNLIGHT DETECTED —  light OFF");
    // publishNotification("SUNLIGHT_START");
  }
}
