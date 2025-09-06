#include <Arduino.h>
#include <BLEDevice.h>

/* 
code will scan for decvice nearby 
if ball is detected then we will print it in serial 
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       //Starts serial monitor
  BLEDevice::init("");        //Initializes BLE --- not scanner does not need name
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);        //Active scan function is to get details such as device name

  //will scan for 2 seconds
  BLEScanResults results = pBLEScan->start(2);

  //we want to loop through all devices foudn
  for(int i = 0; i < results.getCount(); i++){
    BLEAdvertisedDevice device = results.getDevice(i);

    //get device name and strength from signal
    String name = device.getName().c_str();
    int rssi = device.getRSSI();        //radio signal strength valued in dBm or decibels relative to 1 milliwatt

    //Check if it is desired device
    if(name.startsWith("Dragon_Ball")){
      Serial.print("Found: ");
      Serial.print(name);       //will print name of device
      Serial.print(" | Strength of Signal (RSSI) is ");
      Serial.print(rssi);       //will print signal strength --- note!!!! higher value (-40 or closer) indicates close --> Lower (-80) indicates farther
    }
  }

  //wait 1 seconds before scanning again
  delay(1000);
}
