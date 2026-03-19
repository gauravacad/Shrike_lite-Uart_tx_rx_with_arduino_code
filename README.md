# Shrike_lite-Uart_tx_rx_with_arduino_code
# Shrike_lite compilation with Uart_tx_rx_with_arduino_code
## Add Two 8-bit Numbers on FPGA and Return Result via UART
This project demonstrates UART-based communication between an RP2040 and an FPGA. Two 8-bit numbers are sent from the RP2040 to the FPGA over UART. The FPGA stores the received values, performs an addition operation, and then transmits the result back to the RP2040 using UART.

## Overview on FPGA side
- This project consists of three modules :
- top : This module implements the FSM.
- Continuously look for input data
- Add the two 8 bit numbers.
- Generate appropriate transmission signal onces summation is done.
- uart_rx :  This module implements a UART Receiver.
- When the data is received, it makes "data valid" signal high.
- uart_rx :  This module implements a UART Transmitter.
-When the start signal is given, it transmit the data present in its output buffer.


# Please help us on the following
## ! Error facing 
when we use `Arduino_top.ino` that produces the time out issue
```
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
```
