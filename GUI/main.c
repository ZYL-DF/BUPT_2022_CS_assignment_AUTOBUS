#include<stdio.h>
#include"List.h"
#include"Input.h"
#include"Output.h"
#include"Bus.h"
#include"Core.h"
int main(){

    
    read();
    Input();
    CreateStation(TOTAL_STATION*DISTANCE);
    /* PLNode L;//定义一个双向链表,L指向尾节点
	IniList(&L);
	//CreatList(&L);
    L=L->next->next; */
    iniBus();
    Output();
   // Init();      //初始化，包括车的建立，配置文件的导入
    while(judgement_read==0){
        readInput(); //读键盘
        if(judgement_read==1){
            break;
        }
        int target;
        if(bus.state==0 || bus.state==3){
            //CheckTarget();
            target=getTarget(); //由策略选择目标
            
                
                move(target);          //车向目标移动一个单位
            
            
        }
        else{
            //CheckTarget();
            move(target);            //车向目标移动一个单位
        } 
        if(bus.position==22){
            bus.position=22;
        }  
        Output();                  //输出这一秒内的状态

        
        updateListSec(&list1_Head);
        updateListSec(&list2_Head);
    }
    printf("end\n");
    getchar();
    getchar();
    return 0;
}
