#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pCount,NumOfInstance; //���μ����� �ڿ��� ����

typedef struct Que{
	int instance[50]; //�ڿ�
	int pNum; //���μ��� ��ȣ
	struct Que *next;
}Que;

void addQue(Que *Q,int arr[50],int pNum){ //��û ť

	int i;
	Que *p = Q;
	Que *NewQue = (Que*)malloc(sizeof(Que));
	NewQue->pNum = pNum;
	for(i=0;i<NumOfInstance;i++){
		NewQue->instance[i] = arr[i];
	}
	NewQue->next=NULL;
	
	while(p->next!=NULL)p=p->next;

	p->next = NewQue;
}

void delQue(Que *pre_Q,Que *del_Q){
	pre_Q->next = del_Q->next;
	free(del_Q);
	del_Q=NULL;
}
int safe(int banker_c[50][50],int NEED_MAX_c[50][50],int available_c[50],int buffer[50],int pNumber){
	int i,j,n;
	int check=0; //�̹� �Ϸ�� ���μ������� Ȯ���ϴ� ����
	int banker[50][50];
	int NEED_MAX[50][50];
	int available[50];
	int fCount=0;
	int flag[50]={0,}; //�ش� ���μ����� �۾��� �Ϸ��Ͽ����� �Ϸ� 1 �̿Ϸ� 0
	for(i=0;i<pCount;i++){
		for(j=0;j<NumOfInstance;j++){
			banker[i][j] = banker_c[i][j];
			NEED_MAX[i][j] = NEED_MAX_c[i][j];
		}
	}
	for(j=0;j<NumOfInstance;j++){
		available[j] = available_c[j];
	}
	for(i=0;i<NumOfInstance;i++){
		if(buffer[i]>(NEED_MAX[pNumber][i] - banker[pNumber][i]))return 1;
		banker[pNumber][i] += buffer[i];
		available[i] -= buffer[i];
	}
	for(i=0;i<pCount;i++){
		for(j=0;j<NumOfInstance;j++){
			if(banker[i][j]!=NEED_MAX[i][j]){
				break;
			}
		}
		if(j==NumOfInstance){ 
			flag[i] = 1;
			fCount++;
			for(j=0;j<NumOfInstance;j++){
				available[j] += banker[i][j];
				banker[i][j] = 0;
				NEED_MAX[i][j] = 0;
			}
		}
	}

	for(n=0;n<(pCount-fCount);n++){
		check = 0;
		for(i=0;i<pCount;i++){
			for(j=0;j<NumOfInstance && !flag[i];j++){
				if((NEED_MAX[i][j] - banker[i][j]) > available[j]) //�ʿ�� �ϴ� �ڿ��� ���ڶ� ��
					break;
				if(j==NumOfInstance-1){ //���ڶ�������
					for(j=0;j<NumOfInstance;j++){
						available[j] = available[j] + banker[i][j]; //�Ҵ�� �ڿ� ��ȯ
						banker[i][j] = 0 ;
						NEED_MAX[i][j] = 0;
						check = 1;
						flag[i] = 1;
					}
				}
			}
			if(check)break;
		}
		if(!check){
			return 1; // unsafe
		}
	}
	return 0; //safe
}
int main()
{
	FILE *inp = fopen("banker.inp","r");
	FILE *out = fopen("banker.out","w");

	int banker[50][50]={0,}; //���μ����� ���� �ڿ�
	int NEED_MAX[50][50]={0,};//�ʿ�� �ϴ� �ִ��� �ڿ�
	int available[50]={0,}; //���� �̿밡���� �ڿ�
	int buffer[50]={0,};
	
	int i,j; //�ݺ����� ���� ����

	int pNumber; //���μ��� ��ȣ�� �Է¹��� ����
	
	int pComplete=0; //���μ��� ��ȯ�� ������

	int pCheck = 0; //�� ��û�� ��ȿ����

	int Deadlock_Detection = 0;  //����� ���� ����

	char check ; //��û, �Ҵ�, ���Ḧ �Ǻ��� ����

	Que *Q =(Que*)malloc(sizeof(Que));
	
	Q->next = NULL;

	Q->pNum=-1; //dummy Que Node

	Que *pre_Q , *now_Q; //���ť�� �˻��ϰ� ������ �� �ʿ��� �迭

	fscanf(inp,"%d %d",&pCount,&NumOfInstance); //�ڿ��� ���μ����� ���� �Է�

	for(i=0;i<NumOfInstance;i++){
		fscanf(inp,"%d",&available[i]); //�ý��� �ڿ� �Ҵ�
	}
	
	for(i=0;i<pCount;i++){            //���μ����� �ִ� �ʿ� �ڿ�
		for(j=0;j<NumOfInstance;j++){
			fscanf(inp,"%d",&NEED_MAX[i][j]);
		}
	}

	for(i=0;i<pCount;i++){            //���μ����� �ִ� �ʿ� �ڿ�
		for(j=0;j<NumOfInstance;j++){
			fscanf(inp,"%d",&banker[i][j]);
			available[j]-=banker[i][j];
		}
	}
	fscanf(inp,"\n");
	while(1){
		fscanf(inp,"%c",&check);
		
		if(check =='q') //quit�� ���ý� ���α׷� ����
			return 0;
		//else �׹��� ���  ( request , realease)

		fscanf(inp,"e");
		fscanf(inp,"%c",&check);
		if(check=='q'){ //��û
			fscanf(inp,"uest");
			fscanf(inp,"%d",&pNumber);
			//pCheck = 0;
			for(i=0;i<NumOfInstance;i++){
				fscanf(inp,"%d",&buffer[i]);
				/*if(NEED_MAX[pNumber][i] < buffer[i] + banker[pNumber][i])
					pCheck = 1;*/
			}
			addQue(Q,buffer,pNumber);
			fscanf(inp,"\n");
		}
		else{ //��ȯ
			fscanf(inp,"ease");
			fscanf(inp,"%d",&pNumber); //���μ��� ��ȣ �Է�
			for(i=0;i<NumOfInstance;i++){
				fscanf(inp,"%d",&buffer[i]);
				available[i] += buffer[i];
				banker[pNumber][i] -= buffer[i];
			}
			fscanf(inp,"\n");
		}

		// ������ �ʿ��� �κ�
		pre_Q = Q;
		now_Q = Q->next;
		while(now_Q){
			Deadlock_Detection = 0;
			for(i=0;i<NumOfInstance;i++){
				if(now_Q->instance[i] > available[i]){
					Deadlock_Detection=1;
					break;
				}
			}
			if(!Deadlock_Detection){
				Deadlock_Detection = safe(banker,NEED_MAX,available,now_Q->instance,now_Q->pNum);
			}

			if(!Deadlock_Detection){ //��û�� ���� ������� �������� ������ ��û ���
				for(i=0;i<NumOfInstance;i++){
					banker[now_Q->pNum][i] += now_Q->instance[i];
					available[i] = available[i] - now_Q->instance[i]; 
				}
				delQue(pre_Q,now_Q);
				now_Q = pre_Q->next;
			}
			else{// ����� ����
				pre_Q = now_Q;
				now_Q = now_Q->next; // ���� ť Ž��
			}
		}
		for(i=0;i<NumOfInstance;i++){
			fprintf(out,"%d ",available[i]);
		}
		fprintf(out,"\n");
	}
}