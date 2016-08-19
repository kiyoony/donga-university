#include <stdio.h>
#define MAX 10000
#define INF 987654321
int weight[MAX][MAX];
int connection[MAX][MAX];
int head[MAX];
int check[MAX];
int n,sum;
int MIN(int a, int b)
{
	return a < b ? a : b;
}
int f(int index,int min,int step)
{
	int flag = 0;
	check[index] = step;
	for (int i = 0; i < head[index]; i++)
	{
		int p = connection[index][i];
		if (check[p]!=step && weight[index][p])
		{
			int buf;
			flag = 0;
			buf = MIN(weight[index][p], min);
			if (p == n - 1)flag = buf;
			else
			{
				flag = f(p, buf,step);
			}
			if (flag)
			{
				weight[index][p] -= flag;
				weight[p][index] += flag;
				break;
			}
		}
	}
	return flag;
}
int main()
{
	FILE *inp = fopen("flow.inp", "r");
	FILE *out = fopen("flow.out", "w");
	int i, j, k;
	fscanf(inp, "%d", &n);
	while (1)
	{
		fscanf(inp, "%d %d %d", &i, &j, &k);
		if (i < 0)break;
		connection[i][head[i]++] = j;
		weight[i][j] = k;
		connection[j][head[j]++] = i;
		weight[j][i] = k;
	}
	int step = 1;
	while (1)
	{
		int flag = f(0, INF,step++);
		if (flag)
			sum += flag;
		else
			break;
	}
	fprintf(out,"%d\n", sum);
	return 0;
}