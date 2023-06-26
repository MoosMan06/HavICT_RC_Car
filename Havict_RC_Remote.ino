#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

int throttlePin = A2;
int steeringPin = A0;
int pushButton = A1;

const byte address[6] = "00001";

int preciseSteering = 1;

void setup() {
  // put your setup code here, to run once:
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

  // Debugging:
  Serial.print("Throttle:");
  Serial.print(throttle);
  Serial.print(",");
  Serial.print("Steering:");
  Serial.print(steering);
  Serial.print(",");
  Serial.print("Button:");
  Serial.println(button);

  int transmission[4];

  // generating transmission array from inputs:
  if (throttle < 495) {
    transmission[1] = map(throttle, 0, 495, 255, 0);
    transmission[2] = -1;
  }
  else if (throttle > 520) {
    transmission[1] = map(throttle, 520, 1024, 0, 256);
    transmission[2] = 1;
  }
  else {
    transmission[1] = 0;
    transmission[2] = 0;
  }

  if (button < 5) {
    preciseSteering = preciseSteering / -1;
    delay(200);
  }
  
  if (preciseSteering > 0) {
    // didn't have enough time to implement this :(
  }
  else if (preciseSteering < 0) {
    // didn't have enough time to implement this :(
  } 
  // transmitting:
//  Serial.print(transmission[1]);
//  Serial.print(" / ");
//  Serial.print(transmission[2]);
//  Serial.print(" / ");
//  Serial.println(transmission[3]);
//  radio.write(&transmission, sizeof(transmission));
}