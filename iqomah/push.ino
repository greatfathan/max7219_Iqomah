#define PIN_PUSH 7

void pushSetup() {
  pinMode(PIN_PUSH, INPUT);
}

int getPush() {
  return digitalRead(PIN_PUSH);
}

