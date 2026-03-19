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



Error facing 
