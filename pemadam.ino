#include <Servo.h>

#define LM1 2
#define LM2 3
#define RM1 4
#define RM2 5
#define SERVO_PIN 9
#define TRIG_PIN 12
#define ECHO_PIN 13

Servo servo;
int state = 0;

void setup(){
  Serial.begin(9600);

  // Servo
  servo.attach(SERVO_PIN);
  servo.write(0);
  
  // Motor
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
}

void stopMotor(){
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

void moveForward(){
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void moveBackward(){
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void moveRight(){
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

void turnRight(){
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void goLeft(){
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void turnLeft(){
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);

  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

int readDistance(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void travelling(){
  if(state % 2 == 0){
    moveForward();
    state += 1;

    // longer time to travel
    if(state == 8 || state == 10){
      delay(3000);
    }
    else {
      delay(2000);
    }
  }
  else if(state == 1){
    turnRight();
    state += 1;
    delay(500);
  }
  else if(state == 3){
    turnLeft();
    state += 1;
    delay(500);
  }
  else if(state == 5){
    turnRight();
    state += 1;
    delay(500);
  }
  else if(state == 7){
    turnRight();
    state += 1;
    delay(500);
  }
  else if(state == 9){
    turnRight();
    state += 1;
    delay(500);
  }
  else if(state == 11){
    turnRight();

    // back to initial state
    state = 0;
    delay(500);
  }
}

void loop(){
  int objDistance = readDistance();
  Serial.println(objDistance);

  if(objDistance <= 10){
    Serial.println("Fire!!!!");
    stopMotor();
    servo.write(270);
  }
  else {
    servo.write(0);
    travelling();
  }
}
