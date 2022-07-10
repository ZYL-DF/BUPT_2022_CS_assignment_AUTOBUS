#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QString>
#include <QScreen>
#include <QDebug>
#include <QMouseEvent>
#include <QLabel>
#include "Input.h"
#include "Bus.h"
#include <QThread>
#include <QSettings>
#include <QPropertyAnimation>
#include "List.h"
#include "Thread_bus.h"
#include "setting_window.h"


QThread* thread_1;
QThread* thread_2;
int SLEEP_TIME; //是秒来着
int THEME;
BusThread* bus_thread,*bus_thread_2;
int MoveBus_fromidle_fix=0;
int is_running=0;
QString qstrpath;
QPropertyAnimation *animation ;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setWindowIcon(QIcon(":/setting/godskin/logo.ico"));

    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
    player->setLoops(-1);//=QMediaPlayer::Infinite;



    load_res();
    ui->label_bus->move(100-ui->label_bus->height()/2,100-ui->label_bus->width()/2);


    connect(this,SIGNAL(wheel_type_label_up()),this,SLOT(slot_type_up()));
    connect(this,SIGNAL(wheel_type_label_down()),this,SLOT(slot_type_down()));
    connect(this,SIGNAL(wheel_num_label_up()),this,SLOT(slot_num_up()));
    connect(this,SIGNAL(wheel_num_label_down()),this,SLOT(slot_num_down()));

    connect(this,SIGNAL(mouse_click_label_order(int)),this,SLOT(order_sendout(int)));


    connect(this,SIGNAL(mouse_release_label_order()),this,SLOT(order_release()));

    connect(this,SIGNAL(MoveBus_fromidle(int)),this,SLOT(MoveBus(int)));

    connect(this,SIGNAL(open_setting()),this,SLOT(slot_open_setting()));

    connect(this,SIGNAL(open_setting()),&setting_window,SLOT(setvalue()));

    connect(&setting_window,SIGNAL(theme_changed()),this,SLOT(res_reload()));

    animation= new QPropertyAnimation(ui->label_bus, "geometry");


    QPalette color_palette;
    color_palette.setColor(QPalette::WindowText, color_list[13]);//设置颜色
    ui->label_order->setPalette(color_palette);



    thread_2=new QThread;
    bus_thread_2=new BusThread;
    bus_thread_2->moveToThread(thread_2);
    // 启动线程
    //thread_1->start();
    // 让工作的对象开始工作, 点击开始按钮, 开始工作
    connect(bus_thread_2,SIGNAL(update_one_sec()),this,SLOT(update()));
    connect(this,SIGNAL(thread_update_()),bus_thread_2,SLOT(update_()));
    // 启动线程
    thread_2->start();
    emit thread_update_();//优化，cpu从8%->0.8%!!!




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    painter.drawPixmap(QPoint(0,0),background);
    double dpi = QApplication::primaryScreen()->logicalDotsPerInch();//获取屏幕分辨率
    QPen pen_track,pen_position,pen_label;
    QBrush brush_positon;


    {
    QFont label_font("微软雅黑", 15, QFont::Bold, false);
    label_font.setPixelSize(15*dpi/72);

    //画按钮等ui区
    ui->label_type->setFont(label_font);
    ui->label_num->setFont(label_font);
    ui->label_order->setFont(label_font);
    pen_label.setWidth(2);
    //
    pen_label.setColor(QColor(0,0,0,255));
    pen_label.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen_label);

    //QRectF rect_one(700,40,250,100);
    //painter.drawRoundedRect(rect_one,10,10);
    //painter.drawLine(700,90,950,90);

    //QRectF rect_two(700,160,250,280);
    //painter.drawRoundedRect(rect_two,10,10);

    //QRectF rect_three(700,460,250,60);
    //painter.drawLine(825,460,825,520);
    //painter.drawRoundedRect(rect_three,10,10);

    //QRectF rect_four(700,580,250,60);

    //painter.drawRoundedRect(rect_four,10,10);
    }

    drawlabel();



    //画轨道
    pen_track.setWidth(10);
    //
    pen_track.setColor(color_list[0]);
    pen_track.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen_track);

    painter.drawRect(100,100,500,500);

    //画位置
    pen_position.setWidth(10);
    pen_position.setColor(color_list[0]);

    brush_positon.setColor(color_list[1]);
    brush_positon.setStyle(Qt::SolidPattern);
    painter.setPen(pen_position);
    painter.setBrush(brush_positon);

    {
        double pos_x=100.0;
        double pos_y=100.0;
        int total_station=TOTAL_STATION;
        //qDebug("%d,%d,%d",TOTAL_STATION,DISTANCE,STRATEGY);
        int distance=DISTANCE;
        int track_presented=1;
        for(int i=0;i<total_station*distance;i++){

            if(i % distance==0){
                painter.drawEllipse(QPoint(pos_x,pos_y),30,30);
            }
            else{
                painter.drawEllipse(QPoint(pos_x,pos_y),5,5);
            }

            station_pos[0][i]=pos_x;
            station_pos[1][i]=pos_y;
            /*
            if(abs(station_pos[0][i]-100.0)<1){
                station_pos[0][i]=100.0;
            }
            if(abs(station_pos[0][i]-600.0)<1){
                station_pos[0][i]=600.0;
            }
            if(abs(station_pos[1][i]-100.0)<1){
                station_pos[1][i]=100.0;
            }
            if(abs(station_pos[1][i]-600.0)<1){
                station_pos[1][i]=600.0;
            }*/


            if(track_presented==1){
                pos_x+=2000.0/(total_station*distance);
                pos_y=pos_y;
                if(pos_x>600){

                    pos_y+=pos_x-600;
                    pos_x=600;
                    track_presented=2;
                }
            }

            else if(track_presented==2){
                pos_x=pos_x;
                pos_y+=2000.0/(total_station*distance);
                if(pos_y>600){

                    pos_x-=pos_y-600;
                    pos_y=600;
                    track_presented=3;
                }
            }

            else if(track_presented==3){
                pos_x-=2000.0/(total_station*distance);
                pos_y=pos_y;
                if(pos_x<100){

                    pos_y-=100-pos_x;
                    pos_x=100;
                    track_presented=4;
                }
            }

            else if(track_presented==4){
                pos_x=pos_x;
                pos_y-=2000.0/(total_station*distance);
                if(pos_y<100){

                    pos_x-=100-pos_y;
                    pos_y=100;
                    track_presented=5;
                }
            }


        }





            //painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, "hello Qt");
        //编序号
        QFont station_font("微软雅黑", 20, QFont::Bold, false);
        station_font.setPixelSize(20*dpi/72);
        painter.setFont(station_font);
        for(int i=0;i<total_station*distance;i++){
            if(i % distance==0){

                QRectF rect_temp(station_pos[0][i]-20, station_pos[1][i]-20, 40, 40);

                //painter.drawRect(rect_temp);

                painter.drawText(rect_temp,Qt::AlignHCenter | Qt::AlignVCenter,QString::number(i/distance+1));
            }
        }


    }

    {

        QPen pen_background,pen_bus;
        QBrush brush_background,brush_bus;

        pen_background.setWidth(10);
        pen_background.setColor(color_list[3]);
        pen_background.setJoinStyle(Qt::RoundJoin);

        painter.setPen(pen_background);



        brush_background.setColor(color_list[4]);
        brush_background.setStyle(Qt::SolidPattern);

        painter.setBrush(brush_background);




        if(bus.state==1 ||bus.state==2 || bus.state==3||bus.state==4||MoveBus_fromidle_fix==1){//目标层


            if(bus_starting_point_chosen==0){
                if(bus.state==1 ||bus.state==2 ||bus.state==4||MoveBus_fromidle_fix==1){

                    bus_starting_point=bus.stand;

                    bus_starting_point_chosen=1;
                }

            }

            else{
                if(bus.state==3){
                    bus_starting_point_chosen=0;
                }

            }




            bus_ending_point=bus.goal;



                int pos_start=(bus_starting_point-1)*DISTANCE;
                int pos_end=(bus_ending_point-1)*DISTANCE;
                //int pos_start_2=(bus_starting_point-1)*DISTANCE;
                //int pos_end_2=(bus_ending_point-1)*DISTANCE;

                QPoint line_pos[6]={QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0)};

                //track_line(QPoint(station_pos[0][pos_start_2],station_pos[1][pos_start_2]),QPoint(station_pos[0][pos_end_2],station_pos[1][pos_end_2]),bus.direct,line_pos);
                //int track_number=track_num(QPoint(station_pos[0][pos_start_2],station_pos[1][pos_start_2]),QPoint(station_pos[0][pos_end_2],station_pos[1][pos_end_2]),bus.direct);
                track_line(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),QPoint(station_pos[0][pos_end],station_pos[1][pos_end]),bus.direct,line_pos);
                int track_number=track_num(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),QPoint(station_pos[0][pos_end],station_pos[1][pos_end]),bus.direct);
                painter.drawPolyline(line_pos,track_number);


                QFont station_font("微软雅黑", 20, QFont::Bold, false);
                station_font.setPixelSize(20*dpi/72);
                painter.setFont(station_font);



                while(1){



                    if(bus.direct==1){





                        if(pos_start>=TOTAL_STATION*DISTANCE){
                            pos_start=0;
                        }

                        if(pos_start%DISTANCE==0){

                            painter.drawEllipse(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),30,30);

                            QRectF rect_temp(station_pos[0][pos_start]-20, station_pos[1][pos_start]-20, 40, 40);



                            painter.drawText(rect_temp,Qt::AlignHCenter | Qt::AlignVCenter,QString::number(pos_start/DISTANCE+1));

                        }
                        else{

                            painter.drawEllipse(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),5,5);
                        }

                        if(pos_start==pos_end){
                            break;
                        }
                        pos_start++;
                    }
                    else if(bus.direct==-1){
                        if(pos_start<0){
                            pos_start=TOTAL_STATION*DISTANCE-1;
                        }

                        if(pos_start % DISTANCE==0){

                           painter.drawEllipse(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),30,30);

                           QRectF rect_temp(station_pos[0][pos_start]-20, station_pos[1][pos_start]-20, 40, 40);



                           painter.drawText(rect_temp,Qt::AlignHCenter | Qt::AlignVCenter,QString::number(pos_start/DISTANCE+1));
                        }
                        else{

                           painter.drawEllipse(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),5,5);
                        }


                        if(pos_start==pos_end){
                            break;
                        }
                        pos_start--;
                    }



                }









        }
        else {
            bus_starting_point_chosen=0;
        }

    }



    //实时轨---------------------------------------------------------
    {

        QPen pen_background,pen_bus;
        QBrush brush_background,brush_bus;

        pen_background.setWidth(10);
        pen_background.setColor(color_list[5]);
        pen_background.setJoinStyle(Qt::RoundJoin);

        painter.setPen(pen_background);



        brush_background.setColor(color_list[6]);
        brush_background.setStyle(Qt::SolidPattern);

        painter.setBrush(brush_background);




        if(bus.state==1 ||bus.state==2 || bus.state==3||bus.state==4||MoveBus_fromidle_fix==1){//目标层


            if(bus_starting_point_chosen_present==0){
                if(bus.state==1 ||bus.state==2 ||bus.state==4||MoveBus_fromidle_fix==1){

                    bus_starting_point_present=bus.stand;

                    bus_starting_point_chosen_present=1;
                }

            }

            else{
                if(bus.state==3){
                    bus_starting_point_chosen_present=0;
                }

            }




            bus_ending_point_present=bus.position;



                int pos_start=(bus_starting_point_present-1)*DISTANCE;
                int pos_end=bus_ending_point_present;
                QPoint bus_prepos(ui->label_bus->x()+ui->label_bus->width()/2,ui->label_bus->y()+ui->label_bus->height()/2);
                //int pos_start_2=(bus_starting_point-1)*DISTANCE;
                //int pos_end_2=(bus_ending_point-1)*DISTANCE;

                QPoint line_pos[6]={QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0)};
/*
                if(bus_prepos.x()-100<=25){
                    bus_prepos.setX(100);
                }
                if(bus_prepos.y()-100<=25){
                    bus_prepos.setY(100);
                }

*/
                //track_line(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),QPoint(station_pos[0][pos_end],station_pos[1][pos_end]),bus.direct,line_pos);
                //int track_number=track_num(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),QPoint(station_pos[0][pos_end],station_pos[1][pos_end]),bus.direct);
                track_line(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),bus_prepos,bus.direct,line_pos);
                int track_number=track_num(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),bus_prepos,bus.direct);

                painter.drawPolyline(line_pos,track_number);


                QFont station_font("微软雅黑", 20, QFont::Bold, false);
                station_font.setPixelSize(20*dpi/72);
                painter.setFont(station_font);



                while(1){



                    if(bus.direct==1){





                        if(pos_start>=TOTAL_STATION*DISTANCE){
                            pos_start=0;
                        }

                        if(pos_start%DISTANCE==0){

                            painter.drawEllipse(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),30,30);

                            QRectF rect_temp(station_pos[0][pos_start]-20, station_pos[1][pos_start]-20, 40, 40);



                            painter.drawText(rect_temp,Qt::AlignHCenter | Qt::AlignVCenter,QString::number(pos_start/DISTANCE+1));

                        }
                        else{

                            painter.drawEllipse(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),5,5);
                        }

                        if(pos_start==pos_end){
                            break;
                        }
                        pos_start++;
                    }
                    else if(bus.direct==-1){
                        if(pos_start<0){
                            pos_start=TOTAL_STATION*DISTANCE-1;
                        }

                        if(pos_start % DISTANCE==0){

                           painter.drawEllipse(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),30,30);

                           QRectF rect_temp(station_pos[0][pos_start]-20, station_pos[1][pos_start]-20, 40, 40);



                           painter.drawText(rect_temp,Qt::AlignHCenter | Qt::AlignVCenter,QString::number(pos_start/DISTANCE+1));
                        }
                        else{

                           painter.drawEllipse(QPoint(station_pos[0][pos_start],station_pos[1][pos_start]),5,5);
                        }


                        if(pos_start==pos_end){
                            break;
                        }
                        pos_start--;
                    }



                }









        }
        else {
            bus_starting_point_chosen_present=0;
        }

    }
    //update();
}


void MainWindow::drawlabel(){
    double dpi = QApplication::primaryScreen()->logicalDotsPerInch();//获取屏幕分辨率
    QFont label_font("微软雅黑", 20, QFont::Bold, false);


    QPalette color_palette;
    color_palette.setColor(QPalette::WindowText, color_list[7]);//设置颜色
    ui->label_strategy->setPalette(color_palette);
    QPalette color_palette2;
    color_palette2.setColor(QPalette::WindowText, color_list[2]);//设置颜色
    ui->label_type->setPalette(color_palette2);

    ui->label_num->setPalette(color_palette2);

    label_font.setPixelSize(20*dpi/72);

    ui->label_strategy->setFont(label_font);
    ui->label_bus_state->setFont(label_font);


    if(STRATEGY==1){
        ui->label_strategy->setText("先来先服务");
    }
    else if(STRATEGY==2){
        ui->label_strategy->setText("最短寻找时间优先");
    }
    else if(STRATEGY==3){
        ui->label_strategy->setText("顺便服务");
    }


    if(bus.state==0){

        color_palette.setColor(QPalette::WindowText, color_list[8]);//设置颜色
        ui->label_bus_state->setPalette(color_palette);

        ui->label_bus_state->setText("空闲");
    }
    else if(bus.state==1 || bus.state==2){

        color_palette.setColor(QPalette::WindowText, color_list[9]);//设置颜色
        ui->label_bus_state->setPalette(color_palette);

        ui->label_bus_state->setText("运行");
    }
    else if(bus.state==3){

        color_palette.setColor(QPalette::WindowText, color_list[10]);//设置颜色
        ui->label_bus_state->setPalette(color_palette);
        ui->label_bus_state->setText("到站");
    }
    else if(bus.state==4){

        color_palette.setColor(QPalette::WindowText, color_list[11]);//设置颜色
        ui->label_bus_state->setPalette(color_palette);
        ui->label_bus_state->setText("顺便服务");
    }

}

void MainWindow::wheelEvent(QWheelEvent *event)  {//type与num的滚轮实现
    int x = event->position().x();
    int y = event->position().y();


        if (x>=700 && x<=825 && y>=460 && y<=520){
            if(event->angleDelta().y()>0){
                emit wheel_type_label_up();
            }
            else{
                emit wheel_type_label_down();
            }

        }
        else if(x>=826 && x<=950 && y>=460 && y<=520){
            if(event->angleDelta().y()>0){
                emit wheel_num_label_up();
            }
            else{
                emit wheel_num_label_down();
            }
        }

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int x = event->position().x();
    int y = event->position().y();

    if(event->button() == Qt::LeftButton){
        if(x>=700 && x<=950 && y>=580 && y<=640){
            if(is_running==0){
                emit mouse_click_label_order(1);



                thread_1 = new QThread;

                bus_thread = new BusThread;


                    // 将工作的类对象移动到创建的子线程对象中
                bus_thread->moveToThread(thread_1);
                // 启动线程
                //thread_1->start();
                // 让工作的对象开始工作, 点击开始按钮, 开始工作
                connect(this, SIGNAL(mouse_click_label_start()), bus_thread,SLOT(BusWorking()));
                connect(this, SIGNAL(order(int,int)), this, SLOT(Input(int,int)));
                connect(bus_thread, SIGNAL(Output(int)), this, SLOT(Output(int)));
                connect(thread_1, SIGNAL(finished()),thread_1, SLOT(deleteLater()));
                connect(thread_1, SIGNAL(finished()),bus_thread, SLOT(deleteLater()));
                connect(bus_thread, SIGNAL(MoveBus(int)),this, SLOT(MoveBus(int)));
                connect(this, SIGNAL(mouse_click_label_release(int)),bus_thread, SIGNAL(Output(int)));
                connect(this,SIGNAL(MoveBus_fromidle_tothread()),bus_thread, SLOT(eventloop_out()));

                // 启动线程
                thread_1->start();
                emit mouse_click_label_start();

            }
            else{

                emit mouse_click_label_release(TIME);
                emit mouse_click_label_order(0);
            }

        }

        if(x>=810 && x<=840 && y>=5 && y<=35){
            emit open_setting();
        }
    }

}


void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    //int x = event->position().x();
    //int y = event->position().y();

    if(event->button() == Qt::LeftButton){
        //if(x>=700 && x<=950 && y>=580 && y<=640){
            emit mouse_release_label_order();
        //}
    }

}



void MainWindow::slot_type_down(){

    type_pos++;
    if(type_pos>=5){
        type_pos=1;
    }

    ui->label_type->setText(type_name[type_pos-1]);
}
void MainWindow::slot_type_up(){
    type_pos--;
    if(type_pos<=0){
        type_pos=4;
    }

    ui->label_type->setText(type_name[type_pos-1]);
}

void MainWindow::slot_num_down(){
    num_pos++;
    if(num_pos>TOTAL_STATION){
        num_pos=1;
    }

    ui->label_num->setText("第"+QString::number (num_pos, 10)+"站");
}
void MainWindow::slot_num_up(){
    num_pos--;
    if(num_pos<=0){
        num_pos=TOTAL_STATION;
    }

    ui->label_num->setText("第"+QString::number (num_pos, 10)+"站");
}

void MainWindow::order_sendout(int type){
    double dpi = QApplication::primaryScreen()->logicalDotsPerInch();//获取屏幕分辨率
    QFont label_font("微软雅黑", 15, QFont::Bold, false);
    label_font.setPixelSize(15*dpi/72);

    QPalette color_palette;
    color_palette.setColor(QPalette::WindowText, color_list[12]);//设置颜色
    ui->label_order->setPalette(color_palette);

    if(type==1){//发车

            qDebug()<<"fuck";
            is_running=1;
            ui->label_order->setText("执行命令");




    }
    else if(type==0){//执行命令


            if(type_pos==1){
            qDebug()<<"顺时针方向";

            emit order(1,num_pos);


            }
            else if(type_pos==2){
            qDebug()<<"逆时针方向";

            emit order(2,num_pos);
            }
            else if(type_pos==3){
            qDebug()<<"目标";

            emit order(3,num_pos);
            }
            else if(type_pos==4){
                qDebug()<<"停运";
                is_running=0;
                ui->label_order->setText("发车");

                emit order(4,0);

                animation->stop();
                ui->label_bus->move(100-ui->label_bus->height()/2,100-ui->label_bus->width()/2);
            }

            if(type_pos!=4 && bus.stand!=num_pos){

              if(MoveBus_fromidle_fix==0){



                if(bus.state==0){

                    MoveBus_fromidle_fix=1;
                    emit MoveBus_fromidle_tothread();

                    int direct=0;
                    if(abs(bus.stand-num_pos)<TOTAL_STATION/2){
                        if(bus.stand>num_pos){
                            direct=-1;
                        }
                        else{
                            direct=1;
                        }
                    }
                    else if(abs(bus.stand-num_pos)==TOTAL_STATION/2){
                        direct=1;
                    }
                    else{
                        if(bus.stand>num_pos){
                            direct=1;
                        }
                        else{
                            direct=-1;
                        }
                    }

                    if(direct>0){
                        bus.direct=1;
                        bus.goal=num_pos;
                        emit MoveBus_fromidle(bus.position);
                    }
                    else if(direct<0){
                        bus.direct=-1;
                        bus.goal=num_pos;
                        emit MoveBus_fromidle(bus.position);
                    }

                }

                else{
                    MoveBus_fromidle_fix=0;

                }

              }




         }

         if(bus.state!=0){
             MoveBus_fromidle_fix=0;
         }

    }


}

void MainWindow::order_release(){
    double dpi = QApplication::primaryScreen()->logicalDotsPerInch();//获取屏幕分辨率
    QFont label_font("微软雅黑", 15, QFont::Bold, false);
    label_font.setPixelSize(15*dpi/72);

    QPalette color_palette;
    color_palette.setColor(QPalette::WindowText, color_list[13]);//设置颜色
    ui->label_order->setPalette(color_palette);
}



void MainWindow::Input(int type, int num){


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
        //thread_1->requestInterruption();
        thread_1->quit();

    }
}


void MainWindow::Output(int time){

    QString output_text="TIME:"+QString::number(time,10)+"\n"+"BUS:\n"+"position:"+QString::number(bus.position,10)+"\ntarget:";
    for(int i=1;i<=TOTAL_STATION;i++){
        if(CheckNote(&list1_Head,i,1)!=NULL){
           output_text=output_text+"1";
           // printf("1");
        }
        else{
            output_text=output_text+"0";
            //printf("0");
        }
    }

    output_text=output_text+"\n"+"STATION:\nclockwise:";



    for(int i=1;i<=TOTAL_STATION;i++){
        if(CheckNote(&list2_Head,i,1)!=NULL){

            output_text=output_text+"1";
            //printf("1");
        }
        else{

            output_text=output_text+"0";
            //printf("0");
        }
    }


    output_text=output_text+"\n"+"counterclockwise:";
    for(int i=1;i<=TOTAL_STATION;i++){
        if(CheckNote(&list2_Head,-1*i,1)!=NULL){

            output_text=output_text+"1";
            //printf("1");
        }
        else{

            output_text=output_text+"0";
            //printf("0");
        }
    }


    double dpi = QApplication::primaryScreen()->logicalDotsPerInch();//获取屏幕分辨率
    QFont label_font("微软雅黑", 14, QFont::Bold, false);
    label_font.setPixelSize(14*dpi/72);

    QPalette color_palette;
    color_palette.setColor(QPalette::WindowText, color_list[14]);//设置颜色
    ui->label_output->setPalette(color_palette);
    ui->label_output->setFont(label_font);

    if(time==-1){
        //qDebug()<<"STOP!";
        ui->label_output->setText("END");
    }
    else{
        ui->label_output->setText(output_text);
    }

}


void MainWindow::track_line(QPoint start,QPoint end,int direction,QPoint point_list[]){
    /*规定:[100,100]->(600,100)   1
     *    [600,100]->(600,600)   2
     *    [600,600]->(100,600)   3
     *    [100,600]->(100,100)   4
     */

    int start_pos=0,end_pos=0;
    int list_pos=1;
    QPoint arc_point[4]={QPoint(100,100),QPoint(600,100),QPoint(600,600),QPoint(100,600)};


    point_list[0]=start;

    if(start.x()>=100 && start.x()<600 && start.y()==100){
        start_pos=1;
    }
    else if(start.x()==600 && start.y()>=100 && start.y()<600){
        start_pos=2;
    }
    else if(start.x()>100 && start.x()<=600 && start.y()==600){
        start_pos=3;
    }
    else if(start.x()==100 && start.y()>100 && start.y()<=600){
        start_pos=4;
    }

    if(end.x()>=100 && end.x()<600 && end.y()==100){
        end_pos=1;
    }
    else if(end.x()==600 && end.y()>=100 && end.y()<600){
        end_pos=2;
    }
    else if(end.x()>100 && end.x()<=600 && end.y()==600){
        end_pos=3;
    }
    else if(end.x()==100 && end.y()>100 && end.y()<=600){
        end_pos=4;
    }
    //qDebug()<<"s:"<<start_pos<<"   e:"<<end_pos<<"   sx:"<<start.x()<<"   sy:"<<start.y()<<"   ex:"<<end.x()<<"   ey:"<<end.y();
    while(start_pos!=end_pos){

        if(direction==-1){//逆时针，取前者

            point_list[list_pos]=arc_point[start_pos-1];
            list_pos++;

        }


        if(direction==1){
            start_pos++;
        }
        else {
            start_pos--;
        }

        if(start_pos>4){
            start_pos=1;
        }
        if(start_pos<1){
            start_pos=4;
        }

        if(direction==1){//顺时针，取后者

            point_list[list_pos]=arc_point[start_pos-1];
            list_pos++;

        }

    }

    point_list[list_pos]=end;

}


int MainWindow::track_num(QPoint start,QPoint end,int direction){
    /*规定:[100,100]->(600,100)   1
     *    [600,100]->(600,600)   2
     *    [600,600]->(100,600)   3
     *    [100,600]->(100,100)   4
     */

    int start_pos=0,end_pos=0;
    int list_num=2;


    if(start.x()>=100 && start.x()<600 && start.y()==100){
        start_pos=1;
    }
    else if(start.x()==600 && start.y()>=100 && start.y()<600){
        start_pos=2;
    }
    else if(start.x()>100 && start.x()<=600 && start.y()==600){
        start_pos=3;
    }
    else if(start.x()==100 && start.y()>100 && start.y()<=600){
        start_pos=4;
    }

    if(end.x()>=100 && end.x()<600 && end.y()==100){
        end_pos=1;
    }
    else if(end.x()==600 && end.y()>=100 && end.y()<600){
        end_pos=2;
    }
    else if(end.x()>100 && end.x()<=600 && end.y()==600){
        end_pos=3;
    }
    else if(end.x()==100 && end.y()>100 && end.y()<=600){
        end_pos=4;
    }

    //qDebug()<<"s:"<<start_pos<<"   e:"<<end_pos<<"   x:"<<start.x()<<"   y:"<<start.y();
    while(start_pos!=end_pos){




        if(direction==1){
            start_pos++;
        }
        else {
            start_pos--;
        }

        if(start_pos>4){
            start_pos=1;
        }
        if(start_pos<1){
            start_pos=4;
        }

        list_num++;

    }
    //qDebug()<<"list_NUM:"<<list_num;
    return list_num;


}

void MainWindow::load_res(){

    QSettings settings("config.ini",QSettings::IniFormat);

    settings.beginGroup("setting");//进入到节
        if(!settings.childKeys().contains("interval")){//判断节中是否存在键
            settings.setValue("interval","1"); //若不存在则创建并赋值为1
            SLEEP_TIME=1;
        }
        else{
            SLEEP_TIME= settings.value("interval").toInt(); //存在则取出键的值
            qDebug()<< "interval"<<SLEEP_TIME;
            }
        if(!settings.childKeys().contains("theme")){//判断节中是否存在键
            settings.setValue("theme","0"); //若不存在则创建并赋值为0
            THEME=0;
        }
        else{
            THEME = settings.value("theme").toInt(); //存在则取出键的值
            qDebug()<< "theme"<<THEME;
            }
        settings.endGroup();  //beginGroup后必须endGroup



        QString theme_name[]={"classic","darkness","green","blue","pink","year","cyberpunk","tuwei","eldenring","genshin","genshit"};

    bus_pix.load(":/"+theme_name[THEME]+"/godskin/"+theme_name[THEME]+"/bus.png");

    ui->label_bus->setPixmap(bus_pix);
    ui->label_bus->setScaledContents(true);//自适应大小
    ui->label_bus->resize(76, 76);



    background.load(":/"+theme_name[THEME]+"/godskin/"+theme_name[THEME]+"/background.png");



    setting.load(":/"+theme_name[THEME]+"/godskin/"+theme_name[THEME]+"/setting.png");
    ui->label_setting->setPixmap(setting);
    ui->label_setting->setScaledContents(true);//自适应大小
    ui->label_setting->resize(20, 20);



    QString color_name[]={"track_bottom_pen","track_bottom_brush","track_bottom_text",
                            "track_target_pen","track_target_brush",
                           "track_present_pen","track_present_brush",
                         "str_color","idle","running","arrive","convenience","press",
                         "release","output"};


    QSettings settings2("theme.ini",QSettings::IniFormat);
    settings2.beginGroup(theme_name[THEME]);//进入到节
    for(int i=0;i<15;i++){
        color_list[i]=settings2.value(color_name[i]).value<QString>();
    }
    settings2.endGroup();  //beginGroup后必须endGroup



    QPalette color_palette2,color_palette7,color_palette8,color_palette13,color_palette14;
    color_palette7.setColor(QPalette::WindowText, color_list[7]);//设置颜色
    ui->label_strategy->setPalette(color_palette7);

    if(bus.state==0){
        color_palette8.setColor(QPalette::WindowText, color_list[8]);//设置颜色
    }
    else if(bus.state==1||bus.state==2){
        color_palette8.setColor(QPalette::WindowText, color_list[9]);//设置颜色
    }
    else if(bus.state==3){
        color_palette8.setColor(QPalette::WindowText, color_list[10]);//设置颜色
    }
    else if(bus.state==4){
        color_palette8.setColor(QPalette::WindowText, color_list[11]);//设置颜色
    }
    ui->label_bus_state->setPalette(color_palette8);

    color_palette13.setColor(QPalette::WindowText, color_list[13]);//设置颜色
    ui->label_order->setPalette(color_palette13);

    color_palette14.setColor(QPalette::WindowText, color_list[14]);//设置颜色
    ui->label_output->setPalette(color_palette14);

    color_palette2.setColor(QPalette::WindowText, color_list[2]);//设置颜色
    ui->label_type->setPalette(color_palette2);
    ui->label_num->setPalette(color_palette2);



    player->stop();

    qstrpath = "bgm/"+theme_name[THEME]+".mp3";
    player->setSource(QUrl(qstrpath));
    player->play();

    //player->setSource(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));


    //player->play();


}

void MainWindow::MoveBus(int start_pos){




    int pos_temp=start_pos;

    if(bus.direct==1){
        pos_temp++;
        if(pos_temp>=TOTAL_STATION*DISTANCE){
            pos_temp=0;

        }
    }
    else{
        pos_temp--;
        if(pos_temp<0){
            pos_temp=TOTAL_STATION*DISTANCE-1;

        }
    }
    int start_x=station_pos[0][start_pos];
    int start_y=station_pos[1][start_pos];
    int end_x=station_pos[0][pos_temp];
    int end_y=station_pos[1][pos_temp];
    QPoint arc_point[4]={QPoint(100,100),QPoint(600,100),QPoint(600,600),QPoint(100,600)};

    delete animation;
    animation= new QPropertyAnimation(ui->label_bus, "geometry");


    animation->setDuration(SLEEP_TIME*1000);




    if(start_x!=end_x &&start_y!=end_y){//过拐角
        qDebug()<<"fuck";
        double percent;

        animation->setKeyValueAt(0,QRect(station_pos[0][start_pos]-ui->label_bus->width()/2,station_pos[1][start_pos]-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
        if(bus.direct==1){

            if(start_x==100){//4
                percent=double(abs(100.0-start_y)/(abs(100.0-start_y)+abs(end_x-100.0)));
                animation->setKeyValueAt(percent, QRect(100-ui->label_bus->width()/2, 100-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
            }
            else if(start_x==600){//2
                percent=double(abs(600.0-start_y)/(abs(600.0-start_y)+abs(end_x-600.0)));
                animation->setKeyValueAt(percent, QRect(600-ui->label_bus->width()/2, 600-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
            }
            else if(start_y==100){//1
                percent=double(abs(600.0-start_x)/(abs(600.0-start_x)+abs(end_y-100.0)));
                animation->setKeyValueAt(percent, QRect(600-ui->label_bus->width()/2, 100-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
            }
            else if(start_y==600){//3
                percent=double(abs(100.0-start_x)/(abs(100.0-start_x)+abs(end_y-600.0)));
                animation->setKeyValueAt(percent, QRect(100-ui->label_bus->width()/2, 600-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
            }
        }
        else{
            if(start_x==100){//4
                percent=1-double(abs(600.0-start_y)/(abs(600.0-start_y)+abs(end_x-100.0)));
                animation->setKeyValueAt(percent, QRect(100-ui->label_bus->width()/2, 600-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
            }
            else if(start_x==600){//2
                percent=1-double(abs(100.0-start_y)/(abs(100.0-start_y)+abs(end_x-600.0)));
                animation->setKeyValueAt(percent, QRect(600-ui->label_bus->width()/2, 100-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
            }
            else if(start_y==100){//1
                percent=1-double(abs(100.0-start_x)/(abs(100.0-start_x)+abs(end_y-100.0)));
                animation->setKeyValueAt(percent, QRect(100-ui->label_bus->width()/2, 100-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
            }
            else if(start_y==600){//3
                percent=1-double(abs(600.0-start_x)/(abs(600.0-start_x)+abs(end_y-600.0)));
                animation->setKeyValueAt(percent, QRect(600-ui->label_bus->width()/2, 600-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
            }
        }


        animation->setKeyValueAt(1,QRect(station_pos[0][pos_temp]-ui->label_bus->width()/2,station_pos[1][pos_temp]-ui->label_bus->height()/2, ui->label_bus->width(),ui->label_bus->height()));

    }
    else{
        animation->setStartValue(QRect(station_pos[0][start_pos]-ui->label_bus->width()/2,station_pos[1][start_pos]-ui->label_bus->height()/2, ui->label_bus->width(), ui->label_bus->height()));
        animation->setEndValue(QRect(station_pos[0][pos_temp]-ui->label_bus->width()/2,station_pos[1][pos_temp]-ui->label_bus->height()/2, ui->label_bus->width(),ui->label_bus->height()));
    }

    animation->start();
}


void MainWindow::slot_open_setting(){

    setting_window.setModal(true); // true：弹窗不影响主界面操作  false：弹窗锁住主界面操作
    setting_window.show();
}

void MainWindow::res_reload(){
    load_res();
}
