#include <stdio.h>
int n,m;
int arr[10000][10000][3]; // 가중치 , 도착점 , 간선 번호
int number[10000]; // 간선 번호가 몇번이였는지
int heapData[1000000][2];
int floor[10000];
int distance[10000];
int visit[10000];
int before[10000];
void swap(int *a, int *b) // 교체
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int adjust(int a, int b,int target) // 힙이 아니라면 바꿔야할 자리를 반환     힙이면 -1 반환
{
	if(a && b)
	{
		if( a < target && b < target)
			return a < b ? 0 : 1;
		else if( a < target)
			return 0;
		else if( b < target)
			return 1;
		else
			return -1;
	}
	else if(a)
		return a < target ? 0 : -1;
	else if(b)
		return b < target ? 1 : -1;
	else
		return -1;
}
void getMinHeap(int n) // n까지 있는 arr배열에서 최소값 반환 후 힙 구조 적용
{

	int p , temp = 0;
	swap(&heapData[1][0],&heapData[n][0]);
	swap(&heapData[1][1],&heapData[n][1]);
	p = 1;
	while( p < n )
	{
		if(2*p+1 <n ) //두 자식 다 범위안에 들 때
		{
			temp = adjust(heapData[2*p][0],heapData[2*p +1][0], heapData[p][0]);
			if(temp < 0)
			{
				if(heapData[2*p][0] == heapData[p][0] && heapData[2*p +1][0] == heapData[p][0]) // 자식이 다 같을 때
				{
					temp = adjust(heapData[2*p][1],heapData[2*p +1][1], heapData[p][1]);
					if(temp<0)
						break;
					else
					{
						swap(&heapData[2*p +temp][1],&heapData[p][1]);
					}
				}
				else if(heapData[2*p][0] == heapData[p][0])
				{
					if(heapData[2*p][1] < heapData[p][1])
					{
						swap(&heapData[2*p][0],&heapData[p][0]);
						swap(&heapData[2*p][1],&heapData[p][1]);
						temp = 0;
					}
					else
						break;
				}
				else if(heapData[2*p +1][0] == heapData[p][0])
				{
					if(heapData[2*p +1][1] < heapData[p][1])
					{
						swap(&heapData[2*p +1][0],&heapData[p][0]);
						swap(&heapData[2*p +1][1],&heapData[p][1]);
						temp = 1;
					}
					else
						break;
				}
				else // 자식들 모두 부모보다 크다 ( 같지 않음 )
					break;
			}
			else// 자식 중에 작은 데이터가 존재함
			{
				if(heapData[2*p][0] == heapData[2*p +1][0])
				{
					if(heapData[2*p][1] < heapData[2*p+1][1])
					{
						temp = 0;
					}
					else
					{
						temp = 1;
					}
				}
				swap(&heapData[2*p +temp][0],&heapData[p][0]);
				swap(&heapData[2*p +temp][1],&heapData[p][1]);
				// 진행
			}
		}
		else if(2*p < n) // 왼쪽 자식만 있음
		{
			if(heapData[2*p][0] < heapData[p][0])
			{
				swap(&heapData[2*p][0],&heapData[p][0]);
				swap(&heapData[2*p][1],&heapData[p][1]);
				temp = 0;
			}
			else if(heapData[2*p][0] == heapData[p][0] && heapData[2*p][1] < heapData[p][1])
			{
				swap(&heapData[2*p][1],&heapData[p][1]);
				temp = 0;
			}
			else
				break;
		}

		p = (2*p) + temp;
	}
	return ; //heapData[n][0] 최소 값이 위치하고 있음
}
void findPosition(int p) // 힙 구성
{
	int parent = 0;
	while(p>1)
	{
		parent = p/2;
		if(heapData[p][0] < heapData[parent][0])
		{
			swap(&heapData[p][0] , &heapData[parent][0]);
			swap(&heapData[p][1] , &heapData[parent][1]);
		}
		else if(heapData[p][0] == heapData[parent][0] && heapData[p][1] < heapData[parent][1])
		{
			swap(&heapData[p][1] , &heapData[parent][1]);
		}

		p = parent;
	}
}
void process(int num)
{
	int EdgeCount = 0 ,EdgeNumber = 0;
	int index = 1 ,i = 0 , dst = 0; //heap 자료구조 인덱스
	while(EdgeCount < n-1 && index > 0)
	{
		visit[num] = 1;
		for( i = 0 ; i < floor[num]; i ++ )
		{
			dst = arr[num][i][1]; //도착점
			if(!distance[dst]) //연결되어 있지 않았음
			{
				distance[dst] = distance[num] + arr[num][i][0];
				before[dst] = num;
				number[dst] = arr[num][i][2];
				heapData[index][0] = distance[dst];
				heapData[index][1] = dst;
				findPosition(index++);
			}
			else
			{
				if(distance[dst] > distance[num] + arr[num][i][0] || (distance[dst] == distance[num] + arr[num][i][0]
				&& number[dst] < arr[num][i][2]))// num 을 거치는게 더 짧음
				{
					distance[dst] = distance[num] + arr[num][i][0];
					before[dst] = num;
					number[dst] = arr[num][i][2];
					if(!visit[dst])
					{
						heapData[index][0] = distance[dst];
						heapData[index][1] = dst;
						findPosition(index++);
					}
				}
			}
		}
		// 다음 정점 찾기
		index = index - 1;
		while(index>0)
		{
			getMinHeap(index);
			num = heapData[index][1];
			if(!visit[num])
			{
				EdgeCount++;
				break;
			}

			index = index - 1;
		}
	}
}
int main()
{
	int i , j ,pX,pY,weight,dst;
	FILE *inp = fopen("dijkstra.inp","r");
	FILE *out = fopen("dijkstra.out","w");
	fscanf(inp,"%d %d",&n,&m);
	for( i = 1 ; i < n; i ++)
	{
		before[i] = -1;
	}
	for( i = 0 ; i < m; i ++ )
	{
		fscanf(inp,"%d %d %d",&pX,&pY,&weight);
		arr[pX][floor[pX]][0] = weight;
		arr[pX][floor[pX]][1] = pY;
		arr[pX][floor[pX]++][2] = i;
	}
	process(0);
	for(i = 1; i <n; i ++ )
	{
		fprintf(out,"V0 ");
		if(!distance[i])
			fprintf(out,"V%d (%d)\n",i,-1);
		else
		{
			dst = i;
			floor[0] = dst;
			for( j = 1; before[dst]>0; j ++)
			{
				floor[j] = before[dst];
				dst = before[dst];
			}
			for(j=j-1;j>=0;j--)
			{
				fprintf(out,"V%d ",floor[j]);
			}
			fprintf(out,"(%d)\n",distance[i]);
		}
	}
	return 0;
}