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
    
