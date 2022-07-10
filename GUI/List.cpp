#include"List.h"
#include<QDebug>
Node *list1_Head=NULL,*list2_Head=NULL; 
//定义队列一、二的链表头节点
Node *list1_Tail=NULL,*list2_Tail=NULL;
//定义队列一、二的链表尾节点

Node* target_Listhead=NULL;
Node* target_Listtail=NULL;//目标队列的定义

Station *Station_Head=NULL,*Station_Tail=NULL,*Station_Pos=NULL;

/**
 * @brief 添加节点功能
 * 
 * @param a 该节点s的值
 * @param pos 添加节点的位置，若填-1，则认为向链表末尾添加一个节点      
 *            添加之后，这个位置之后的节点统一后移
 * @param head 传入要添加节点的链表头节点(调用时记得加&)
 * @param tail 传入要添加节点的链表尾节点(调用时记得加&)
 */
void AddList(int a,int pos,Node** head,Node** tail){
    if(pos!=-1){
        
        Node *node=CheckNote(head,pos,2);
        //先统一检查注入节点是否存在
        if(node==NULL){
            printf("Add note failed!\nThe note is invaild\n");
        }
        else{
            Node * temp=(Node*)malloc(sizeof(Node));

            if(pos==0){     //如果是插入成为头节点
                temp->next=*head;
                temp->s=a;
                temp->is_Onesec=1;
                *head=temp;
            }

            else{           //在中间插入节点
                Node *node_previous=CheckNote(head,pos-1,2);
                temp->next=node;        //先接后面
                temp->s=a;
                temp->is_Onesec=1;
                node_previous->next=temp;   //再接前面
            }
        }

    }

    else{
        Node * temp=(Node*)malloc(sizeof(Node));

        temp->s=a;
        temp->is_Onesec=1;
        temp->next=NULL;
    
        if(*head==NULL){
            *head=temp;
        }

        else{
            (*tail)->next=temp;
        }
        *tail=temp;
    }
}
 
/**
 * @brief 删除节点功能
 * 
 * @param head 传进去的链表头，一般填&head
 * @param tail 传进去的链表尾，一般填&tail
 * @param pos 删除节点的位置(从0开始算），若填-1或不填，则认为在链表末尾删除一个节点      
 *            删除之后，这个位置之后的节点统一前移
 */
void DeleteList(Node **head,Node **tail,int pos){
    if(pos!=-1){                //指定删除节点

       int num=ScanList(head,0);

       if(num-1<pos){ //链表里没有节点，删除失败
           //printf("Could not find the node\nDelete list failed!\n");
       }
       else{

           if(pos==0){      //删除头节点
                if(num==1)
                    DeleteList_head(head,tail,2);
                else 
                    DeleteList_head(head,tail,1);
            }
            else if(pos>0 && pos<num-1){
                DeleteList_mid(head,pos);
            }
            else if(pos==num-1){
                DeleteList_tail(head,tail);
            }
        
       }
       
    }

    else{                        //默认删除最后一个节点
        int num=ScanList(head,0);

       if(num-1<pos){ //链表里没有节点，删除失败
           //printf("Could not find the node\nDelete list failed!\n");
       }
       else{
           if(num==1){
               DeleteList_head(head,tail,2);
           }
           else{
               DeleteList_tail(head,tail);
           }
       }
    }
}
 
/**
 * @brief 删除链表头节点
 * 
 * @param temp 传进去的链表头，一般填head
 * @param type 为1，有大于一个节点；为2，只有一个节点
 */
 void DeleteList_head(Node **head,Node **tail,int type){
     //Node* temp=*head;
    if(type==1){
        Node * temp2=(*head)->next;
        free(*head);
        *head=temp2;
    }
    else if(type==2){
        free(*head);
        *head=NULL;
        *tail=NULL;
    }
}


/**
 * @brief 删除链表中间节点
 * 
 * @param temp 传进去的链表头，一般填head
 * @param pos 要删除的节点序号（从零开始）
 */
void DeleteList_mid(Node **head,int pos){
    Node* temp=*head;
    int r_pos=0;
    while(r_pos<pos-1){
        temp=temp->next;
        r_pos++;
    }
    Node *pre_Node=temp;             //前一个节点
    Node *next_Node=temp->next->next;//后一个节点

    temp=temp->next;            //切换到pos所指的节点
    free(temp);
    pre_Node->next=next_Node;
}

/**
 * @brief 删除链表尾节点
 * 
 * @param temp 传进去的链表头，一般填head
 */
void DeleteList_tail(Node **head,Node **tail){
    Node* temp=*head;
    while(temp->next!=*tail){
            temp=temp->next;
            
        }

           free(*tail);
           temp->next=NULL;
           *tail=temp;
       
}


/**
 * @brief 输出当前链表内所有节点的s值
 * 
 * @param temp 传进去的链表头，一般填head
 * @param is_printf =1:输出，否则不输出
 * @return 链表中节点的个数 
 */
 int ScanList(Node **head,int is_printf){
    //printf("\n");
    int pos=0;
    Node *temp=*head;
    while (temp!=NULL)
    {
        if(is_printf) printf("%d\n",(temp)->s);
        temp=(temp)->next;
        pos++;
    }
    //printf("\n");
    return pos;
}
 
/**
 * @brief 查找结点功能
 * 
 * @param temp 传进去的链表头，一般填head
 * @param a type为1时，查找s为a的节点；type为2时，查找编号为a的节点（头节点从零开始）
 * @param type 1或2
 */
/* void FindNote(Node *temp,int a,int type){
    int pos=0;
    int isFound=0;
    switch (type)
    {
    case 1:{
        while (temp!=NULL)
        {
            if(temp->s==a){
                printf("%d is found at node %d\n",a,pos);
                isFound=1;
            }
            pos++;
            temp=temp->next;
        }
        if(isFound==0){
            printf("Could not find node\n");
        }
        break;
    }
        
    case 2:{
        while (temp!=NULL)
        {
            if(pos==a){
                printf("node %d is found,its point is %d\n",a,temp->s);
                break;
            }
            pos++;
            temp=temp->next;
        }
        if(a>pos){
            printf("Could not find node\n");
        }
        break;
    }
    }
    
} */


/**
 * @brief 检查节点是否存在
 * 
 * @param temp 传进去的链表头，一般填head
 * @param a type为1时，查找s为a的节点；type为2时，查找编号为a的节点（头节点从零开始）
 * @param type 1或2
 * @return Node* 返回第一个符合条件的节点；若无，则返回NULL
 */
 Node *CheckNote(Node **head,int a,int type){
    int pos=0;
    Node *temp=*head;
    switch (type)
    {
    case 1:{
        while (temp!=NULL)
        {
            if((temp)->s==a){
                //printf("%d is found at node %d\n",a,pos);
                return (temp);
                
            }
            pos++;
            temp=(temp)->next;
        }
            
            //printf("Could not find node\n");
            return NULL;

        break;
    }
        
    case 2:{
        while (temp!=NULL)
        {
            if(pos==a){
                return temp;
                break;
            }
            pos++;
            temp=(temp)->next;
        }
        if(a>pos || a<0){
            //printf("Could not find node\n");
            return NULL;
        }
        break;
    }

    default:{
        return NULL;
    }
    }
    return NULL;
}


Node *CheckNote_B(Node **head,int a,int type){
int pos=0;
    Node *temp=*head;
    switch (type)
    {
    case 1:{
        while (temp!=NULL)
        {
            if((temp)->s==a && temp->is_Onesec==1){
                //printf("%d is found at node %d\n",a,pos);
                return (temp);
                
            }
            pos++;
            temp=(temp)->next;
        }
            
            //printf("Could not find node\n");
            return NULL;

        break;
    }
        
    case 2:{
        while (temp!=NULL)
        {
            if(pos==a && temp->is_Onesec==1){
                return temp;
                break;
            }
            pos++;
            temp=(temp)->next;
        }
        if(a>pos || a<0){
            //printf("Could not find node\n");
            return NULL;
        }
        break;
    }

    default:{
        return NULL;
    }
    }
    return NULL;
}


Node *CheckNote_C(Node **head,int a,int type){
int pos=0;
    Node *temp=*head;
    switch (type)
    {
    case 1:{
        while (temp!=NULL)
        {
            if(abs((temp)->s)==a && temp->is_Onesec==1){
                //printf("%d is found at node %d\n",a,pos);
                return (temp);
                
            }
            pos++;
            temp=(temp)->next;
        }
            
            //printf("Could not find node\n");
            return NULL;

        break;
    }
        
    case 2:{
        while (temp!=NULL)
        {
            if(pos==a && temp->is_Onesec==1){
                return temp;
                break;
            }
            pos++;
            temp=(temp)->next;
        }
        if(a>pos || a<0){
            //printf("Could not find node\n");
            return NULL;
        }
        break;
    }

    default:{
        return NULL;
    }
    }
    return NULL;
}



/**
 * @brief 负责更新节点存在的时间，是否大于1s
 * 
 * @param head 
 */
void updateListSec(Node **head){
    Node* temp=*head;
    while(temp!=NULL){
        if(temp->is_Onesec==0){
            temp->is_Onesec=1;
        }
        temp=temp->next;
    }
}

/**
 * @brief 返回传入指定节点在指定队列中的位置，从0开始
 * 
 * @param head 指定节点
 * @param node 指定队列
 * @return int 指定节点在指定队列中的位置
 */
int getPositionOfList(Node **head,Node **node){
    int i=0;
    Node* temp=*head;
    if(*node==NULL){
        return -1;
    }
    while(temp!=NULL){
        if(temp==*node){
            return i;
        }
        temp=temp->next;
        i++;
    }
    return -1;
}

/**
 * @brief 创建一个双向链表
 * 
 * @param a 节点填充的值
 * @param head 链表头
 * @param tail 链表尾
 */
void AddListDouble(int a,Station** head,Station** tail){
    
        Station * temp=( Station*)malloc(sizeof( Station));

        temp->position=a;
        
        temp->next=NULL;
        temp->previous=NULL;
        if(*head==NULL){
            
            *head=temp;
        }

        else{
            
            temp->previous=*tail;
            (*tail)->next=temp;

        }
        *tail=temp;
    
}

/**
 * @brief 创建一个符合题意的双向链表
 * 
 * @param n 总长度
 */
void CreateStation(int n){
    for(int i=0;i<n;i++){
        AddListDouble(i,&Station_Head,&Station_Tail);
    }
    Station_Tail->next=Station_Head;
    Station_Head->previous=Station_Tail;
    Station_Pos=Station_Head;
}

int SortList_A(Node** head,int pos,int total_station){
    Node* temp=*head;
    int sort_num[100];
    for(int i=0;i<100;i++){
        sort_num[i]=0;
    }
     
    int num=0;
    while(temp!=NULL){
        
           if(temp->s>0 && abs(temp->s)!=pos){
               if(temp->s>=pos){
                   sort_num[num]=temp->s-pos;
                   num++;
               }
               else{
                    sort_num[num]=total_station+temp->s-pos;
                    num++;
               }
           }
           else if(abs(temp->s)!=pos){
               if(abs(temp->s)<=pos){
                   sort_num[num]=-1*(temp->s+pos);
                   num++;
               }
               else{
                    sort_num[num]=-1*(pos+total_station-abs(temp->s));
                    num++;
               }
           } 
        
        
        temp=temp->next;
        
    }
    for(int i=0;i<num;i++){
        for(int j=i;j<num;j++){
            if(abs(sort_num[i])>abs(sort_num[j])||(abs(sort_num[i])==abs(sort_num[j]) && abs(sort_num[i]<0))){
                int change=sort_num[i];
                sort_num[i]=sort_num[j];
                sort_num[j]=change;
            }
        }
    }
    int result=0;
    if(num>0){
        if(sort_num[0]>=0){

        result=pos+sort_num[0] ;
        if(result>total_station){
            result=result-total_station;
        }
        }
        else{
                if (pos+sort_num[0]>0){
                
                    result=-1*(pos+sort_num[0]);
                }
                else{
                    result=-1*(pos+sort_num[0]+total_station);
                }
                
        }
    }
    else{
        result=NULL;
    }
    
    return result;
}

/**
 * @brief 负责测量A,B站点之间的距离
 * 
 * @param pos_A A站点
 * @param pos_B B站点
 * @param type 1:顺时针计算 2：逆时针计算 3：顺逆时针都计算
 * @param length 站点之间的距离，DISTANCE
 * @return int 对于前两种，返回距离；对于第三种，返回最近的一种，前有正负号表示顺逆时针
 */
int Direction_Station(int pos_A,int pos_B,int type,int length){
    Station* temp=Station_Head;
    Station* temp2=Station_Head;
    pos_A=abs(pos_A);
    pos_B=abs(pos_B);
    while(temp->position!=(pos_A-1)*length){
        temp=temp->next;
    }
    while(temp2->position!=(pos_B-1)*length){
        temp2=temp2->next;
    }
    Station* temp3=temp;
    int distwise=0;
    int distcounter=0;
    while(temp!=temp2){
        distwise++;
        temp=temp->next;
    }
    temp=temp3;
    while(temp!=temp2){
        distcounter++;
        temp=temp->previous;
    }
    if(type==1){
        return distwise;
    }
    if(type==2){
        return -distcounter;
    }
    if(type==3){
        return distwise<=distcounter?distwise:-distcounter;
    }
    return 0;
}



/**
 * @brief 策略二使用的选择目标函数
 * 
 * @param head 链表头
 * @param pos 车当前位置
 * @param total_station 站点总数
 * @param distance 站点距离
 * @return int 返回最优选
 */
int SortList_B(Node** head,int pos,int total_station,int distance){
    Node* temp=*head;
    int sort_num[100];
    for(int i=0;i<100;i++){
        sort_num[i]=0;
    }
    int num=0;
    while(temp!=NULL){
        if(abs(temp->s)!=pos){//取最短路径
            /* if(abs(abs(temp->s)-pos)<=abs(total_station-abs(abs(temp->s)-pos))){
                if(abs(temp->s)>pos){
                    sort_num[num]=abs(temp->s)-pos;
                }
                else{
                    sort_num[num]=abs(temp->s)-pos;
                }
                num++;
            }
            else{
                if(abs(temp->s)>pos){
                    sort_num[num]=-1*abs(total_station-abs(abs(temp->s)-pos));
                }
                else{
                    sort_num[num]=abs(total_station-abs(abs(temp->s)-pos));
                }
                //sort_num[num]=-1*abs(total_station-abs(temp->s)+pos);
                num++;
            } */
            sort_num[num]=Direction_Station(pos,temp->s,3,distance);
            num++;
        }
        
        
        temp=temp->next;
        
    }

    for(int i=0;i<num;i++){
        for(int j=i;j<num;j++){
            if(abs(sort_num[i])>abs(sort_num[j])||(abs(sort_num[i])==abs(sort_num[j]) && abs(sort_num[i]<0))){
                int change=sort_num[i];
                sort_num[i]=sort_num[j];
                sort_num[j]=change;
            }
        }
    }
    int result=0;
    if(num>0){
       /*  if(sort_num[0]>=0){

        result=pos+sort_num[0] ;
        if(result>total_station){
            result=result-total_station;
        }
        }
        else{
                if (pos+sort_num[0]>0){
                
                    result=-1*(pos+sort_num[0]);
                }
                else{
                    result=-1*(pos+sort_num[0]+total_station);
                }
                
        } */
        result=pos+sort_num[0]/distance;
        if(result>total_station){
            result=result-total_station;
            
        }
        if(result<=0){
            result=total_station+result;
            
        }
        if(Direction_Station(pos,result,3,distance)<0){
                result=-1*result;
            }
    }
    else{
        result=NULL;
    }
    
    return result;
} 


int SortList_C(Node** head,int pos,int total_station,int direct,int distance){
    Node* temp=*head;
    int sort_num[100];
    for(int i=0;i<100;i++){
        sort_num[i]=0;
    }
    int num=0;
    if (direct==0)//没有确定方向时
    {
        while(temp!=NULL){
            if(abs(temp->s)!=pos){//取最短路径
               sort_num[num]=Direction_Station(pos,temp->s,3,distance);
                num++;
            }
        

            temp=temp->next;
        
        }
    }
    
    else if(direct==1){//顺时针方向计算距离
        while(temp!=NULL){
            if(abs(temp->s)!=pos){//取最短路径
                
                   sort_num[num]=Direction_Station(pos,temp->s,1,distance);
                
                               
                        
                    
                    num++;
            }
             temp=temp->next;
        }
        
        
           
        
    }

else if(direct==-1){//逆时针方向计算距离
        while(temp!=NULL){
            if(abs(temp->s)!=pos){//取最短路径
                
                    sort_num[num]=Direction_Station(pos,temp->s,2,distance);
                
                               
                        
                    
                    num++;
            }
            temp=temp->next;
        }
        
        
            
        
    }

    for(int i=0;i<num;i++){
        for(int j=i;j<num;j++){
            if(abs(sort_num[i])>abs(sort_num[j])||(abs(sort_num[i])==abs(sort_num[j]) && abs(sort_num[i]<0))){
                int change=sort_num[i];
                sort_num[i]=sort_num[j];
                sort_num[j]=change;
            }
        }
    }
    int result=0;
    if(num>0){
        //if(sort_num[0]>=0){

        /* result=pos+sort_num[0] ;
        if(result>total_station){
            result=result-total_station;
        }
        }
        else{
                if (pos+sort_num[0]>0){
                
                    result=-1*(pos+sort_num[0]);
                }
                else{
                    result=-1*(pos+sort_num[0]+total_station);
                } */
            result=pos+sort_num[0]/distance;
        if(result>total_station){
            result=result-total_station;
            
        }
        if(result<=0){
            result=total_station+result;
            
        }

        if(Direction_Station(pos,result,3,distance)<0){

                result=-1*result;

            }
                
        //}
    }
    else{
        result=NULL;
    }
    

    return result;
} 
