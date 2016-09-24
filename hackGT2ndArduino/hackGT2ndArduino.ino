void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  digitalWrite(2,LOW);
}
int servoVal;
int micVal;
void loop() {
  while(digitalRead(2) == LOW);
  servoVal = analogRead(5);
  micVal = analogRead(0);
  if (servoVal > micVal) {
    analogWrite(2, round(servoVal/micVal));
  } else {
    analogWrite(2, round(micVal/servoVal));
  }
  while(1);
}

