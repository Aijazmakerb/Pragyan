#include <NewPing.h>
#include <Servo.h>

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

NewPing sonar(TRIG_PIN, ECHO_PIN);
Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(en1, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(en2, OUTPUT);

  myservo.attach(8);
}

void loop() {
  int distance = sonar.ping_cm();
  delay(50);
  Serial.println(distance);

  if (distance > 20) {
    forward();

  } else {
    Serial.println("Avoid obstacle starting");
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
