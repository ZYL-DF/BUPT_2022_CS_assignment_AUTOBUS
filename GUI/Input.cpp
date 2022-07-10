#include<stdio.h>
#include<string.h>
#include"List.h"
#include<stdlib.h>
//#include<QDebug>
struct Innode
{
	int num;
	int data;
	struct Innode* last;
	struct Innode* next;
};
struct Innode* List_Head;
struct Innode* List_Tail;
/* struct Node *list1_Head,*list2_Head;
struct Node *list1_Tail,*list2_Tail; */
int TOTAL_STATION;
int STRATEGY;
int DISTANCE;
int judgement_read=0;
struct Innode* createList();
struct Innode* createNode();
void insertNodeByHead(struct Innode*headNode);
void cut(struct Innode*listhead);
struct Innode* list_point;
void read()
{
	/*定义相关变量*/ 
	char str4[500];
	int i,j,k;
	/*为相关变量赋值*/ 
	i=0;
	j=0;
	k=0;
    FILE*fp=fopen("./dict.dic","r");
	/*将文件内关键数据存入三大全局变量*/ 
	while(fgets(str4,500,fp)!=NULL)
	{

		/*若一行首字母为T，
		则其对应总站点数*/ 
		if(str4[0]=='T')
		{
			if(str4[18]=='\0')
			{
				TOTAL_STATION=str4[16]-48;
			}
			else if(str4[18]!='\0')
			{
				TOTAL_STATION=(str4[16]-48)*10+(str4[17]-48);
			}
			i=1;
		}
		/*若一行首字母为S，
		则其对应方法，注：1为FCFS，2为SSTF，３为SCAN*/ 
		if(str4[0]=='S')
		{
			if(str4[13]=='F')
			{
				STRATEGY=1;
			}
			else if(str4[13]=='T')
			{
				STRATEGY=2;
			}
			else if(str4[13]=='A')
			{
				STRATEGY=3;
			}
			j=1;
		}
		/*若其首字母为D，则其对应每站之间距离*/ 
		if(str4[0]=='D')
		{
			DISTANCE=str4[11]-48;
			k=1;
		}
		/*清空数组，防止越界*/ 
		memset(str4,0,sizeof(str4));
	}
	/*若文件中未标明该数据则取缺省值*/ 
	if(i==0)
	{
        TOTAL_STATION=5;
	}
	if(j==0)
	{
		STRATEGY=1;
	}
	if(k==0)
	{
		DISTANCE=2;
	}
}

/*
void Input()
{
	char str[25];
	int mid,judgement;
	judgement=1;
	mid=0;
	List_Head=createList();
	List_Tail=List_Head;
	while(judgement!=0)
	{
		scanf("%s",str);
		insertNodeByHead(List_Tail);
		List_Tail=List_Tail->next;
		if(str[1]=='o')
		{
			List_Tail->num=2;
			scanf("%d",&mid);
			List_Tail->data=mid*(-1);
		}
		else if(str[5]=='w')
		{
			List_Tail->num=2;
			scanf("%d",&mid);
			List_Tail->data=mid;
		}
		else if(str[1]=='a')
		{
			List_Tail->num=1;
			scanf("%d",&mid);
			List_Tail->data=mid;
		}
		else if(str[1]=='n')
		{
			List_Tail->num=0;
			judgement=0;
		}
		else
		{
			List_Tail->num=-1;
		}
		memset(str,0,sizeof(str));
		mid=0;	
	}
	cut(List_Head);
	list_point=List_Head->next;
}
void cut(struct Innode*listhead) 
{
	struct Innode*list;
	struct Innode*list_next;
	list=List_Head->next;
	while(list->num!=0)
	{
		list_next=list->next;
		if(list->num==list_next->num&&list->num!=-1&&list->data==list_next->data)
		{
			list->next=list_next->next;
			list_next->next=NULL;
			free(list_next);
		}
		else
		{
			list=list->next;
		}
	}
}
void readInput()
{
	if(list_point->next!=NULL)
	{
		if(list_point->num==1||list_point->num==2)
		{
			while(list_point->num!=-1&&list_point->num!=0&&list_point->next!=NULL)
			{
				if(list_point->num==1)
				{
					if(STRATEGY==1){
						int target=list_point->data;

                    	if(CheckNote(&list1_Head,target,1)==NULL){
                       	 	AddList(1000*target,-1,&target_Listhead,&target_Listtail);
							AddList(list_point->data,-1,&list1_Head,&list1_Tail);	
                    	}
					}
					else{
						AddList(list_point->data,-1,&list1_Head,&list1_Tail);
					}
					
					
					
					
				}
				else if(list_point->num==2)
				{
					
					if(STRATEGY==1){
						int target=list_point->data;

                    	if(CheckNote(&list2_Head,target,1)==NULL){
                       	 	AddList(target,-1,&target_Listhead,&target_Listtail);
							AddList(list_point->data,-1,&list2_Head,&list2_Tail);	
                    	}
					}
					else{
						AddList(list_point->data,-1,&list2_Head,&list2_Tail);	
					}
					

					
				}
				list_point=list_point->next;
			}
		}
		list_point=list_point->next;
	}
	else
	{
		judgement_read=1;
	}
}
struct Innode* createList()
{
    struct Innode* headNode=(struct Innode*)malloc(sizeof(struct Innode));
    headNode->next=NULL;
    return headNode;
}
struct Innode* createNode()
{
    struct Innode* newNode=(struct Innode*)malloc(sizeof(struct Innode));
    newNode->next=NULL;
    return newNode;
}
void insertNodeByHead(struct Innode*headNode)
{
    struct Innode*newNode=createNode();
    headNode->next=newNode;
}
*/
