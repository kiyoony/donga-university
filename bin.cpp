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
int optDistance(int p,int q) // p , q �������� ���̿� ���� �Ÿ� ��ȯ
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

			for( i = 0 ; i < n; i ++ ) // �ʱ�ȭ , ���������� 1�� ���� ��
			{
				check[0][i] = getT_L(i) + getT_R(i); // i ��° ���� ���������� ����
			}
			Zfix = getT_R(0); // 0 to n-1
			for(k = 1; k < m ; k ++ ) // ���������� ���� k + 1 ��
			{
				Rfix = getT_R(i);
				Lfix = Zfix;
				for( i = 0 ; i < n; i ++ )
				{
					mSum = 0;

					Rfix = i ? Rfix - (arr[i]-arr[i-1])*(n - i) : Zfix; // i ������ ���� i+1 ~ n ���� �̸��� �Ÿ��� ��
					Lfix = Zfix;
					for(j = 0; j <= i ; j ++ )
					{
						Lfix = j ? Lfix - (arr[j]-arr[j-1])*(n - j) : Lfix; // j ������ ���� j+1 ~ n ���� �̸��� �Ÿ��� ��
						temp = Lfix - Rfix; // j��°�� i��° ���� ����
						comp = check[k-1][j] - temp + optDistance(j,i); // j���� ���� �� + j �� i ���� ������ ���� �� ���� ���� �ٽ� ����
					
						if((mSum && comp < mSum) || !mSum)// j��°���� k ��° ���������� �ְ� i ��°�� k+1 ��° ���������� ����
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
