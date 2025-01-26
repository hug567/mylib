#!/usr/bin/python3
# pdf转png脚本
# 需安装：pip install fitz
#         pip install PyMuPDF
# 2025-01-20

import os
import sys
import fitz
import argparse

def one_pdf_to_image(fname, zoom):
    image_prefix = os.path.basename(fname).split('.')[0]
    print(f'will transmit all pdf pages to png file: {fname} -----------------')
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

def pdfs_to_images(dpath, zoom):
    #one_pdf_to_image(fname, zoom)
    list = os.listdir(dpath)
    for i in range(0, len(list)):
        path = os.path.join(dpath, list[i])
        if os.path.isfile(path) and path.endswith('.pdf'):
            print(f'path: {path}')
            one_pdf_to_image(path, zoom)
        else:
            print(f'path: {path} may not be a pdf file')

def main():
    parser = argparse.ArgumentParser(description='Pdf to image png')
    parser.add_argument('-f', '--file', type=str, help='pdf file')
    parser.add_argument('-d', '--dir', type=str, help='pdf file dir')
    parser.add_argument('-z', '--zoom', type=float, default=2.0, help='zoom factor')

    args = parser.parse_args()

    if args.file and os.path.isfile(args.file):
        one_pdf_to_image(args.file, args.zoom)
        return

    if not args.dir or not os.path.isdir(args.dir):
        print('does not specify dir')
        return

    pdfs_to_images(args.dir, args.zoom)

if __name__ == '__main__':
    main()
