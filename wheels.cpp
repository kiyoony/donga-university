#include <stdio.h>
int goal;
int check[10000];
int ten[4] = { 1000,100,10,1 };
int Queue[10000];
int front, rear;
int input(FILE *inp)
{
	int temp, ret = 0;
	for (int i = 0; i < 4; i++) {
		fscanf(inp, "%d", &temp);
		ret += temp * ten[i];
	}
	return ret;
}
int change(int target,int index,int type)
{
	int arr[4] = { 0 }, i = 0,ret = 0;
	while (target)
	{
		arr[i] = target / ten[i];
		target = target - ten[i] * arr[i];
		i++;
	}
	if (type)
	{
		if (arr[index] == 9)arr[index] = 0;
		else arr[index]++;
	}
	else
	{
		if (arr[index] == 0)arr[index] = 9;
		else arr[index]--;
	}
	for (i = 0; i < 4; i++) {
		ret += arr[i] * ten[i];
	}
	return ret;
}
int main()
{
	FILE *inp = fopen("wheels.inp", "r");
	FILE *out = fopen("wheels.out", "w");
	int testcase;
	int iCount = 0;
	int n,m;
	fscanf(inp, "%d", &testcase);

	for (iCount = 0; iCount < testcase; iCount++)
	{
		int first = 0,temp,ban,index = 0;
		for (int i = 0; i < 10000; i++) { check[i] = 0; }
		front = rear = goal = 0;
		index = -1;
		first = input(inp);
		goal = input(inp);
		fscanf(inp, "%d", &m);
		for (int i = 0; i < m; i++)
		{
			ban = input(inp);
			check[ban] = -1;
		}
		Queue[rear++] = first;
		check[first] = -1;
		while (front != rear)
		{
			int cur = Queue[front++];
			if (cur == goal)
			{
				index = cur;
				break;
			}
			for (int i = 0; i < 4; i++)
			{
				int p = change(cur,i,1);
				int m = change(cur,i,0);
				if (!check[p])
				{
					Queue[rear++] = p;
					check[p] = check[cur] + 1;
				}
				if (!check[m])
				{
					Queue[rear++] = m;
					check[m] = check[cur] + 1;
				}
			}
		}
		fprintf(out, "%d\n", index < 0 ? index : (check[index]+1));
	}
	return 0;
}