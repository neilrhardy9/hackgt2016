void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(12, OUTPUT);
  digitalWrite(2,LOW);
  digitalWrite(12, LOW);
}
int servoVal;
int micVal;
void loop() {
  while(digitalRead(2) == LOW);
  servoVal = analogRead(5);
  micVal = analogRead(0);
  if (micVal == 0) micVal++;
  if (servoVal > micVal) {
    analogWrite(2, round(servoVal/micVal));
  } else {
    analogWrite(2, round(micVal/servoVal));
  }
  analogWrite(3, servoVal);
  digitalWrite(12, HIGH);
  while(1);
}

