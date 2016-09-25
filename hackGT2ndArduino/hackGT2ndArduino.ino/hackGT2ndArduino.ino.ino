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
  if (micVal == 0) micVal++;
  analogWrite(2, (servoVal*micVal) % 1023);
  while(1);
}

