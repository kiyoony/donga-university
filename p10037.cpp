#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int arr[5000];
int main()
{
	FILE *inp = fopen("p10037.inp", "r");
	FILE *out = fopen("p10037.out", "w");
	int testcase;
	int iCount = 0;
	int i;
	fscanf(inp, "%d", &testcase);

	for (iCount = 0; iCount < testcase; iCount++)
	{
		/*int p[5000][2], pl = 0;
		int back[5000] = { 0, };*/
		fscanf(inp, "%d", &n);
		for (i = 0; i < n; i++)
		{
			fscanf(inp, "%d", &arr[i]);
		}
		sort(arr, arr + n);
		int sum = 0;
		while (n > 3)
		{
			if (2 * arr[1] < +arr[n - 2] + arr[0])
			{
				sum += arr[0] + 2 * arr[1] + arr[n - 1];
				/*p[pl][0] = arr[0];
				p[pl][1] = arr[1];
				back[pl] = arr[0];
				pl++;
				p[pl][0] = arr[n - 2];
				p[pl][1] = arr[n - 1];
				back[pl] = arr[1];
				pl++;*/
			}
			else
			{
				sum += arr[n - 1] + arr[n - 2] + 2 * arr[0];
				/*p[pl][0] = arr[0];
				p[pl][1] = arr[n - 2];
				back[pl] = arr[0];
				pl++;
				p[pl][0] = arr[0];
				p[pl][1] = arr[n - 1];
				back[pl] = arr[0];
				pl++;*/
			}
			n = n - 2;
		}
		//n == 3 || n == 2
		if (n == 3) // n - > 2
		{
			/*p[pl][0] = arr[0];
			p[pl][1] = arr[n-1];
			back[pl] = arr[0];
			pl++;*/
			sum += arr[n - 1] + arr[0];
			n--;
		}
		if (n == 2)
		{
			/*p[pl][0] = arr[0];
			p[pl][1] = arr[1];*/
			sum += arr[1];
			/*pl++;*/
			fprintf(out, "%d\n", sum);
			/*for (i = 0; i < pl; i++)
			{
				fprintf(out, "%d %d\n", p[i][0], p[i][1]);
				if (i != pl - 1)
					fprintf(out, "%d\n", back[i]);
			}*/
		}
		else// n == 1
		{
			fprintf(out, "%d\n", arr[0]);
		}

	}
	return 0;
}