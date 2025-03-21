#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define LM35_PIN 4 // Pin analógico donde conectaste el LM35

const char *ssid = "Renatooo";         // 🔁 Cambia esto
const char *password = "1234567AB"; // 🔁 Cambia esto

AsyncWebServer server(80);
float temperatureC = 0.0;

void setup() {
  Serial.begin(9600);
  delay(1000);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Ruta web para mostrar temperatura
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta http-equiv='refresh' content='2'><title>Temperatura LM35</title></head><body>";
    html += "<h1>🌡 Temperatura desde LM35</h1>";
    html += "<p><strong>Temperatura:</strong> " + String(temperatureC, 1) + " &deg;C</p>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  // Leer el sensor
  int adcValue = analogRead(LM35_PIN);
  float voltage = (adcValue / 4095.0) * 3.3; // ADC de 12 bits, referencia 3.3V
  temperatureC = voltage * 100.0; // LM35 = 10mV/°C

  Serial.print("Temp: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(1000);
}
