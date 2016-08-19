#include <stdio.h>
char arr[52][52];
int n, m;
int length(char *x)
{
	int index = 0;
	while (x[index] != '\0')
	{
		if (x[index] < 'a')
		{
			x[index] = x[index] - 'A' + 'a';
		}
		index++;
	}
	return index;
}
int check(int x, int y, char *target, int l)
{
	int i, j;
	int grid[8][2] = { {0,1},{1,1}, {1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };
	for (int k = 0; k < 8; k++)
	{
		for (i = 0; i < l; i++)
		{
			if (target[i] != arr[x + grid[k][0]*i][y + grid[k][1]*i])break;
		}
		if (i == l)return 1;
	}
	return 0;
}
int main()
{
	FILE *inp = fopen("p10010.inp", "r");
	FILE *out = fopen("p10010.out", "w");
	int testcase;
	int iCount = 0;
	int i, j,k;
	char Text[52];
	fscanf(inp, "%d", &testcase);

	for (iCount = 0; iCount < testcase; iCount++)
	{
		if (iCount)fprintf(out, "\n");
		fscanf(inp, "%d %d\n", &n, &m);
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= m; j++)
			{
				fscanf(inp, "%c", &arr[i][j]);
				if (arr[i][j] < 'a') // 대문자 일 때
				{
					arr[i][j] = arr[i][j] - 'A' + 'a';
				}
			}
			fscanf(inp, "\n");
		}
		for (i = 0; i <= n + 1 ; i++)
		{
			arr[i][0] = arr[i][m+1] = '.';
		}
		for (i = 0; i <= m + 1; i++)
		{
			arr[0][i] = arr[0][n + 1] = '.';
		}
		fscanf(inp, "%d", &k);
		for (k; k > 0; k --)
		{
			fscanf(inp, "%s", Text);
			int l = length(Text);
			int flag = 0;
			for (i = 1; i <= n; i++)
			{
				for (j = 1; j <= m; j++)
				{
					if (check(i, j, Text, l))
					{
						fprintf(out, "%d %d\n", i, j);
						flag = 1;
						break;
					}
				}
				if (flag)break;
			}
		}
	}
	return 0;
}