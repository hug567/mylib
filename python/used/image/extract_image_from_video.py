# 从视频中提取帧图片
# 安装包：pip install opencv-python
# 2024-10-17

import os
import cv2
import argparse

def extract_image_from_video(video, frames_per_s=5):
    if not os.path.exists(video):
        print('file does not exist:', video)
        return

    # 打开视频文件
    cap = cv2.VideoCapture(video)
    if not cap.isOpened():
        print("Error: Could not open video.")
        return
    # 帧率
    fps = cap.get(cv2.CAP_PROP_FPS)
    # 总帧数
    total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    # 没秒提取指定帧时的帧间隔，默认每秒提取5帧
    frame_interval = int(fps // frames_per_s)

    name, ext = os.path.splitext(os.path.basename(video))
    frame_count = 0
    saved_count = 0
    # 循环读取视频帧
    while True:
        ret, frame = cap.read()
        # 如果没有读取到帧，结束循环
        if not ret:
            break
        if frame_count % frame_interval == 0:
            # 保存当前帧
            fname = os.path.join(os.getcwd(), f'{name}_{saved_count:05d}.jpg')
            cv2.imwrite(fname, frame)
            print(f"extract frame: {fname}")
            saved_count += 1

        frame_count += 1

    # 释放视频对象
    cap.release()

def main():
    parser = argparse.ArgumentParser(description='Extract image from video')

    parser.add_argument('-v', '--video', type=str, help='files dir')
    args = parser.parse_args()

    if not args.video:
        print('does not specify video file')
        return
    print('video file:', args.video)
    extract_image_from_video(args.video)

if __name__ == '__main__':
    main()
