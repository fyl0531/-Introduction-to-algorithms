#include <stdio.h>
#include <stdlib.h>
 
typedef struct QNode{
	int value;	//当前结点的总价值
	int weight; //当前的总重量
	struct QNode *next;
}QNode, *QueuePtr;
 
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}Queue;
 
int initQueue(Queue &Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		return -1;
	Q.front->next=NULL;
 
	return 1;
}
 
int emptyQueue(Queue Q)
{
	if (Q.front==Q.rear)
		return 1;
	else
		return 0;
}
 
int destroyQueue(Queue &Q)
{
	while(Q.front){
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return 1;
}
 
int enQueue(Queue &Q, int value, int weight)
{
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)
		return -1;
	p->value=value; 
	p->weight=weight; 
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	
	return 1;
}
 
int deQueue(Queue &Q, int &value, int &weight)
{
	QueuePtr p;
	if(Q.front==Q.rear)
		return -1;
	p=Q.front->next;
	value=p->value;
	weight=p->weight;
	Q.front->next=p->next;
 
	if(Q.rear==p) Q.rear=Q.front;
	
	free(p);
 
	return 1;
}
 
Queue loadingQueue;
int bestvalue, n;
 
void inQueue(int value, int weight, int i)
{
	if(i==n-1)
	{
		if(value>bestvalue)
			bestvalue=value;
	}
	else
		enQueue(loadingQueue,value,weight);
}
 
 
 
int main()
{
	
	int i,j,k;
	int *w, *v, ew, ev;
	int c;
 
	printf("input the number of things and the volume of ships:");
	scanf("%d%d",&n,&c);
 
	w=new int[n];
	v=new int[n];
	printf("input the weights:");
	
	for(i=0;i<n;i++)
		scanf("%d",&w[i]);
 
	printf("input the values:");
 
	for(i=0;i<n;i++)
		scanf("%d",&v[i]);
 
	
	initQueue(loadingQueue);
	enQueue(loadingQueue,-1,0);		
	//int deQueue(Queue &Q, int &value, int &weight)	
	//void inQueue(int value, int weight, int i)
	//int enQueue(Queue &Q, int value, int weight)
 
 
	i=0;	//层数
	ew=0;	//扩展结点对应的载重量
	ev=0;	
 
	while(true)
	{
		if(ew+w[i]<=c)
			inQueue(ev+v[i],ew+w[i],i);
		inQueue(ev,ew,i);
 
		deQueue(loadingQueue, ev,ew);
 
		if(ev==-1) //同层结点尾部
		{
			if(emptyQueue(loadingQueue))
			{
				printf("the result is %d.\n",bestvalue);
			}
 
			enQueue(loadingQueue,-1,0);
			deQueue(loadingQueue, ev,ew);
			i++;
		}
	}		
	
	return 0;
}

