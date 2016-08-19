#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *inp = fopen("tree.inp","r");
FILE *out = fopen("tree.out","w");
char Text[9];
int R_number = 0;
char buf;
typedef struct ListNode{
	int r;
	char T_Text[9];
	int number;
	struct ListNode *L;
	struct ListNode *R;
}ListNode;
ListNode* AllocNode(ListNode *Node,char type)
{
	Node = (ListNode*)malloc(sizeof(ListNode));
	Node->L = NULL;
	Node->R = NULL;
	if(type=='r')
	{
		Node->number = R_number ++;
		Node->r = 1;
	}
	else
	{
		strcpy(Node->T_Text,Text);
		Node->r = 0;
	}
	return Node;
}
ListNode* Loop(ListNode *cur)
{
	fscanf(inp,"%s",Text);
	fscanf(inp,"%c",&buf);
	fprintf(out,"%s",Text);
	fprintf(out,"%c",buf);
	if(Text[0]=='(')
	{
		cur = AllocNode(cur,'r');
		cur->L = Loop(cur->L);
		cur->R = Loop(cur->R);
		fscanf(inp,"%s",Text); // ')' buffer
		fscanf(inp,"%c",&buf);
		fprintf(out,"%s",Text);
		fprintf(out,"%c",buf);
	}
	else if(Text[0]==')')
	{
		return cur;
	}
	else//(Text[0]=='T')
	{
		cur = AllocNode(cur,'T');
	}
	return cur;
}
void printNode(ListNode *Node)
{
	if(Node->r)
	{
		fprintf(out,"r%d\n",Node->number);
	}
	else
	{
		fprintf(out,"%s\n",Node->T_Text);
	}
}
void Preorder(ListNode *temp)
{
	if(temp)
	{
		printNode(temp);
		Preorder(temp->L);
		Preorder(temp->R);
	}
}
void Inorder(ListNode *temp)
{
	if(temp)
	{
		Inorder(temp->L);
		printNode(temp);
		Inorder(temp->R);
		free(temp);
		temp = NULL;
	}
}
int main()
{
	ListNode *root = NULL;
	int testcase;
	int iCount = 0 ;
	
	fscanf(inp,"%d",&testcase);

	for( iCount = 0 ; iCount < testcase; iCount ++)
	{
		R_number = 0;
		root = Loop(root);
		fprintf(out,"Preorder\n");
		Preorder(root);
		fprintf(out,"Inorder\n");
		Inorder(root);

	}
	return 0;
}