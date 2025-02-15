#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEServer.h>

int scanTime = 5; // 스캔 시간 (초)
const int measuredPower = -59; // 신호 세기 (1미터 거리에서의 예상 RSSI 값)
const float environmentalFactor = 3.0; // 환경 감쇠 인자
String targetMACAddress = "xx:xx:xx:xx:xx:xx"; // 원하는 장치의 MAC 주소로 변경

// BLEClient 콜백 클래스 정의: 연결 및 연결 해제 이벤트 처리
class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
    Serial.println("Connected to the device."); // 장치에 연결되었을 때 출력
  }

  void onDisconnect(BLEClient* pclient) {
    Serial.println("Disconnected from the device."); // 장치에서 연결이 해제되었을 때 출력
  }
};

float calculateDistance(int rssi) {
  // RSSI를 통해 거리를 추정하는 함수
  return pow(10, ((measuredPower - rssi) / (10 * environmentalFactor)));
}

void scandevices() {
  Serial.println("Scanning for BLE devices...");

  BLEDevice::init("ESP32_Device"); // BLE 장치 초기화 및 이름 설정
  BLEScan* pBLEScan = BLEDevice::getScan(); // BLE 스캐너 객체 생성
  pBLEScan->setActiveScan(true); // 액티브 스캔 설정 (더 많은 광고 데이터를 수집)
  BLEScanResults foundDevices = pBLEScan->start(scanTime); // 스캔 시작 및 결과 저장

  bool deviceFound = false; // 대상 장치 발견 여부를 추적하기 위한 변수

  // 스캔된 모든 장치들을 확인
  for (int i = 0; i < foundDevices.getCount(); ++i) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i); // 스캔된 장치 가져오기
    String deviceAddress = device.getAddress().toString().c_str(); // 장치의 MAC 주소를 문자열로 가져오기
    int rssi = device.getRSSI();
    float distance = calculateDistance(rssi);

    // 10cm 이내의 장치만 출력
    if (distance <= 0.1) { // 10cm = 0.1m
      Serial.print("Device found: ");
      Serial.print(device.getName().c_str());
      Serial.print(" | MAC Address: ");
      Serial.print(deviceAddress);
      Serial.print(" | RSSI: ");
      Serial.print(rssi);
      Serial.print(" | Estimated Distance: ");
      Serial.print(distance);
      Serial.println(" meters");

      // MAC 주소 저장 및 연결 시도
      targetMACAddress = deviceAddress;
      deviceFound = true;

      // 장치가 발견되었으면 연결 시도
      BLEClient* pClient = BLEDevice::createClient(); // BLE 클라이언트 객체 생성
      Serial.println("Created client. Attempting to connect...");

      pClient->setClientCallbacks(new MyClientCallback()); // 연결 이벤트 처리를 위한 콜백 설정

      // BLEAddress 객체로 변환하여 연결 시도
      BLEAddress bleAddress(deviceAddress.c_str());
      pClient->connect(bleAddress); // BLEAddress를 사용하여 장치에 연결 시도

      // 연결 성공 여부 확인
      if (pClient->isConnected()) {
        Serial.println("Successfully connected to the target device!"); // 연결 성공 시 메시지 출력
      } else {
        Serial.println("Failed to connect to the target device."); // 연결 실패 시 메시지 출력
      }

      break; // 장치에 연결 시도를 했으므로 루프 종료
    }
  }

  // 목표 장치를 찾지 못한 경우 메시지 출력
  if (!deviceFound) {
    Serial.println("Target device not found.");
  }

  Serial.println("Scan complete!"); // 스캔 완료 메시지 출력
}

void setup() {
  Serial.begin(115200); // 시리얼 통신 초기화 (115200 baud rate)
  delay(1000); // 안정적인 시리얼 통신을 위해 약간의 지연 추가

  scandevices(); // 장치 스캔 및 연결 시도
}