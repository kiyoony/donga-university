#include <stdio.h>
#define mod 10000007
long long int arr[26][26][26];

int main()
{
	FILE *inp = fopen("queue.inp", "r");
	FILE *out = fopen("queue.out", "w");
	int n, l, r, i, j, k;

	for (i = 1; i <= 25; i++)
	{
		arr[i][i][1] = 1;
		arr[i][1][i] = 1;
	}

	for (i = 2; i <= 25; i++)
		for (j = 1; j <= i; j++)
			for (k = 1; k <= i; k++)
				arr[i][j][k] = (arr[i - 1][j][k] * (i - 2) + arr[i - 1][j - 1][k] + arr[i - 1][j][k - 1]) % mod;


	int iCount;
	int testcase;
	fscanf(inp, "%d", &testcase);
	for (iCount = 0; iCount < testcase; iCount++)
	{
		fscanf(inp,"%d %d %d", &n, &l, &r);
		fprintf(out,"%lld\n", arr[n][l][r]);
	}

	return 0;
}