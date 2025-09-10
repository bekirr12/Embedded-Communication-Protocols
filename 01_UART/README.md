# UART Communication Protocol

[UART](https://img.shields.io/badge/Protocol-UART-blue.svg)

This document serves as a detailed guide to the theoretical foundations, operational principles, and practical importance of the **UART (Universal Asynchronous Receiver-Transmitter)** communication protocol. It is a fundamental building block for debugging and inter-device serial communication in embedded systems.

## Table of Contents
1.  [What is UART?](#what-is-uart)
2.  [Core Concepts](#core-concepts)
    * [Physical Connection](#physical-connection)
    * [Asynchronous Communication](#asynchronous-communication)
3.  [The UART Data Frame](#the-uart-data-frame)
4.  [Key Configuration Parameters](#key-configuration-parameters)
5.  [Physical Layer & Voltage Levels](#physical-layer--voltage-levels)
    * [TTL / CMOS Logic](#ttl--cmos-logic)
    * [RS-232 Standard](#rs-232-standard)
6.  [Common Problems & Troubleshooting](#common-problems--troubleshooting)
7.  [Code Examples](#code-examples)

---

## What is UART?

**UART** is a hardware peripheral that facilitates serial and asynchronous data communication between two digital devices. It converts parallel data from a microcontroller into a serial bitstream for transmission over a single line and translates the incoming serial bitstream back into parallel data for the receiving device.

**Key Features:**
* **Simplicity:** Requires a minimum of two data wires for communication.
* **Asynchronous:** No shared clock signal is necessary, which simplifies wiring.
* **Widespread:** It is available as a hardware peripheral in nearly all microcontrollers.
* **Debugging:** It provides the easiest method to print a program's internal state or sensor data to a computer.

## Core Concepts

### Physical Connection

A minimal UART connection requires three mandatory lines:

* **TX (Transmit):** The line for sending data.
* **RX (Receive):** The line for receiving data.
* **GND (Ground):** A common ground connection is essential for both devices to correctly reference voltage levels.

The connection is always crossed over: the TX pin of one device connects to the RX pin of the other.

```
                  +-----------+        +-----------+
                  |  Device A |        |  Device B |
                  |           |        |           |
                  |     TX  o | -----> | o RX      |
                  |           |        |           |
                  |     RX  o | <----- | o TX      |
                  |           |        |           |
                  |    GND  o | ------ | o GND     |
                  +-----------+        +-----------+
```

### Asynchronous Communication

Being "asynchronous" means that the sender and receiver do not use a shared clock signal. So, how is synchronization achieved? Through a pre-agreed set of rules before communication begins:
1.  **Baud Rate:** The speed of data transmission.
2.  **Data Frame:** The structure used to package the data.

The receiver listens for a change on the line (the Start Bit) to detect incoming data and then samples the line at the agreed-upon baud rate using its own internal clock.

## The UART Data Frame

In UART, data is sent in packets called "frames."

**Idle State:** When there is no communication, the line is held constant at a logic '1' (HIGH) level.

![UART Frame](https://i.imgur.com/7wG2b5p.png)

The anatomy of a frame is as follows:

1.  **Start Bit:** The transmitter initiates communication by pulling the line to '0' (LOW) for one bit duration. This is a "wake-up" signal for the receiver.
2.  **Data Bits:** The actual data, which is typically 8 bits (1 byte). The data is sent **LSB (Least Significant Bit) first**.
3.  **Parity Bit (Optional):** A simple error-checking bit. It can be set to complete the total number of '1's in the data to an Even or Odd number. In modern applications, it is often not used (`None`).
4.  **Stop Bit(s):** To signal the end of the frame, the line is pulled back to '1' (HIGH) for one or two bit durations. This brings the line back to the `Idle` state, ready for the next frame.

## Key Configuration Parameters

For successful communication, both the transmitter and receiver must be configured with the **exact same parameters**:

| Parameter     | Common Values                    | Description                                                   |
|---------------|----------------------------------|---------------------------------------------------------------|
| **Baud Rate** | 9600, 19200, **115200** | The number of bits transmitted per second. The most critical setting. |
| **Data Bits** | 7, **8** | The number of data bits in each frame.                        |
| **Parity** | **None**, Even, Odd              | The method for error checking.                                |
| **Stop Bits** | **1**, 2                         | The number of bits indicating the end of a frame.             |

The most common configuration is **115200 8N1** (115200 baud, 8 data bits, No parity, 1 stop bit).

## Physical Layer & Voltage Levels

### TTL / CMOS Logic
This is the standard level used between microcontrollers or between an MCU and a USB-to-TTL converter.
* **Logic '1' (High):** +3.3V or +5V
* **Logic '0' (Low):** 0V (GND)

### RS-232 Standard
An older standard used in legacy PC serial ports and industrial equipment.
* **Logic '1' (High):** -3V to -15V
* **Logic '0' (Low):** +3V to +15V

> **WARNING:** RS-232 uses both **inverted logic** and a much **higher voltage range** than TTL. Never connect a microcontroller directly to an RS-232 port. You must use a voltage level shifter IC, such as a **MAX232**, to convert the levels, or you will permanently damage the microcontroller.

## Common Problems & Troubleshooting

1.  **Problem: Receiving garbled, meaningless characters (`Junk Data`).**
    * **99% Cause:** **Baud Rate Mismatch.** Ensure the sender and receiver are set to the exact same baud rate.
    * **Other Causes:** Missing common GND connection, mismatched Stop Bit or Data Bit settings.

2.  **Problem: Not receiving any data.**
    * **Cause:** TX and RX pins may be connected incorrectly. Check that they are crossed (`TX -> RX`, `RX -> TX`).
    * **Other Causes:** Missing common GND connection.

3.  **Problem: Data loss is occurring.**
    * **Cause:** The receiver cannot process the incoming data fast enough, and its buffer is overflowing (Overrun Error).
    * **Solution:** Use an interrupt or DMA-based reading method in your code, or lower the baud rate.

## Code Examples

You can find practical code examples for this protocol in the following directory:

➡️ [`Code_Examples/`](./Code_Examples/)
