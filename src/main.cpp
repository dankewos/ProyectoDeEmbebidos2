#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Pines de sensores y actuadores
const int IR_ENTRADA = 39;
const int IR_SALIDA  = 4;
const int LED_VERDE  = 0;
const int LED_ROJO   = 2;
const int BUZZER     = 36;

// --- Configuración WiFi ---
const char* ssid     = "carrito";
const char* password = "12345678";

// IP de la ESP32-CAM (servidor)
String camIP = "http://192.168.4.1";   // cambia esta IP por la real de la CAM

void setup() {
  // Inicializa pines de entrada
  pinMode(IR_ENTRADA, INPUT);
  pinMode(IR_SALIDA, INPUT);

  // Inicializa pines de salida
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Apaga todo al inicio
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, HIGH);
  digitalWrite(BUZZER, LOW);

  // --- Conexión WiFi ---
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi!");
  Serial.print("IP ESP32 (maqueta): ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Lee sensores IR
  bool irEntrada = digitalRead(IR_ENTRADA);
  bool irSalida  = digitalRead(IR_SALIDA);

  // Sensor de entrada activado
  if (irEntrada == HIGH) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(BUZZER, HIGH);

    // --- Notificar a ESP32-CAM ---
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(camIP + "/inicio"); // ruta que atenderá la CAM
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.println("Notificación INICIO enviada");
      } else {
        Serial.println("Error al enviar INICIO");
      }
      http.end();
    }
  } else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(BUZZER, LOW);
  }

  // Sensor de salida activado
  if (irSalida == HIGH) {
    digitalWrite(LED_ROJO, HIGH);

    // --- Notificar a ESP32-CAM ---
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(camIP + "/fin"); // ruta que atenderá la CAM
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.println("Notificación FIN enviada");
      } else {
        Serial.println("Error al enviar FIN");
      }
      http.end();
    }
  } else {
    digitalWrite(LED_ROJO, LOW);
  }

  delay(50);  // Pequeño retardo para estabilidad
}
