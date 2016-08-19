#include <stdio.h>
#include <stdlib.h>
int n;
int type[2];		// -1 preorder   0 inorder   1 postorder
int top = -1;
int stack[10001];
int Aindex = 0,Bindex = 0;
FILE *inp = fopen("tree.inp","r");
FILE *out = fopen("tree.out","w");
typedef struct ListNode{
	int data;
	struct ListNode *L;
	struct ListNode *R;
}ListNode;

ListNode* addNode(ListNode *cur,int data)
{
	cur = (ListNode*)malloc(sizeof(ListNode));
	cur->data = data;
	cur->L = NULL;
	cur->R = NULL;
	return cur;
}
int findRoot(int *in,int *post,int p,int q)
{
	int i;
	for( i = p; i < q; i++)
	{
		if(in[i]==post[Bindex])
		{
			return in[i];
		}
	}
	return 0;
}
ListNode* detectPre(int *in,int *post,ListNode *cur,int rootData,int p,int q)
{
	int subroot = 0,i = 0 , rootPoint = 0;
	if(p>=q)return cur;
	cur = addNode(cur,rootData);
	Bindex--;
	if(p==q-1)
	{
		return cur;
	}
	for( i = p; i < q; i++)
	{
		if(in[i] == rootData)
		{
			rootPoint = i;
			break;
		}
	}
	subroot = findRoot(in,post,p,q);
	if(subroot)cur->R = detectPre(in,post,cur->R,subroot,rootPoint+1,q);
	subroot = findRoot(in,post,p,q);
	if(subroot)cur->L = detectPre(in,post,cur->L,subroot,p,rootPoint);
	return cur;
}
ListNode* detectPost(int *pre,int *in,ListNode *cur)
{
	if(Aindex>=n)return cur;
	if(top == -1 || stack[top] != in[Bindex])
	{
		cur = addNode(cur,pre[Aindex]);
		stack[++top] = pre[Aindex++];
	}
	else if(stack[top]==in[Bindex])
	{
		Bindex++;
		top--;
		return cur;
	}
	if(cur->data != stack[top] && stack[top]==in[Bindex])
	{
		return cur;
	}
	cur->L = detectPost(pre,in,cur->L);
	if(cur->data != stack[top] && stack[top]==in[Bindex])
	{
		return cur;
	}
	else if(cur->data == stack[top])
	{
		top--;
		Bindex++;
	}
	cur->R = detectPost(pre,in,cur->R);
	return cur;
}
void travel(ListNode *temp,int n)
{
	if(temp)
	{
		if(n==-1)fprintf(out,"%d\n",temp->data);
		travel(temp->L,n);
		if(n==0)fprintf(out,"%d\n",temp->data);
		travel(temp->R,n);
		if(n==1)fprintf(out,"%d\n",temp->data);
	}
}
int main()
{
	int i = 0;
	int what = 0;
	int F_order[10001];
	int S_order[10001];
	ListNode *root = NULL;
	fscanf(inp,"%d",&n);

	fscanf(inp,"%d",&type[0]);
	what +=type[0];
	for( i = 0 ; i < n; i ++)
	{
		fscanf(inp,"%d",&F_order[i]);
	}
	fscanf(inp,"%d",&type[1]);
	what+=type[1];
	for(i = 0 ;i < n ; i ++)
	{
		fscanf(inp,"%d",&S_order[i]);
	}
	switch(what)
	{
	case -1:
		root = detectPost(type[0]?F_order:S_order , type[0]?S_order:F_order , root);
		break;
	case 1:
		Bindex = n-1;
		root = detectPre(!type[0]?F_order:S_order , !type[0]?S_order:F_order, root,!type[0]?S_order[n-1]:F_order[n-1],0,n);
		break;
	}
	travel(root,what*-1);
	return 0;
}
