#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(5,8);

Servo steeringServo;

const int motorControlPin1 = 2;
const int motorControlPin2 = 4;
const int motorThrottlePin = 11;

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {
  
  if (radio.available()) {
    int message[3];

    radio.read(&message, sizeof(message));

    int throttle = message[0];
    int direction = message[1];
    int steering = message[2];

    // Debug info:
    Serial.print(throttle);
    Serial.print(" / ");
    Serial.print(direction);
    Serial.print(" / ");
    Serial.println(steering);
    
    if (direction < 0) {
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      analogWrite(motorThrottlePin, throttle);
    }
    else if (direction > 0) {
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      analogWrite(motorThrottlePin, throttle);
    }
    else {
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      analogWrite(motorThrottlePin, 0);
    }
  }
}
