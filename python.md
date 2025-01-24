# 运算符
## **算术运算符**  
用于数学运算：
- `//`：地板除法（取整）
- `**`：幂运算（指数）

注：python中的除法不会自动取整
## **逻辑运算符**  
用于布尔运算：
- `and`：与
- `or`：或
- `not`：非
## **位运算符**  
对二进制进行操作：
- `&`：按位与
- `|`：按位或
- `^`：按位异或
- `~`：按位取反
- `<<`：左移
- `>>`：右移

## **成员运算符**  
用于检查一个值是否在**容器**中：
- `in`：在…中
- `not in`：不在…中

```python
if 'banana' in fruits:  #friut是一个列表，banana是一个字符串
    print('香蕉在列表中')
```
## **身份运算符**  
用于判断两个对象是否为同一个对象：
- `is`：是（指向同一对象）
- `is not`：不是（指向不同对象）

## **条件运算符（三元运算符）**  
简化的条件语句：
```python
x if condition else y
```
表示如果 `condition` 为真，结果是 `x`，否则是 `y`

# 数据结构
1. **列表 (List) [类似vector]**    
   列表是一个有序的**可变**集合，可以包含不同类型的元素。它使用方括号 `[]` 定义，支持索引和切片操作。  
   示例：
   ```python
   my_list = [1, 2, 3, 4]
   my_list.append(5)  # 添加元素
   print(my_list[0])  # 访问元素
   ```

2. **元组 (Tuple)**  
   元组是一个有序的**不可变**集合，定义时使用小括号 `()`，一旦创建后不可修改。  
   示例：
   ```python
   my_tuple = (1, 2, 3)
   print(my_tuple[1])  # 访问元素
   ```

3. **集合 (Set)**  
   集合是一个无序的不重复元素集合，使用大括号 `{}` 定义，支持数学集合的运算，如并集、交集等。  
   示例：
   ```python
   my_set = {1, 2, 3}
   my_set.add(4)  # 添加元素
   print(my_set)
   ```

4. **字典 (Dictionary)**  
   字典是一个无序的键值对集合，使用大括号 `{}` 定义，键是唯一的。  
   示例：
   ```python
   my_dict = {"name": "Alice", "age": 25}
   print(my_dict["name"])  # 访问值
   my_dict["age"] = 26  # 修改值
   ```
   注：**逗号**连接，键值间冒号间隔
5. **字符串 (String)**  
   字符串是一个**不可变**的字符序列，使用单引号 `''` 或双引号 `""` 定义。  
   示例：
   ```python
   my_str = "Hello, world!"
   print(my_str[0])  # 访问字符
   ```
# 相关函数
## 1. **列表（List）**
Python中的列表是一种**动态数组**，支持添加、删除、查找等多种操作。

- **初始化列表**
  ```python
  my_list = []
  ```
- **添加元素**
  ```python
  my_list.append(10)  # 在末尾添加元素
  my_list.insert(0, 20)  # 在指定位置添加元素
  ```
- **删除元素**
  ```python
  my_list.remove(10)  # 删除指定元素
  my_list.pop()  # 删除末尾元素
  my_list.pop(0)  # 删除指定位置的元素
  ```
- **查找元素**
  ```python
  index = my_list.index(20)  # 查找元素索引
  exists = 10 in my_list  # 判断元素是否存在
  ```
- **排序**
  ```python
  my_list.sort()  # 升序排序
  my_list.sort(reverse=True)  # 降序排序
  ```
- **反转**
  ```python
  my_list.reverse()  # 反转列表
  ```

### 2. **元组（Tuple）**
元组是一个不可变的序列，常用于不需要修改的数据。

- **初始化元组**
  ```python
  my_tuple = (1, 2, 3)
  ```
- **查找元素**
  ```python
  exists = 2 in my_tuple  # 判断元素是否存在
  index = my_tuple.index(3)  # 查找元素索引
  ```
- **切片**
  ```python
  sliced_tuple = my_tuple[1:3]  # 获取子元组
  ```

### 3. **字典（Dictionary）**
字典是一种无序的键值对集合，支持快速查找、插入和删除。

- **初始化字典**
  ```python
  my_dict = {'a': 1, 'b': 2}
  ```
- **添加键值对**
  ```python
  my_dict['c'] = 3  # 添加新键值对
  ```
- **删除键值对**
  ```python
  del my_dict['a']  # 删除指定键值对
  my_dict.pop('b')  # 删除并返回值
  ```
- **查找值**
  ```python
  value = my_dict.get('b')  # 查找键的值，若不存在则返回None
  value = my_dict.get('d', 'default')  # 设置默认值
  ```
- **遍历字典**
  ```python
  for key, value in my_dict.items():
      print(key, value)
  ```

### 4. **集合（Set）**
集合是一个无序且不重复的元素集合，支持基本的集合运算。

- **初始化集合**
  ```python
  my_set = {1, 2, 3}
  ```
- **添加元素**
  ```python
  my_set.add(4)  # 添加单个元素
  my_set.update([5, 6])  # 添加多个元素
  ```
- **删除元素**
  ```python
  my_set.remove(2)  # 删除指定元素
  my_set.discard(3)  # 删除元素，若不存在不报错
  my_set.pop()  # 删除并返回任意元素
  ```
- **集合运算**
  ```python
  set1 = {1, 2, 3}
  set2 = {3, 4, 5}
  union = set1 | set2  # 并集
  intersection = set1 & set2  # 交集
  difference = set1 - set2  # 差集
  ```

### 5. **队列（Queue）**
Python标准库`queue`模块提供了线程安全的队列实现，或者使用`collections.deque`来实现一个普通的队列。

- **使用`queue.Queue`（线程安全）**
  ```python
  import queue
  q = queue.Queue()
  q.put(1)  # 入队
  q.put(2)
  item = q.get()  # 出队
  ```
- **使用`collections.deque`**
  ```python
  from collections import deque
  dq = deque()
  dq.append(1)  # 队尾入队
  dq.appendleft(2)  # 队头入队
  item = dq.popleft()  # 队头出队
  ```

### 6. **栈（Stack）**
栈通常使用列表（`list`）来实现，支持LIFO（后进先出）操作。

- **初始化栈**
  ```python
  stack = []
  ```
- **压栈**
  ```python
  stack.append(1)
  ```
- **弹栈**
  ```python
  item = stack.pop()
  ```

### 7. **双端队列（Deque）**
双端队列（`deque`）允许在两端都进行插入和删除操作，通常用于实现队列和栈。

- **初始化双端队列**
  ```python
  from collections import deque
  dq = deque([1, 2, 3])
  ```
- **从队头插入**
  ```python
  dq.appendleft(0)  # 队头插入
  ```
- **从队尾插入**
  ```python
  dq.append(4)  # 队尾插入
  ```
- **从队头删除**
  ```python
  dq.popleft()  # 从队头删除
  ```
- **从队尾删除**
  ```python
  dq.pop()  # 从队尾删除
  ```

这些是Python中常见的数据结构和相关操作。如果你对某个数据结构有更详细的需求或问题，随时可以提问！
