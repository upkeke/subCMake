# Set the project name
project (public)

# Add a library with the above sources
add_library(${PROJECT_NAME} Tree.cpp)
# 给动态库取别名
add_library(lib::public ALIAS ${PROJECT_NAME})

# 添加头文件
target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)
message(STATUS "public PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

