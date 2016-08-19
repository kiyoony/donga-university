#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INF 10000
typedef struct Node {
	long long int x, y;
};
Node arr[10000];
Node outside[5];
Node target;
int tmp[4][2] = { {1,1},{-1,-1},{-1,1},{1,-1} };
int n, m;
long long int cal(Node a, Node b, Node c)// 3���� ��
{
	return (a.x*b.y) + (b.x * c.y) + (c.x* a.y) - (a.y*b.x) - (b.y*c.x) - (c.y * a.x);
}//return ���� ���� => ������� ������ , 0 => ����  , ��� =>������� ����
long long int abs(long long int a, long long int b)
{
	return a > b ? a - b : b - a;
}
double distance(Node a, Node b) // �� �������� �Ÿ��� ����
{
	return sqrt((abs(a.x, b.x) *abs(a.x, b.x)) + (abs(a.y, b.y) * abs(a.y, b.y)));
}
int main()
{
	FILE *inp = fopen("point.inp", "r");
	FILE *out = fopen("point.out", "w");

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			outside[i].x = (INF+rand()%INF) * tmp[i][j];
			outside[i].y = (INF+rand()%INF) * tmp[i][j];
		}
	}
	outside[4].x = (INF+rand()%INF) , outside[4].y = 5000; // �ܺ��� �� 5��
	fscanf(inp, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(inp, "%lld %lld", &arr[i].x,&arr[i].y);
	}
	fscanf(inp, "%d", &m);
	for (int i = 0; i < m; i++)
	{
		fscanf(inp, "%lld %lld", &target.x, &target.y);
		int cnt = 0;
		for (int k = 0; k < 5; k++)
		{
			int meet = 0,flag = 1;
			for (int j = 0; j < n; j++)
			{
				if (!cal(arr[j], arr[(j + 1) % n], target) && (distance(arr[j], target) <= distance(arr[j], arr[(j + 1)%n])))//������ ���� ���� ��
				{
					cnt++;
					flag = 0;
					break;
				}
				if ((cal(arr[j%n], arr[(j + 1) % n], outside[k]) * cal(arr[j%n], arr[(j + 1) % n], target) < 0 ) &&
					(cal(outside[k], target, arr[j%n]) * cal(outside[k], target, arr[(j + 1) % n]) < 0)) //(������ ���� ����)
					meet++;
			}
			if (meet & flag)//������ ���� ���� ���� Ƚ���� Ȧ�� �� ��
				cnt++;
		}
		fprintf(out, "%d\n", cnt > 2 ? 1 : 0);
	}
	return 0;
}