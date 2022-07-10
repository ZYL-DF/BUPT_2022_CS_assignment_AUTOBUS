#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#ifndef _LIST_H
#define _LIST_H


typedef struct Node
{
    int s;          //队列存放的站点值
    int is_Onesec;//判断是否已经生成1秒
    struct Node *next;
}Node;

typedef struct Station
{
    int position;          //队列存放的站点值
    struct Station *previous;
    struct Station *next;
}Station;


extern Node *list1_Head,*list2_Head; 
//定义队列一、二的链表头节点,list1为下车目的地,list2为发出请求的站点
extern Node *list1_Tail,*list2_Tail;
//定义队列一、二的链表尾节点,list1为下车目的地,list2为发出请求的站点
extern Station *Station_Head,*Station_Tail,*Station_Pos;

extern Node* target_Listhead;
extern Node* target_Listtail;//目标队列的定义
extern int BUS_DIRECT;//策略三永久方向

void AddList(int a,int pos,Node** head,Node** tail);
void DeleteList(Node **head,Node **tail,int pos);
void DeleteList_head(Node **head,Node **tail,int type);
void DeleteList_mid(Node **head,int pos);
void DeleteList_tail(Node **head,Node **tail);
int ScanList(Node **head,int is_printf);
void FindNote(Node *temp,int a,int type);
Node *CheckNote(Node **head,int a,int type);
Node *CheckNote_B(Node **head,int a,int type);
Node *CheckNote_C(Node **head,int a,int type);
void updateListSec(Node **head);
int getPositionOfList(Node **head,Node **node);
void AddListDouble(int a,Station** head,Station** tail);
void CreateStation(int n);
int Direction_Station(int pos_A,int pos_B,int type,int length);
int SortList_B(Node** head,int pos,int total_station,int distance);
int SortList_C(Node** head,int pos,int total_station,int direct,int disdance);
#endif