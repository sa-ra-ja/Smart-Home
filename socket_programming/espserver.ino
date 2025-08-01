#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Redmi K50i";         // Replace with your Wi-Fi network name
const char* password = "zzzzzzzz"; // Replace with your Wi-Fi network password
int LED_PIN = 2;                             // GPIO pin connected to the LED (e.g., GPIO2 for the onboard LED)

WiFiServer server(80); // Create a server instance on port 80

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Turn off the LED initially

  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start the server
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available(); // Check for incoming client connections
  if (!client) {
    return;
  }

  Serial.println("New client connected");
  while (client.connected()) {
    if (client.available()) {
      String request = client.readStringUntil('\r'); // Read the client request
      Serial.print("Request: ");
      Serial.println(request);

      if (request.indexOf("GET /on") != -1) {
        digitalWrite(LED_PIN, HIGH); // Turn on the LED
        Serial.println("LED ON");
      } else if (request.indexOf("GET /off") != -1) {
        digitalWrite(LED_PIN, LOW); // Turn off the LED
        Serial.println("LED OFF");
      }
      
      // Send a simple response to the client
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type: text/html");
      client.println();
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.print("<h1>LED is now ");
      client.print(digitalRead(LED_PIN) == HIGH ? "ON" : "OFF");
      client.println("</h1>");
      client.println("<a href=\"/on\"><button>Turn ON</button></a>");
      client.println("<a href=\"/off\"><button>Turn OFF</button></a>");
      client.println("</html>");

      break; // Exit the loop after processing the request
    }
  }
  delay(1); // Small delay to allow the client to disconnect
}

