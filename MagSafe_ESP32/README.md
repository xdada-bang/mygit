## 프로젝트 소개
휴대용 혈당계의 복잡한 매뉴얼, 나쁜 휴대성을 해결하기 위해 핸드폰 뒤에 붙이는 형식의 Maqsafe( iPhone 충전기, 자석을 이용해 뒤에 붙히기만 하면된다.) 혈당계를 생각했습니다.
자주 채혈을 한다는 불편함을 해결하기위해 AI 인식을 이용한 식단관리, 먹은 음식에 대한 데이터를 도출 한뒤 올라갈 혈당을 예상할수있습니다. 
이것을 사용함으로써 사용자는 자신의 혈당을 항상 알기위해 채혈을 하는것을 방지해 불편함을 해소시킬수 있습니다.

## 개발기간
2024.11 ~ 2024.11

## 개발인원
- 팀장 맹규호 HW/SW 총괄 및 AI 인식 담당 
- 팀원 김진수 하드웨어 구현
- 팀원 방제우(본인) Bluetooth 통신 구현, 코드 디버깅
- 팀원 이종화 하드웨어 구현
  
## 프로젝트 개요
맥세이프 기반 혈당계를 활용해 스마트폰과의 근거리 무선통신 기능을 구현하여 휴대성과 터치 인터페이스를 만들어 편의성 향상. 
음식 데이터 셋을 추출 하여 AI 화면 인식을 통해 혈당 예측합니다. 
그후 하루에 먹은 음식에 대한 예상 혈당치 출력하는 프로젝트입니다.

본문에는 ESP32 BLE 통신 기능만 포함하고 있습니다.

## 개발환경 및 기술스택
- Programming Language : C++
- Framework : Arduino(ESP32 Development)
- Hardware : ESP32(TTGO LoRa32 V1) ,SmartPhone(Android/iOS)
- IDE & Tools: PlatformIO(VSCode)
- 통신 기술 : ESP32 BLE(Blutooth Low Energy), 근거리 무선 통신 (BLE)으로 데이터 송수신

## 프로젝트 실행 방법

1️⃣ ESP32 보드를 PC 또는 노트북과 연결
2️⃣ VSCode 에서 PlatformIO로 프로젝트 열기 
-VSCode 에서 PlatformIO Upload 또는 터미널에서 실행
3️⃣ 코드 빌드 및 실행

   
## 주요 기능
✅ ESP32를 BLE 서버로 설정

✅ 스마트폰과 BLE 데이터 송수신
- 스마트폰에서 데이터 요청하면 응답 패킷 전송

✅ BLE 연결 상태 모니터링
- BLE 클라이언트가 연결되었을 때 상태 메시지 출력

## 추가시키고 싶은 점 
🔹 NFC 통신 구현

🔹 STM32 기반으로 개발

