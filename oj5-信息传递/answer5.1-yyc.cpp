#include"stdio.h"
#include"queue"
#include"cstring"

#pragma warning(disable:4996)

int BFS(unsigned short** nodes, unsigned short N)
{
	std::queue<unsigned short*> q;
	q.push(nodes[0]);
	unsigned short sss = 0;
	nodes[0][2] = 1;
	sss++;
	while (!q.empty()) 
	{
		unsigned short* current = q.front();
		q.pop();
		for (unsigned short j = 0; j < current[1]; j++)
		{
			if (!nodes[current[j+3]][2])
			{
				nodes[current[j + 3]][2] = 1;
				q.push(nodes[current[j + 3]]);
				sss++;
			}
		}
	}
	if (sss == N)
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

int BFSp(unsigned short** nodes, unsigned short N,unsigned short target)
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
			if (current[j + 3] == target)
			{
				printf("%hu\n", 1);
				return 1;
			}
			if (!a[current[j+3]])
			{
				a[current[j+3]] = 1;
				q.push(nodes[current[j + 3]]);
			}
		}
	}
	printf("%hu\n", 0);
	return 0;
}
int main()
{
	unsigned short N=0, M=0;
	scanf("%hu", &N);
	scanf("%hu", &M);
	unsigned short** nodes = new unsigned short*[N];
	unsigned short* nodesVisit = new unsigned short[N];
	memset(nodesVisit, 0, sizeof(nodesVisit));
	for (int i = 0; i < N; i++)
	{
		unsigned short n = 0;
		unsigned short m = 0;
		scanf("%hu", &n);
		nodes[i] = new unsigned short[n+3];
		nodes[i][0] = i;//存储编号
		nodes[i][1] = n;//存储下一个节点数量
		nodes[i][2] = 0;//存储是否访问过，0为否
		for (unsigned short j = 0; j < n; j++)
		{
			scanf("%hu", &m);
			nodes[i][j+3] = m;
			nodesVisit[m]++;
		}
	}
	if (BFS(nodes, N) == 0)
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
		if (nodesVisit[q] >= 2 || q == 0)
		{
			unsigned short str = 0;
			unsigned short sum = nodes[p][1];
			while (str < sum && nodes[p][str + 3] != q)
			{
				str++;
			}
			nodes[p][str + 3] = 0;
			BFSp(nodes, N,q);
			nodes[p][str + 3] = q;
		}
		else
		{
			printf("%d\n", 0);
		}
		
	}
	return 0;
}
