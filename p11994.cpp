#include <stdio.h>
#define MAX 50001
int n, m;

int head[MAX];
int color[MAX];
int parent[MAX];
int count[31];
int findAct(int index,int neg) // �ְ� ������ ã����
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
		if (head[index] == other)return 0; // ��� �� �ٸ� �񱳴���� ������
		parent[head[index]] = step++;
		index = head[index];
	}
	return index; //�ְ� ���� ����
}
void paint(int index, int target,int what)
{
	while (index != target)
	{
		color[index] = what;
		index = head[index];
	}
}
int get(int start, int end) // edge ���� ����
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
			if (existY) //y�� x�� ������ �ƴ�
			{
				existX = checkAct(y, x); // x�� y�� �����ΰ�?
				if (existX) // x �� y�� ������ �ƴ�
				{
					if (existX == existY) // ���� ������ ������ �ִ� ( ������ )
					{
						int index = x , meetP;
						while (!parent[index])
						{
							index = head[index];
						}
						meetP = index; //������ ����
						paint(x, meetP, c);
						paint(y, meetP, c);
						
					}
					else // ������ �ʴ´�
					{
						//ignore
					}
				}
				else //x�� y�� ����
				{
					int index = y;
					while (1) {
						color[index] = c;
						if (head[index] == x)break;
						index = head[index];
					}
				}
			}
			else // y�� x�� ����
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
					else // ������ ����
					{
						//
					}
				}
				else //y�� x�� ����
				{
					//x -> y ���� �� ���� , ���� ����
					edgeX = get(x, y);
				}
			}
			else // ������
			{
				//y - > x ���� �� ����, ���� ����
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