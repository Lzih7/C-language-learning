## 基本目的
- 提供一种有组织的管理库、依赖的方式，同时简化命令行
## 格式
```makefile
target: dependencies
  command1
  command2
```
- dependencies是目标文件的依赖文件
- command用于生成target
### 实例
```makefile
run: run.o
  g++ run.o another.o -o run

run.o: run.cpp
  g++ -c run.cpp

another.o: another.cpp
  g++ -c another.cpp

clean:
  rm -rf *.o run
```
## 命令
1. make
2. make target (make后加上对应目标的命令) eg: make clean
