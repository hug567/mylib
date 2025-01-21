#!/usr/bin/python3
# pdf转png脚本
# 需安装：pip install fitz
#         pip install PyMuPDF
# 2025-01-20

import os
import sys
import fitz
import argparse

def pdf2image(fname, zoom):
    image_prefix = os.path.basename(fname).split('.')[0]
    print(f'image_prefix: {image_prefix}')
    pdf = fitz.open(fname)
    for i in range(0, pdf.page_count):
        page = pdf[i]
        # 设置x/y方向缩放系数，和旋转角度
        trans = fitz.Matrix(zoom, zoom).prerotate(0)
        pm = page.get_pixmap(matrix=trans, alpha=False)
        image_name = image_prefix + '_' + str(i) + '.png'
        print(f'will save pdf page[{i}] with zoom factor {zoom} to image: {image_name}')
        pm.save(image_name)
    pdf.close()

def main():
    parser = argparse.ArgumentParser(description='Pdf to image png')
    parser.add_argument('-f', '--file', type=str, help='pdf file')
    parser.add_argument('-z', '--zoom', type=float, default=2.0, help='zoom factor')

    args = parser.parse_args()
    if not args.file or not os.path.exists(args.file):
        print('there is no file:', args.file)
        return

    pdf2image(args.file, args.zoom)

if __name__ == '__main__':
    main()
