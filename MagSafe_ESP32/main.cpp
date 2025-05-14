#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEServer.h>

int scanTime = 5; 
const int measuredPower = -59; 
const float environmentalFactor = 3.0; 
String targetMACAddress = "xx:xx:xx:xx:xx:xx"; 


class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
    Serial.println("Connected to the device."); 
  }

  void onDisconnect(BLEClient* pclient) {
    Serial.println("Disconnected from the device."); 
  }
};

float calculateDistance(int rssi) {
  
  return pow(10, ((measuredPower - rssi) / (10 * environmentalFactor)));
}

void scandevices() {
  Serial.println("Scanning for BLE devices...");

  BLEDevice::init("ESP32_Device"); 
  BLEScan* pBLEScan = BLEDevice::getScan(); 
  pBLEScan->setActiveScan(true); 
  BLEScanResults foundDevices = pBLEScan->start(scanTime); 

  bool deviceFound = false; 

 
  for (int i = 0; i < foundDevices.getCount(); ++i) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i); 
    String deviceAddress = device.getAddress().toString().c_str(); 
    int rssi = device.getRSSI();
    float distance = calculateDistance(rssi);

 
    if (distance <= 0.1) { 
      Serial.print("Device found: ");
      Serial.print(device.getName().c_str());
      Serial.print(" | MAC Address: ");
      Serial.print(deviceAddress);
      Serial.print(" | RSSI: ");
      Serial.print(rssi);
      Serial.print(" | Estimated Distance: ");
      Serial.print(distance);
      Serial.println(" meters");

      targetMACAddress = deviceAddress;
      deviceFound = true;

      BLEClient* pClient = BLEDevice::createClient(); 
      Serial.println("Created client. Attempting to connect...");

      pClient->setClientCallbacks(new MyClientCallback()); 

      BLEAddress bleAddress(deviceAddress.c_str());
      pClient->connect(bleAddress); 

      
      if (pClient->isConnected()) {
        Serial.println("Successfully connected to the target device!"); 
      } else {
        Serial.println("Failed to connect to the target device."); 
      }

      break; 
    }
  }

 
  if (!deviceFound) {
    Serial.println("Target device not found.");
  }

  Serial.println("Scan complete!"); 
}

void setup() {
  Serial.begin(115200); 
  delay(1000); 

  scandevices();
}