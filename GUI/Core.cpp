#include"List.h"
#include"Input.h"
#include<QDebug>
#include"Bus.h"
//int BUS_DIRECT=0;
void CheckTarget(){
    if(STRATEGY==1){
        if(CheckNote(&list2_Head,0,2)!=NULL){
            
                int target=list2_Tail->s;

                    if(CheckNote(&target_Listhead,target,1)==NULL && bus.goal!=target && CheckNote(&target_Listhead,-1*target,1)==NULL){
                        AddList(target,-1,&target_Listhead,&target_Listtail);
                    }
                    
             
        }
        if(CheckNote(&list1_Head,0,2)!=NULL){
            
                int target=list1_Tail->s;
                //target=target*1000;
                   if(CheckNote(&target_Listhead,target,1)==NULL&& bus.goal!=target){
                   AddList(target,-1,&target_Listhead,&target_Listtail);
                }
               
            
            
        }

         /* Node* temp=target_Listhead;
        while(temp!=NULL){
            printf("%d ",temp->s);
            temp=temp->next;
        }  */
    }
}
int getTarget(){    
    if(STRATEGY==1){
        LIST1_NUM=0,LIST2_NUM=0;
        int note_pos;
	    Node* temp=target_Listhead;
	    while (temp!= NULL)
	    {
            
            int temp_s=temp->s;
            int is_list1=0;
            if(temp_s>=1000){
                temp_s=temp_s/1000;
                is_list1=1;
            }
            if(abs(temp_s)==bus.stand){
                DeleteList(&target_Listhead,&target_Listtail,0);
                temp=target_Listhead;
                if(is_list1==1){
                    LIST1_NUM++;
                }
                else{
                    LIST2_NUM++;
                }
            }
            else{
                break;
            }
            if(temp==NULL){
                break;
            }
            else{
                temp=temp->next;
            }
                
            
            
		    
			    
		
	    }

        /* if(target>=1000){//当前目标是list1里面的
                    target=target/1000;
                    LIST1_NUM++;
                }
                else{//当前目标是list2里面的
                    LIST2_NUM++;
                } */
        //先对后续相同站点的节点从list1，list2，targetlist中删去
        //LIST1_NUM,LIST2_NUM为要从list1，list2中从头连续删掉的，bus.c中实现
        /* temp=CheckNote(&target_Listhead, -1*bus.goal, 1);
	    while (temp!= NULL)
	    {
		
		    
			    note_pos=getPositionOfList(&target_Listhead,&temp);	
			    if(note_pos!=-1)		
			    {
				    DeleteList(&target_Listhead, &target_Listtail, note_pos);
				    //list1_cur=list1_Head;
			    }
		    
		    if(target_Listhead!=NULL){
			    temp=CheckNote(&target_Listhead, -1*bus.goal, 1);
		    }
            else{
			temp=NULL;
		    }
		
	    } */


        if(CheckNote(&list1_Head,0,2)==NULL && CheckNote(&list2_Head,0,2)==NULL){
            return 0;
        }
            else{
                if (CheckNote(&target_Listhead,0,2)!=NULL)
                {
                    int target=target_Listhead->s;

               
                
                Node *temp_all_head=NULL;
                Node *temp_all_tail=NULL;

                if(target>=1000){//当前目标是list1里面的
                    target=target/1000;
                    BUS_FROM=1;
                }
                else{//当前目标是list2里面的
                    BUS_FROM=2;
                } 

                AddList(target,-1,&temp_all_head,&temp_all_tail);
                target=SortList_B(&temp_all_head,bus.stand,TOTAL_STATION,DISTANCE);
                DeleteList(&target_Listhead,&target_Listtail,0);
                
                return target;
            }




        }
    }
    if(STRATEGY==2){
        Node *temp1=list1_Head;
        Node *temp2=list2_Head;
        int target1=SortList_B(&temp1,bus.stand,TOTAL_STATION,DISTANCE);
        int target2=SortList_B(&temp2,bus.stand,TOTAL_STATION,DISTANCE);
        if(target1==NULL && target2==NULL){
            return 0;
        }
        else if(target1==NULL){
           
            return target2;
        }
        else if(target2==NULL){
            return target1;
        }
        else{

        
            Node *temp_all_head=NULL;
            Node *temp_all_tail=NULL;
            AddList(target1,-1,&temp_all_head,&temp_all_tail);
            AddList(target2,-1,&temp_all_head,&temp_all_tail);
            int target_all=SortList_B(&temp_all_head,bus.stand,TOTAL_STATION,DISTANCE);
            return target_all;
        }

    }

    if(STRATEGY==3){
        Node *temp1=list1_Head;
        Node *temp2=list2_Head;
        int target1=SortList_C(&temp1,bus.stand,TOTAL_STATION,BUS_DIRECT,DISTANCE);
        int target2=SortList_C(&temp2,bus.stand,TOTAL_STATION,BUS_DIRECT,DISTANCE);
        if(target1==NULL && target2==NULL){
            return 0;
        }
        else if(target1==NULL){
           
            if(target2>0 && BUS_DIRECT==0){
             BUS_DIRECT=1;
            }
            else if(target2<0 && BUS_DIRECT==0){
             BUS_DIRECT=-1;
            }


            return target2;
        }
        else if(target2==NULL){
            
            if(target1>0 && BUS_DIRECT==0){
             BUS_DIRECT=1;
            }
            else if(target1<0 && BUS_DIRECT==0){
             BUS_DIRECT=-1;
            }


            return target1;
        }
        else{

        
            Node *temp_all_head=NULL;
            Node *temp_all_tail=NULL;
            AddList(target1,-1,&temp_all_head,&temp_all_tail);
            AddList(target2,-1,&temp_all_head,&temp_all_tail);
            int target_all=SortList_C(&temp_all_head,bus.stand,TOTAL_STATION,BUS_DIRECT,DISTANCE);

            if(target_all>0 && BUS_DIRECT==0){
             BUS_DIRECT=1;
            }
            else if(target_all<0 && BUS_DIRECT==0){
             BUS_DIRECT=-1;
            }

            return target_all;
        }

    }
    return 0;
}
