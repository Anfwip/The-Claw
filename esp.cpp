#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                      AwsEventType type, void *arg, uint8_t *data, size_t len) {
  // optional: handle messages from browser
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(1000);

  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  server.begin();
}

void loop() {
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 3000) {
    lastSend = millis();

    String message = R"rawliteral({
      "fingerColor": "#ff6600",
      "fingerWidth": 50,
      "fingerHeight": 140,
      "palmColor": "#0099ff",
      "palmWidth": 230,
      "palmHeight": 120
    })rawliteral";

    ws.textAll(message);
  }
}
