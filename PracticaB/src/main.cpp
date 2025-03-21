#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define OLED_SDA 16
#define OLED_SCL 17

#define LM35_PIN 4 // Pin analógico donde conectas la salida del LM35

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

void setup() {
  Wire1.begin(OLED_SDA, OLED_SCL);
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("¡No se pudo iniciar el OLED!"));
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int adcValue = analogRead(LM35_PIN); // Leer el valor del ADC
  float voltage = (adcValue / 4095.0) * 3.3; // Convertir a voltaje (ESP32 ADC = 12 bits)
  float temperatureC = voltage * 100.0; // LM35 = 10 mV/°C

  // Mostrar en monitor serie
  Serial.print("Temperatura: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // Mostrar en OLED
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("🌡 Temp: ");
  display.print(temperatureC, 1);
  display.print(" C");
  display.display();

  delay(1000);
}
