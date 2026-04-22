#include <PS4Controller.h>
int  IN1 = 18;
int IN2 = 19;
int IN3 = 21;
int IN4 = 23;

bool R1 = 0;
bool L1 = 0;
bool R2 = 0;
bool L2 = 0;


void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(115200);
  PS4.begin();
  Serial.println("Ready, waiting for controller to connect...");
  while (!PS4.isConnected())
    ;
  Serial.println("Controller connected successfully!");
}

void loop() {

  R1 = (PS4.RStickY() > 0) ? HIGH : LOW;
  L1 = (PS4.LStickY() > 0) ? HIGH : LOW;
  R2 = PS4.RStickY() != 0 ? !R1 : R1;
  L2 = PS4.LSticky() != 0  ? !L1 : L1;
  while(PS4.LStickY() == 0 && PS4.RStickY() == 0);
  digitalWrite(IN1, R1);
  digitalWrite(IN2, R2);
  digitalWrite(IN3, L1);
  digitalWrite(IN4, L2);

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


