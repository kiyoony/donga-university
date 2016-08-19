#include <stdio.h>
#define MAX 50001
int n, m;

int head[MAX];
int color[MAX];
int parent[MAX];
int count[31];
int findAct(int index,int neg) // 최고 조상을 찾아줌
{
	while (head[index])
	{
		if (head[index] == neg)return 0;
		else index = head[index];
	}

	return index;
}
int checkAct(int index, int other)
{
	for (int i = 0; i <= n; i++) { parent[i] = 0; }
	int step = 1;
	while (head[index])
	{
		if (head[index] == other)return 0; // 경로 상에 다른 비교대상이 존재함
		parent[head[index]] = step++;
		index = head[index];
	}
	return index; //최고 조상 리턴
}
void paint(int index, int target,int what)
{
	while (index != target)
	{
		color[index] = what;
		index = head[index];
	}
}
int get(int start, int end) // edge 갯수 리턴
{
	int cnt = 0;
	while(start!= end)
	{
		cnt++;
		count[color[start]] = 1;
		start = head[start];
	}
	return cnt;
}
int main()
{
	FILE *inp = fopen("p11994.inp", "r");
	FILE *out = fopen("p11994.out", "w");
	int i, j,type,x,y,c;
	int existX,existY;
	fscanf(inp, "%d %d", &n, &m);

	for (i = 1; i <= n; i++)
	{
		fscanf(inp, "%d", &head[i]);
	}
	for (i = 1; i <= n; i++)
	{
		fscanf(inp, "%d", &color[i]);
	}
	for (i = 0; i < m; i++)
	{
		fscanf(inp, "%d", &type);
		if (type == 1)
		{
			fscanf(inp, "%d %d %d", &x, &y, &c);
			if (x != y)
			{
				existX = findAct(y,x);
				if (existX) // x isn't y ancestor
				{
					head[x] = y;
					color[x] = c;
				}

			}
		}
		else if (type == 2)
		{
			fscanf(inp, "%d %d %d", &x, &y, &c);
			existY = findAct(x, y);
			if (existY) //y는 x의 조상이 아님
			{
				existX = checkAct(y, x); // x가 y의 조상인가?
				if (existX) // x 도 y의 조상이 아님
				{
					if (existX == existY) // 공통 조상을 가지고 있다 ( 만난다 )
					{
						int index = x , meetP;
						while (!parent[index])
						{
							index = head[index];
						}
						meetP = index; //만나는 지점
						paint(x, meetP, c);
						paint(y, meetP, c);
						
					}
					else // 만나지 않는다
					{
						//ignore
					}
				}
				else //x는 y의 조상
				{
					int index = y;
					while (1) {
						color[index] = c;
						if (head[index] == x)break;
						index = head[index];
					}
				}
			}
			else // y는 x의 조상
			{
				int index = x;
				while (1) {
					color[index] = c;
					if (head[index] == y)break;
					index = head[index];
				}
			}
		}
		else // type == 3
		{
			int edgeX, edgeY, colorCnt;
			edgeX = edgeY = colorCnt = 0;
			for (j = 0; j <= 30; j++) { count[j] = 0; }
			fscanf(inp, "%d %d", &x, &y);
		
			existX = findAct(y, x);
			if (existX)
			{
				existY = checkAct(x, y);
				if (existY)
				{
					if (existX == existY)
					{
						int index = y, meetP;
						while (!parent[index]) {
							index = head[index];
						}
						meetP = index;
						edgeX = get(x, meetP);
						edgeY = get(y, meetP);
					}
					else // 만나지 않음
					{
						//
					}
				}
				else //y는 x의 조상
				{
					//x -> y 까지 색 갯수 , 엣지 갯수
					edgeX = get(x, y);
				}
			}
			else // 존재함
			{
				//y - > x 까지 색 갯수, 엣지 갯수
				edgeY = get(y, x);
			}
			for (j = 0; j <= 30; j++) {
				if (count[j])colorCnt++;
			}
			fprintf(out, "%d %d\n", edgeX + edgeY, colorCnt);
		}
	}
	return 0;
}