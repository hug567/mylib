# 文件名中有unix时间戳，在文件名中补充CST时间
# 2024-10-16

import os
import re
import argparse
from datetime import datetime, timezone, timedelta

def is_time_str_exited(fname):
    pattern_list = [
        r'(202[4-9][0-1]\d[0-3]\d)',
        r'(202[4-9]-[0-1]\d-[0-3]\d)',
    ]

    for pattern in pattern_list:
        match = re.search(pattern, fname)
        if match:
            return True
    return False

def get_unit_timestamp(fname):
    pattern = r'(17[2-9]\d{10})'
    match = re.search(pattern, fname)
    if match:
        timestamp = match.group(1)
        utc_time = datetime.fromtimestamp(int(timestamp[:10]), timezone.utc)
        cst_timezone = timezone(timedelta(hours=8))
        cst_time = utc_time.astimezone(cst_timezone)
        return cst_time.strftime('%Y%m%d')
    return ''

def supplement_fname_time(fname):
    if is_time_str_exited(fname):
        print('there is already time str in fname:', fname)
        return
    timestamp = get_unit_timestamp(fname)
    if timestamp == '':
        print('get timestamp from fname', fname, 'failed')
        return
    name, ext = os.path.splitext(os.path.basename(fname ))
    new_fname = name + '_' + timestamp + ext
    print('will rename', fname, 'to', new_fname)
    os.rename(fname, new_fname)

def main():
    parser = argparse.ArgumentParser(description='Get student information')

    parser.add_argument('-d', '--dir', type=str, help='files dir')
    args = parser.parse_args()

    if not args.dir:
        print("Not specify dir")
        return
    print('dir:', args.dir)

    if not os.path.isdir(args.dir):
        print('dir does not exist:', args.dir)
        return

    os.chdir(args.dir)
    cur_dir = os.getcwd()
    for file in os.listdir(cur_dir):
        if os.path.isfile(os.path.join(cur_dir, file)):
            supplement_fname_time(file)

if __name__ == '__main__':
    main()
