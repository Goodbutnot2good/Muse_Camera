#include <CurieBLE.h>
BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
const int ledPin = 13; // pin to use for the LED
char command;
String string;  
boolean ledon = false;  

void setup() {
  Serial.begin(9600);
  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  // set advertised local name and service UUID:
  blePeripheral.setLocalName("LED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());
  // add service and characteristic:
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);
  // set the initial value for the characeristic:
  switchCharacteristic.setValue(0);
  // begin advertising BLE service:
  blePeripheral.begin();
  }

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
  }
  
  if (Serial.available() > 0) 
  {string = "";}
    
  while(Serial.available() > 0) {
    command = ((byte)Serial.read());

    if(command == ':') {
      break;
    }
    else {
      string += command;
    }
    delay(1);
  }
    
  if(string == "TO") {
      ledOn();
      ledon = true;
  }
    
  if(string =="TF") {
      ledOff();
      ledon = false;
      Serial.println(string);
  }
    
  if ((string.toInt()>=0)&&(string.toInt()<=255)) {
    if (ledon==true) {
      analogWrite(led, string.toInt());
      Serial.println(string);
      delay(10);
    }
  }
}

void ledOn() {
    analogWrite(led, 255);
    delay(10);
}
 
void ledOff() {
    analogWrite(led, 0);
    delay(10);
}