#include <SoftwareSerial.h>

const int pinRX = 5;
const int pinTX = 4;
const int pinBarcodeTrigger = 16;
char c;

String barcodeValue;

SoftwareSerial mySerial(pinRX, pinTX, false); // RX, TX

void setup() {
  pinMode(pinBarcodeTrigger, OUTPUT);
  pinMode(pinRX, INPUT);
  pinMode(pinTX, OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  byte message[] = {0x0B, 0x04, 0x31, 0x00, 0x00, 0x41, 0x30, 0x30, 0x30, 0x30, 0xFF, 0xFD, 0xC0};
  mySerial.write(message, sizeof(message));
}

void loop() {
  digitalWrite(pinBarcodeTrigger, HIGH);
  delay(30);
  digitalWrite(pinBarcodeTrigger, LOW);
  if (mySerial.available()) {
    c = mySerial.read();
    Serial.print(c);
    if ((int)c == 13) {
      Serial.println("Sender strekkode..");
    }
  }
  delay(200);
}
