# C 风格字符串

## 自己写一个strcpy函数
```
void my_strcpy(char *dest, const char *src) {
    // 循环复制每个字符，包括最后的 '\0'
    while ((*dest++ = *src++) != '\0') {
        // 空循环体，核心逻辑在表达式中
    }
}
```
**可以不用存储origin**
```
char *my_strcpy(char *dest, const char *src) {
    char *original_dest = dest;  // 保存目标地址指针
    while ((*dest++ = *src++) != '\0');  // 逐字符复制，直到遇到字符串结束符 '\0'
    return original_dest;  // 返回目标地址
}
```
**更好的写法**

## 实例
```
/*
 * 去除字符串两端空格的函数trim
 * 将字符串开头和末尾的所有空格字符去除
 *
 * 参数说明：
 *      - s：char*，原始字符串
 *      - t：char*，去掉所有首尾空格后的字符串
 * 返回值说明：
 *      - 无
 *
 */
void trim(char *s, char *t)
{
    // TODO
    char *p = s;
    char *q = s;
    while (*q != '\0')
    {
        q++;
    }
    q--;
    while (*p == ' ' && *p != '\0')
    {
        p++;
    }
    while (*q == ' ' && q != s)
    {
        q--;
    }
    while (p <= q)
    {
        *t++ = *p++;
    }
    *t = '\0';
    // END OF TODO
}
```
+ 这是void写法，无返回值
+ *t指向的位置无所谓
### 后续main函数
```
int main()
{
    char s[MAXN + 1], t[MAXN + 1];

    fgets(s, MAXN, stdin);
    char *p = strchr(s, '\n');
    if (p)
        *p = '\0';

    trim(s, t);
    printf("(%s)\n", t);

    return 0;
}
```
