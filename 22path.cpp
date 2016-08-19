#include <stdio.h>
int d,n,m;
int arr[101][101];
int check[101][101];
char String[102];
int SelectVertex[10001][2];
int cnt = 0;
int range(int i,int j)
{
	if(i>=0 && i<n && j>=0 && j<m)
		return 1;
	else
		return 0;
}
int distance(int x,int y)
{
	int data = x > y ? x - y : y - x;
	if(data<=5)
		return data;
	else
		return 10-data;
}
void insert(int i,int j,int turn)
{
	SelectVertex[turn][0] = i;
	SelectVertex[turn][1] = j;
}
int f(int i,int j,int turn)
{
	int temp = 0, flag = 0;
	check[i][j] = turn;
	if(i == n-1 && j == m-1)
	{
		if(!cnt || turn < cnt)
		{
			cnt = turn;
			insert(i,j,turn);
		}
		return turn-1;
	}
	if(range(i,j+1) && (!check[i][j+1] || check[i][j+1] > turn + 1 ) && distance(arr[i][j],arr[i][j+1]) <=d)//©Л
	{
		temp = f(i,j+1,turn+1);
		if(temp && temp <= turn)
		{
			turn = temp;
			insert(i,j,turn);
			flag = 1;
		}
	}
	if(range(i+1,j) && (!check[i+1][j] || check[i+1][j] > turn + 1 ) && distance(arr[i][j],arr[i+1][j]) <=d)//го
	{
		temp = f(i+1,j,turn+1);
		if(temp && temp <= turn)
		{
			turn = temp;
			insert(i,j,turn);
			flag = 1;
		}
	}
	if(range(i,j-1) && (!check[i][j-1] || check[i][j-1] > turn + 1 ) && distance(arr[i][j], arr[i][j-1])<=d)//аб
	{
		temp = f(i,j-1,turn+1);
		if(temp && temp <= turn)
		{
			turn = temp;
			insert(i,j,turn);
			flag = 1;
		}
	}
	if(range(i-1,j) && (!check[i-1][j] || check[i-1][j] > turn + 1 ) && distance(arr[i][j],arr[i-1][j])<=d)//╩С
	{
		temp = f(i-1,j,turn+1);
		if(temp && temp <= turn)
		{
			turn = temp;
			insert(i,j,turn);
			flag = 1;
		}
	}
	return flag ? turn-1 : flag;
}
int main()
{
	FILE *inp = fopen("path.inp","r");
	FILE *out = fopen("path.out","w");
	int i,j,k,flag = 0;
	fscanf(inp,"%d %d %d",&d,&n,&m);
	for( i = 0 ;i < n;i ++ )
	{
		fscanf(inp,"%s",String);
		for(j = 0 ; j < m ; j ++ )
		{
			arr[i][j] = String[j] - '0';
		}
	}
	flag = f(0,0,1);
	if(cnt)
	{
		for(k = 1 ; k <= cnt; k ++)
		{
			i = SelectVertex[k][0];
			j = SelectVertex[k][1];
			fprintf(out,"(%d %d) [%d]\n",i,j,arr[i][j]);
		}
	}
	else
	{
		fprintf(out,"Impossible!");
	}
	return 0;
}