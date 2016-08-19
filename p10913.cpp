#include <stdio.h>
#define INF -987654321
int n, k;
int max(int a, int b)
{
	return a > b ? a : b;
}
int main()
{
	FILE *inp = fopen("p10913.inp", "r");
	FILE *out = fopen("p10913.out", "w");
	int iCount = 0;
	int i, j , p , q;


	for (iCount = 0;; iCount++)
	{
		int arr[76][76];
		int dp[76][77][3][6]; // (x , y) 0-위쪽 1-왼쪽 2-오른쪽 ,음수를 지난 횟수
		int flag[76][77][3][6] = { 0, };
		int minus = 0;
		fscanf(inp,"%d %d", &n, &k);
		if (!n && !k)break;

		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				fscanf(inp,"%d", &arr[i][j]);
			}
		}
		for (i = 1; i <= n; i++)
		{
			for (j = 0; j <= n+1; j++)
			{
				for (p = 0; p < 3; p++)
				{
					for (q = 0; q < 6; q++)
					{
						dp[i][j][p][q] = INF;
					}
				}
			}
		}
		minus = arr[1][1] < 0 ? 1 : 0;
		dp[1][1][0][minus] = dp[1][1][1][minus] = dp[1][1][2][minus] = arr[1][1];
		flag[1][1][0][minus] = flag[1][1][1][minus] = flag[1][1][2][minus] = 1;
		
		for (i = 2; i <= n; i++) // 첫줄 왼쪽에서 오는 것
		{
			minus = arr[1][i] < 0 ? 1 : 0;
			for (p = 0; p <= 5-minus; p++)
			{
				if (flag[1][i - 1][1][p])
				{
					flag[1][i][1][p + minus] = 1;
					dp[1][i][1][p + minus] = max(dp[1][i][1][p + minus], dp[1][i - 1][1][p] + arr[1][i]);
				}
			}
		}
		for (i = 2; i <= n; i++)
		{
			for (j = 1; j <= n; j++) // 위쪽 처리
			{
				minus = arr[i][j] < 0 ? 1 : 0;
				for (p = 0; p <= 5 - minus; p++)
				{
					for (q = 0; q < 3; q++)
					{
						if (flag[i - 1][j][q][p])
						{
							flag[i][j][0][p + minus] = 1;
							dp[i][j][0][p + minus] = max(dp[i][j][0][p + minus], dp[i - 1][j][q][p] + arr[i][j]);
						}
					}
				}
			}
			for (j = 2; j <= n; j++) // 왼쪽
			{
				minus = arr[i][j] < 0 ? 1 : 0;
				for (p = 0; p <= 5 - minus; p++)
				{
					for (q = 0; q < 2; q++)
					{
						if (flag[i][j - 1][q][p])
						{
							flag[i][j][1][p + minus] = 1;
							dp[i][j][1][p + minus] = max(dp[i][j][1][p + minus], dp[i][j - 1][q][p] + arr[i][j]);
						}
					}
				}
			}
			for (j = n-1; j >= 1; j--) // 오른쪽
			{
				minus = arr[i][j] < 0 ? 1 : 0;
				for (p = 0; p <= 5 - minus; p++)
				{
					for (q = 0; q < 2; q++)
					{
						if (flag[i][j + 1][ q * 2 ][p])
						{
							flag[i][j][2][p + minus] = 1;
							dp[i][j][2][p + minus] = max(dp[i][j][2][p + minus], dp[i][j + 1][q * 2][p] + arr[i][j]);
						}
					}
				}
			}
		}
		int result = INF, f = 0;

		for (p = 0; p <= k; p++)
		{
			for (q = 0; q < 2; q++)
			{
				if (flag[n][n][q][p])
				{
					f = 1;
					result = max(result, dp[n][n][q][p]);
				}
			}
		}

		if (f)
			fprintf(out,"Case %d: %d\n", iCount + 1, result);
		else
			fprintf(out,"Case %d: impossible\n", iCount + 1);
	}
	return 0;
}