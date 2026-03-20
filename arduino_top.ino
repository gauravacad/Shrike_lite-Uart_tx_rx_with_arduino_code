  #include "Shrike.h"

ShrikeFlash fpga;

const int reset_pin = 2;
uint8_t value = 1;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000);

  Serial.println("Starting FPGA Flash...");

  // ---- Flash FPGA ----
  fpga.begin();
  fpga.flash("/FPGA_bitstream_MCU.bin");

  Serial.println("FPGA Flash Done");

  // ---- Reset FPGA ----
  pinMode(reset_pin, OUTPUT);
  digitalWrite(reset_pin, HIGH);
  delay(1000);
  digitalWrite(reset_pin, LOW);
  delay(1000);

  // ---- UART Init ----
  Serial1.begin(115200);   // GPIO0=TX, GPIO1=RX

  delay(500);
  Serial.println("UART Communication Started");
}

void loop() {
  uint8_t a = value;
  uint8_t b = value + 1;

  // ---- Send to FPGA ----
  Serial1.write(a);
  delay(10);
  Serial1.write(b);

  // Debug
  Serial.print("Sent: ");
  Serial.print(a);
  Serial.print(", ");
  Serial.println(b);

  // ---- Wait for reply ----
  unsigned long start = millis();
  bool received = false;

  while (millis() - start < 1000) {
    if (Serial1.available() > 0) {
      uint8_t reply = Serial1.read();

      Serial.print("Result: ");
      Serial.print(a);
      Serial.print(" + ");
      Serial.print(b);
      Serial.print(" = ");
      Serial.println(reply);

      Serial.print("HEX: 0x");
      Serial.println(reply, HEX);

      received = true;
      break;
    }
  }

  if (!received) {
    Serial.println("Timeout: No response from FPGA");
  }

  Serial.println("----------------------");

  value++;

  delay(2000);
}

