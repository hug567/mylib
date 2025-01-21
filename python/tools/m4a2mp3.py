#!/usr/bin/python3
# m4a转mp3脚本
# windows中需先下载ffmpeg，并加入系统环境变量PATH：
#     https://ffmpeg.org/download.html#build
# linux中需先安装ffmpeg:
#    sudo apt instll ffmpeg
# 需安装：pip install ffmpeg
#         pip install pydub
# 2025-01-21

import os
import sys
import argparse
from pydub import AudioSegment

def m4a2mp3(fname):
    print(f'm4a file: {fname}')
    mp3_prefix = os.path.basename(fname).split('.')[0]
    audio = AudioSegment.from_file(fname, format="m4a")
    mp3_fname = mp3_prefix + '.mp3'
    print(f'will save to mp3 file: {mp3_fname}')
    audio.export(mp3_fname, format='mp3')

def main():
    parser = argparse.ArgumentParser(description='m4a to mp3')
    parser.add_argument('-f', '--file', type=str, help='pdf file')

    args = parser.parse_args()
    if not args.file or not os.path.exists(args.file):
        print('there is no file:', args.file)
        return

    m4a2mp3(args.file)

if __name__ == '__main__':
    main()
