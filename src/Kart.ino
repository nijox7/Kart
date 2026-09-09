#define B1 2
#define B2 3
#define B3 4

void setup() {
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  delay(16);
  int val1 = digitalRead(B1);
  int val2 = digitalRead(B2);
  int val3 = digitalRead(B3);

  if (val1 == 0) {
    Serial.print("R");
  }
  if (val2 == 0) {
    Serial.print("L");
  }
  if (val3 == 0) {
    Serial.print("A");
  }
  Serial.print("\n");
}
