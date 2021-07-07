#include <Servo.h>

int val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(28800);
  Serial.setTimeout(1);
  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    val = Serial.readString().toInt();
  }
  if (true) {
    Serial.println(1);
  }
  else if (true) {
    Serial.println(2);
  }
  else if (true) {
    Serial.println(3);
  }
  else if (true) {
    Serial.println(4);
  }
  else if (true {
    Serial.println(5);
  )
  }
  delay(15);
}
