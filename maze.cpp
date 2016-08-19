#include <stdio.h>
int n,m;
int arr[500][500];
int check[500][500];
int SelectVertex[500][2];
int cnt = 0;
int range(int i,int j)
{
	if(i >= 0 && i < n && j >= 0 && j < m )
		return 1;
	else
		return 0;
}
void insert(int i,int j)
{
	SelectVertex[cnt][0] = i;
	SelectVertex[cnt++][1] = j;
}
int f(int i,int j)
{
	int flag = 0;
	check[i][j] = 1; // 방문
	if(i == n - 1 && j == m - 1 )
	{
		insert(i,j);
		return 1;
	}
	if(range(i,j+1) && !check[i][j+1] && (arr[i][j]==1 || arr[i][j] == 3)) //  오른쪽
	{
		flag = f(i,j+1);
		if(flag)
		{
			insert(i,j);
			return 1;
		}
	}
	if(range(i+1,j) && !check[i+1][j] && arr[i][j]>=2) // 아래쪽
	{
		flag = f(i+1,j);
		if(flag)
		{
			insert(i,j);
			return 1;
		}
	}
	if(range(i,j-1) && !check[i][j-1] && (arr[i][j-1]==1 || arr[i][j-1]==3)) // 왼쪽
	{
		flag = f(i,j-1);
		if(flag)
		{
			insert(i,j);
			return 1;
		}
	}
	if(range(i-1,j) && !check[i-1][j] && arr[i-1][j] >=2) // 위쪽
	{
		flag = f(i-1,j);
		if(flag)
		{
			insert(i,j);
			return 1;
		}
	}
	return 0;
}
int main()
{
	FILE *inp = fopen("maze.inp","r");
	FILE *out = fopen("maze.out","w");
	int pX,pY,x,type;
	fscanf(inp,"%d %d",&n,&m);
	
	while(1)
	{
		fscanf(inp,"%d %d",&x,&type);
		if(x == -1)break;
		pX = x / m;
		pY = x % m;
		arr[pX][pY] = type;
	}
	type = f(0,0);
	if(type)
	{
		for(cnt=cnt-1; cnt>=0;cnt--)
		{
			fprintf(out,"%d\n",(SelectVertex[cnt][0] * m) + SelectVertex[cnt][1]);
		}
	}
	else
	{
		fprintf(out,"No Solution!");
	}
	return 0;
}