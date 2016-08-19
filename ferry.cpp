#include <stdio.h>
int arr[200];
int selected[200];
int dp[10001][2];//
int number[10001];
int max = 0;
int abs(int a, int b)
{
	return a > b ? a - b : b - a;
}
int main()
{
	FILE *inp = fopen("ferry.inp", "r");
	FILE *out = fopen("ferry.out", "w");
	int testcase;
	int iCount = 0;
	int cost, n,i,cLength;
	fscanf(inp, "%d", &testcase);

	for (iCount = 0; iCount < testcase; iCount++)
	{
		fscanf(inp, "%d", &cost);
		cost = cost * 100;
		cLength = n = 0;
		while (1)
		{
			fscanf(inp, "%d", &arr[n]);
			if (!arr[n])break;
			else {
				selected[n] = 0;
				n++;
			}

		}
		for (i = 0; i <= cost; i++) { dp[i][0] = dp[i][1] = -1; }
		max = dp[0][0] = 0;
		for (i = 0; i < n; i++)
		{
			cLength += arr[i];
			if (cLength <= 2 * cost)
			{									//k를 쓰고 나머지가 cost보다 작아야함
				for (int k = cost; k >= arr[i] && cLength - k <= cost; k--) //길이가 k일 때 최대 갯수,길이 저장
				{
					if (dp[ k-arr[i] ][0] != -1) {
						dp[k][0] = i+1;
						dp[k][1] = k - arr[i]; // 어느길이에서 왔는지
						number[k] = dp[k-arr[i]][0]; // 어느번호에서 왔는지
						if (dp[max][0] < dp[k][0]) {
							max = k;
						}
						else if (dp[max][0] == dp[k][0] && abs(max, cLength-max) > abs(k, cLength-k)) {
							max = k;
						}
					}
				}
			}
		}
		fprintf(out, "%d\n", dp[max][0]);
	}
	return 0;
}