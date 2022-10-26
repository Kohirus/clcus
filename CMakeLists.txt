cmake_minimum_required(VERSION 3.0)
project(chat)

# 生成 compile_commadns.json 文件
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置最终的可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty)

# 加载子目录
add_subdirectory(src)
