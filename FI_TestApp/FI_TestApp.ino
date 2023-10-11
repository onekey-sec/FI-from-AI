#pragma GCC push_options
#pragma GCC optimize ("O0")
#include <Arduino.h>
#include <Crypto.h>
#include <AES.h>


#define LED_BUILTIN 13
char* string1 = "55555555AAAAAAAA";
char* string2 = "5555555555555555";
int cnt;

// Key, plaintext, and ciphertext buffers
byte key[16];
byte plaintext[16];
byte ciphertext[16];
byte decryptedtext[16];

// Define loop unrolling factor
#define UNROLL_FACTOR 50

// Define macro for loop unrolling
#define UNROLL_ITER(j) \
  cnt++;              \
  cnt++;              \
  cnt++;              \
  cnt++;              \
  cnt++;              \

// Define macro for loop unrolling
#define UNROLL_LOOP_BODY \
  UNROLL_ITER(0)         \
  UNROLL_ITER(1)         \
  UNROLL_ITER(2)         \
  UNROLL_ITER(3)         \
  UNROLL_ITER(4)         \

// Creating an object of AES128 class
AES128 aes128;

// Function declarations
void runLoopFunction();
void runStringComparison();
void runThirdFunction();
void runStringComparisonComplex();
void runStringComparisonDoubleC();
void runStringComparisonRand();
void runStringComparisonState();
void memcpyPCctr();

// Function declarations
void randomfn();
void randomfn2();
void randomfn3();
void normalfn();

// for memcpy - for 32bit arm
void (*p[16])() = {&randomfn3, &randomfn, &normalfn, &randomfn2, &randomfn3, &randomfn, &normalfn, &randomfn2, &randomfn3, &randomfn, &normalfn, &randomfn2, &randomfn3, &randomfn, &normalfn, &randomfn2};
void (*q[16])();
void *memcpy1(void *dest, const void *src, size_t len);  // Function prototype



void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char trigger = Serial.read();
    switch (trigger) {
      case 0x41: // ASCII 'A'
        runLoopFunction();
        break;
      case 0x42: // ASCII 'B'
        runStringComparison();
        break;
      case 0x43: // ASCII 'C'
        runStringComparisonComplex();
        break;
      case 0x44: // ASCII 'D'
        runStringComparisonDoubleC();
        break;
      case 0x45: // ASCII 'E'
        runStringComparisonRand();
        break;
      case 0x46: // ASCII 'F'
        runStringComparisonState();
        break;
      case 0x47: // ASCII 'G'
        runLoopUnrolledFunction();
        break;
      case 0x48: // ASCII 'H'
        readBytesFromSerial(key, sizeof(key));
        break;
      case 0x49: // ASCII 'I'
        readBytesFromSerial(plaintext, sizeof(plaintext));
        break;
      case 0x4A: // ASCII 'J'
        readBytesFromSerial(ciphertext, sizeof(ciphertext));
        break;
      case 0x4B: // ASCII 'K'
        aesencrypt();
        break;
      case 0x4C: // ASCII 'L'
        aesdecrypt();
        break;
      case 0x4D: // ASCII 'M'
        memcpyPCctr();
        break;
        

      // Add more cases for additional functions if needed
    }
  }
}

// Function for loop addition
void runLoopFunction() {
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger

  float cnt = 0;
  for (float i = 0; i < 50; i++) {
    for (float j = 0; j < 50; j++) {
      cnt++;
    }
  }

  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  // Send results back
  //Serial.print("Loop Function Result: ");
  Serial.println(cnt);
}



// Function for string comparison
void runStringComparison() {
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger
  int cnt;
  // Compare strings
  if (strcmp(string1, string2) == 0) {
    cnt = 0x55;
  } else {
    cnt = 0xAA;
  }

  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  // Send results back
  if (cnt == 0x55) {
    Serial.println("PASS");
    cnt = 0xAA;
  } else {
    Serial.println("FAIL");
  }
}

// Function for the third operation
void runStringComparisonComplex() {
  int cnt;
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger
  delayMicroseconds(1);

  // Your third function logic
  if (strcmp(string1, string2) == 0) {
    cnt = 0x55;
  } else {
    cnt = 0xAA;
  }

  delayMicroseconds(1);
  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  // Send results back
  if (cnt == 0x55) {
    Serial.println("PASS");
    cnt = 0xAA;
  } else {
    Serial.println("FAIL");
  }
}

// Function for the fourth operation
void runStringComparisonDoubleC() {
  int cnt;
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger
  delayMicroseconds(1);

  // Your fourth function logic
  if (strcmp(string1, string2) == 0) {
    cnt = 0x55;
  } else {
    cnt = 0xAA;
  }
  // Your fourth function logic
  if (strcmp(string1, string2) == 0) {
    cnt = 0x55;
  } else {
    cnt = 0xAA;
  }
  delayMicroseconds(1);
  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  // Send results back
  if (cnt == 0x55) {
    Serial.println("PASS");
    cnt = 0xAA;
  } else {
    Serial.println("FAIL");
  }
}

// Function for the fifth operation
void runStringComparisonRand() {

  int cnt;
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger
  //delayMicroseconds(1);
  delayMicroseconds(random(1, 5));
  // Your fifth function logic
  if (strcmp(string1, string2) == 0) {
    cnt = 0x55;
  } else {
    cnt = 0xAA;
  }
  // Your fifth function logic
  if (strcmp(string1, string2) == 0) {
    cnt = 0x55;
  } else {
    cnt = 0xAA;
  }
  delayMicroseconds(random(1, 5));
  //delayMicroseconds(1);

  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  // Send results back
  if (cnt == 0x55) {
    Serial.println("PASS");
    cnt = 0xAA;
  } else {
    Serial.println("FAIL");
  }
}

// Function for the sixth operation
void runStringComparisonState() {
  int state = 0;
  int cnt=0xAA;
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger

  //delayMicroseconds(1);
  delayMicroseconds(random(1, 5));
  // Your sixth function logic
  if (strcmp(string1, string2) == 0) {
    cnt = 0x55;
    state=0xAB;
  } else {
    cnt = 0xAA;
    state=0xBA;
  }
  // Your sixth function logic
  if (strcmp(string1, string2) == 0) {
    cnt = 0x55;
    state=0xAB;
  } else {
    cnt = 0xAA;
    state=0xBA;
  }
  delayMicroseconds(random(1, 5));
  //delayMicroseconds(1);

  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  // Send results back
  if (cnt == 0x55) {
    Serial.println("PASS");
    cnt = 0xAA;
  } else {
    Serial.println("FAIL");
  }
}

// Function for the sixth operation
void memcpyPCctr() {

  digitalWrite(LED_BUILTIN, HIGH); // start of trigger
  for(int i=0;i<=5;i++)
  {
    memcpy1(q, p, sizeof(p));
  }
  digitalWrite(LED_BUILTIN, LOW); // end of trigger
  Serial.println("FAIL");
  
}


void *memcpy1(void *dest, const void *src, size_t len) {
  char *d = (char *)dest;
  const char *s = (char *)src;
  while (len--)
    *d++ = *s++;
  return dest;
}

void randomfn() {
  cnt = 12;
  Serial.print(cnt);
  Serial.println("PASS");
}

void randomfn2() {
  cnt = 23;
  Serial.print(cnt);
  Serial.println("PASS");
}

void randomfn3() {
  cnt = 34;
  Serial.print(cnt);
  Serial.println("PASS");
}

void normalfn() {
  cnt = 76;
  Serial.print(cnt);
  Serial.println("PASS");
}

// Function for loop unrolled addition
void runLoopUnrolledFunction() {
  float cnt = 0;
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger

  // Unrolled loop using macro
  for (float i = 0; i < 50; i += UNROLL_FACTOR) {
    // Repeat UNROLL_LOOP_BODY up to UNROLL_FACTOR times
    UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY
    UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY
    UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY
    UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY UNROLL_LOOP_BODY
    // ... Repeat up to UNROLL_FACTOR - 1
  }
  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  // Send results back
  //Serial.print("Loop Function Result: ");
  Serial.println(cnt);
}

// Function to read bytes from Serial input
void readBytesFromSerial(byte* buffer, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    while (!Serial.available()) {} // Wait for data
    buffer[i] = Serial.read();
  }
}

// Function to perform encryption
void aesencrypt() {
  aes128.setKey(key, 16); // Setting Key for AES
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger
  aes128.encryptBlock(ciphertext, plaintext);
  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  //Serial.print("Ciphertext:");
  for (int i = 0; i < sizeof(ciphertext); i++) {
    Serial.write(ciphertext[i]);
  }
  Serial.println();
}

// Function to perform decryption
void aesdecrypt() {
  aes128.setKey(key, 16); // Setting Key for AES
  digitalWrite(LED_BUILTIN, HIGH); // start of trigger
  aes128.decryptBlock(decryptedtext, ciphertext);
  digitalWrite(LED_BUILTIN, LOW); // end of trigger

  //Serial.print("Decryptedtext:");
  for (int i = 0; i < sizeof(decryptedtext); i++) {
    Serial.write(decryptedtext[i]);
  }
  Serial.println();
}
