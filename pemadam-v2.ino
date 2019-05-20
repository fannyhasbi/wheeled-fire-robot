#include <Servo.h>

// motor pin
#define EN_M 9
#define LM1 2
#define LM2 3
#define RM1 4
#define RM2 5
// flame sensor pin
#define LEFT_S A0
#define CENTER_S A1
#define RIGHT_S A2
// servo pin
#define SERVO_PIN 10
// emergency alarm
#define EMERGENCY 7

Servo servo;
int motorSpeed = 130;
int servoPosition = 0;
bool fire = false;
int state = 0;

void setup(){
  pinMode(EN_M, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(EMERGENCY, OUTPUT);

  servo.attach(SERVO_PIN);
  servo.write(0);
  analogWrite(EN_M, motorSpeed);
  Serial.begin(9600);
}

void stopMove(){
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

void turnLeft(){
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);

  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void moveLeft(){
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void turnRight(){
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void moveRight(){
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

void travelling(){
  int r = random(0, 3);

  switch(r){
    case 0: moveForward(); break;
    case 1: moveLeft(); break;
    case 2: moveRight(); break;
    default: moveForward(); break;
  }
}

void putoff(){
  stopMove();
  // turn off alarm
  digitalWrite(EMERGENCY, LOW);

  for(servoPosition = 0; servoPosition < 180; servoPosition += 2){
    servo.write(servoPosition);
    delay(10);
  }

  delay(2000);

  for(servoPosition = 180; servoPosition > 0; servoPosition -= 2){
    servo.write(servoPosition);
    delay(10);
  }

  fire = false;
}

void loop(){
  int leftS = analogRead(LEFT_S);
  int centerS = analogRead(CENTER_S);
  int rightS = analogRead(RIGHT_S);

  leftS = map(leftS, 0, 1023, 0, 3);
  centerS = map(centerS, 0, 1023, 0, 100);
  rightS = map(rightS, 0, 1023, 0, 3);

  Serial.println(leftS);
  Serial.println(centerS);
  Serial.println(rightS);
  Serial.println(servoPosition);
  Serial.println("\n\n");

  if(leftS == 0 && centerS <= 50 && rightS == 0){
    digitalWrite(EMERGENCY, LOW);
    travelling();
    fire = false;
  }
  else if(leftS > 0){
    digitalWrite(EMERGENCY, HIGH);
    turnLeft();
    fire = false;
  }
  else if(rightS > 0){
    digitalWrite(EMERGENCY, HIGH);
    turnRight();
    fire = false;
  }
  else if(centerS > 50){
    digitalWrite(EMERGENCY, HIGH);

    if(centerS > 85){
      stopMove();
      fire = true;
    }
    else {
      moveForward();
    }
  }

  while(fire){
    putoff();
  }

  delay(500);
}
