# 图片右下角添加文字
# 安装库：
#   pip install opencv-python pytz
# 2024-10-16

import os
import re
import cv2
import pytz
import argparse
import datetime

def guess_date_by_fname(fname):
    date = ''

    # eg: mmexport1723093243581.jpg
    #     wx_camera_1722823585742.jpg
    pattern = r'17[2-9]\d{10}'
    mth = re.search(pattern, fname)
    if mth:
        timestamp = mth.group(0)
        utc_time = datetime.datetime.fromtimestamp(int(timestamp[:10]), datetime.UTC)
        cst_tz = pytz.timezone('Asia/Shanghai')
        cst_time = utc_time.replace(tzinfo=pytz.utc).astimezone(cst_tz)
        date = cst_time.strftime('%Y-%m-%d')

    # eg: IMG_20240712_123129.jpg
    pattern = r'IMG_(202[4-9][0-1]\d[0-3]\d)_'
    mth = re.search(pattern, fname)
    if mth:
        time_str = mth.group(1)
        date = time_str[0:4] + '-' + time_str[4:6] + '-' + time_str[6:8]

    return date

def color_str_to_list(color_str):
    color_list = (255, 255, 255)

    if color_str == 'white':
        color_list = (255, 255, 255)
    elif color_str == 'red':
        color_list = (35, 35, 243)
    elif color_str == 'blue':
        color_list = (243, 35, 35)
    else:
        color_list = (255, 255, 255)
    print(f'using color list: {color_list}')

    return color_list

def add_date_text_to_image(args):
    # 高、宽、字体大小、字体粗细、添加位置x坐标、添加位置y坐标
    supported_img = [
        [960,  544,  0.6, 1, 20, 940  ],
        [1080, 1920, 1.0, 2, 30, 1050 ],
        [1280, 720,  0.6, 1, 20, 1260 ],
        [1707, 1280, 0.8, 1, 30, 1677 ],
        [1702, 1276, 1.0, 1, 30, 1672 ],
        [1856, 4000, 2.0, 3, 50, 1806 ],
        [1920, 1080, 0.8, 1, 30, 1890 ],
        [4000, 1856, 1.5, 2, 50, 3950 ],
        [4608, 2144, 1.5, 2, 50, 4558 ],
    ]

    image = cv2.imread(args.file)
    if image is None:
        print('read image failed')
        return
    height, width, channels = image.shape
    print(f'image size: ({height} x {width})')

    text_size = 0
    text_thickness = 0
    text_x = 0
    text_y = 0
    for supported in supported_img:
        supported_height = supported[0]
        supported_width = supported[1]
        if supported_height == height and supported_width == width:
            text_size = supported[2]
            text_thickness = supported[3]
            text_x = supported[4]
            text_y = supported[5]
            break
    if text_size == 0:
        print('not supported image size:', height, 'x', width)
        return

    print('text_size:', text_size)
    print('text_thickness:', text_thickness)
    print(f'text_x/y: ({text_x}, {text_y})')

    # add date text to image
    cv2.putText(image, args.date, (text_x, text_y), cv2.FONT_HERSHEY_SIMPLEX,
                text_size, color_str_to_list(args.color), text_thickness,
                cv2.LINE_AA)
    # save image
    saved_fname = args.date + '.jpg'
    print(f'add text to image success, will save to file: {saved_fname}')
    cv2.imwrite(saved_fname, image)

def main():
    parser = argparse.ArgumentParser(description='Get student information')

    parser.add_argument('-f', '--file', type=str, help='image file name')
    parser.add_argument('-d', '--date', type=str, help='added date string')
    parser.add_argument('-c', '--color', type=str, default='white', help='added date text color')
    args = parser.parse_args()

    if not args.file or not os.path.exists(args.file):
        print('there is no file:', args.file)
        return

    if not args.date:
        args.date = guess_date_by_fname(args.file)
        if not args.date:
            print('guess image date by file name failed')
            return

    print('file:', args.file)
    print('date:', args.date)
    print('color:', args.color)
    add_date_text_to_image(args)

if __name__ == '__main__':
    main()
