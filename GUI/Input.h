/* #include<stdio.h>
 #include<string.h>
#include<stdlib.h> 
#include"List.h"  */
 /*定义链表List*/
#ifndef _INPUT_H
#define _INPUT_H

/*定义四个全局变量*/ 
extern int TOTAL_STATION;
extern int STRATEGY;
extern int DISTANCE;
extern int judgement_read;
void read();
//void Input();
//void readInput();

struct Innode
{
	int num;
	int data;
	struct Innode* last;
	struct Innode* next;
};
//extern struct Innode* List_Head;
#endif
