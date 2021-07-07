  
#include <Servo.h>


int val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(1);
  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    val = Serial.readString().toInt();
  }
  if (val == 4) {
    Serial.println("Storm Mode");
  }
  else if (val == 3) {
    Serial.println("Rain Mode");
  }
  else if (val == 2) {
    Serial.println("Cloud/Fog Mode");
  }
  else if (val == 1) {
    Serial.println("Sun Mode");
  }
  delay(15);
}
