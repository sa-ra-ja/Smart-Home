

#define BLYNK_TEMPLATE_ID "TMPL3F3Rcqxu6"
#define BLYNK_TEMPLATE_NAME "srjclean"
#define BLYNK_AUTH_TOKEN "dbQeQHfh9buAA9qQj0zWCrugJaoBBZmf"

#include <BlynkSimpleEsp8266.h>

// WiFi credentials
char ssid[] = "Sathya";
char pass[] = "nithya12345";

// Pin definitions
#define LED1_PIN D0        // LED 1 controlled by Blynk (V0)
#define FAN_RELAY_PIN D1   // Fan Relay controlled by Blynk (V1)
#define LED3_PIN D2        // LED 3 controlled by Blynk (V2)
#define STM32_LED_PIN D4   // LED controlled by STM32 UART

// Blynk button handlers
BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(LED1_PIN, value);  // Normal LED
}

BLYNK_WRITE(V1) {  // Fan control button
  int value = param.asInt();
  // Relay is active LOW -> invert the logic
  digitalWrite(FAN_RELAY_PIN, !value);   // ON = LOW, OFF = HIGH
}

BLYNK_WRITE(V2) {
  int value = param.asInt();
  digitalWrite(LED3_PIN, value); // Normal LED
}

void setup() {
  Serial.begin(115200); // UART RX from STM32
  
  pinMode(LED1_PIN, OUTPUT);
  pinMode(FAN_RELAY_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(STM32_LED_PIN, OUTPUT);
  
  // Initialize all OFF (for relay OFF = HIGH)
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(FAN_RELAY_PIN, HIGH);   // Fan OFF initially
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(STM32_LED_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // Check UART data from STM32
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '1') {
      digitalWrite(STM32_LED_PIN, HIGH);
    } else if (c == '0') {
      digitalWrite(STM32_LED_PIN, LOW);
    }
  }
}
