#include <stdio.h>
int arr[102][102];
int n, m;
void f(int x, int y)
{
	int fill[3] = { -1,0,1 };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[x + fill[i]][y + fill[j]] ++;
		}
	}
}
int main()
{
	FILE *inp = fopen("p10189.inp", "r");
	FILE *out = fopen("p10189.out", "w");

	int n, m, i, j,index = 1;
	char Text[101];
	while (1)
	{
		fscanf(inp,"%d %d", &n, &m);
		if (n&&m)
		{
			fprintf(out,"Field #%d:\n",index++);
			for (i = 0; i <= n + 1; i++) {
				for (j = 0; j <= m + 1; j++) { arr[i][j] = 0; }
			}
			for (i = 0; i < n; i++)
			{
				fscanf(inp,"%s", Text);
				for (j = 0; j < m; j++)
				{
					if (Text[j] == '*')
					{
						arr[i + 1][j + 1] = -10;
						f(i + 1, j + 1);
					}
				}
			}
			for (i = 1; i <= n; i++)
			{
				for (j = 1; j <= m; j++)
				{
					if (arr[i][j] < 0)fprintf(out, "*");
					else fprintf(out, "%d", arr[i][j]);
				}
				fprintf(out,"\n");
			}
			fprintf(out,"\n");
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
