constexpr uint32_t UART_BAUD = 115200;

int readReplyByte(unsigned long timeoutMs);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }

  Serial1.setTX(0);
  Serial1.setRX(1);
  Serial1.begin(UART_BAUD);
  delay(50);

  while (Serial1.available() > 0) {
    Serial1.read();
  }

  Serial.println("FPGA UART sum auto test ready.");
}

void loop() {
  static uint8_t value = 1;
  uint8_t a = value;
  uint8_t b = value + 1;

  while (Serial1.available() > 0) {
    Serial1.read();
  }

  Serial1.write(a);
  Serial1.write(b);
  Serial1.flush();

  int reply = readReplyByte(1000);
  if (reply < 0) {
    Serial.println("Timeout waiting for FPGA response.");
    value = value + 1;
    delay(2000);
    return;
  }

  Serial.print(a);
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println((uint8_t)reply);

  value = value + 1;
  delay(2000);
}

int readReplyByte(unsigned long timeoutMs) {
  unsigned long startTime = millis();
  while (millis() - startTime <= timeoutMs) {
    if (Serial1.available() > 0) {
      return Serial1.read();
    }
    delay(1);
  }
  return -1;
}
