#include <WiFi.h>
#include <HTTPClient.h>

// Change these to match your WiFi network
const char* ssid = "Redmi";
const char* password = "simple23";

// Change this to match your local server's IP address
const char* serverIP = "192.168.162.130";
const int serverPort = 5000;

HTTPClient http;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}

void loop() {
  // Make GET request
  Serial.println("Making GET request...");
  String url = "http://" + String(serverIP) + ":" + String(serverPort) + "/get";
  http.begin(url);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.print("Response payload: ");
    Serial.println(response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  // Make POST request
  Serial.println("Making POST request...");
  url = "http://" + String(serverIP) + ":" + String(serverPort) + "/post";
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  String requestBody = "{\"key\": \"value\"}";
  httpResponseCode = http.POST(requestBody);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.print("Response payload: ");
    Serial.println(response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  delay(2000);
}
