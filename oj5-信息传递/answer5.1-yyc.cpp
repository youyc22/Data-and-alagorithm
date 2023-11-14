#include"stdio.h"
#include"queue"
#include"cstring"

#pragma warning(disable:4996)

int BFS(unsigned short** nodes, unsigned short N)//广度优先搜索，判断是否可以全部遍历
{
	std::queue<unsigned short*> q;//创建队列
	q.push(nodes[0]);
	char a[65536] = { 0 };//用于判断节点是否访问过，1为访问过
	unsigned short sss = 0;//访问过的节点数量
	a[0] = 1;
	sss++;
	while (!q.empty()) 
	{
		unsigned short* current = q.front();
		q.pop();
		for (unsigned short j = 0; j < current[1]; j++)
		{
			if (!a[current[j+2]])//如果未访问过，加入队列
			{
				a[current[j + 2]] = 1;
				q.push(nodes[current[j + 2]]);
				sss++;
			}
		}
	}
	if (sss == N)//全部访问过，输出1
	{
		printf("%d\n", 1);
		return 1;
	}
	else
	{
		printf("%d\n", 0);
		return 0;
	}
}

int BFS(unsigned short** nodes, unsigned short N,unsigned short target)//重载函数，判断删除通道后是否可以到达target
{
	std::queue<unsigned short*> q;
	q.push(nodes[0]);
	char a[65536] = { 0 };
	a[0] = 1;
	while (!q.empty())
	{
		unsigned short* current = q.front();
		q.pop();
		for (unsigned short j = 0; j < current[1]; j++)
		{
			if (current[j + 2] == target)
			{
				printf("%hu\n", 1);//只要能访问到target即可认为其他都能访问到，直接退出
				return 1;
			}
			if (!a[current[j+2]])
			{
				a[current[j+2]] = 1;
				q.push(nodes[current[j + 2]]);
			}
		}
	}
	printf("%hu\n", 0);//否则输出0
	return 0;
}
int main()
{
	unsigned short N=0, M=0;//节点总数和破坏的通道数
	scanf("%hu", &N);
	scanf("%hu", &M);
	unsigned short** nodes = new unsigned short*[N];
	unsigned short* nodesVisit = new unsigned short[N];//计算每个节点有多少条通道指向它
	memset(nodesVisit, 0, sizeof(nodesVisit));//全部赋为0
	for (int i = 0; i < N; i++)
	{
		unsigned short n = 0;
		unsigned short m = 0;
		scanf("%hu", &n);
		nodes[i] = new unsigned short[n+2];
		nodes[i][0] = i;//存储编号
		nodes[i][1] = n;//存储引出的通道数
		for (unsigned short j = 0; j < n; j++)
		{
			scanf("%hu", &m);
			nodes[i][j+2] = m;
			nodesVisit[m]++;//通道数加1
		}
	}
	if (BFS(nodes, N) == 0)//如果不能遍历，全部输出0
	{
		for (int j = 0; j < M; j++)
		{
			printf("%hu\n", 0);
		}
		return 0;
	}
	for (unsigned short i = 0; i < M; i++)
	{
		unsigned short p = 0, q = 0;
		scanf("%hu %hu", &p, &q);
		if (nodesVisit[q] >= 2 )//如果有大于1条通道
		{
			unsigned short str = 0;
			unsigned short sum = nodes[p][1];
			while (str < sum && nodes[p][str + 2] != q)
			{
				str++;
			}
			nodes[p][str + 2] = 0;
			BFS(nodes, N, q);
			nodes[p][str + 2] = q;
		}
		else//否则直接输出0
		{
			printf("%d\n", 0);
		}		
	}
	return 0;
}
