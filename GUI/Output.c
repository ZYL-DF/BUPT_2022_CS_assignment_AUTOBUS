#include"Bus.h"
#include"Input.h"
#include"List.h"
int globalTime=0;
void Output(){
    
    printf("TIME:%d\n",globalTime);
    
    printf("BUS:\n");
    
    printf("position:%d\n",bus.position);
    
    printf("target:");
    for(int i=1;i<=TOTAL_STATION;i++){
        if(CheckNote(&list1_Head,i,1)!=NULL){
            printf("1");
        }
        else{
            printf("0");
        }
    }
    printf("\n");

    printf("STATION:\n");

    printf("clockwise:");
    for(int i=1;i<=TOTAL_STATION;i++){
        if(CheckNote(&list2_Head,i,1)!=NULL){
            printf("1");
        }
        else{
            printf("0");
        }
    }
    printf("\n");

    printf("counterclockwise:");
    for(int i=1;i<=TOTAL_STATION;i++){
        if(CheckNote(&list2_Head,-i,1)!=NULL){
            printf("1");
        }
        else{
            printf("0");
        }
    }



    
    printf("\n");
/* TIME:0
BUS:
position:0
target:0000000000
STATION:
clockwise:0000000000
counterclockwise:0000000000 */

    globalTime++;
}
