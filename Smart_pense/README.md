## 프로젝트 소개
우분투 20.04 버전 Jetson Xavier 환경에서 Yolov4와 OpenCV를 사용하여 특정 객체(자동차, 사람)를 실시간 탐지하는 프로젝트입니다.

## 개발기간
2023.06 ~ 2023.09

## 개발인원
- 팀장 양윤모 HW/SW 총괄 
- 팀원 정필준 하드웨어 구현 
- 팀원 방제우(본인) AI 인식 및 마이크로프로세서 기반 프로그래밍 개발 (이 저장소에 포함된 코드)
- 팀원 맹규호 마이크로프로세서 기반 프로그래밍 구현
- 팀원 김윤진 하드웨어 중점 케드 설계 및 기술조사
- 팀원 원승우 AI 인식 및 마이크로프로세서 기반 프로그래밍 개발
  
## 프로젝트 개요
이 프로젝트는 Yolov4와 Opencv, CUDA 가속을 활용하여 실시간 인식을 구현합니다.
Hardware와 연결된 웹캠을 통해 영상을 입력받고, 감시된 객체를 화면에 표시합니다. 

그중 사용자가 지정한 특정 구간(y_label)을 통과하는 객체를 감지합니다.
객체를 탐지시 팬스에 연결된 차단기 및 스피커에 신호가 전달되어 출력합니다.

본문 에는 팀 프로젝트 중 제가 담당했던 객체 인식 기능만 포함되어 있습니다.

🔹 프로젝트 구조
  - main.py : 프로젝트 메인 코드
  - config : YOLOv4.cfg 파일 및 coco.names
  - README.md : 프로젝트 설명 파일


## 개발환경 및 기술스택
- Programming : Python, Opnecv
- Framework : Yolov4
- Hardware : Jetson Xaiver
- OS : Ubuntu 20.04

## 프로젝트 실행 방법

1️⃣ Yolo 가중치 파일 다운로드

!wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v3_optimal/yolov4.weights

2️⃣ 필요한 패키지 설치

pip install -r requirements.txt

3️⃣ 실행

python main.py

📌 ESC 키를 누르면 종료합니다.
   
## 주요 기능
✅ YOLOv4를 활용한 객체 탐지


✅ OpenCV를 이용한 실시간 영상 처리


✅ 특정 구간을 통과하는 특정 객체 감지 기능


✅ CUDA 지원 기능

## 개선할 점 
🔹 CUDA 사용 오류 개선

🔹 해상도를 늘리면서 FPS를 늘리는 방법 추가

🔹Jetson Xavier외 라즈베리 파이에 적용할 수 있는 코드 구상 
