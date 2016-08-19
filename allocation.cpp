#include <stdio.h>
#include <stdlib.h>
int pCount;//��ü ����
typedef struct Timeslice //�ð��� ��Ÿ�� ����Ʈ
{
	int time;
	int isEnd;
	struct Timeslice *next;
}Timeslice;
typedef struct MemoryList //�޸𸮿� ���� ����Ʈ
{
	int Number; //��û ��ȣ
	int ArriveTime;//�����ð�
	int BurstTime;//���ð�
	int Size; //ũ��
	struct MemoryList *link; //��ũ
}MemoryList;
void addMemoryList(MemoryList *M,int Number,int ArriveTime,int BurstTime,int Size) //�޸𸮿� ���� ����Ʈ���� �߰�
{
	MemoryList *p = M;
	MemoryList *New = (MemoryList*)malloc(sizeof(MemoryList));
	New->Number = Number;
	New->ArriveTime =ArriveTime;
	New->BurstTime = BurstTime;
	New->Size = Size;
	New->link = NULL;
	while(p->link!=NULL)p=p->link;
	p->link= New;
}
void DelMemoryList(MemoryList *M,int Number)//�޸𸮿� ����Ǹ� ����Ʈ���� ����
{
	MemoryList * p = M;
	MemoryList *del;
	while(p->link->Number!=Number)p = p->link;
	del = p->link;
	p->link = del->link;
	del = NULL;
	free(del);
}
void addTimeList(int time,int isEnd,Timeslice *T) //���� ����,��ȯ�ð��� ������ ����Ʈ
{
	Timeslice * p = T->next,*pre =T;
	Timeslice *New ;
	while(p!=NULL)
	{
		if(p->time>=time)break;
		pre = p,p=p->next;
	}
	if(p&&p->time==time)
	{
		p->isEnd=isEnd;
		return;
	}
	New = (Timeslice*)malloc(sizeof(Timeslice));
	New->next = pre->next;
	New->time = time;
	New->isEnd = isEnd;
	pre->next = New;
}
void CopyMemoryList(MemoryList *target,MemoryList*origin) //�ӽ÷� ����ϱ����� �޸𸮺���
{
	MemoryList *p =origin->link;
	MemoryList *q =target;
	MemoryList *New;
	while(p!=NULL)
	{
		New = (MemoryList*)malloc(sizeof(MemoryList));
		New->ArriveTime = p->ArriveTime;
		New->BurstTime = p->BurstTime;
		New->Number = p->Number;
		New->Size = p->Size;
		New->link = NULL;
		q->link = New;
		p = p->link,q = q->link;
	}
}
int WhoisMostFit(int Memory[1000][3],int BufPos,int CurPos,int fit) //���� �� fit�� �������� (���� ������,���� ������)
{
	fit = (fit==1)?1:-1;
	return (Memory[BufPos][1]-BufPos)*fit <= (Memory[CurPos][1]-CurPos)*fit ? BufPos:CurPos; //fit�� ������ ��ġ�� ��ȯ��
}
int Myposition(int Memory[1000][3],MemoryList *CurP,int time,int fit) //���������� ��ġ
{
	int position = 0;
	int Buf=-1;
	while(position<1000)
	{
		if((Memory[position][1] - position) >= CurP->Size && Memory[position][0]==-1) //���� �ִ� ������
		{
			if(!fit)
				return position;
			else
				Buf = (Buf<0) ? position:WhoisMostFit(Memory,Buf,position,fit);
		}
		position = Memory[position][1];
	}
	return Buf;
}
void releaseMemory(int Memory[1000][3],int time)//�޸� ��ȯ
{
	int position=0;
	while(position<1000)
	{
		if(Memory[position][2]==time)
			Memory[position][0] = -1;

		position = Memory[position][1];
	}
	position = 0 ; //����� �����ֱ�
	while(position<1000)
	{
		if(Memory[position][0] == -1 && Memory[Memory[position][1]][0] == -1 &&Memory[position][1]!=1000)
			Memory[position][1] = Memory[Memory[position][1]][1];
		else
			position = Memory[position][1];
	}
}
int Memory_allocation(MemoryList *M,int fit) //fit  -> 0 first 1 best 2 worst
{
	MemoryList *Copy_M = (MemoryList*)malloc(sizeof(MemoryList));
	MemoryList * p,*temp;
	Timeslice *T = (Timeslice*)malloc(sizeof(Timeslice));
	int Memory[1001][3]; //������� ���μ�����ȣ,������,������ �ð� ����
	int position = 0; //����� �޸� �ּ�
	int Bufposition =0;
	T->next = NULL,T->time = -1;
	Copy_M->link = NULL;
	CopyMemoryList(Copy_M,M);	//�ӽ÷� ����ϱ� ���� CopyMemoryList
	p = Copy_M->link;
	Memory[0][0] = -1,Memory[1000][0] = -1;
	Memory[0][1] = 1000;
	while(p)
	{
		addTimeList(p->ArriveTime,0,T);
		p = p->link;
	}
	p = Copy_M->link;
	T = T->next; // ���� ó�� �ð�����
	while(T) //���ð��� ���������� ( T �� �ð��� ���� ����Ʈ)
	{
		if(T->isEnd) //��ȯ�Ϸ��� �ڸ��� ���� ��
			releaseMemory(Memory,T->time);
		position = 0 , p = Copy_M->link; //�� �ʱ�ȭ
		while(p)
		{
			if(p->ArriveTime <= T->time)//���������μ����϶�
			{
				position = Myposition(Memory,p,T->time,fit);
				if(position != -1) //���� ��
				{
					if(p->Number == pCount -1)return position;
					Bufposition = Memory[position][1];
					Memory[position][0] = p->Number;
					Memory[position][1] = p->Size + position;
					Memory[position][2] = T->time + p->BurstTime;
					if(Memory[position][1]!=Bufposition){
						Memory[Memory[position][1]][1] = Bufposition;
						Memory[Memory[position][1]][0] = -1;
					}
					addTimeList(T->time + p->BurstTime,1,T);
					temp = p;
					p= p->link;
					DelMemoryList(Copy_M,temp->Number);
				}
				else
					p = p->link;
			}
			else
				break;
		}
		T = T->next;
	}
}
void Datainput(FILE *in,MemoryList *M) //������ �Է�
{
	int AT,BT,SZ; //�����ð�,����ð�,������
	for(int i=0;i<pCount;i++)
	{
		fscanf(in,"%d %d %d",&AT,&BT,&SZ);
		addMemoryList(M,i,AT,BT,SZ);
	}
}
int main()
{
	FILE *inp = fopen("allocation.inp","r");
	FILE *out = fopen("allocation.out","w");
	fscanf(inp,"%d",&pCount);
	MemoryList *M = (MemoryList*)malloc(sizeof(MemoryList));
	M->link=NULL;
	Datainput(inp,M);
	for(int i=0;i<3;i++)
	{
		fprintf(out,"%d\n",Memory_allocation(M,i));
	}
	return 0;
}