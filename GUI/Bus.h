#include<stdio.h>
#include<stdlib.h>

#ifndef _BUS_H
#define _BUS_H

typedef struct Bus
{
	int direct;
	int position;//轨道号（从0开始）
	int goal;//(当前目标站点)
	int accumlated_second;
	int num;
	int orbit_number;//表示为经过公车站后的单位,并规定处于站点时orbit_number=0
	int stand;//(公车上一个走过的站点)
	int state;
}Bus;

extern Bus bus;
extern int LIST1_NUM,LIST2_NUM,BUS_FROM;

/*准备定义环形轨道*/
typedef struct Pos_Node
{
	int position;
	struct Pos_Node* pre_ptr;
	struct Pos_Node* next;
}Pos_Node, * PLNode;

/*初始化链表*/
//void IniList(PLNode* L);

/*生成链表*/
//void CreatList(PLNode* L, int i);


/*定义不同状态*/
enum state_codes { _idle = 0, _goclockwise = 1, _gocounterclockwise = 2,_stop=3,_stop_temp=4 };


/*初始化公车最出静止时的资料*/
void iniBus();
void deleteSelfpos();
/*公车移动的函数*/
void move(int target);
#endif
