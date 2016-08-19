#include <stdio.h>
int arr[1001][1001];
int check[1001];
int n;
int selected[1001];
int cnt;
void f(int index, int type)
{
	check[index] = 1;
	for (int i = 0; i < n; i++)
	{
		if (!check[i] && (type ? arr[i][index] : arr[index][i]))
		{
			f(i, type);
		}
	}
	if (!type)
		selected[cnt++] = index;
}
int main()
{
	FILE *inp = fopen("scc.inp", "r");
	FILE *out = fopen("scc.out", "w");
	int testcase;
	int iCount = 0;
	int m;
	int x, y,result = 0;
	fscanf(inp, "%d %d", &n, &m);	
	for (int i = 0; i < m; i++)
	{
		fscanf(inp, "%d %d", &x, &y);
		arr[x][y] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		if (!check[i])f(i, 0);
	}
	for (int i = 0; i < n; i++) { check[i] = 0; }
	for (int i = 0; i < n; i++)
	{
		int p = selected[n - i - 1];
		if (!check[p])
		{
			result++;
			f(p, 1);
		}
	}
	fprintf(out, "%d", result);
	return 0;
}