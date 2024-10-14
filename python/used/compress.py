import os
import zipfile
import tarfile
import gzip
import shutil
import random

# 使用zip压缩单个文件
def zip_file(input_file, output_file):
    with zipfile.ZipFile(output_file, 'w', zipfile.ZIP_DEFLATED) as zipf:
        zipf.write(input_file, os.path.basename(input_file))

# 使用tar压缩单个文件
def tar_file(input_file, output_file):
    with tarfile.open(output_file, 'w') as tarf:
        tarf.add(input_file, arcname=os.path.basename(input_file))

# 使用gzip压缩单个文件
def gzip_file(input_file, output_file):
    with open(input_file, 'rb') as f_in, gzip.open(output_file, 'wb') as f_out:
        shutil.copyfileobj(f_in, f_out)

# 只能混合压缩单个普通文件
def mix_random_compression(input_file, layers=5):
    if not os.path.isfile(input_file):
        print("文件不存在：", input_file)
        return

    need_compressed_file = input_file
    suffix = ""
    # 多层随机混合压缩
    for layer in range(1, layers + 1):
        # 随机选择一个压缩文件类型
        method = random.choice(['zip', 'tar', 'gzip'])
        # 根据类型压缩文件
        if method == 'zip':
            suffix += ".zip"
            output_file = f"{input_file}" + suffix
            zip_file(need_compressed_file, output_file)
        elif method == 'tar':
            suffix += ".tar"
            output_file = f"{input_file}" + suffix
            tar_file(need_compressed_file, output_file)
        elif method == 'gzip':
            suffix += ".gz"
            output_file = f"{input_file}" + suffix
            gzip_file(need_compressed_file, output_file)
        if layer > 1:
            os.remove(need_compressed_file)
        need_compressed_file = output_file
    print("成功对文件：", input_file, "随机混合压缩", layers, "次，压缩后的文件：", output_file)

def main():
    # 文件夹的路径
    folder_path = './compressed_dir'
    # 判断目录是否存在
    if not os.path.isdir(folder_path):
        print("目录不存在：", folder_path)
        return
    # 进入目录
    os.chdir(folder_path)
    cur_dir = os.getcwd()
    # 遍历目录中的所有文件，并进行混合压缩，将忽略目录
    for file in os.listdir(cur_dir):
        if os.path.isfile(os.path.join(cur_dir, file)):
            mix_random_compression(file)

if __name__ == '__main__':
    main()