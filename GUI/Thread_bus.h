#ifndef THREAD_BUS_H
#define THREAD_BUS_H


#include <QObject>
#include <QEventLoop>

extern int TIME;

class BusThread : public QObject
{
    Q_OBJECT
public:
    explicit BusThread(QObject *parent = nullptr);
    //void Output_Pre(int);//发送output信号
    // 工作函数

//QEventLoop loop;

signals:
void Output(int);//output信号(TIME)
void MoveBus(int);
void update_one_sec();
public slots:
void eventloop_out();
void BusWorking();
void update_();
//void Input(int,int);//接受命令，输入队列一二之中



};



#endif // THREAD_BUS_H
