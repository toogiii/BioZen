#include <Servo.h>

Servo myservo;

int val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myservo.attach(9);
  Serial.setTimeout(1);
  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    val = Serial.readString().toInt();
  }
  if (val != 0) {
    Serial.println(val);
  }
  myservo.write(180-val);
  delay(15);
}
