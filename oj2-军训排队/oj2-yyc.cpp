//用两个数组模拟双向链表


#include"stdio.h"
#pragma warning(disable:4996)

int main()
{
	int N = 0;
	int j = 0;
	int a[3] = { 0 };
	int next[100000] = { 0 };
	int prev[100000] = { 0 };
	next[0] = 1;
	prev[0] = -1;
	next[1] = -1;
	prev[1] = 0;
	scanf("%d", &N);
	while (N--)
	{
		scanf("%d", &a[0]);
		switch (a[0])
		{
		case 1:
			scanf("%d %d", &a[1], &a[2]);
			if (next[a[1]] == -1)
			{
				next[a[1]] = a[2];
				prev[a[2]] = a[1];
				next[a[2]] = -1;
			}
			else
			{
				next[a[2]] = next[a[1]];
				prev[next[a[1]]] = a[2];
				next[a[1]] = a[2];
				prev[a[2]] = a[1];
			}
			break;
		case 2:
			scanf("%d", &a[1]);
			if (next[a[1]] == -1)
				j = 0;
			else
				j = next[a[1]];
			printf("%d\n", j);
			break;
		case 3:
			scanf("%d", &a[1]);
			if (next[a[1]] == -1)
			{
				next[prev[a[1]]] = -1;
				next[a[1]] = 0;
				prev[a[1]] = 0;
			}
			else
			{
				next[prev[a[1]]] = next[a[1]];
				prev[next[a[1]]] = prev[a[1]];
				prev[a[1]] = 0;
				next[a[1]] = 0;
			}		
			break;
		}
	}
	int i = next[0];
	while (i != -1)
	{
		printf("%d\n", i);
		i = next[i];
	}
	return 0;
}
