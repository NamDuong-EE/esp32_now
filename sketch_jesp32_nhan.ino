#include <esp_now.h>
#include <WiFi.h>
#include <WebServer.h>

#define LED_PIN 2

WebServer server(80);

// ========================
// Cấu trúc dữ liệu
// ========================
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

struct_message myData;

// Biến hiển thị web
String senderMAC = "-";
unsigned long packetCount = 0;

// ========================
// Trang web
// ========================
void handleRoot() {

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta http-equiv='refresh' content='1'>
<meta name='viewport' content='width=device-width,initial-scale=1'>
<title>ESP32 Monitor</title>
</head>

<body style="font-family:Arial;text-align:center">

<h2>ESP32 ESP-NOW Monitor</h2>

<hr>

)rawliteral";

  html += "<p><b>Packets:</b> " + String(packetCount) + "</p>";
  html += "<p><b>Sender:</b> " + senderMAC + "</p>";
  html += "<p><b>Char:</b> " + String(myData.a) + "</p>";
  html += "<p><b>Int:</b> " + String(myData.b) + "</p>";
  html += "<p><b>Float:</b> " + String(myData.c) + "</p>";
  html += "<p><b>Bool:</b> " + String(myData.d) + "</p>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

// ========================
// Callback nhận ESP-NOW
// ========================
void OnDataRecv(const esp_now_recv_info_t *recv_info,
                const uint8_t *incomingData,
                int len)
{

  memcpy(&myData, incomingData, sizeof(myData));

  packetCount++;

  char macStr[18];

  sprintf(macStr,
          "%02X:%02X:%02X:%02X:%02X:%02X",
          recv_info->src_addr[0],
          recv_info->src_addr[1],
          recv_info->src_addr[2],
          recv_info->src_addr[3],
          recv_info->src_addr[4],
          recv_info->src_addr[5]);

  senderMAC = String(macStr);

  Serial.println("\n===== RECEIVE =====");

  Serial.print("Packets : ");
  Serial.println(packetCount);

  Serial.print("MAC     : ");
  Serial.println(senderMAC);

  Serial.print("Char    : ");
  Serial.println(myData.a);

  Serial.print("Int     : ");
  Serial.println(myData.b);

  Serial.print("Float   : ");
  Serial.println(myData.c);

  Serial.print("Bool    : ");
  Serial.println(myData.d);

  Serial.println("===================");

  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
}

// ========================
// Setup
// ========================
void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  // AP ở channel 1 để dùng với ESP-NOW
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP32_DEBUG", "12345678", 1);

  Serial.println();
  Serial.println("================================");
  Serial.println("ESP32 DEBUG AP");
  Serial.print("SSID : ");
  Serial.println("ESP32_DEBUG");
  Serial.print("PASS : ");
  Serial.println("12345678");
  Serial.print("IP   : ");
  Serial.println(WiFi.softAPIP());
  Serial.println("================================");

  server.on("/", handleRoot);
  server.begin();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("ESP-NOW Ready");
}

// ========================
// Loop
// ========================
void loop() {
  server.handleClient();
}