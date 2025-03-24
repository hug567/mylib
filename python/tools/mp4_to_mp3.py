#!/usr/bin/python3
# 从mp4文件中提取音频并存为mp3文件
# 需安装：pip install moviepy
# 2025-01-21

import os
import sys
import argparse
from moviepy import VideoFileClip

def mp4_to_mp3(fname):
    print(f'mp4 file: {fname}')
    mp3_prefix = os.path.basename(fname).split('.')[0]
    mp3_fname = mp3_prefix + '.mp3'

    video = VideoFileClip(fname)
    audio = video.audio
    print(f'will save to mp3 file: {mp3_fname}')
    audio.write_audiofile(mp3_fname)

def main():
    parser = argparse.ArgumentParser(description='mp4 to mp3')
    parser.add_argument('-f', '--file', type=str, help='mp4 file')

    args = parser.parse_args()
    if not args.file or not os.path.isfile(args.file):
        print('there is no file:', args.file)
        return

    mp4_to_mp3(args.file)

if __name__ == '__main__':
    main()
