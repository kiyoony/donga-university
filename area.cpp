#include <stdio.h>
#include <math.h>
typedef struct Node
{
	int x, y, r;
}Node;
Node arr[3];
typedef struct Con
{
	double x, y;
}Con;
double point[2][2];
int zero;
Con result[3];
double distance(double a, double b)
{
	return a > b ? a - b : b - a;
}
void calc(double a, double b, double r, double c, double d, double s)
{
	double e = c - a;
	double f = d - b;
	double p = sqrt(e * e + f * f);
	double k = (p * p + r * r - s * s) / (2 * p);
	if (r >= k)
	{
		double x1 = a + (e * k) / p + (f / p) * sqrt(r * r - k * k);
		double y1 = b + (f * k) / p - (e / p) * sqrt(r * r - k * k);
		double x2 = a + (e * k) / p - (f / p) * sqrt(r * r - k * k);
		double y2 = b + (f * k) / p + (e / p) * sqrt(r * r - k * k);
		point[0][0] = x1, point[0][1] = y1;
		point[1][0] = x2, point[1][1] = y2;
	}
	else
	{
		zero = 1;
	}
}
double ret(double x, double y)
{
	return sqrt(x*x + y*y);
}
double cal(Con a, Con b, Con c)// 3개의 점
{
	return (a.x*b.y) + (b.x * c.y) + (c.x* a.y) - (a.y*b.x) - (b.y*c.x) - (c.y * a.x);
}//return 값이 음수 => 진행방향 오른쪽 , 0 => 평행  , 양수 =>진행방향 왼쪽
int main()
{
	FILE *inp = fopen("area.inp", "r");
	FILE *out = fopen("area.out", "w");
	int testcase;
	int iCount = 0;
	int i;
	fscanf(inp, "%d", &testcase);
	for (iCount = 0; iCount < testcase; iCount++)
	{
		for (i = 0; i < 3; i++)
		{
			fscanf(inp, "%d %d %d", &arr[i].x, &arr[i].y, &arr[i].r);
		}
		for (i = 0; i < 3; i++)
		{
			zero = 0;
			int flag = 0;
			calc(arr[i].x, arr[i].y, arr[i].r, arr[(i + 1) % 3].x, arr[(i + 1) % 3].y, arr[(i + 1) % 3].r);

			if (!zero)
			{
				if (ret(distance(point[0][0], arr[(i + 2) % 3].x), distance(point[0][1], arr[(i + 2) % 3].y)) <
					ret(distance(point[1][0], arr[(i + 2) % 3].x), distance(point[1][1], arr[(i + 2) % 3].y)))
				{
					flag = 0;
				}
				else
				{
					flag = 1;
				}
				result[i].x = point[flag][0], result[i].y = point[flag][1];
			}
			else
				break;
		}
		if (!zero)
			fprintf(out, "%.2lf\n", cal(result[0], result[1], result[2]) / 2);
		else
			fprintf(out, "0.00\n");
	}
	return 0;
}