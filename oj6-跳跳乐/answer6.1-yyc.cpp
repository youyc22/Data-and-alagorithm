//Rotate函数整体移动数组中元素位置时可以节省大量时间
#include"cstdio"
#include"algorithm"
#include"vector"
#include"cmath"
#pragma warning(disable:4996)
void delete_num(std::vector<int>& vec, int num)//删除元素
{
    auto lower = std::lower_bound(vec.begin(), vec.end(), num);
    vec.erase(lower);
}
void insert_num(std::vector<int>& vec, int num)//插入元素
{
    auto pos = std::lower_bound(vec.begin(), vec.end(), num);
    vec.insert(pos, num);
}
int calculate_num(std::vector<int>& vec, int num, int H)//在插入元素前计算台阶对数
{
    int max = (num + H < 0) ? 2147483647 : num + H;
    auto left = std::lower_bound(vec.begin(), vec.end(), num - H);
    auto right = std::upper_bound(vec.begin(), vec.end(), max);
    return std::distance(left, right);
}
int sort_and_calculate(std::vector<int>& initial, std::vector<int>& sorted, int K, int H) //先将数组前K项排序后存入sorted中
{
    std::vector<int> temp(initial.begin(), initial.begin() + K);
    int sum = 0;
    // 折半插入排序，每插入一个元素前计算台阶对数
    for (int i = 1; i < K; ++i) {
        int key = temp[i];
        int max = ( key + H < 0) ? 2147483647 : key + H;
        auto leftt = std::lower_bound(temp.begin(), temp.begin() + i, key - H);
        auto rightt = std::upper_bound(temp.begin(), temp.begin() + i, max);
        sum += std::distance(leftt, rightt);
        auto pos = std::lower_bound(temp.begin(), temp.begin() + i, key);
        std::rotate(pos, temp.begin() + i, temp.begin() + i + 1);
        temp[pos - temp.begin()] = key;
    }
    // 将排序后的元素复制到sorted中
    sorted.assign(temp.begin(), temp.end());
    temp.clear();
    return sum;
}
int main()
{
    int M = 0, K = 0, H = 0;
    long long sum = 0;
    scanf("%d%d%d", &M, &K, &H);
    int min = std::min(M, K);//防止M小于K
    std::vector<int> step(min);//储存顺序
    std::vector<int> s(min);//滑动排序窗口
    for (int i = 0; i < min; i++)
    {
        scanf("%d", &step[i]);//输入
    }
    sum += sort_and_calculate(step, s, min, H);//先计算前K项中的台阶总数
    for (int j = K; j < M; j++)//窗口每向右移动1，计算新台阶与原窗口中可以跳跃的台阶对数，删除窗口左侧元素，插入新元素
    {
        int delStep = step[0], newStep=0;
        scanf("%d", &newStep);
        std::rotate(step.begin(), step.begin() + 1, step.end());
        step[K - 1] = newStep;
        sum += calculate_num(s, newStep, H);
        delete_num(s, delStep);
        insert_num(s, newStep);
    }
    printf("%lld\n", sum);
    return 0;
}
