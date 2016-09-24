#include <CurieBLE.h>
#include <Servo.h>

//declare bluetooth
BLEPeripheral player1;  //first peripheral
BLEService go("19B10000-E8F2-537E-4F6C-D104768A1214"); //GOGOGOGOGOGOGO
BLECharCharacteristic HotelIndia("19B10000-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify);
BLECentral *bleCentral1 = NULL; // peer central device

//declare pin connections
const int ledPin = 13; // pin to use for the LED

//declare the servos and related variables
Servo light_flicker;
int val;
int pos = 50;
bool bluetooth = true;

void setup() {
  light_flicker.attach(9);
  bluetooth = true;
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  Serial.begin(9600);
  light_flicker.write(20);
  //configure pins
  pinMode(ledPin, OUTPUT);

  //configure bluetooth connection
  player1.setLocalName("LED");
  player1.setAdvertisedServiceUuid(go.uuid());

  //add services and characteristics
  player1.addAttribute(go);
  player1.addAttribute(HotelIndia);

  //assign event handlers for characteristics
  HotelIndia.setEventHandler(BLEWritten, buttonPressed);
  //initial characteristic values
  HotelIndia.setValue(0);  //no go

  //assign event handlers for connected, disconnected to peripheral
  player1.setEventHandler(BLEConnected, ConnectHandler);
  player1.setEventHandler(BLEDisconnected, DisconnectHandler);

  //begin advertising connection
  player1.begin();
  Serial.println(("Bluetooth device active, waiting for connections..."));
}

void loop() {
  player1.poll();
}

void buttonPressed(BLECentral & central, BLECharacteristic & characteristic) {
  if (*characteristic.value() == 0) {
    digitalWrite(ledPin, LOW); //...
  } else {
    digitalWrite(ledPin, HIGH); //GOGOGOGOGOGOGOGOGOGOGOGOGOGOGOGOGOGOGO
    doTheThing();
  }
}

void ConnectHandler(BLECentral & central) {
  // central connected event handler
  bleCentral1 = &central;
  Serial.print("Connected event, central: ");
  Serial.println(bleCentral1->address());
}

void DisconnectHandler(BLECentral & central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

int inc = 2;
int count = 0;

void doTheThing() {
  Serial.println("trying to do the thing");
  while (bluetooth) {
    // put your main  code here, to run repeatedly:
    if ((pos == 40) || (pos == 130)) {
      inc = inc * -1;
    }
    pos += inc;
    //Serial.println(pos);
    light_flicker.write(pos);
    delay(30);                       // waits 15ms for the servo to reach the position
    val = analogRead(0);
    if (val > 300) {
      count++;
      Serial.println(count);
    }
    digitalWrite(3, LOW);
    if (count > 10) {
      digitalWrite(2, HIGH);
    }
    if (count > 30) {
      digitalWrite(3, HIGH);
    }
    if (digitalRead(4) == HIGH) {
      bluetooth = false;
    }
  }
}

