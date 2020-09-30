#!/usr/bin/python3
# -*- coding: utf-8 -*-
import time
import cv2
import numpy as np
 
# 0=内蔵カメラ
cap = cv2.VideoCapture(0)
 
#fps = int(cap.get(cv2.CAP_PROP_FPS))
#w = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
#h = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi', fourcc, 30, (1920, 1080))
time0 = time.time()   

while True:
    ret, frame = cap.read()
    #cv2.imshow('frame', frame)
    out.write(frame)
    if (time.time() - time0 >= 5):
    #if cv2.waitKey(1) & 0xFF  == ord('q'):
        break


cap.release()
out.release()
cv2.destroyAllWindows()

