#include <stdio.h>
int n, m;
long long int arr[301];
long long int dp[301][301];
int main()
{
	FILE *inp = fopen("p00911.inp", "r");
	FILE *out = fopen("p00911.out", "w");
	int testcase;
	int iCount = 0;
	int i = 0, j = 0;
	for (i = 0; i < 301; i++) {
		dp[0][i] = dp[i][0] = 1;
	}
	for (i = 1; i < 301; i++)
	{
		for (j = 1; j < 301; j++)
		{
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	while (fscanf(inp, "%d %d", &n, &m) != EOF)
	{
		long long int result = 1,sum = 0;
		for (i = 0; i < m; i++)
		{
			fscanf(inp, "%lld", &arr[i]);
			sum += arr[i];
			if (i)
			{
				result *= dp[sum-arr[i]][arr[i]];
			}
		}
		fprintf(out,"%lld\n", result);

	}
	return 0;
}