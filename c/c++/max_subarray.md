# 问题概述
- 在给定数组中，找到**和最大**的**连续子序列**
# 算法设计
## kadane 算法
```python
def maxSubArray(nums):
    max_current = max_global = nums[0]
    for num in nums[1:]:
        max_current = max(num, max_current + num)
        max_global = max(max_global, max_current)
    return max_global
```
### 算法步骤：
1. 初始化两个变量：max_current 和 max_global，都设为第一个元素
2. **从第二个元素开始**遍历数组：
- max_current = max(当前元素, max_current + 当前元素)
- max_global = max(max_global, max_current)
3. 最后返回 max_global
## 算法原理
+ global变量储存最大值
+ current记录实时变化，判断是否带上前面的元素
