# 执行脚本：cmake -P test_strcmp.cmake

include(../script/common.cmake)

log_info_var(CMAKE_CURRENT_SOURCE_DIR)
log_info_var(CMAKE_CURRENT_BINARY_DIR)

set(var1 "test_var")
set(var2 "test_var")

# 比较字符串是否相等
if(${var1} STREQUAL ${var2})
	log_info("var1 is same as var2")
else()
	log_info("var1 is not same as var2")
endif()
