#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "Redmi";
const char* password = "simple23";

// we will control these in subsequent updates
#define LED_BUILTIN 2
#define LED_DELAY 100
#define FIRMWARE_VERSION "1.0"

void setupOTA() {
  // Initialize OTA
  ArduinoOTA.setHostname("esp32"); // Set the hostname
  ArduinoOTA.setPassword("admin"); // Set the OTA password
  ArduinoOTA.onStart([]() {
    Serial.println("Start updating.");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)         Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)   Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)     Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void setupPeripherals() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void setupWifi() {
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void blinkLED() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(LED_DELAY);
  digitalWrite(LED_BUILTIN, LOW);
  delay(LED_DELAY);
}

void setup() {
  Serial.begin(115200);
  
  setupPeripherals();
  setupWifi(); 
  setupOTA();

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("Device v%s\n", FIRMWARE_VERSION);
}

void loop() {
  ArduinoOTA.handle(); // Handles OTA update, if any

  // Your application logic goes here
  blinkLED();
}
