# 动态分配空间
1. 返回一个数组是需要给数组动态分配空间，**否则return时会清楚该内存**
2. malloc在stdlib中，需在适当时free
```
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for(int i=0;i<numsSize;i++){
        for(int j=i+1;j<numsSize;j++){
            if(nums[i]+nums[j]==target){
                int* arr=(int*)malloc(sizeof(int)*2);
                arr[0]=i;
                arr[1]=j;
                *returnSize = 2;
                return arr;
            }
        }
    }
    return NULL;
}
```
# 链表使用
1. 每个node->next都要动态分配空间，并且最后要用tail=tail->next;来保证循环
2. 写完一个节点后要加上node->next=NULL之类
3. NULL可在条件判断是当作0使用
4. node1||node2即检验两个节点是否都为空
```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
   struct ListNode *head=NULL,*tail=NULL;
   int carry=0;
   while(l1||l2){  /*l1,l2是否全为NULL*/
    int n1=l1?l1->val:0;
    int n2=l2?l2->val:0;  //0与NULL等价
    int sum=n1+n2+carry;
    if(!head){    /*head为NULL则执行，只执行一次*/
        head=tail=malloc(sizeof(struct ListNode));  //head,tail指向相同地址
        tail->val=sum%10;
        tail->next=NULL;  //固定用法
    }else{
        tail->next=malloc(sizeof(struct ListNode));
        tail->next->val=sum%10;
        tail=tail->next;
        tail->next=NULL;
    }
    carry=sum/10;
    if(l1){
        l1=l1->next;
    }
    if(l2){
        l2=l2->next;
    }
   }
   if(carry>0){
    tail->next=malloc(sizeof(struct ListNode));  //所有的新节点都要malloc
    tail->next->val=carry;
    tail->next->next=NULL;
   }

   return head;
}
```
# 滑动窗口法
例题：无重复最长字串的长度
-
1. hash：用ASCII形式储存每个字母出现次数
2. **maxlen储存最长序列，用len与maxlen作比较决定**
3. 滑动窗口：start,end；end从0开始右移
   + end每移动一位hash[s[end]]++，len++
   + hash的一个元素>1时start右移 len--
```
/*滑动窗口来解决连续长度问题*/

int lengthOfLongestSubstring(char* s) {
    int hash[256]={0};
    int maxlen=0;
    int len=0;

    int start=0,end;
    for(int end=0;end<strlen(s);end++){

        hash[s[end]]++;  //表示对应的ACSII码，也是256的原因
        len++;

        while(hash[s[end]]>1){  /*出现超过一次的情况*/
            hash[s[start]]--;  //由于后面的start++，次数需减1
            start++;
            len--;
        }

        if(len>maxlen) maxlen=len;
    }
    
    return maxlen;
}
```
# 两数组
例题：求中位数
-
+ ***不必合并数组***
1.每次取两个数组待取元素的较小一个，之后自增
  ```
   arr[i]=(nums1[s1]>nums2[s2])?nums2[s2++]:nums1[s1++];
  ```
2. 注意：**不要越界**
3. 数组实际最大项为num-1，填写时时刻注意
```
/*先写个O(m+n)的吧*/
/*其实不需合并两个数组*/
/*下一步学习简化空间复杂度*/
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int num=nums1Size+nums2Size;
    int arr[nums1Size+nums2Size];
   
    int n1=num/2,n2=num/2+1;
    int s1=0,s2=0;
    for(int i=0;;i++){
        
        if(s1<nums1Size&&s2<nums2Size){
            arr[i]=(nums1[s1]>nums2[s2])?nums2[s2++]:nums1[s1++];
        }
        else if(s1>=nums1Size){
            arr[i]=nums2[s2++];
        }
        else if(s2>=nums2Size){
            arr[i]=nums1[s1++];
        }
        if(i==n2-1) break;
    }
    double ret;
    if(num%2==0){
        ret=(arr[n1-1]+arr[n2-1])/2.0;
    }else{
        ret=arr[n2-1]*1.0;
    }  

    return ret;
}
```
# 回文--中心扩展法
1. 分类：奇偶
2. max标志
3. 条件，防越界
4. **用'\0'替换收尾字符串**
5. 具体写法：
   + 指针or坐标(数组)定位 =>**坐标优先**   坐标是个int类型的数，使用方便广泛
   + 条件可并在循环中
```
char* longestPalindrome(char* s) {
    int len=strlen(s);
    int max=0;
    int p=0;
    for(int i=0;i<len;i++){
        int left=i-1,right=i+1;
        while(left>=0&&right<len&&s[left]==s[right]){
            left--;
            right++;
        }
        if(right-left+1-2>max){
            max=right-left+1-2;
            p=left+1;  //最左侧坐标
        }
    }
    for(int i=0;i<len;i++){
        int left=i,right=i+1;
        while(left>=0&&right<len&&s[left]==s[right]){
            left--;
            right++;
        }
        if(right-left+1-2>max){
            max=right-left+1-2;  //一max做标志判断是否改变p的位置
            p=left+1;  //最左侧坐标
        }
    }
    s[p+max]='\0';   //点睛之笔
    return p+s;
}
```
# 字符、数的对应关系表示
## 2个数组
```
int arr[13]={1000,900,500,400,100,90,50,40,10,9,5,4,1};
char *s[13]={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
char* intToRoman(int num) {
    char* s1=(char*)malloc(sizeof(char)*16);
    s1[0]='\0';  //不可忽视！
    for(int i=0;i<13;i++){
        while(num>=arr[i]){
            num-=arr[i];
            strcpy(s1+strlen(s1),s[i]);
        }
        if(num==0){
            break;
        }
    }
    return s1;
}
```
**转罗马数字**
+ int数组元素坐标与char数组坐标对应
+ 无需使用*查找功能*
## 一个数组
```
/*int arr[7]={1,2,10,50,100,500,1000};
char romma[7]={'I','V','X','L','C','D','M'};
合二为一，利于利用内在联系*/
int romanToInt(char* s) {
    int symbolValues[26];
    symbolValues['I' - 'A'] = 1;
    symbolValues['V' - 'A'] = 5;
    symbolValues['X' - 'A'] = 10;
    symbolValues['L' - 'A'] = 50;
    symbolValues['C' - 'A'] = 100;
    symbolValues['D' - 'A'] = 500;
    symbolValues['M' - 'A'] = 1000;
    int len=strlen(s);
    int sum=0;
    for(int i=0;i<len;i++){
       
        if(i<len-1){
            if(symbolValues[s[i]-'A']<symbolValues[s[i+1]-'A']){
                sum-=symbolValues[s[i]-'A'];
            }else{
                sum+=symbolValues[s[i]-'A'];
            }
        }
        else sum+=symbolValues[s[i]-'A'];
    }

    return sum;

}
```
**罗马数字转数字**
+ 需要*查找功能*  =>用一个数组表示对应关系
+ 与双数组相比，缺少了直接***用i递增的循环***访问int数组的功能
# 双指针 
水桶问题
---
```
/*O(n)的优化算法*/
/*双指针*/
int maxArea(int* height, int heightSize) {
    int max = 0;
    int left = 0;
    int right = heightSize - 1;
    
    while (left < right) {
        // 计算当前面积
        int current = (height[left] < height[right] ? height[left] : height[right]) * (right - left);
        // 更新最大面积
        if (current > max) {
            max = current;
        }
        // 移动指针
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return max;
}
```
# 关于是否进入循环的判定
最长公共前缀
---
```
char* longestCommonPrefix(char** strs, int strsSize) {
    char* s=(char*)malloc(sizeof(char)*500);
    int step=0;
    
    for(int i=0;i<strsSize;i++){
        int isprime=0;
        int step=0;
        if(i==0){
            strcpy(s,strs[i]);
        }else{
            for(int j=0;s[j]==strs[i][j]&&j<strlen(s);j++){        //////////
                step=j;
                isprime=1;
            }
            s[(isprime==1)?(++step):step]='\0';
        }
    }

    return s;
}
```
+ step是否++，取决于循环是否进入
+ /////行不进入和进入一次step的值均为0
# 巧妙回溯
```
void backtrack(char* digits,int index,char* combination,char** ret){
    
    if(index==strlen(digits)){
        ret[cnt] = (char *)malloc((strlen(combination) + 1) * sizeof(char));
        strcpy(ret[cnt++],combination);
        return;
    }
    const char* letter=s[digits[index]-'0'];
    for(int i=0;i<strlen(letter);i++){
        combination[index]=letter[i];

        backtrack(digits,index+1,combination,ret);
    }
}
```
# 合并k个链表
重置的重要性
-
```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* ret = head;
    int minnum = -1;
    int min=INT_MAX;
    int isprime;
    do{
        isprime=0;
        min=INT_MAX;  ////
        minnum = -1;  ////必须要加
        for (int i = 0; i < listsSize; i++) {
            if (lists[i] != NULL) {
                isprime=1;
                if ((lists[i]->val) < min) {
                    min = lists[i]->val;
                    minnum = i;
                }
            }
        }
        if(isprime){
            head->next = lists[minnum];
            lists[minnum] = lists[minnum]->next;
            head = head->next;
        }
    }while(isprime);
    head->next=NULL;    ////
    return ret->next;
}
/*重置的重要性*/
```
***还需注意链表的最后一个节点一定为NULL***
# 非递减数组中查找元素的第一和最后位置
```
class Solution {
public:
    int lower(vector<int>& nums,int target){
        int left=0;
        int right=nums.size()-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if(nums[mid]>=target){
                right=mid-1;
            }else{
                left=mid+1;
            }
        }
        return left;
    }
    
    vector<int> searchRange(vector<int>& nums, int target) {
        int start=lower(nums,target);
        if(start>=nums.size()||nums[start]!=target){
            return {-1,-1};
        }
        int end=lower(nums,target+1)-1;
        return {start,end};
    }
};
```
**红蓝染色法**

**一直为闭区间查找**
