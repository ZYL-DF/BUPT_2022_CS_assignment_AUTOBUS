#include"input.h"
#include"List.h"
#include"Bus.h" 
Bus bus;
int LIST1_NUM=0,LIST2_NUM=0,BUS_FROM=0;
int BUS_FROM_PRE=0;
int BUS_DIRECT=0;
void iniBus()
{
	bus.position = 0;
	bus.num = 0;
	bus.accumlated_second = 0;
	bus.orbit_number = 0;//最初位于1号站点的0单位上
	bus.stand = 1;//最初站为1号站
	bus.state = 0;//公车的最初为静止状态
	bus.direct=0;//为策略三做准备
}

/*传入参数state表当前状态*/
/*ptr是定义好的轨道，在这里ptr会随要求顺逆时针而指向前驱或后驱节点*/
/*
使用：move(bus,(state)1,ptr);//在第1次运行完成以后position应返回1，ptr指向后驱节点
*/
void move(int target)
{
	

	 if(bus.state==_stop_temp)
	{
		
	if(STRATEGY==2){

		
		int note_pos;
		Node* temp=CheckNote_B(&list1_Head, bus.stand, 1);
		while (temp!= NULL)
		{
		/*或者判断列队里面有没有跟goal一样,并且onesecond超过一秒的要求,若有就直接删除该节点*/
		/*找有没有相同的请求的节点*/
		//temp = CheckNote(&list1_Head, bus.goal, 1);
		/*判断要不要删除？*/
			if (temp->is_Onesec == 1)//有找到
			{
				note_pos=getPositionOfList(&list1_Head,&temp);	
				if(note_pos!=-1)		
				{
					DeleteList(&list1_Head, &list1_Tail, note_pos);
					//list1_cur=list1_Head;
				}
			}
			if(list1_Head!=NULL){
				temp=CheckNote_B(&list1_Head, bus.stand, 1);
			}
			else{
				temp=NULL;
			}
		
		}

		//Node* list2_cur = list2_Head;
		temp=CheckNote_B(&list2_Head, bus.direct*bus.stand, 1);
		while (temp!= NULL)
		{
			if (temp->is_Onesec == 1)//有找到
			{
				note_pos=getPositionOfList(&list2_Head,&temp);	
				if(note_pos!=-1)		
				{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				//list1_cur=list1_Head;
				}
			}
			if(list2_Head!=NULL){
				temp=CheckNote_B(&list2_Head, bus.direct*bus.stand, 1);
			}
			else{
				temp=NULL;
			}
		
	
		}

		
	}

	if(STRATEGY==3){

		
		int note_pos;
		Node* temp=CheckNote_B(&list1_Head, bus.stand, 1);
		while (temp!= NULL)
		{
		/*或者判断列队里面有没有跟goal一样,并且onesecond超过一秒的要求,若有就直接删除该节点*/
		/*找有没有相同的请求的节点*/
		//temp = CheckNote(&list1_Head, bus.goal, 1);
		/*判断要不要删除？*/
			if (temp->is_Onesec == 1)//有找到
			{
				note_pos=getPositionOfList(&list1_Head,&temp);	
				if(note_pos!=-1)		
				{
					DeleteList(&list1_Head, &list1_Tail, note_pos);
					//list1_cur=list1_Head;
				}
			}
			if(list1_Head!=NULL){
				temp=CheckNote_B(&list1_Head, bus.stand, 1);
			}
			else{
				temp=NULL;
			}
		
		}

		//Node* list2_cur = list2_Head;
		temp=CheckNote_B(&list2_Head, bus.stand, 1);
		while (temp!= NULL)
		{
			if (temp->is_Onesec == 1)//有找到
			{
				note_pos=getPositionOfList(&list2_Head,&temp);	
				if(note_pos!=-1)		
				{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				//list1_cur=list1_Head;
				}
			}
			if(list2_Head!=NULL){
				temp=CheckNote_B(&list2_Head, bus.stand, 1);
			}
			else{
				temp=NULL;
			}
		
	
		}

		temp=CheckNote_B(&list2_Head, -1*bus.stand, 1);
		while (temp!= NULL)
		{
			if (temp->is_Onesec == 1)//有找到
			{
				note_pos=getPositionOfList(&list2_Head,&temp);	
				if(note_pos!=-1)		
				{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				//list1_cur=list1_Head;
				}
			}
			if(list2_Head!=NULL){
				temp=CheckNote_B(&list2_Head, -1*bus.stand, 1);
			}
			else{
				temp=NULL;
			}
		
	
		}

	}
		

		if(target==0)
			{
				bus.state=_idle;
				
			}
			else if(target>0)
			{
				bus.state=_goclockwise;
				bus.goal=target;
			}
			else if(target<0)
			{
				bus.state=_gocounterclockwise;
				bus.goal=abs(target);
			}

		return;
	} 

if(bus.state==_stop){

	if(STRATEGY==1){


		if(BUS_FROM_PRE==1){
			LIST1_NUM++;
		}
		else if(BUS_FROM_PRE==2){
			LIST2_NUM++;
		}
	
	for(int i=0;i<LIST1_NUM;i++){
            DeleteList(&list1_Head,&list1_Tail,0);
        }
    for(int i=0;i<LIST2_NUM;i++){
            DeleteList(&list2_Head,&list2_Tail,0);
        }
	
}

if(STRATEGY==2||STRATEGY==3){

	
	/* Node* list1_cur = list1_Head;
	int note_pos;
	Node* temp;
	while (list1_cur != NULL)
	{
		/*或者判断列队里面有没有跟goal一样,并且onesecond超过一秒的要求,若有就直接删除该节点*/
		/*找有没有相同的请求的节点*/
		//temp = CheckNote(&list1_Head, bus.goal, 1);
		/*判断要不要删除？*/
		/*if (list1_cur->s == bus.goal&&bus.goal==bus.stand && list1_cur->is_Onesec == 1)
		{
			note_pos=getPositionOfList(&list1_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list1_Head, &list1_Tail, note_pos);
				list1_cur=list1_Head;
			}
		}
		if(list1_cur!=NULL){
			list1_cur = list1_cur->next;
		}
	}

	Node* list2_cur = list2_Head;
	while (list2_cur!= NULL)
	{
		temp= CheckNote(&list2_Head,bus.goal, 1);
		if (list2_cur->s== bus.goal &&bus.goal==bus.stand &&list2_cur->is_Onesec == 1)
		{
			note_pos=getPositionOfList(&list2_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				list2_cur=list2_Head;
			}
		}
		if(list2_cur!=NULL){
			list2_cur =list2_cur->next;
		}
		
	
	}
	
	Node* list3_cur = list2_Head;
	while (list3_cur!= NULL)
	{
		temp= CheckNote(&list2_Head,-1*bus.goal, 1);
		if (list3_cur->s== -1*bus.goal &&bus.goal==bus.stand &&list3_cur->is_Onesec == 1)
		{
			note_pos=getPositionOfList(&list2_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				list3_cur=list2_Head;
			}
		}
		if(list3_cur!=NULL){
			list3_cur =list3_cur->next;
		}
		
	
	} */

	int note_pos;
	Node* temp=CheckNote_B(&list1_Head, bus.goal, 1);
	while (temp!= NULL)
	{
		/*或者判断列队里面有没有跟goal一样,并且onesecond超过一秒的要求,若有就直接删除该节点*/
		/*找有没有相同的请求的节点*/
		//temp = CheckNote(&list1_Head, bus.goal, 1);
		/*判断要不要删除？*/
		if (temp->is_Onesec == 1)//有找到
		{
			note_pos=getPositionOfList(&list1_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list1_Head, &list1_Tail, note_pos);
				//list1_cur=list1_Head;
			}
		}
		if(list1_Head!=NULL){
			temp=CheckNote_B(&list1_Head, bus.goal, 1);
		}
		else{
			temp=NULL;
		}
		
	}

	//Node* list2_cur = list2_Head;
	temp=CheckNote_B(&list2_Head, bus.goal, 1);
	while (temp!= NULL)
	{
		if (temp->is_Onesec == 1)//有找到
		{
			note_pos=getPositionOfList(&list2_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				//list1_cur=list1_Head;
			}
		}
		if(list2_Head!=NULL){
			temp=CheckNote_B(&list2_Head, bus.goal, 1);
		}
		else{
			temp=NULL;
		}
		
	
	}

	temp=CheckNote_B(&list2_Head, -1*bus.goal, 1);
	while (temp!= NULL)
	{
		if (temp->is_Onesec == 1)//有找到
		{
			note_pos=getPositionOfList(&list2_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				//list1_cur=list1_Head;
			}
		}
		if(list2_Head!=NULL){
			temp=CheckNote_B(&list2_Head, -1*bus.goal, 1);
		}
		else{
			temp=NULL;
		}
		
	
	}
}

	if(target==0)
		{
			
			bus.state=_idle;
			bus.goal=0;
			//BUS_DIRECT=0;
			deleteSelfpos();
		}
		else if(target>0)
		{
			bus.state=_goclockwise;
			bus.goal=target;
		}
		else if(target<0)
		{
			bus.state=_gocounterclockwise;
			bus.goal=abs(target);
		}

		return;
}


	/*_idle为公车的最初的静止状态*/
	if (bus.state == _idle)
	{
		if(target==0)
		{
			
			bus.state=_idle;
			bus.goal=0;
			//BUS_DIRECT=0;
			deleteSelfpos();
		}
		else if(target>0)
		{
			bus.state=_goclockwise;
			bus.goal=target;
		}
		else if(target<0)
		{
			bus.state=_gocounterclockwise;
			bus.goal=abs(target);
		}
		bus.accumlated_second++;
		
	}

	
	/*顺时针行驶*/
	if (bus.state == _goclockwise)
	{
		bus.direct = 1;
		if (bus.stand != bus.goal)//当前"站点"不在目标站点上
		{
			bus.orbit_number++;
			
			Station_Pos =Station_Pos->next;
			bus.position = Station_Pos->position;
			if (bus.orbit_number == DISTANCE)//若完成一整个站点的移动
			{
				bus.stand++;
				bus.orbit_number = 0;
			}

			bus.accumlated_second++;//完成一步秒数+1
		}

		/*若超出第（TOTAL_STATION ）号站则代表重新返回1号站*/
		if (bus.stand == TOTAL_STATION + 1)
		{
			bus.stand = 1;
		}
		
	}

	/*逆时针行驶*/
	else if (bus.state == _gocounterclockwise)
	{
		bus.direct = -1;
		if (bus.stand != bus.goal)//当前站点不在目标站点上
		{
			bus.orbit_number++;//内轨道一样+1；
			
			Station_Pos = Station_Pos->previous;
			bus.position = Station_Pos->position;
			if (bus.orbit_number == DISTANCE)//若完成一整个站点的移动
			{
				bus.stand--;
				bus.orbit_number = 0;
			}

			bus.accumlated_second++;//完成一步秒数+1
		}

		//若超出1号站则代表重新返回第TOTAL_STATION 号站
		if (bus.stand == 0)
		{
			bus.stand = TOTAL_STATION;
		}
		
		
	}


	/* if(STRATEGY==1){
		if(bus.goal==bus.stand&& bus.state!=_stop && bus.orbit_number==0)
		{
			bus.state=_stop;
			return;
		}
	}

	 if(STRATEGY==2||STRATEGY==3){*/
		if(bus.goal==bus.stand && bus.state!=_stop && bus.orbit_number==0)
		{
			BUS_FROM_PRE=BUS_FROM;
			bus.state=_stop;
			return;
		}
	//}
	

	if(STRATEGY==2){//策略二顺便停车

	
		if((bus.state==1 || bus.state==2)&& bus.goal!=bus.stand && bus.orbit_number==0){//对下车不用区分方向
			Node* temp=list1_Head;
			while(temp!=NULL){
				if(temp->s==bus.stand &&temp->is_Onesec==1){
					bus.state=_stop_temp;
					return;
				}
				temp=temp->next;
			}
			

			temp=list2_Head;
			while(temp!=NULL){
				if(temp->s==bus.direct*bus.stand && temp->is_Onesec==1){
					bus.state=_stop_temp;
					return;
				}
				temp=temp->next;
			}

		}
	}

	if(STRATEGY==3){//策略三顺便停车

	
		if((bus.state==1 || bus.state==2)&& bus.goal!=bus.stand && bus.orbit_number==0){//对下车不用区分方向
			Node* temp=list1_Head;
			while(temp!=NULL){
				if(temp->s==bus.stand &&temp->is_Onesec==1){
					bus.state=_stop_temp;
					return;
				}
				temp=temp->next;
			}
			
			temp=list2_Head;
			while(temp!=NULL){
				if(abs(temp->s)==bus.stand && temp->is_Onesec==1){
					bus.state=_stop_temp;
					return;
				}
				temp=temp->next;
			}

		}
	}
}

//删除stop和idle状态下生成在自身位置的目标
void deleteSelfpos(){
	int note_pos;
	Node* temp=CheckNote_B(&list1_Head, bus.stand, 1);
	while (temp!= NULL)
	{
		/*或者判断列队里面有没有跟goal一样,并且onesecond超过一秒的要求,若有就直接删除该节点*/
		/*找有没有相同的请求的节点*/
		//temp = CheckNote(&list1_Head, bus.goal, 1);
		/*判断要不要删除？*/
		if (temp->is_Onesec == 1)//有找到
		{
			note_pos=getPositionOfList(&list1_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list1_Head, &list1_Tail, note_pos);
				//list1_cur=list1_Head;
			}
		}
		if(list1_Head!=NULL){
			temp=CheckNote_B(&list1_Head, bus.stand, 1);
		}
		else{
			temp=NULL;
		}
		
	}

	//Node* list2_cur = list2_Head;
	temp=CheckNote_B(&list2_Head, bus.stand, 1);
	while (temp!= NULL)
	{
		if (temp->is_Onesec == 1)//有找到
		{
			note_pos=getPositionOfList(&list2_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				//list1_cur=list1_Head;
			}
		}
		if(list2_Head!=NULL){
			temp=CheckNote_B(&list2_Head,bus.stand, 1);
		}
		else{
			temp=NULL;
		}
		
	
	}

	temp=CheckNote_B(&list2_Head, -1*bus.stand, 1);
	while (temp!= NULL)
	{
		if (temp->is_Onesec == 1)//有找到
		{
			note_pos=getPositionOfList(&list2_Head,&temp);	
			if(note_pos!=-1)		
			{
				DeleteList(&list2_Head, &list2_Tail, note_pos);
				//list1_cur=list1_Head;
			}
		}
		if(list2_Head!=NULL){
			temp=CheckNote_B(&list2_Head, -1*bus.stand, 1);
		}
		else{
			temp=NULL;
		}
		
	
	}
}