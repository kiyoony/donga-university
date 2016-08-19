#include <stdio.h>
int arr[501];
int n,m;
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int minData(int p,int q)
{
	return p < q ? p : q;
}
int partition(int p,int q)
{
	int L = p+1;
	int R = q;
	while(1)
	{
		while( L < R && arr[L] < arr[p] ) L++;
		while( L <=R && arr[R] >= arr[p] ) R--;

		if(L < R)
		{
			swap(&arr[L],&arr[R]);
		}
		else
		{
			swap(&arr[R],&arr[p]);
			return R;
		}

	}
}
void quicksort(int p, int q)
{
	if(p < q)
	{
		int position = partition(p,q);
		quicksort(p,position-1);
		quicksort(position+1,q);
	}
}
int getT_L(int p)
{
	int i = 0 ;
	int sum = 0;
	for( i = 0 ; i < p ; i ++ )
	{
		sum += arr[p] - arr[i];
	}
	return sum;
}
int getT_R(int p)
{
	int i = p+1;
	int sum = 0;
	for( i ; i < n ; i++ )
	{
		sum+= arr[i] - arr[p];
	}
	return sum;
}
int optDistance(int p,int q) // p , q 쓰레기통 사이에 최적 거리 반환
{
	int i = p+1;
	int sum = 0;
	for(i ; i < q; i ++ )
	{
		sum += minData( arr[i] - arr[p] , arr[q] - arr[i]);
	}
	return sum;
}
int main()
{
	int iCount = 0;
	int testcase;
	int i,j,k,comp,mSum,temp;
	int Rfix,Lfix,Zfix;
	FILE *inp = fopen("bin.inp","r");
	FILE *out = fopen("bin.out","w");

	fscanf(inp,"%d",&testcase);

	for( iCount = 0 ; iCount < testcase; iCount ++ )
	{
		int check[501][501]={0,};
		fscanf(inp,"%d %d",&n,&m);

		for( i = 0 ; i < n; i ++ )
		{
			fscanf(inp,"%d",&arr[i]);
		}
		if(n==m)
		{
			fprintf(out,"0\n");
		}
		else
		{
			quicksort(0,n-1);

			for( i = 0 ; i < n; i ++ ) // 초기화 , 쓰레기통이 1개 있을 때
			{
				check[0][i] = getT_L(i) + getT_R(i); // i 번째 집에 쓰레기통을 놓음
			}
			Zfix = getT_R(0); // 0 to n-1
			for(k = 1; k < m ; k ++ ) // 쓰레기통의 갯수 k + 1 개
			{
				Rfix = getT_R(i);
				Lfix = Zfix;
				for( i = 0 ; i < n; i ++ )
				{
					mSum = 0;

					Rfix = i ? Rfix - (arr[i]-arr[i-1])*(n - i) : Zfix; // i 점으로 부터 i+1 ~ n 까지 이르는 거리의 합
					Lfix = Zfix;
					for(j = 0; j <= i ; j ++ )
					{
						Lfix = j ? Lfix - (arr[j]-arr[j-1])*(n - j) : Lfix; // j 점으로 부터 j+1 ~ n 까지 이르는 거리의 합
						temp = Lfix - Rfix; // j번째와 i번째 공백 구간
						comp = check[k-1][j] - temp + optDistance(j,i); // j까지 최적 합 + j 와 i 사이 구간을 빼준 뒤 최적 합을 다시 구함
					
						if((mSum && comp < mSum) || !mSum)// j번째까지 k 번째 쓰레기통이 있고 i 번째에 k+1 번째 쓰레기통을 놓음
						{
							mSum = comp;
							check[k][i] = mSum;
						}
					}
				}
			}
			temp = 0;
			for( i = 0 ; i < n; i ++ )
			{
				if(temp)
				{
					temp = minData(temp , check[m-1][i]);
				}
				else
				{
					temp = check[m-1][i];
				}
			}
			fprintf(out,"%d\n",temp);
		}
	}
	return 0;
}
