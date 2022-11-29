cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
project(subcmake)

# Add sub directories
# 定义子目录src，用以递归的调用src中的MakeLists.txt
add_subdirectory(public)
add_subdirectory(app)

# 动态链接库部分
# 添加头文件所在的目录
include_directories(./lib_head)
# 设置lib的路径（这个路径虽然可以不必在环境变量中，但同时确保这个dll在环境变量里面有一个备份，或者要和exe在一起
# 其实可以直接使用环境变量的目录里面的dll
set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib) # 这儿用绝对路径，相对路径目前不可行
# 如果环境变量中有dll，这一步可以省略,这个只是在当dll在其他目录下的时候保证当前程序能够编译通过
link_directories(${LIB_PATH})
#添加动态连接库 1
link_libraries(${LIB_PATH}/libhello.dll)
link_libraries(${LIB_PATH}/libthd.dll)
add_executable(${PROJECT_NAME} main.cpp)

#添加动态连接库 2
#target_link_libraries(${PROJECT_NAME} ${LIB_PATH}/libhello.dll) #libpydll.dll
# Link the static library from subproject1 using it's alias sub::lib1
# Link the header only library from subproject2 using it's alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    lib::app
    lib::public
)
