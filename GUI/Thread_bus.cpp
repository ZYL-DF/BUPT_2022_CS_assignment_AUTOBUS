#include "Thread_bus.h"
#include "mainwindow.h"
#include <QThread>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include<stdio.h>
#include"List.h"
#include"Input.h"
#include"Output.h"
#include"Bus.h"
#include"Core.h"

int TIME=0;
int PRE_POS=0;
QEventLoop* loop_pointer;
BusThread::BusThread(QObject *parent) : QObject(parent)
{


}





void BusThread::BusWorking()
{
    TIME=0;
    iniBus();

    CreateStation(TOTAL_STATION*DISTANCE);


    judgement_read=0;

    emit Output(TIME);

    while(1){

        if(judgement_read==1){

            iniBus();
            judgement_read=0;
            emit Output(-1);
            //qDebug()<<"send!";
            break;
        }
        int target;
        if(bus.state==0 || bus.state==3){
            //CheckTarget();
            target=getTarget(); //由策略选择目标


                move(target);          //车向目标移动一个单位


        }
        else{

            move(target);            //车向目标移动一个单位
        }

        //Output();                  //输出这一秒内的状态


        updateListSec(&list1_Head);
        updateListSec(&list2_Head);

        if(bus.position!=PRE_POS && bus.state!=3 && bus.state!=0 && bus.state!=4){
            emit MoveBus(bus.position);
            PRE_POS=bus.position;
        }

        if(bus.state!=0){
            MoveBus_fromidle_fix=0;
        }


            QEventLoop loop;
            loop_pointer=&loop;
            //QTimer *Ptimer  = new QTimer(this);
            QTimer::singleShot(SLEEP_TIME*1000, &loop, SLOT(quit()));





            loop.exec();//非阻塞延时，魔法!

            if(MoveBus_fromidle_fix==1){


                QEventLoop loop2;

                QTimer::singleShot(SLEEP_TIME*1000, &loop2, SLOT(quit()));
                qDebug()<<"cao";
                loop2.exec();//非阻塞延时，魔法!
            }


/*
        if(MoveBus_fromidle_fix==1){

            if(loop.isRunning()){
                loop.exit();

                QTimer::singleShot(10000, &loop, SLOT(quit()));
                loop.exec();//非阻塞延时，魔法!
            }


        }

        */


        //QThread::sleep(1);


        if(judgement_read==1){

            iniBus();
            judgement_read=0;
            emit Output(-1);

            break;
        }


        TIME++;


        emit Output(TIME);


    }



}


void BusThread::eventloop_out(){


if(MoveBus_fromidle_fix==1){

    if(loop_pointer ->isRunning()){
        loop_pointer ->exit();

        //QTimer::singleShot(10000, loop_pointer , SLOT(quit()));
        //loop_pointer ->exec();//非阻塞延时，魔法!
    }


}




}




void BusThread::update_(){
    while(1){
        QEventLoop loop;

        QTimer::singleShot(100, &loop, SLOT(quit()));

        loop.exec();

        emit update_one_sec();
    }

}
/*
void BusThread::Input(int type, int num){


     qDebug()<<type<<"  "<<num;

    if(type==3){
        if(STRATEGY==1){


                if(CheckNote(&list1_Head,num,1)==NULL){
                AddList(1000*num,-1,&target_Listhead,&target_Listtail);
                AddList(num,-1,&list1_Head,&list1_Tail);
               }
         }
        else{
            AddList(num,-1,&list1_Head,&list1_Tail);
        }

    }
    else if(type==1){
        if(STRATEGY==1){


                if(CheckNote(&list2_Head,num,1)==NULL){
                AddList(num,-1,&target_Listhead,&target_Listtail);
                AddList(num,-1,&list2_Head,&list2_Tail);
               }
         }
        else{
            AddList(num,-1,&list2_Head,&list2_Tail);
        }

    }
    else if(type==2){

        if(STRATEGY==1){


                if(CheckNote(&list2_Head,-1*num,1)==NULL){
                AddList(-1*num,-1,&target_Listhead,&target_Listtail);
                AddList(-1*num,-1,&list2_Head,&list2_Tail);
               }
         }
        else{
            AddList(-1*num,-1,&list2_Head,&list2_Tail);
        }
    }

    else if(type==4){
        judgement_read=1;
    }
}
*/
/*
void BusThread::Output_Pre(int TIME){


    emit Output(TIME);

}
*/
