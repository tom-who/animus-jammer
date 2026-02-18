#include <SPI.h>
#include <RF24.h>

#define CE_PIN1 10
#define CSN_PIN1 9

#define CE_PIN2 8
#define CSN_PIN2 7

RF24 radio1(CE_PIN1, CSN_PIN1, 16000000); // Set max rate for both radios (16000000)
RF24 radio2(CE_PIN2, CSN_PIN2, 16000000);

void setup() {
  SPI.begin(13, 12, 11); // This is specific for my wiring and microcontroller, as the SPI interface is defined as something else that doesnt fit with the esp32 nano
  Serial.begin(115200);
  delay(5000);

  // Check if both radios are working

  if (!radio1.begin()) {
    Serial.println("Radio 1 isnt working!");
  } else {
    Serial.println("Radio 1 OK");
  }
  if (!radio2.begin()) {
    Serial.println("Radio 2 isnt working!");
  } else {
    Serial.println("Radio 2 OK");
  }

  // Configure radios to jam

  radio1.setAutoAck(false);
  radio1.stopListening();
  radio1.setRetries(0, 0);
  radio1.setPALevel(RF24_PA_MAX, true);
  radio1.setDataRate(RF24_2MBPS);
  radio1.setCRCLength(RF24_CRC_DISABLED);
  radio1.startConstCarrier(RF24_PA_MAX, 45);
  radio2.setAutoAck(false);
  radio2.stopListening();
  radio2.setRetries(0, 0);
  radio2.setPALevel(RF24_PA_MAX, true);
  radio2.setDataRate(RF24_2MBPS);
  radio2.setCRCLength(RF24_CRC_DISABLED);
  radio2.startConstCarrier(RF24_PA_MAX, 45);

  // At this point they are already screaming a bunch of noise but on channel 45 specifically, we wait for user input to continue

  while(Serial.available() == 0){}
}

void loop() {

  // Constantly switch channels between 1 - 80 (Bluetooth channels)
  radio1.setChannel(random(81));
  radio2.setChannel(random(81));
}
