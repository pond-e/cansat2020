#!/usr/bin/python3
# -*- coding: utf-8 -*-
import time
import cv2
import numpy as np
 
# 0=内蔵カメラ
cap = cv2.VideoCapture(0)

while(True):
    for num in range(25):
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            frame = cap.read()
            cv2.imwrite(str(num) + '.png',frame)
            print(str(num) + '枚目')

    break

cap.release()
cv2.destroyAllWindows()
