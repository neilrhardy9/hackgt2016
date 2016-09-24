#include <CurieBLE.h>

//declare bluetooth
BLEPeripheral player1;  //first peripheral
BLEService go("19B10000-E8F2-537E-4F6C-D104768A1214"); //GOGOGOGOGOGOGO
BLECharCharacteristic HotelIndia("19B10000-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify);
BLECentral *bleCentral1 = NULL; // peer central device 

//declare pin connections
const int ledPin = 13; // pin to use for the LED

void setup() {
  Serial.begin(9600);
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
