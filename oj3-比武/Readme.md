# 比武
by  郑瑜
## 问题描述
N个士兵站成一列，每个士兵都有一个武力值。对于队伍中任意两个士兵X和Y，如果他们在队伍中相邻，或者他们之间没有士兵的武力值严格大于X和Y的武力值中的较小值，那么他们需要进行一次比武。请计算总共需要进行几次比武。
## 输入格式
第一行：一个整数N，代表士兵的总数

第2到第N+1行：每行是一个整数，表示队伍中从头至尾每个士兵的武力值
## 输出格式
一个整数，表示比武的次数
### 输入样例
输入样例1：

8

2

7

1

6

5

3

4

2

输入样例2：
5

4

2

2

2

5

### 输出样例
输出样例1：

9

输出样例2：

10

## 提示
请使用scanf/printf实现输入/输出

比武的次数可能很大，超过int的范围

不同士兵的武力值可能相等

可能用到的结论：对于任意士兵Z，排在Z前面且武力值比Z小的士兵不会和排在Z后面的士兵比武

 
对于全部的测试点，保证1<=每个士兵的武力值<231

1-2测试样例：N<=1×103

3-4测试样例：1×103<N<=1×104

5-10测试样例：1×104<N<=5×105
