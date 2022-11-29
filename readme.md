# 多级目录CMakeLists
[参考](https://blog.csdn.net/qq_26849933/article/details/116454719)

1. app 目录
函数，类所在文件夹，只能被main.cpp调用
2. dll
动态链接库，其他文件夹都能调用
3. public
存放公共函数和类其他文件夹都能调用

大写为变量名

小写为函数名



## PROJECT_SOURCE_DIR

CMakeLists所在的目录的路径

CMAKE_CURRENT_SOURCE_DIR 貌似和它有一样的作用

![image-20221130040359656](F:\图片保存处勿动\image-20221130040359656.png)

##　set

后边只能是绝对路径，也可以通过PROJECT_SOURCE_DIR和PROJECT_SOURCE_DIR来转成相对路径

```cmake
set(HEAD_PATH "E:/code/cmake_dll/get_dll")
include_directories(${HEAD_PATH})

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib) # 当前目录的子目录lib
```

# 生成动态库

[项目位置](E:\code\cmake_dll\get_dll\CMakeLists.txt)

head.h

```c++
#ifndef HELLO_H
#define HELLO_H

    void helloDll();
    void setName(const char* name);
    int t_max(int a,int b);

#endif
```

head.cpp

```cpp

#include<iostream>
#include"hello.h"
void helloDll()
{
    std::cout<<"hello"<<std::endl;
}
void setName(const char* name)
{
    std::cout<<"this is "<< name <<std::endl;
}
int t_max(int a,int b)
{
    return a>b?a:b;
}
```

cmakelists.txt

```cmake

cmake_minimum_required(VERSION 3.20)
# 设置工程名称
PROJECT(HELLOLIB)

# 指定编译器
set(CMAKE_CXX_STANDARD 14)

# 创建变量SRC 源码文件
SET(SRC hello.cpp)
# 添加构建目标， 动态链接库 名字叫做hello
add_library(hello SHARED  ${SRC})

 # 设定动态链接库的保存路径 ，也可以不用设置，dll会直接保存在build目录下
SET(LIBRARY_OUTPUT_PATH  "E:/ode/MyLib/bin")

```



# 链接动态链接库

环境window  gcc 8.1.0 64位  vscode 

需要 dll 和头文件

E:\code\mutCMakeLists

![image-20221130064510130](F:\图片保存处勿动\image-20221130064510130.png)

```cmake
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
#添加动态连接库
link_libraries(${LIB_PATH}/libhello.dll)
link_libraries(${LIB_PATH}/libthd.dll)

add_executable(${PROJECT_NAME} main.cpp)
#target_link_libraries(${PROJECT_NAME} ${LIB_PATH}/libhello.dll) # 这可以这种方式
# Link the static library from subproject1 using it's alias sub::lib1
# Link the header only library from subproject2 using it's alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    lib::app
    lib::public
)
```



简单讲也动态链接库，一个链接了动态链接库的exe，要想运行必须附带动态链接库dll，要么这动态链接库在exe的同目录下，要么这个dll的路径在环境变量中，本台电脑转为动态链接库的保存设置了一个地址，E:/ode/MyLib/bin，这个地址已经被添加到环境变量里面了，

## 第一步 添加头文件的目录

dll的头文件在子目录lib_head中

include_directories(./lib_head)

## 第二步 添加dll所在的目录

这一步某些情况下需要

### 情况1 

》》E:\code\MyLib\bin 这个目录在环境变量中，加入此时没有这几个dll，只在当前目录子目录lib下存在，

![image-20221130065330909](F:\图片保存处勿动\image-20221130065330909.png)

```cmake
include_directories(./lib_head)
# 设置lib的路径（这个路径虽然可以不必在环境变量中，但同时确保这个dll在环境变量里面有一个备份，或者要和exe在一起
# 其实可以直接使用环境变量的目录里面的dll
set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib) # 这儿用绝对路径，相对路径目前不可行
# 如果环境变量中有dll，这一步可以省略,这个只是在当dll在其他目录下的时候保证当前程序能够编译通过
link_directories(${LIB_PATH})
```

则需要link_directories() 把./lib加进去，那么链接的时候系统也会去这个文件夹下面找，同时要把这几个dll拷贝到build文件夹下面，与exe文件同目录，同时如果exe要发给别人，也要把这几个dll同时发个别人，没有dll，exe运行不了

### 情况2

dll已经被复制到这个有环境变量的文件夹下面，那么不需要link_directories这一步，系统能够找到

![image-20221130065956754](F:\图片保存处勿动\image-20221130065956754.png)



但是后面link_libraries这一步需要加上这个dll的绝地路径，仅仅是libthd.dll也不够

```cmake
set(LIB_PATH "E:\code\MyLib\bin") # 这儿用绝对路径，相对路径目前不可行
```

## 第三步 链接dll

可以用link_libraries也可以用target_link_libraries,二者用法基本相同[cmake 的link_libraries和target_link_libraries](https://blog.csdn.net/harryhare/article/details/89143410)

不同的是link_libraries是放在add_executable之前，target_link_libraries放在之后

```cmake
#添加动态连接库 1
link_libraries(${LIB_PATH}/libhello.dll)
link_libraries(${LIB_PATH}/libthd.dll)
add_executable(${PROJECT_NAME} main.cpp)

#添加动态连接库 2
#target_link_libraries(${PROJECT_NAME} ${LIB_PATH}/libhello.dll) #libpydll.dll
```



## target_link_libraries 和 link_libraries



### link_directories 

这个函数是添加动态库的查找路径，否者系统只会在下面路径中查找动态库

- 应用程序所在目录 exe
- 当前目录
- 系统目录 : `C:\Windows\System32`
- Windows目录: `C:\Windows`
- 环境变量PATH中所有目录

![image-20221130043339647](F:\图片保存处勿动\image-20221130043339647.png)

link_directories(./)这儿我的查找目录就是当前目录

```cmake
# 添加依赖的.h文件路径(即hello.h所在的文件夹)
include_directories(./lib_head)
# 添加动态链接库的查找目录，
link_directories(./)
# 链接动态库
link_libraries(libhello.dll)
add_executable(${PROJECT_NAME} main.cpp)
```
只在这儿添加只能保证链接通过

下面这几个地方中有dll才能保证exe正常运行

- 应用程序所在目录 exe
- 当前目录
- 系统目录 : `C:\Windows\System32`
- Windows目录: `C:\Windows`
- 环境变量PATH中所有目录



