#include <stdio.h>
#define MAX 5001
int N, P, M,target;
int medic[100];//ºÀ»ç ±â°£ÀÇ ºÀ»ç Áö¿ª °¹¼ö
int connection[MAX][MAX];
int weight[MAX][MAX];
int check[MAX];
int head[MAX];
int give(int week, int place)
{
	int index = 0;
	for (int i = 0; i < P; i++)
	{
		if (week == i+1) {
			index += place;
			break;
		}
		else {
			index += medic[i];
		}
	}
	return N + index;
}
int f(int index,int step)
{
	int flag = 0;
	check[index] = step;
	for (int i = 0; i < head[index]; i++)
	{
		int p = connection[index][i];
		if (check[p] != step && weight[index][p])
		{
			if (p == target)flag = 1;
			else {
				flag = f(p, step);
			}
			if (flag) {
				weight[index][p]--;
				weight[p][index]++;
				break;
			}
		}
	}
	return flag;
}
int main()
{
	int iCount, testcase, i, j;
	FILE *inp = stdin;
	FILE *out = stdout;
	setbuf(stdout, NULL);
	fscanf(inp, "%d", &testcase);
	for (iCount = 0; iCount < testcase; iCount++)
	{
		fprintf(out, "Case #%d\n", iCount + 1);
		fscanf(inp, "%d %d %d", &N, &P, &M);
		target = N+1;
		for (i = 0; i < P; i++)
		{
			fscanf(inp, "%d", &medic[i]);
			target += medic[i];
		}
		for (i = 0; i <= target; i++)
		{
			check[i] = head[i] = 0;
		}
		for (i = 0; i < N; i++)
		{
			connection[0][head[0]++] = i + 1;
			weight[0][i + 1] = M;
			int cnt;
			fscanf(inp, "%d", &cnt);
			for (j = 0; j < cnt; j++)
			{
				int week, place;
				fscanf(inp, "%d %d", &week, &place);
				int p = give(week, place);
				connection[i + 1][head[i+1]++] = p;
				weight[i + 1][p] = 1;
				connection[p][head[p]++] = target;
				weight[p][target] = 1;
			}
		}
		int sum = 0, flag = 0,step = 1;
		while (1)
		{
			flag = f(0, step++);
			if (!flag)break;
			else {
				sum += 1;
			}
		}
		if (sum == target - N-1)
			fprintf(out, "1\n");
		else
			fprintf(out, "0\n");
	}
	return 0;
}