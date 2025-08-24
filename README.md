# MazeBot — ESP32 Maqueta (Sensores y Actuadores)

**Descripción breve**  
Firmware para la **ESP32 (WROOM-32)** instalada en la **maqueta del laberinto**. Este módulo gestiona **sensores IR** de inicio/fin, **señalización con LEDs** y **buzzer**, y se comunica por **Wi-Fi (AP/STA)** con la app/ESP32-CAM y (opcional) **Firebase** para registrar eventos (tiempos, puntuación, estado).

---

## Características
- Lectura de **IR de ENTRADA y SALIDA** para cronometraje del recorrido.
- **LED verde/rojo** para estados (listo, corriendo, fin/alerta).
- **Buzzer** para feedback acústico (inicio/fin/fallos).
- Comunicación Wi-Fi por **HTTP/MQTT** (según configuración del proyecto).
- Proyecto listo para **Visual Studio Code + PlatformIO**.

---

## Pines (config por defecto)

```cpp
// Pines de sensores y actuadores (configuración actual)
const int IR_ENTRADA = 39;  // Entrada digital (solo input)
const int IR_SALIDA  = 4;   // Entrada/Salida digital
const int LED_VERDE  = 0;   // Salida (strapping pin)
const int LED_ROJO   = 2;   // Salida (strapping pin)
const int BUZZER     = 36;  // Salida
