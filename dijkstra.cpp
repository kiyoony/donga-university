#include <stdio.h>
int n,m;
int arr[10000][10000][3]; // ����ġ , ������ , ���� ��ȣ
int number[10000]; // ���� ��ȣ�� ����̿�����
int heapData[1000000][2];
int floor[10000];
int distance[10000];
int visit[10000];
int before[10000];
void swap(int *a, int *b) // ��ü
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int adjust(int a, int b,int target) // ���� �ƴ϶�� �ٲ���� �ڸ��� ��ȯ     ���̸� -1 ��ȯ
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
void getMinHeap(int n) // n���� �ִ� arr�迭���� �ּҰ� ��ȯ �� �� ���� ����
{

	int p , temp = 0;
	swap(&heapData[1][0],&heapData[n][0]);
	swap(&heapData[1][1],&heapData[n][1]);
	p = 1;
	while( p < n )
	{
		if(2*p+1 <n ) //�� �ڽ� �� �����ȿ� �� ��
		{
			temp = adjust(heapData[2*p][0],heapData[2*p +1][0], heapData[p][0]);
			if(temp < 0)
			{
				if(heapData[2*p][0] == heapData[p][0] && heapData[2*p +1][0] == heapData[p][0]) // �ڽ��� �� ���� ��
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
				else // �ڽĵ� ��� �θ𺸴� ũ�� ( ���� ���� )
					break;
			}
			else// �ڽ� �߿� ���� �����Ͱ� ������
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
				// ����
			}
		}
		else if(2*p < n) // ���� �ڽĸ� ����
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
	return ; //heapData[n][0] �ּ� ���� ��ġ�ϰ� ����
}
void findPosition(int p) // �� ����
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
	int index = 1 ,i = 0 , dst = 0; //heap �ڷᱸ�� �ε���
	while(EdgeCount < n-1 && index > 0)
	{
		visit[num] = 1;
		for( i = 0 ; i < floor[num]; i ++ )
		{
			dst = arr[num][i][1]; //������
			if(!distance[dst]) //����Ǿ� ���� �ʾ���
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
				&& number[dst] < arr[num][i][2]))// num �� ��ġ�°� �� ª��
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
		// ���� ���� ã��
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