#include <Servo.h>

Servo light_flicker;
int val;
int pos = 50;
bool bluetooth = true;
void setup() {
  // put your setup code here, to run once:
  light_flicker.attach(9);
  bluetooth = true;
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);
  //pinMode(4, INPUT);
  digitalWrite(2, LOW);
  digitalWrite(7,LOW);
  //digitalWrite(4, LOW);
  Serial.begin(9600);
  light_flicker.write(20);
}
int inc = 5;
int count = 0;
void loop() {
  while (digitalRead(2) == HIGH) {}
  // put your main  code here, to run repeatedly:
  delay(100);
  bool keepGoing = true;
  while (keepGoing) {
    Serial.println(digitalRead(2));
    if ((pos == 40) || (pos == 130)) {
      inc = inc * -1;
      if (millis() % 3 == 0) {
        keepGoing = false;
      }
    }
    pos += inc;
    light_flicker.write(pos);
    delay(50);                       // waits 15ms for the servo to reach the position
    val = analogRead(0);
    if (val > 300) {
      count++;
    }
  }
  count = count%1023;
  digitalWrite(7,HIGH);
  analogWrite(5, count);
}
