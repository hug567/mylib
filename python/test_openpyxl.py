###############################################################################
# 功  能：python操作Excel
# 版  本：python 3.6.3
# 依赖包：openpyxl-3.0.3、jdcal-1.4.1、et_xmlfile-1.0.1
# 时  间：2020-02-27
###############################################################################

# 导入openpyxl包
import openpyxl
from openpyxl import load_workbook

# Excel文件名
filename="test.xlsx"

# 打开Excel，获取workbook
wb = load_workbook(filename)

# 获取所有sheet
sheets = wb.worksheets
print("All sheets: ", end="")
print(sheets)

# 获取sheet
sheet = sheets[0]
print("Sheet title: " + sheet.title)

# 获取表格
cell = sheet['A1']
print("A1 = %d" % cell.value)

# 插入列
sheet.insert_rows(1)
cell = sheet['A1']
cell.value = "进度"

# 保存workbook
wb.save("test2.xlsx")
