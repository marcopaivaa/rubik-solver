import numpy as np
import cv2 as cv
import time as t

SQUARE_SIZE = 40
SPACE_SIZE = 80
DRAW_SIZE = (SQUARE_SIZE * 3) + (SPACE_SIZE * 4)
DRAW_STEP = SQUARE_SIZE + SPACE_SIZE
cap = cv.VideoCapture(0)
time = t.time()
img = np.array([])

while(True):
    ret, frame = cap.read()
    #hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    height, width = frame.shape[0], frame.shape[1]
    x,y = ((width - DRAW_SIZE)/2) + SPACE_SIZE,((height - DRAW_SIZE)/2) + SPACE_SIZE
    rect = []
    b,g,r = 0,0,0

    if(t.time() > time + 10):
        img = frame
        time = t.time()

    for i in range(0, 9):
        if(i % 3 != 0):
            x += DRAW_STEP
        else:
            x = (width - DRAW_SIZE)/2 + SPACE_SIZE
            if(i > 0):
                y += DRAW_STEP
        rect.append([int(x), int(y)])

    for point in rect:
        x,y = point[0],point[1]
        cv.rectangle(frame,(x,y),(x+SQUARE_SIZE,y+SQUARE_SIZE),(255,255,255),2)
        area = frame[y:y+SQUARE_SIZE, x:x+SQUARE_SIZE]
        b = area[:,:,0]
        g = area[:,:,1]
        r = area[:,:,2]
        b = np.mean(b)
        g = np.mean(g)
        r = np.mean(r)
        cv.rectangle(frame,(x,y),(x+SQUARE_SIZE,y+SQUARE_SIZE),(int(b),int(g),int(r)),cv.FILLED)
        cv.putText(frame,"TOTAL: "+str(frame.shape), (x,y-10), cv.FONT_HERSHEY_SIMPLEX, 0.3, 255)
        cv.putText(frame,"X: "+str(x)+" - Y: "+str(y), (x,y), cv.FONT_HERSHEY_SIMPLEX, 0.3, 255)
        cv.putText(frame,"B: "+str(b), (x,y+10), cv.FONT_HERSHEY_SIMPLEX, 0.3, 255)
        cv.putText(frame,"G: "+str(g), (x,y+20), cv.FONT_HERSHEY_SIMPLEX, 0.3, 255)
        cv.putText(frame,"R: "+str(r), (x,y+30), cv.FONT_HERSHEY_SIMPLEX, 0.3, 255)

    cv.imshow('rubik_capture',frame)
    if(img.any()):
        cv.imshow('img',img)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()