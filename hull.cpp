#include <stdio.h>
typedef struct Node {
	int x;
	int y;
}Node; // 좌표
Node arr[20000];
int check[20000];
int selected[20000];
int cal(Node a, Node b, Node c)// 3개의 점
{
	return (a.x*b.y) + (b.x * c.y) + (c.x* a.y) - (a.y*b.x) - (b.y*c.x) - (c.y * a.x);
}//return 값이 음수 => 진행방향 오른쪽 , 0 => 평행  , 양수 =>진행방향 왼쪽
int abs(int a, int b)
{
	return a > b ? a - b : b - a;
}
int main()
{
	FILE *inp = fopen("hull.inp", "r");
	FILE *out = fopen("hull.out", "w");
	int n, i;
	int result = 0;
	fscanf(inp, "%d", &n);
	int index = 0, count = 0, sec, p, fir, chk = 0;
	for (i = 0; i < n; i++)
	{
		fscanf(inp, "%d %d", &arr[i].x, &arr[i].y);
		if (arr[index].x > arr[i].x)
		{
			index = i;
		}
		else if (arr[index].x == arr[i].x && arr[index].y > arr[i].y) {
			index = i;
		}
		check[i] = 0;
	}
	selected[count++] = index; // 첫번째 점
	check[index] = 1;
	fir = index;
	chk = 1;
	while (chk < n)
	{
		sec = -1;               //두번째 점
		for (i = 0; i < n; i++)
		{
			if (!check[i])
			{
				if (sec < 0)
				{
					sec = i;
				}
				else
				{
					p = cal(arr[index], arr[sec], arr[i]);
					if (p < 0)// 유망하다
					{
						sec = i;
					}
					else if (p == 0)// 직선상에 있음  => 가까이 있는 것을 버림
					{
						if (abs(arr[index].x, arr[i].x) > abs(arr[index].x, arr[sec].x) ||
							abs(arr[index].y, arr[i].y) > abs(arr[index].y, arr[sec].y))
						{
							check[sec] = 1;
							sec = i;
							chk++;
						}
						else
						{
							check[i] = 1;
							chk++;
						}
					}
					else {} // 버림
				}
			}
		}
		if (count > 2 || chk == n)
		{
			p = cal(arr[index], arr[sec], arr[fir]);
			if (p <= 0)//처음 점으로 선을 이어야함
			{
				if (p == 0) // 직선일 경우
				{
					if (abs(arr[index].x, arr[sec].x) < abs(arr[index].x, arr[fir].x) ||
						abs(arr[index].y, arr[sec].y) < abs(arr[index].y, arr[fir].y))
					{
						break;
					}
				}
				break;
			}
		}
		selected[count++] = sec;
		chk++;
		check[sec] = 1;
		index = sec;
	}
	fprintf(out, "%d\n", count);
	for (i = 0; i < count; i++)
	{
		fprintf(out, "%d %d\n", arr[selected[i]].x, arr[selected[i]].y);
	}
	return 0;
}