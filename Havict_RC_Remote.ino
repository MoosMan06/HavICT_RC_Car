#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

int throttlePin = A2;
int steeringPin = A0;
int pushButton = A1;

int message[3]; //message = {Throttle, Direction, Steering}

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  pinMode(throttlePin, INPUT);
  pinMode(steeringPin, INPUT);
  pinMode(pushButton, INPUT);
}

void loop() {
  int throttle = analogRead(throttlePin);
  int steering = analogRead(steeringPin);
  int button = analogRead(pushButton);

  // Debug info
  Serial.print("Throttle:");
  Serial.print(throttle);
  Serial.print(",");
  Serial.print("Steering:");
  Serial.print(steering);
  Serial.print(",");
  Serial.print("Button:");
  Serial.println(button);

  // Generating message array from inputs:
  if (throttle < 490) {
    message[0] = map(throttle, 0, 495, 255, 0);
    message[1] = -1;
  }
  else if (throttle > 520) {
    message[0] = map(throttle, 520, 1024, 0, 256);
    message[1] = 1;
  }
  else {
    message[0] = 0;
    message[1] = 0;
  }

  message[2] = map(steering, 0, 1024, 50, 120);

  // More debug info:
  Serial.print(message[0]);
  Serial.print(" / ");
  Serial.print(message[1]);
  Serial.print(" / ");
  Serial.println(message[2]);

  // Transmitting:
  radio.write(&message, sizeof(message));
}
