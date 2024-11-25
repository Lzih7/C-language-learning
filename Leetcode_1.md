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
