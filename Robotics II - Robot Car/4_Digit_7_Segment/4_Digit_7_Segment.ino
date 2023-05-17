/*
Code used in the 4 digit 7 segment in the robot car.
*/

// Pin assignments for 7-segment display
const int latchPin = 10;
const int clockPin = 11;
const int dataPin = 12;

// Binary representations of numbers from 0 to 9
int numbers[] = {
  B01111110,  // 0
  B00010000,  // 1
  B00000000,  // 2
  B00000000,  // 3
  B00010001,  // 4
  B00000000,  // 5
  B00000000,  // 6
  B00110000,  // 7
  B00111111,  // 8
  B00110001   // 9
};


/*
B00000000 are not able to be used

In my particular broken 4 digit 7 segment:

Bit 3 turns on bit 2
Bit 4 turns on bit 3
Bit 5 turns on bit 4
Bit 6 turns on bit 5
Bit 7 turns on bit 6
Bit 8 turns on bit 7

I haven't tested it, but I presume bit 1 turns on bit 8 and bit 2 turns on bit 1.
*/

void setup() {
  // Set pin modes for control pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // Set pin modes for segment control pins
  for (int i = 2; i <= 5; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Display digit 0
  digitalWrite(2, HIGH);  // Activate segment A
  digitalWrite(3, HIGH);  // Activate segment B
  digitalWrite(4, HIGH);  // Activate segment C
  digitalWrite(5, LOW);   // Deactivate segment D

  // Send data for digit 0 to the 7-segment display
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, numbers[0]);  // Display number 0
  digitalWrite(latchPin, HIGH);

  delay(5);  // Delay for a short period

  // Display digit 0 rotated 90 degrees
  digitalWrite(2, HIGH);  // Activate segment A
  digitalWrite(3, HIGH);  // Activate segment B
  digitalWrite(4, LOW);   // Deactivate segment C
  digitalWrite(5, HIGH);  // Activate segment D

  // Send data for digit 0 to the 7-segment display
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, numbers[0]);  // Display number 0
  digitalWrite(latchPin, HIGH);

  delay(5);  // Delay for a short period

  // Display digit 4
  digitalWrite(2, HIGH);  // Activate segment A
  digitalWrite(3, LOW);   // Deactivate segment B
  digitalWrite(4, HIGH);  // Activate segment C
  digitalWrite(5, HIGH);  // Activate segment D

  // Send data for digit 4 to the 7-segment display
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, numbers[4]);  // Display number 4
  digitalWrite(latchPin, HIGH);

  delay(5);  // Delay for a short period

  // Display digit 1
  digitalWrite(2, LOW);   // Deactivate segment A
  digitalWrite(3, HIGH);  // Activate segment B
  digitalWrite(4, HIGH);  // Activate segment C
  digitalWrite(5, HIGH);  // Activate segment D

  // Send data for digit 1 to the 7-segment display
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, numbers[1]);  // Display number 1
  digitalWrite(latchPin, HIGH);

  delay(5);  // Delay for a short period
}