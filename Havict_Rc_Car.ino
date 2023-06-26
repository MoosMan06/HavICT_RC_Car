#include <Servo.h>

Servo steeringServo;

void setup() {
  // put your setup code here, to run once:
  steeringServo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  steeringServo.write(85);
  delay(2000);
  steeringServo.write(50);
  delay(2000);
  steeringServo.write(120);
  delay(100000);
}
