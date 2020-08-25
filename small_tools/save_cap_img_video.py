import cv2
import numpy as np
import time

clicked = False
def onMouse(event, x, y, flags, param):
    global clicked
    if event == cv2.EVENT_LBUTTONUP:
        clicked = True

# 点击窗口保存图像，依次命名为1 2 3 4
# esc退出，保存在当前目录
def saveImage(device_num = 1):
    global clicked, text
    imgNum = 0
    text = ""
    cap = cv2.VideoCapture(device_num)
    # cap.set(cv2.CAP_PROP_FRAME_WIDTH, 64)
    # cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 48)
    cv2.namedWindow('DataCollectWindow')
    cv2.setMouseCallback('DataCollectWindow', onMouse)

    ret, frame = cap.read()
    while ret and cv2.waitKey(1) != 27:
        ret, frame = cap.read()
        if clicked:
            clicked = False
            imgNum = imgNum + 1
            imgName = "img"+"%d.jpg" % imgNum
            print(str(imgName) + " saved!")
            cv2.imwrite(imgName, frame)
            text = str(imgName) + " saved!"

        cv2.putText(frame, text, (40, 50), cv2.FONT_HERSHEY_COMPLEX, 2.0, (0, 0, 255), 2)
        cv2.imshow('DataCollectWindow', frame)

        # frame = binaryMask(frame)
    cv2.destroyAllWindows('DataCollectWindow')
    cap.release()


# 按空格开始或者暂停录制
# esc退出，保存在当前目录，按当前时间命名
def saveVideo(device_num = 1):
    # video_name = 'output.avi'
    width, height = 1920, 1080   # 640, 480   1920, 1080
    fps = 24.0
    video_num = 0
    cap = cv2.VideoCapture(device_num)
    cap.set(3, width)
    cap.set(4, height)    

    video_name = time.strftime("%Y%m%d.%H%M%S.avi", time.localtime()) 
    fourcc = cv2.VideoWriter_fourcc(*'XVID') 
    out = cv2.VideoWriter(video_name, fourcc, fps, (width, height), True) # fps 帧大小 彩色 

    save = False
    showtxt = ''
    start = 0
    while(cap.isOpened()):
        ret, frame = cap.read()
        if ret==True:
            frame = cv2.flip(frame, 1) # 不翻转

            if save:
                out.write(frame)

            cv2.putText(frame, video_name, (30, 50), None, 1.0, (0, 255, 255), 2) 
            cv2.putText(frame, ' '*8 + showtxt, (30, 50), None, 2.0, (0, 255, 255), 2)            
            cv2.imshow('video', frame)

            key = cv2.waitKey(27)
            if key == 13: # enter - 13 
                save = True
                showtxt = '    save...'
            elif key == 32: # 空格 - 32
                save = not save
                if save:   
                    showtxt = '    save...'
                else:
                    showtxt = '    pause'
            elif key == 27: # esc - 27
                break
        else:
            break
    cap.release()
    out.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    saveImage()
    # saveVideo()
