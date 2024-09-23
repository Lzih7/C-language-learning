# 1.条件控制与循环控制
## 1.1.条件控制
### if语句：
```
max(a,b){
    if(a>b){
        printf("%d",a);
    }else{
        printf("%d",b);
    }
}
```
```
scanf("%d",&a);
    if(a>999){
        n=4;
    }else if(a>99){
        n=3;
    }else if(a>9){
        n=2;
    }else{
        n=1;
    }
   ```
关键字：if、else、else if 
### switch case:
```
switch(type){   //type为整数类型
    case 1：
        ......;
        break;
    case 2:
        ......;
        break;
    default:
        ......;
}
```
注：并不是必须每个case都需要break；

   type的值与每个case后的常量比较，相同则执行语句，直到遇到break。 

关键词：switch、case、default
## 1.2.循环语句
### while语句
```
while(){
    ......;
}
```
***符合条件，则进入循环，在循环进行前检验***
### for语句
```
for(i=1;i<n;i++){
    ......;
}
```
***任何for语句都能改写成while语句***
### do-while语句
```
do{
    ......;
}while();
```
***do-while语句在执行后检查***
# 2.结构体的运用
存放商品信息的一个结构体
```
#include<stdio.h>
#include<string.h>
typedef struct{
    double price;
    char category[80];
    char factory[80];
    char material[10][40];
    int cnt;
} Product;

void printf(struct Product a){
    printf("价格：%lf\n",a.price);
    printf("品种：%s\n",a.category);
    printf("生产厂家：%s\n",a.factory);
    printf("原料：")；
    for(int i=0;i<p.cnt;i++){
        printf("%s ",material[i]);
    }
}
int main(){
    struct Product a;
    a.price = 50.50;
    strcpy(a.category, "食品");
    strcpy(a.factory, "UESTC公司");
    a.cnt = 2;
    strcpy(a.material[0], "面粉");
    strcpy(a.material[1], "糖");
    prinf(a);

    return 0;
}
```
以下是个人结构体学习的部分心得
## 结构体
+ 多使用typedef来简化
+ struct Person是结构体类型，而Person person1是结构体变量，与Person的结构相同
+ 作为函数参数时，格式：void f(Person person1){}，要带上Person
+ 字符数组：[]内的是字符长度减一，因为以\0结束；a[][]前一个为个数，后一个为字符长度
+ strcpy()函数可将字符串常量复制到结构体中，需用string.h头文件定义
+ 结构体可以使用指针，用->访问结构体成员
# 3.开发结构与指针
## 3.1.开发结构
### 预处理器
在编译之前**对源代码进行处理**

内容：

1.宏定义

#define N 10;

之后可以使用int array[N]来定义数组

2.错误检查

3.代码生成

4.文件包含

允许将一个文件的内容包含到另一个文件中

5.条件编译

根据特定的条件选择是否编译某部分代码
### 头文件
stdio.h, string.h等

包含函数声明，宏定义，常量定义等，可以避免**代码重用**
### 库函数
即预先被编写好的函数集合，使开发更加快速高效

一些C语言标准库函数：printf,scanf,strcpy,malloc,free,sqart,sin,cos,tan,srand
 
**库函数使用需要包含对应的头文件**
# 指针与地址
指针类型的变量指向一个变量的地址，如`int *p=&a;`
```
int a=7;
int b=5;
int *p=&a;
int *q=&b;
int c=0;
c=*p;
*p=*q;
*q=c;
printf("a=%d",*p);
printf("b=%d",*q);
```
# 2,8,16进制
## 进制换算
二进制：每三位可换算八进制，每四位可换算十六进制

