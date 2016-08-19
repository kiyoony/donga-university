#include <stdio.h>
int arr[1001][1001];
int reverse[1001][1001];
int rhead[1001];
int head[1001];
int check[1001];
int group[1001];
char people[1001][25];
int number[1001];
char A[25];
int n,m;
int Ncnt;
int who()
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; people[i][j] != '\n'; j++)
		{
			if (people[i][j] != A[j])break;
		}
		if (people[i][j] == '\n')return i;
	}
	return 0;
}
void scc(int index)
{
	check[index] = 1;
	for (int i = 0; i < head[index]; i++)
	{
		int p = arr[index][i];
		if (!check[p])scc(p);
	}
	number[Ncnt++] = index;
}
void grouping(int index)
{
	group[index] = 1;
	for (int i = 0; i < rhead[index]; i++)
	{
		int p = reverse[index][i];
		if (!group[p])grouping(p);
	}
}
int main()
{
	FILE *inp = fopen("p11709.inp", "r");
	FILE *out = fopen("p11709.out", "w");
	int i,j,x,y;

	while(1)
	{
		fscanf(inp, "%d %d\n", &n, &m);
		if (!n && !m)break;
		Ncnt = 0;
		for (i = 0; i < n; i++)
		{
			fgets(people[i], 25, inp);
			check[i+1] = rhead[i+1] = head[i+1] = group[i+1] = 0;
			for (j = 1; j <= n; j++)
			{
				reverse[i+1][j] = arr[i + 1][j] = 0;
			}
		}
		for (i = 0; i < m; i++)
		{
			fgets(A, 25, inp);
			x = who();
			fgets(A, 25, inp);
			y = who();
			arr[x+1][head[x+1]++] = y+1; // x 는 y를 신뢰함
			reverse[y + 1][rhead[y + 1]++] = x + 1; //역으로 갈 때
		}
		for (i = 1; i <= n; i++)
		{
			if (!check[i])scc(i);
		}
		int result = 0;
		for (i = 0; i < n; i++)
		{
			if (!group[number[n-i-1]])
			{
				grouping(number[n-i-1]);
				result++;
			}
		}
		fprintf(out, "%d\n", result);
	}
	return 0;
}