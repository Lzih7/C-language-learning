# 打家劫舍问题
- 一个给定数组，不可连续打劫，返回最大金额
## 实现
### 暴力回溯
```python
def rob(nums:List[int]) _.int:
  n=len(nums)
  def dfs(int i):
    if i<0:
      return 0
    res=max(dfs(i-1),dfs(i-2)+1)
    return res
  return dfs(n-1)
```
+ 高时间复杂度
### 优化代码
+ **记忆化**
```python
def rob(nums:List[int]) _.int:
  n=len(nums)
  # @cache
  cache=[-1]*n
  def dfs(int i):
    if i<0:
      return 0
    if cache[i]!=-1:
      return cache[i]
    res=max(dfs(i-1),dfs(i-2)+1)
    cahce[i]=res
    return cache[i]
  return dfs(n-1)
```
+ O(n)简化
### 动态规划
- 核心：去掉递归中的‘递’，只进行‘归’，即自下而上
- 递推
- 需要对i=0，i=1的情况特殊处理
```python
def rob(nums:List[int]) _.int:
  n=len(nums)
  f=[0]*(n+2)
  for i, x in enumerate(nums):
    f[i+2]=max(f[i+1],f[i]+x)
  return f[n+1]
```
### 空间优化
```python
def rob(nums:List[int]) _.int:
  n=len(nums)
  f0=f1=0
  for i, x in enumerate(nums):
    new_f=max(f1, f0+x)
    f0=f1
    f1=new_f
  return f1
```
- python的语言特性：出了for循环， new_f立刻被销毁
