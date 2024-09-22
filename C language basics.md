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
ps:此部分包含少量GPT成分，以下是个人结构体学习的部分心得
## 结构体
+ 多使用typedef来简化
+ struct Person是结构体类型，而Person person1是结构体变量，与Person的结构相同
+ 作为函数参数时，格式：void f(Person person1){}，要带上Person
+ 字符数组：[]内的是字符长度减一，因为以\0结束；a[][]前一个为个数，后一个为字符长度
+ strcpy()函数可将字符串常量复制到结构体中，需用string.h头文件定义
+ 结构体可以使用指针，用->访问结构体成员
