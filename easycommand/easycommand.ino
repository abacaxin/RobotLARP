#include <ESP32Servo.h>

#include <PS4Controller.h>
int  IN3 = 18;
int IN4 = 19;
int IN1 = 23;
int IN2 = 21;

bool R1 = 0;
bool L1 = 0;
bool R2 = 0;
bool L2 = 0;

int pos = 0;
int target = 0;
unsigned long lastMove = 0;
int interval = 300;


int pinServo = 22;

Servo servo;
void setup() {
  PS4.begin("ec:e3:34:48:7b:1c");
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
  servo.write(180);
  delay(300);
  servo.write(0);
  delay(300);
}

void loop() {
  
  if(!PS4.isConnected()){}
  else{
    if(PS4.R1() || PS4.R2()){
      lastMove = millis();
      while(millis() - lastMove < interval){
        servo.write(90);
        R1 = (PS4.RStickY() > 0) ? HIGH : LOW;
        L1 = (PS4.LStickY() > 0) ? HIGH : LOW;
        R2 = PS4.RStickY() != 0 ? !R1 : R1;
        L2 = PS4.LStickY() != 0  ? !L1 : L1;

        digitalWrite(IN1, L1);
        digitalWrite(IN2, L2);
        digitalWrite(IN3, R1);
        digitalWrite(IN4, R2);
      }
      lastMove = millis();
      while(millis() - lastMove < interval){
        servo.write(5);
        R1 = (PS4.RStickY() > 0) ? HIGH : LOW;
        L1 = (PS4.LStickY() > 0) ? HIGH : LOW;
        R2 = PS4.RStickY() != 0 ? !R1 : R1;
        L2 = PS4.LStickY() != 0  ? !L1 : L1;

        digitalWrite(IN1, L1);
        digitalWrite(IN2, L2);
        digitalWrite(IN3, R1);
        digitalWrite(IN4, R2);
      }
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
    for (; pos <= target; pos + 10) {
      servo.write(pos);
    }
  } else {
    for (; pos >= target; pos - 10) {
      servo.write(pos);
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

      delay(10);
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

      delay(10);
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
