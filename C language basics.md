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
    char catagory[80];
    char factory[80];
    char material[10][40];
    int cnt;
} Product;

void printf(struct Product a){
    printf("价格：%lf\n",a.price);
    printf("品种：%s\n",a.catagory);
    printf("生产厂家：%s\n",a.factory);
    printf("原料：")；
    for(int i=0;i<p.cnt;i++){
        printf("%s ",material[i]);

int main(){
    struct Product prod1;
    prod1.price = 29.99;
    strcpy(prod1.category, "食品");
    strcpy(prod1.manufacturer, "UESTC公司");
    prod1.ingredient_count = 2;
    strcpy(prod1.ingredients[0], "面粉");
    strcpy(prod1.ingredients[1], "糖");
    printProduct(prod1);

    return 0;
}
