#include <NewPing.h>
//W for hand tracking
//w for remote control
#define TRIG_PIN 12
#define ECHO_PIN 11

const int en1 = 9;
const int pin1 = 4;
const int pin2 = 5;
const int pin3 = 7;
const int pin4 = 6;
const int en2 = 10;

const int speed = 130;
const int turnSpeed = 150;

const int ir1 = 2;
const int ir2 = 3;

char command;

int mode = 1;

NewPing sonar(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);

  pinMode(en1, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(en2, OUTPUT);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
}

void loop() {

  if (Serial.available()) {
    command = Serial.read();
    Serial.println(command);
  }

  if (command == 'W') {
    mode = 1;
  } else if (command == 'w') {
    mode = 2;
  }

  int distance = sonar.ping_cm();

  int irLeft = digitalRead(ir1);
  int irRight = digitalRead(ir2);

  if (mode == 1) {
    if (command == 'F') {
      forward();
    } else if (command == 'L') {
      left();
    } else if (command == 'R') {
      right();
    } else if (command == 'B') {
      backward();
    } else{
      stop();
    }
  } else if (mode == 2) {
    if (distance >= 1 && distance <= 20) {
      forward();
    } else if (irLeft == LOW && irRight == HIGH) {
      left();
    } else if (irLeft == HIGH && irRight == LOW) {
      right();
    } else {
      stop();
    }
  }
}

void forward() {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin4, LOW);
  analogWrite(en1, speed);
  analogWrite(en2, speed);
}

void backward() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin4, HIGH);
  analogWrite(en1, speed);
  analogWrite(en2, speed);
}

void right() {
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  analogWrite(en1, turnSpeed);
  analogWrite(en2, turnSpeed);
}

void left() {
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
  analogWrite(en1, turnSpeed);
  analogWrite(en2, turnSpeed);
}

void stop() {
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
