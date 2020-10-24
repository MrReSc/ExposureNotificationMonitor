#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define SCAN_TIME_SECONDS 5

BLEScan *scanner;
int counter = 0;
BLEUUID serviceUUID = (uint16_t) 0xfd6f; // Service UUID Exposure Notification Service

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  // Called when a BLE device is discovered.
  void onResult(BLEAdvertisedDevice advertisedDevice) override {
    // If the Service UUID is not 0xfd6f, it can be ignored
    if (!advertisedDevice.haveServiceUUID() || !advertisedDevice.getServiceUUID().equals(serviceUUID)) {
      return;
    }
    Serial.printf("MAC: %s | RSSI: %d \r\n", advertisedDevice.getAddress().toString().c_str(), advertisedDevice.getRSSI());
    counter ++;
  }
};

void setup() {
  Serial.begin(115200);
  
  // Initialize scanner.
  BLEDevice::init("ESP");
  scanner = BLEDevice::getScan();
  scanner->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  scanner->setActiveScan(true); // Active scan uses more power, but gets results faster.
  scanner->setInterval(100);
  scanner->setWindow(99);
}

void loop() {
  Serial.println("-----");
  
  // Scan.
  scanner->start(SCAN_TIME_SECONDS, false);
  Serial.println("Currently visible devices: " + String(counter));

  // Cleanup.
  scanner->clearResults();  // delete results fromBLEScan buffer to release memory
  counter = 0;
}