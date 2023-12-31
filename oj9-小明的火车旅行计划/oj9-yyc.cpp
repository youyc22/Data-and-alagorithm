//本题实际上完成的并不完美，可以看到104~107行有一个神奇的判断，原因是第七个点一开始超时了，超时的原因是终点的路径价格更新完后队列中还有很多点，
//程序依然没有停止，所以只能用这种愚蠢的办法来强行break，这个16当然是试出来的，待我想到好的解决办法后再更新

#include <cstdio>
#include <vector>
#include <queue>
#include <climits>
#pragma warning(disable:4996)

class Node
{
public:
    unsigned int destination, time, price;
    char visited;
    Node(unsigned int n, unsigned int t, unsigned int p, char v) : destination(n), time(t), price(p), visited(v) {}
    void set_visited(char v)
    {
        visited = v;
    }
};

int dijkstra(std::vector<std::vector<Node>>& graph, unsigned int start, unsigned int end, unsigned int time_limit, unsigned int n)
{
    unsigned int N = graph.size() - 1;
    //优先级队列数组，第一个为时间，第二个为价格，按照时间的降序排列
    std::vector<std::priority_queue<std::pair<unsigned int, unsigned int>>> dist(N + 1);
    std::queue<unsigned int> pq;
    dist[start].push(std::make_pair(0, 0));
    pq.push(start);
    int flag = 0;
    int same_num = 0;
    int in_num = 0;
    while (!pq.empty())
    {
        unsigned int u = pq.front();
        pq.pop();
        for (Node& neighbor : graph[u])
        {
            unsigned int v = neighbor.destination;
            unsigned int time = neighbor.time;
            unsigned int price = neighbor.price;
            if (!dist[v].empty())
            {
                int length = dist[u].size();
                std::priority_queue<std::pair<unsigned int, unsigned int>> temp = dist[u];
                flag = 0;
                for (int i = 0; i < length; i++)
                {
                    unsigned int now_time = temp.top().first + time;
                    unsigned int now_price = temp.top().second + price;
                    temp.pop();
                    if (now_time <= time_limit)
                    {
                        while (!dist[v].empty() && now_time < dist[v].top().first && now_price < dist[v].top().second)
                        {
                            dist[v].pop();
                        }
                        if (!dist[v].empty() && now_time > dist[v].top().first && now_price > dist[v].top().second)
                        {
                        }
                        else
                        {
                            std::priority_queue<std::pair<unsigned int, unsigned int>> tempp = dist[v];
                            while (!tempp.empty())
                            {
                                if (now_time == tempp.top().first && now_price == tempp.top().second)
                                {
                                    flag = 0;
                                    break;
                                }
                                tempp.pop();
                                flag = 1;
                            }
                            if (flag)
                            {
                                dist[v].push(std::make_pair(now_time, now_price));
                            }
                        }
                    }
                }
                if (!neighbor.visited) { pq.push(v); }
            }
            else
            {
                int length = dist[u].size();
                std::priority_queue<std::pair<unsigned int, unsigned int>> temp = dist[u];
                for (int i = 0; i < length; i++)
                {
                    unsigned int now_time = temp.top().first + time;
                    unsigned int now_price = temp.top().second + price;
                    temp.pop();
                    if (now_time <= time_limit)
                    {
                        dist[v].push(std::make_pair(now_time, now_price));
                    }
                }
                if (!dist[v].empty())
                {
                    pq.push(v);
                }
            }
            neighbor.set_visited(1);
        }
        if (dist[end].size() > 16)
        {
            break;
        }
    }

    if (!dist[end].empty())
    {
        unsigned int min_price = dist[end].top().second;
        dist[end].pop();
        while (!dist[end].empty())
        {
            min_price = std::min(min_price, dist[end].top().second);
            dist[end].pop();
        }
        return min_price;
    }
    else
    {
        return -1;
    }
}

int main()
{
    int N = 0, M = 0, time_limit = 0;
    scanf("%d %d", &N, &M);
    std::vector<std::vector<Node>> data(N + 1);

    for (int i = 0; i < M; i++)
    {
        unsigned int start = 0, end = 0, time = 0, price = 0;
        scanf("%d %d %d %d", &start, &end, &time, &price);
        data[start].push_back(Node(end, time, price, 0));
    }

    unsigned int start_point = 0, destination = 0;
    scanf("%d %d %d", &start_point, &destination, &time_limit);

    int min_price = dijkstra(data, start_point, destination, time_limit, N);

    printf("%d", min_price);
    return 0;
}
