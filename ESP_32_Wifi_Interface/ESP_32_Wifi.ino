#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_AP";
const char* password = "esp32password";

WebServer server(80);

String htmlContent = "index.html"; // Masukkan kode HTML dan JavaScript di sini

void handleRoot() {
  server.send(200, "text/html", htmlContent);
}

void handleConnect() {
  String ssidValue = server.arg("ssid");
  String passwordValue = server.arg("password");

  // Kode untuk menghubungkan ESP32 ke WiFi menggunakan ssidValue dan passwordValue
  // ...

  server.send(200, "text/html", "Connected to WiFi");
}

void handleScanWiFi() {
  String wifiOptions = "";
  int numOfNetworks = WiFi.scanNetworks();
  for (int i = 0; i < numOfNetworks; i++) {
    wifiOptions += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
  }
  
  htmlContent.replace("<!-- WiFi options will be added dynamically using JavaScript -->", wifiOptions);

  server.send(200, "text/html", htmlContent);
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/connect", HTTP_POST, handleConnect);
  server.on("/scan", HTTP_GET, handleScanWiFi);

  server.begin();
}

void loop() {
  server.handleClient();
}
