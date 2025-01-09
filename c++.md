# 获取输入
```
cin.getline(char* sentence, int maxsize);
```
# 函数
## 重载
根据**调用的参数**的不同来判断调用那个重载函数
## 内联
inline 关键字
+ 直接复制代码
+ 减少调用函数产生的时间开销，但占用内存增加
## 递归调用
可通过记忆化存储数据(动态规划)来降低时间复杂度
## 循环遍历
```
for(auto n:numbers){};
```
# 引用变量
```
int& b=a;
```
a，b代表相同的内存区域，即为不许解引用的指针
+ 提升性能
```
float calculate(vector<float>& values);
float calculate(const vector<float> values);  //则values不会被修改
```
## new 运算符
```
char* p1=new char;  //未初始化
int* p1=new int(2);
char* p3=new char[5];
char* p4=new char[5]{1,2,3,4,5};
```
## delate 运算符
只能删除new的内存
```
delate p1;
delate []p3;
```

+ 注：**定义的指向常量的指针必须用const修饰**
## 智能指针
shared_ptr<int> pInt(new int(2));
