##### cmake 和make书写示例

基本结构

```
cmake_minimum_required(VERSION 2.8)
set(target_name decode)

project(${target_name} C CXX) //这句话是什么意思

add_compile_options(-std=c++11 -Wno-deprecated-declarations -fPIC)

include_directories(/mnt/include /app/include)

aux_source_directory(. SRCDIR)

link_directories(/mnt/lib /app/lib)

file(GLOB SOURCE_FILES "./*.cpp" "/mnt/*.cpp")

//编译库的时候
add_library(${target_name} SHARED ${SOURCE_FILES})

//编译可执行文件的时候

add_executable(${target_name} ${SOURCE_FILES})

target_link_library(${target_name}
					-lpthread
					-lopencv_imgproc
)

```





示例2 make的使用

- 使用make，将当前路径下所有cpp（包括子文件夹）编译成一个库

```
SRC=$(wildcard *.cpp)
DIR=$(notdir ${SRC})
OBJ=$(patsubst %.cpp,%.o, ${DIR})//将所有的cpp便成.o文件
MAINS=test

DIROPENCV=/usr/local/libs/opencv.pc
LDFLAGS= `pkg-config ${DIROPENCV} --libs`
CPPFLAGS=`pkg-config ${DIROPENCV} --cflags`

all:${OBJ}
	@echo ${SRC}
	@echo ${DIR}
	@echo ${OBJ}
	@g++ ${OBJ} -o ${MAINS} ${CPPFLAGS}
	
%.o:%.cpp
	@echo ${CPPFLAGS}
	@g++ -c -g $< -o $@ ${LDFLAGS} ${CPPFLAGS}
	
.PHONY:clean
	
clean:
	rm -rf ./*.o
```



- 关键词注释<https://www.cnblogs.com/yongfengnice/p/11789651.html>
- CPPFLAGS：预处理器需要的选项， -I
- CFLAGS: 编译的时候使用的参数 -Wall -g -c (-c compile 只编译不连接。-g 在可执行程序中包含标准调试信息)
- LDFLAGS:链接库使用的选项，—L -l



gcc编译器有许多选项，-o 表示要输出的可执行文件名 -c 表示只要求编译器输出目标代码，而不必要输出可执行文件，-g 表示要求编译器在编译的时候提供我们以后对程序进行调试的信息



- makefile有三个非常有用的变量<http://www.360doc.com/content/14/0625/15/16285334_389630875.shtml>

  

  ```
  $@ $^ $<
  
  $@ --目标文件
  $^ --所有依赖文件
  $< --第一个依赖文件
  
  
  main: main.o mytool1.o mytool2.o 
  //转换以后的格式，变成可执行文件
  g++ -o $@ $^
  
  main.o:main.c mytool1.h mytool2.h
  //转换以后的格式
  g++ -c $<
  
  mytool1.o :mytool1.c mytool1.h
  
  g++ -c $<
  
  mytool2.o :mytool2.c mytool2.h
  
  g++ -c $<
  
  
  
  //解释所有的程序编写
  g++ -c -g $< -o $@ ${LDFLAGS} ${CPPFLAGS}
  
  g++ -c -g $< //生成.o文件
  //往后加上  -o $@ //生成目标文件
  
  ```

  



- wildcard

  <https://www.cnblogs.com/yuguangyuan/p/6740276.html>

  用法$(wildcard PATTERN…) 在Makefile中，它被展开为已经存在的、使用空格分开的，匹配此模式的所有文件列表。

  ```
  $(wildcard *.c)获取工作目录下的所有的.c文件列表
  
  $(patsubst %.c,%.o,$(wildcard *.c))
  //首先使用wildcard函数获取工作目录下的.c文件列表，之后将列表中所有文件名的后缀.c替换为.o。
  这样就可以得到在当前目录可生成的.o文件列表
  
  
  //在一个目录下可以使用如下内容的makefile来将工作目录下的所有.c文件进行编译并最后连接成为一个可执行文件
  
  objects:=${patsubst %.c,%.o,${wildcard *.c}}
  
  //对变量赋值 （：=）
  
  foo:$(objects)
  cc -o foo ${objects}
  ```

  

  具体的例子解析

  假设test目录下有很多文件

  

  ```
  src=$(wildcard *.cpp )
  dir=$(notdir $(src))
  obj=$(patsubst %.cpp,%.o,$(dir)) 
  MAINS=test
  
  all:$(obj)
  	@echo ${src}  
  	@echo $(dir)  
  	@echo $(obj) 
  	@ g++  $(obj) -o $(MAINS)
  	@echo "end"
  
  .PHONY:clean
  
  clean:
  	rm -rf ./*.o
  ```

  

  

  

  

  

  

  

  

  

  

  







