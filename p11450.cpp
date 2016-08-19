#include <stdio.h>
#define INF 987654321
using namespace std;
#include <algorithm>
int n, m;
int length[20];
int arr[20][20];
int dp[20][20][2]; //최대 최소
int result;
bool compare(int a, int b)
{
	return a > b;
}
int f(int step,int sum,int type)
{
	int i = 0;
	if (type && dp[step][0][0] && sum + dp[step][0][0] <= result)return sum + dp[step][0][0];
	if (!type&& dp[step][length[step] - 1][1] && sum + dp[step][length[step] - 1][1] > m)return sum + dp[step][length[step]-1][1];
	if (step == n)
	{
		return sum;
	}
	for (i = 0; i < length[step]; i++)
	{
		dp[step][i][0] = f(step + 1, sum + arr[step][i], 0);
		dp[step][i][1] = f(step + 1, sum + arr[step][i], 1);
		for (int j = 0; j < 2; j++)
		{
			if (dp[step][i][j] <= m)
				result = result > dp[step][i][j] ? result : dp[step][i][j];
		}
	}
	if (type)
		return dp[step][0][0];
	else
		return dp[step][length[step] - 1][1];
}
int main()
{
	FILE *inp = fopen("p11450.inp", "r");
	FILE *out = fopen("p11450.out", "w");
	int testcase;
	int iCount = 0;
	int i, j, k;
	fscanf(inp, "%d", &testcase);

	for (iCount = 0; iCount < testcase; iCount++)
	{
		fscanf(inp, "%d %d", &m, &n);
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				dp[i][j][0] = dp[i][j][1] = 0;
			}
		}
		result = 0;
		for (i = 0; i < n; i++)
		{
			fscanf(inp, "%d", &k);
			for (j = 0; j < k; j++)
			{
				fscanf(inp, "%d", &arr[i][j]);
			}
			length[i] = k;
			sort(arr[i], arr[i] + k,compare); //열 정렬
		}
		f(0, 0,0);
		if (result)
			fprintf(out, "%d\n", result);
		else
			fprintf(out, "no solution\n");
	}
}