#include <ESP32Servo.h>

#include <PS4Controller.h>
int  IN1 = 18;
int IN2 = 19;
int IN3 = 21;
int IN4 = 23;

bool R1 = 0;
bool L1 = 0;
bool R2 = 0;
bool L2 = 0;

int pos = 0;
int target = 0;
unsigned long lastMove = 0;
int interval = 10; // speed of servo


int pinServo = 22;

Servo servo;
void setup() {
  PS4.begin("EC:E3:34:49:04:0C");
  servo.setPeriodHertz(50);  // standard servo frequency
  servo.attach(pinServo, 500, 2400);  // min/max pulse width (µs)
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(115200);
  PS4.begin();
  Serial.println("Ready, waiting for controller to connect...");
  while (!PS4.isConnected());
  Serial.println("Controller connected successfully!");
  moveTo(180);
  moveTo(0);
}

void loop() {
  if(!PS4.isConnected()){}
  else{
    if(PS4.R1() || PS4.R2()){
      shoot(90);
      shoot(0);
    }
    R1 = (PS4.RStickY() > 0) ? HIGH : LOW;
    L1 = (PS4.LStickY() > 0) ? HIGH : LOW;
    R2 = PS4.RStickY() != 0 ? !R1 : R1;
    L2 = PS4.LStickY() != 0  ? !L1 : L1;

    digitalWrite(IN1, L1);
    digitalWrite(IN2, L2);
    digitalWrite(IN3, R1);
    digitalWrite(IN4, R2);
  }

  //Serial.print(PS4.LStickX());
  //Serial.println(PS4.LStickY());
  /*while (PS4.LStickY() > 0) {
    Serial.println("Front");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  while (PS4.LStickY() < 0) {
    Serial.println("Back");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  */
}

void moveTo(int target) {
  if (pos < target) {
    for (; pos <= target; pos++) {
      servo.write(pos);
      delay(10);
    }
  } else {
    for (; pos >= target; pos--) {
      servo.write(pos);
      delay(10);
    }
  }
}
void shoot(int target){
  if (pos < target) {
    for (; pos <= target; pos++) {
      servo.write(pos);
      
      R1 = (PS4.RStickY() > 0) ? HIGH : LOW;
      L1 = (PS4.LStickY() > 0) ? HIGH : LOW;
      R2 = PS4.RStickY() != 0 ? !R1 : R1;
      L2 = PS4.LStickY() != 0  ? !L1 : L1;

      digitalWrite(IN1, L1);
      digitalWrite(IN2, L2);
      digitalWrite(IN3, R1);
      digitalWrite(IN4, R2);

      delay(5);
    }
  } else {
    for (; pos >= target; pos--) {
      servo.write(pos);
      
      R1 = (PS4.RStickY() > 0) ? HIGH : LOW;
      L1 = (PS4.LStickY() > 0) ? HIGH : LOW;
      R2 = PS4.RStickY() != 0 ? !R1 : R1;
      L2 = PS4.LStickY() != 0  ? !L1 : L1;

      digitalWrite(IN1, L1);
      digitalWrite(IN2, L2);
      digitalWrite(IN3, R1);
      digitalWrite(IN4, R2);

      delay(5);
    }
  }
}
void updateServo() {
  if (millis() - lastMove >= interval) {
    lastMove = millis();

    if (pos < target) {
      pos++;
      servo.write(pos);
    } else if (pos > target) {
      pos--;
      servo.write(pos);
    }
  }
}
