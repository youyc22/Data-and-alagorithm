#include <stdio.h>
#include <stack>
#pragma warning(disable:4996)
int main()
{
    std::stack<int> st;  // 存储武力值
    std::stack<int> repeat; //储存重复个数
    long long battles = 0;     // 初始化比武次数
    int N = 0, num = 0, warriors = 0, flag = 1;
    scanf("%d", &N);
    scanf("%d", &warriors);
    st.push(warriors);
    repeat.push(1);
    for (int i = 0; i < N-1; i++)
    {
        scanf("%d", &warriors);
        while (!st.empty() && st.top() < warriors)
        {
            st.pop();  // 弹出栈中武力值小于当前士兵的士兵
            battles += repeat.top();
            repeat.pop();
        }
        if (!st.empty() && st.top() == warriors)//武力值相等时
        {
            int j = repeat.top();
            j++;
            battles += j;
            if (st.size() == 1)
            {
                battles--;
            }
            repeat.pop();
            repeat.push(j);
            continue;
        }
        if (!st.empty())
        {
            battles++;  // 相邻士兵进行一次比武
        }
        st.push(warriors);  // 士兵入栈
        repeat.push(1);
    }
    printf("%lld", battles);
    return 0;
}
