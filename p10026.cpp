#include <stdio.h>
#include <algorithm>
using namespace std;
typedef struct node {
	double per;
	int index;
}node;
bool comp(node a, node b)
{
	if (a.per < b.per)
		return false;
	else if (a.per == b.per)
	{
		if (a.index < b.index)
			return true;
		else
			return false;
	}
	else
		return true;
}
int main()
{
	FILE *inp = fopen("p10026.inp", "r");
	FILE *out = fopen("p10026.out", "w");
	int testcase;
	int iCount = 0;
	int a, b;
	int n;
	fscanf(inp, "%d", &testcase);
	node arr[1001];
	for (iCount = 0; iCount < testcase; iCount++)
	{
		if (iCount)fprintf(out, "\n");
		fscanf(inp, "%d", &n);

		for (int i = 0; i < n; i++)
		{
			fscanf(inp, "%d %d", &a, &b);
			arr[i].index = i + 1;
			arr[i].per = (double)b/(double)a;
		}
		sort(arr, arr + n, comp);
		for (int i = 0; i < n; i++)
		{
			fprintf(out, "%d ", arr[i].index);
		}

	}
}