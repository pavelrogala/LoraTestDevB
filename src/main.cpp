#include <SPI.h>
#include <LoRa.h>

#define ss   5   // Chip select pin for LoRa
#define rst  14  // Reset pin for LoRa
#define dio0 2   // Interrupt pin for LoRa

#define LED_PIN 13

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

  // Setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  // Try to initialize LoRa
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);  // Wait and keep trying to initialize LoRa
  }

  // Set sync word to ensure you're not receiving messages from other LoRa modules
  LoRa.setSyncWord(0xF3);

   // Set LED pin as output
  pinMode(LED_PIN, OUTPUT);

  Serial.println("LoRa Initializing OK!");
}


void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";
    while (LoRa.available()) {
      received += (char)LoRa.read();
    }
    
    if (received == "HIGH") {
      Serial.println(received);
      digitalWrite(LED_PIN, HIGH);
      Serial.println("toggle high");
    }

    if(received == "LOW") {
      Serial.println(received);
      digitalWrite(LED_PIN, LOW);
      Serial.println("toggle low");
    }
  }
}