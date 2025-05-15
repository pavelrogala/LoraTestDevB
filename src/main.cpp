#include <SPI.h>
#include <LoRa.h>

#define LED_PIN 12
#define LORA_CS 5
#define LORA_RST 14
#define LORA_IRQ 4

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize LoRa
  if (!LoRa.begin(433E6)) {  // Set LoRa frequency (e.g., 868 MHz)
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  
  Serial.println("LoRa Receiver Initialized!");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";
    while (LoRa.available()) {
      received += (char)LoRa.read();
    }
    
    if (received == "BUTTON_PRESSED") {
      digitalWrite(LED_PIN, HIGH); // Turn on LED
      Serial.println("Button pressed, LED ON");
    } else {
      digitalWrite(LED_PIN, LOW); // Turn off LED
      Serial.println("Button not pressed, LED OFF");
    }
  }
}