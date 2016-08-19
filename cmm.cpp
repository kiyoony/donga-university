#include <stdio.h>
int arr[51];
int First[51];
int Second[51];
int scope[51][2];
long long int DP[51][51];
int check[51][51];
int N;
long long int Greedy_first()
{
	long long int result = 0;
	int MultiCount =  N;
	int n = 0,p = 0,m = 0;
	int index = 0,temp=0 ,Count = 0;
	int Max = 0 ,MaxP = 0,MaxN = 0,MaxM = 0;
	while(MultiCount > 1)
	{
		index = 0;
		while(index <= N)
		{
 			temp = 0;
			while(First[index+temp] && index+temp <= N)temp++;
			n = index+temp;
			temp++;
			if(index + temp > N)break;
			while(First[index+temp] && index+temp <= N)temp++;
			p = index+temp;
			temp++;
			if(index + temp > N)break;
			while(First[index+temp] && index+temp <= N)temp++;
			m = index+temp;
			if(index + temp > N)break;
			index++;

			if(Max < arr[p])
			{
				MaxP = p , MaxN = n , MaxM = m;
				Max = arr[p];
			}
		}
		result += arr[MaxN] * arr[MaxP] * arr[MaxM];
		if(MultiCount>2)scope[MaxN+1][0] ++ , scope[MaxM][1] ++;
		First[MaxP] = ++Count,	Max = 0;
		MultiCount--;
	}
	return result;
}
long long int Greedy_Second()
{
	long long int result = 0;
	int MultiCount =  N;
	int n = 0,p = 0,m = 0;
	int index = 0,temp=0 , Count = 0;
	int Max = 10001 ,MaxP = 0,MaxN = 0,MaxM = 0;
	while(MultiCount > 1)
	{
		index = 0;
		while(index <= N)
		{
 			temp = 0;
			while(Second[index+temp] && index+temp <= N)temp++;
			n = index+temp;
			temp++;
			if(index + temp > N)break;
			while(Second[index+temp] && index+temp <= N)temp++;
			p = index+temp;
			temp++;
			if(index + temp > N)break;
			while(Second[index+temp] && index+temp <= N)temp++;
			m = index+temp;
			if(index + temp > N)break;

			if(Max > arr[n] * arr[m])
			{
				MaxP = p , MaxN = n , MaxM = m;
				Max = arr[n] * arr[m];
			}
			index++;
		}
		result += arr[MaxN] * arr[MaxP] * arr[MaxM];
		if(MultiCount>2)scope[MaxN+1][0] ++ , scope[MaxM][1] ++;
		Second[MaxP] = ++Count , Max = 10001;
		MultiCount--;
	}
	return result;
}
long long int positionData(int n,int p,int m) // ¿ä±â !
{
	return DP[n][p] + DP[p+1][m] + (arr[n-1] * arr[p] * arr[m]);
}
void initScope()
{
	int i = 0 ;
	for( i = 0 ; i < N ; i ++ )
	{
		scope[i+1][0] = 0;
		scope[i+1][1] = 0;
	}
}
void printScope(FILE *out)
{
	int i = 0 , j = 0;
	for( i = 0 ; i < N ; i ++ )
	{
		for( j = 0 ; j < scope[i+1][0]; j ++ )
		{
			fprintf(out,"(");
		}
		fprintf(out,"A%d",i+1);
		for( j = 0 ; j < scope[i+1][1]; j ++ )
		{
			fprintf(out,")");
		}
	}
	fprintf(out,"\n");
	initScope();
}
long long int Dynamic()
{
	int i , j , k;
	long long int temp = 0;

	for( i = 1 ; i < N; i++ )
	{
		for( j = 1 ; j + i <= N ; j ++ ) // j ~ i + j
		{
			for( k = j ; k < j+i ; k ++ )
			{
				temp = positionData(j,k,j+i);
				
				if(k==j)
				{
					DP[j][i+j] = temp;
					check[j][i+j] = k;
				}
				else if(temp < DP[j][i+j])
				{
					DP[j][i+j] = temp;
					check[j][i+j] = k;
				}
			}
		}
	}
	return DP[1][N];
}
void set_Dynamic_scope(int p, int q) // p ~ q
{
	int cut = check[p][q];
	if(p>=q)return;
	if(p<cut)
	{
		scope[p][0]++;
		scope[cut][1]++;
		set_Dynamic_scope(p,cut);
	}
	if(cut+1<q)
	{
		scope[cut+1][0]++;
		scope[q][1]++;
		set_Dynamic_scope(cut+1,q);
	}
}
int main()
{
	FILE *inp = fopen("cmm.inp","r");
	FILE *out = fopen("cmm.out","w");
	int testcase;
	int iCount;
	int i;
	fscanf(inp,"%d",&testcase);
	for(iCount = 0 ; iCount < testcase; iCount ++ )
	{
		fscanf(inp,"%d",&N);

		for(i = 0 ; i <=N ;i ++)
		{
			fscanf(inp,"%d",&arr[i]);
			First[i] = 0;
			Second[i]= 0;
		}
		fprintf(out,"Test Case Number : %d\n",iCount + 1);
		fprintf(out,"%lld ",Greedy_Second());
		printScope(out);
		fprintf(out,"%lld ",Greedy_first());
		printScope(out);
		fprintf(out,"%lld ",Dynamic());
		set_Dynamic_scope(1,N);
		printScope(out);
	}
	return 0;
}
