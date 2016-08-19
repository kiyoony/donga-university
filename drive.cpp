#include <stdio.h>
int m , n , L , G;
int width[1001][1001];
int height[1001][1001];
int data[1001][1001][2];  // 0 번째는 데이터 1번쨰는 방향정보   0 아래 1 오른쪽  
int floor[1001]; //몇 단계 까지 있는지
int minData(int p, int q)
{
	if(!p)
		return q;
	else if(!q)
		return p;
	else return p < q? p : q;
}
int main()
{
	FILE *inp = fopen("drive.inp","r");
	FILE *out = fopen("drive.out","w");
	int testcase;
	int iCount;
	int i = 0 , j = 0 , k = 0 ;
	int a  , buf = 0 , temp = 0 , index = 0, down = 0;
	fscanf(inp,"%d",&testcase);

	for( iCount = 0 ; iCount < testcase ; iCount ++ )
	{
		fscanf(inp,"%d %d %d %d",&m,&n,&L,&G);
		for( i = 0 ; i < m ; i ++ )
		{
			for( j = 0 ; j< n - 1; j ++ )
			{
				fscanf(inp,"%d",&width[i][j]);
			}
		}
		for( i = 0 ; i < m -1 ; i ++ )
		{
			for( j= 0 ; j < n; j ++ )
			{
				fscanf(inp,"%d",&height[i][j]);
			}
		}
		data[0][0][0] = 0;
		for( j = 1 ;j < n; j ++ )
		{
			floor[j] = 1;
			data[j][0][0] = width[0][j-1] + data[j-1][0][0];
		}
		floor[0] = 1;

		for( i = 1 ; i < m ; i ++ )
		{
			for( j = 0 ;j < n ; j  ++ )
			{
				if(j==0)
				{
					data[j][0][1] += height[i-1][0]; 
				}
				else
				{
					if(i>1)data[j][0][0] = 0;
					a = floor[j-1];
					if(data[j-1][a-1][1])a++;
					if(data[j][floor[j]-1][0])floor[j]++;
					floor[j] = a > floor[j] ? a : floor[j];
					for( k = floor[j]-1; k>0; k--)
					{
						data[j][k][0] = minData(data[j-1][k-1][1],data[j-1][k][0]);
						data[j][k][1] = minData(data[j][k-1][0],data[j][k][1]);
						if(data[j][k][0])data[j][k][0]+=width[i][j-1];
						if(data[j][k][1])data[j][k][1]+=height[i-1][j];
					}
				}
			}
		}
		for(k = 1 ; k < floor[j-1] ; k++)
		{
			buf = minData(data[j-1][k][0],data[j-1][k][1]);
			if( buf && buf <= G)break;
		}
		if(k < floor[j-1])
		{
			fprintf(out,"%d\n",L *(n+m-2) + k);
		}
		else
		{
			fprintf(out,"-1\n");
		}
		for( i = 0 ; i < m; i ++)
		{
			for(j = 0 ; j < floor[i] ; j++ )
			{
				data[i][j][0] = data[i][j][1] = 0;
			}
		}
	}
	return 0;
}