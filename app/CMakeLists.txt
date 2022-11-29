# Set the project name
project (app)

# Add a library with the above sources
# 生成动态库
add_library(${PROJECT_NAME} winTree.cpp)
# 为动态库添加别名
add_library(lib::app ALIAS ${PROJECT_NAME})

#包含头文件
target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
    PUBLIC ${PROJECT_SOURCE_DIR}/../public
)
message(STATUS "app PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "app CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
