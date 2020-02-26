# 导入openpyxl包
import openpyxl

from openpyxl import load_workbook

# Excel文件名
filename="test.xlsx"

# 打开Excel，获取workbook
workbook = load_workbook(filename)

# 获取所有sheet名
sheets_name = workbook.get_sheet_names()
print("all sheet: ", end = "") # 输出不换行
print(sheets_name)

# 获取第一个sheet
sheet = workbook.get_sheet_by_name(sheets_name[0].title())
cell = sheet['A1']
print("A1 = %d" % cell.value)

# 插入列
sheet.insert_rows(1, 0)
cell = sheet['A1']
cell.value = "进度"

# 保持workbook
workbook.save("test2.xlsx")
