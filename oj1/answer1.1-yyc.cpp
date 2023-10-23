#include <stdio.h>
#pragma warning (disable:4996)

int pow(int a, int n)
{
	int r = 1;
	for (int i = 0; i < n; i++)
	{
		r *= a;
	}
	return r;
}
int main()
{
	int N = 0;
	int number = 0;
	int result=0;
	scanf("%d", &N);
	int a[32] = { 0 };
	for (int j = 0; j < 3 * N - 1; j++)
	{
		scanf("%d", &number);
		for (int i = 0; i < 32; i++)
		{
			a[i] += (number >> i) & 1;
		}
	}
	for (int i = 0; i < 32; i++)
	{
		if (a[i] % 3 != 0)
		{
			result += pow(2, i);
		}
	}
	printf("%d", result);
}
