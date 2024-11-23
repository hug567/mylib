# 读取mp3文件标签信息
# ID3v1：mp3文件尾部128字节，存储标签信息
#   header[3]: 标签头，必须是'TAG'
#   title[30]: 标题
#   artist[30]: 作者
#   album[30]: 专辑
#   year[4]: 年份
#   comment[30]: 备注
#   genre[1]: 范例
# 2024-11-21

import os
import argparse

def read_tag_info(fname):
    f = open(fname, 'rb')
    if f is None:
        print(f'open mp3 file {fname} failed')
        return
    f.seek(-128, 2)

    # read header str, shoule be 'TAG'
    try:
        header = f.read(3).decode('utf-8')
    finally:
        print(f'read tag from {fname} failed')
        return
    print(f'header str: {header}')
    if header != 'TAG':
        print(f'there is no tag in mp3 file {fname}')
        return

    title = f.read(30).decode('gbk')
    print(f'title: {title}')
    artist = f.read(30).decode('gbk')
    print(f'artist: {artist}')
    album = f.read(30).decode('gbk')
    print(f'album: {album}')
    year = f.read(4).decode('gbk')
    print(f'year: {year}')
    comment = f.read(30).decode('gbk')
    print(f'comment: {comment}')
    genre = f.read(1)#.decode('utf-8')
    print(f'genre: {genre}')

def main():
    parser = argparse.ArgumentParser(description='Read mp3 tag info')

    parser.add_argument('-f', '--file', type=str, help='mp3 file name')
    args = parser.parse_args()

    if not args.file or not os.path.exists(args.file):
        print('there is no file:', args.file)
        return

    read_tag_info(args.file)

if __name__ == '__main__':
    main()
