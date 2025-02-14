import numpy as np
import cv2

config_path = 'config/yolov4.cfg' 
weights_path = 'config/yolov4.weights'
names_path = 'config/coco.names'
#원하는 모델로 바꿔서 사용

with open(names_path, "r") as f:
    classes = [line.strip() for line in f.readlines()]

net = cv2.dnn.readNet(weights_path, config_path)
net.setPreferableBackend(cv2.dnn.DNN_BACKEND_CUDA)
net.setPreferableTarget(cv2.dnn.DNN_TARGET_CUDA)

#CUDA 사용시 해상도 높힐수있음
frame_width, frame_height = 640, 480
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, frame_width)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, frame_height)

line_y = int(frame_height * 0.5)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break
    
cv2.line(frame, (0, line_y), (frame_width, line_y), (255, 255, 255), 2)
layer_names = net.getLayerNames()
output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers()]
detections = net.forward(output_layers)

boxes = []
confidences = []
class_ids = []

for output in detections:
    for detection in output:
        scores = detection[5:]
        class_id = np.argmax(scores)
        confidence = scores[class_id]
        if confidence > 0.5:
            center_x = int(detection[0] * frame_width)
            center_y = int(detection[1] * frame_height)
            w = int(detection[2] * frame_width)
            h = int(detection[3] * frame_height)
            x = int(center_x - w / 2)
            y = int(center_y - h / 2)
            boxes.append([x, y, w, h])
            confidences.append(float(confidence))
            class_ids.append(class_id)

    indices = cv2.dnn.NMSBoxes(boxes, confidences, 0.7, 0.5)

    for i in indices:
        i = i[0]
        box = boxes[i]
        x, y, w, h = box
        label = str(classes[class_ids[i]])
        confidence = confidences[i]
        color = (0, 0, 255)
        cv2.rectangle(frame, (x, y), (x + w, y + h), color, 2)
        cv2.putText(frame, f'{label} {confidence:.2f}', (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)
        object_center_y = y + h // 2

        if line_y - 5 <= object_center_y <= line_y + 5:
            print(f'True: {label} detected crossing the line')

        cv2.imshow('video', frame)
    
    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()