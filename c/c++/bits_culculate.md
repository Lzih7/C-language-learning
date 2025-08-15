## 基本概念
- `1 << n` 表示1右移n位，即每次`*2`
- `1011011 >> i` 表示每次右移i位右移一位即为`/2`
## 运用
### 列出所有情况
eg:
# P2036 [COCI 2008/2009 #2] PERKET

## 题目描述

Perket 是一种流行的美食。为了做好 Perket，厨师必须谨慎选择食材，以在保持传统风味的同时尽可能获得最全面的味道。你有 $n$ 种可支配的配料。对于每一种配料，我们知道它们各自的酸度 $s$ 和苦度 $b$。当我们添加配料时，总的酸度为每一种配料的酸度总乘积；总的苦度为每一种配料的苦度的总和。

众所周知，美食应该做到口感适中，所以我们希望选取配料，以使得酸度和苦度的绝对差最小。

另外，我们必须添加至少一种配料，因为没有任何食物以水为配料的。

## 输入格式

第一行一个整数 $n$，表示可供选用的食材种类数。

接下来 $n$ 行，每行 $2$ 个整数 $s_i$ 和 $b_i$，表示第 $i$ 种食材的酸度和苦度。

## 输出格式

一行一个整数，表示可能的总酸度和总苦度的最小绝对差。

## 输入输出样例 #1

### 输入 #1

```
1
3 10
```

### 输出 #1

```
7
```
```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> ingredients(n);
    for (int i = 0; i < n; ++i) {
        cin >> ingredients[i].first >> ingredients[i].second;
    }

    int min_diff = INT_MAX;
    // 枚举所有非空子集
    for (int mask = 1; mask < (1 << n); ++mask) {
        int s_product = 1;
        int b_sum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                s_product *= ingredients[i].first;
                b_sum += ingredients[i].second;
            }
        }
        int current_diff = abs(s_product - b_sum);
        if (current_diff < min_diff) {
            min_diff = current_diff;
        }
    }

    cout << min_diff << endl;
    return 0;
}
```
+ 用二进制的1或0表示是否被记录
