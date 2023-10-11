#  Fault Injection Test Application

## Overview

This Arduino sketch is designed as a Fault Injection Test Application, allowing users to simulate various fault scenarios and assess the robustness of the system. The sketch encompasses functions triggered by specific commands sent through the Serial Monitor, each representing a distinct fault injection scenario.

## Usage/Test

1. **Upload Sketch**: Load the sketch onto your Target/Arduino board.
2. **Open Serial Monitor**: Use the Serial Monitor to communicate with the Arduino.
3. **Send Commands**: Employ ASCII commands (A, B, ..., M) to get default response for specific fault and mitigation scenarios.
4. **Observe System Response**: Monitor the behavior of the system under a real fault conditions.

## Fault Injection Scenarios

### 1. Loop Function (`runLoopFunction`)

Injects faults into a nested loop to evaluate how the system handles disruptions in basic loop functionality.

### 2. String Comparison (`runStringComparison`)

Simulates faults during string comparison operations, allowing assessment of the system's response to unexpected behavior.

### 3. String Comparison Complex (`runStringComparisonComplex`)

Introduces faults in a more intricate string comparison scenario, providing insights into the system's resilience under complex conditions.

### 4. String Comparison Double C (`runStringComparisonDoubleC`)

Repeats the string comparison operation with injected faults, evaluating the system's behavior in the presence of duplicated faults.

### 5. String Comparison Rand (`runStringComparisonRand`)

Simulates random faults during string comparison, adding variability to fault injection scenarios.

### 6. String Comparison State (`runStringComparisonState`)

Injects faults into string comparison with state management, assessing the system's response to faults in more complex scenarios.

### 7. Memcpy PC Ctr (`memcpyPCctr`)

Simulates faults in memory copying operations, allowing users to evaluate the system's robustness in handling faults during data transfer.

### 8. AES Encryption and Decryption (`aesencrypt` and `aesdecrypt`)

Injects faults during AES encryption and decryption processes, evaluating the system's behavior under fault conditions in cryptographic operations.

### 9. Loop Unrolled Function (`runLoopUnrolledFunction`)

Tests the system's resilience to faults in loop unrolling, assessing its ability to recover from disruptions in optimized loop structures.

## Fault Injection Commands

- A: Loop Function Fault
- B: String Comparison Fault
- C: Complex String Comparison Fault
- D: Double String Comparison Fault
- E: Random String Comparison Fault
- F: String Comparison with State Fault
- G: Loop Unrolled Function Fault
- H: Set AES Key Input
- I: Set Plaintext Input
- J: Set Ciphertext Input
- K: Inject Fault in AES Encryption
- L: Inject Fault in AES Decryption
- M: Inject Fault in Memory Copy

## Additional Notes

- `delayMicroseconds` is used to simulate delays associated with fault conditions.
- The built-in LED on pin 13 indicates the start and end of functions.
- System responses to fault injections are communicated through the serial port based on the micrcontroller.

This sketch serves as a powerful tool for fault injection testing, allowing users to assess the resilience and fault-tolerance of their systems in various scenarios.
