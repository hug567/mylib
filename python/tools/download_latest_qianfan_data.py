import requests
from bs4 import BeautifulSoup
from requests.adapters import HTTPAdapter
from requests.packages.urllib3.util.retry import Retry
import datetime

# 设置重试策略
retry_strategy = Retry(
    total=3,  # 总共重试次数
    backoff_factor=1,  # 重试间隔时间
    status_forcelist=[429, 500, 502, 503, 504],  # 需要重试的状态码
    allowed_methods=["HEAD", "GET", "OPTIONS"]  # 需要重试的方法
)
adapter = HTTPAdapter(max_retries=retry_strategy)
http = requests.Session()
http.mount("https://", adapter)
http.mount("http://", adapter)

# 发送GET请求获取页面内容
url = "https://celestrak.org/satcat/table-satcat.php?NAME=qianfan"
response = http.get(url, timeout=30)
response.raise_for_status()  # 检查请求是否成功

# 使用BeautifulSoup解析HTML
soup = BeautifulSoup(response.text, 'html.parser')

# 找到所有以/NORAD/elements/gp.php?CATNR=开头的链接
links = soup.find_all('a', href=True)
norad_links = [link['href'] for link in links if link['href'].startswith('/NORAD/elements/gp.php?CATNR=')]

# 打开一个文件用于保存所有Latest Data
output_file = "all_norad_data.txt"
with open(output_file, 'w') as file:
    # 遍历每一个链接
    for link in norad_links:
        norad_catalog_number = link.split('=')[-1]

        # 构建Latest Data的完整URL
        latest_data_url = f"https://celestrak.org{link}"

        # 发送GET请求获取Latest Data
        try:
            latest_data_response = http.get(latest_data_url, timeout=10)
            latest_data_response.raise_for_status()  # 检查请求是否成功

            # 将获取的数据写入文件
            file.write(f"NORAD Catalog Number: {norad_catalog_number}\n")
            file.write(latest_data_response.text)
            file.write("\n\n")  # 添加分隔符
        except requests.exceptions.RequestException as e:
            print(f"get data from {latest_data_url} fail with error: {e}")

# 获取当前日期
current_date = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")

# 输入和输出文件名
input_file = "all_norad_data.txt"
output_file = f"qianfan_TLE_{current_date}.txt"

with open(input_file, 'r') as infile, open(output_file, 'w') as outfile2:
    for line in infile:
        if line.startswith('1') or line.startswith('2') or line.startswith('QIANFAN'):
            outfile2.write(line.strip() + '\n')
print(f"save file to: {output_file}")
