#include <cstdio>
#include <vector>
#include <climits>
#pragma warning(disable:4996)
class Edge
{
public:
    int end, time, price;
    Edge(int n, int t, int p, char v) : end(n), time(t), price(p){}
};
int min_price = INT_MAX;
void dfs(std::vector<int>& time_sum, std::vector<int>& price_sum, std::vector<std::vector<Edge>>& data, int current, int end, int time_limit, int current_price, int current_time)
{
    if (current == end)
    {
        min_price = std::min(min_price, current_price);
        return ;
    }
    for (auto& edge : data[current])
    {
        if (edge.time <= time_limit)
        {
            if (current_time + edge.time < time_sum[edge.end] || current_price + edge.price < price_sum[edge.end])
            {
                time_sum[edge.end] = current_time + edge.time;
                price_sum[edge.end] = current_price + edge.price;
                dfs(time_sum, price_sum, data, edge.end, end, time_limit - edge.time, current_price + edge.price, current_time + edge.time);
            }
        }
    }
}
int main()
{
    int N = 0, M = 0, time_limit = 0, start_point = 0, end = 0;
    scanf("%d %d", &N, &M);
    std::vector<std::vector<Edge>> data(N + 1);
    std::vector<int> time_sum(N + 1,INT_MAX), price_sum(N + 1, INT_MAX);
    for (int i = 0; i < M; i++)
    {
        int start = 0, end = 0, time = 0, price = 0;
        scanf("%d %d %d %d", &start, &end, &time, &price);
        data[start].push_back(Edge(end, time, price, 0));
    }
    scanf("%d %d %d", &start_point, &end, &time_limit);
    dfs(time_sum, price_sum, data, start_point, end, time_limit, 0, 0);
    printf("%d", min_price == INT_MAX ? -1 : min_price);
    return 0;
}
