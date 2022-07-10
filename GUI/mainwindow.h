#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPropertyAnimation>
#include<QAudioOutput>
#include<QMediaPlayer>
#include "setting_window.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

void paintEvent(QPaintEvent *);
void wheelEvent(QWheelEvent *event);
void mousePressEvent(QMouseEvent *event);
void mouseReleaseEvent(QMouseEvent *event);
int bus_starting_point=1,bus_starting_point_present=1;
int bus_ending_point=1,bus_ending_point_present=1;;
int bus_starting_point_chosen=0,bus_starting_point_chosen_present=0;//flag
void track_line(QPoint start,QPoint end,int direction,QPoint point_list[]);//用于确认目标轨，实时轨的轨道曲线采样点
int track_num(QPoint start,QPoint end,int direction);
void load_res();


private:
QPixmap bus_pix ;
QPixmap background;
QPixmap setting;
setting_window setting_window;



signals:
void wheel_type_label_up();   //滚轮向上切换命令类型
void wheel_type_label_down(); //滚轮向下切换命令类型
void wheel_num_label_up();    //滚轮向上切换第几组
void wheel_num_label_down();  //滚轮向下切换第几组
void mouse_click_label_order(int type); //鼠标点击发送命令按钮
void mouse_click_label_release(int time); //鼠标点击,刷新output
void mouse_click_label_start(); //鼠标点击发车按钮
void mouse_release_label_order(); //鼠标点击发送命令按钮后释放
void order(int type,int num);//给公车发送命令
void MoveBus_fromidle(int);
void MoveBus_fromidle_tothread();
void open_setting();
void thread_update_();

private slots:
    void slot_type_up();       //滚轮向上切换命令
    void slot_type_down();     //滚轮向下切换命令
    void slot_num_up();        //滚轮向上切换第几组
    void slot_num_down();      //滚轮向下切换第几组
    void order_sendout(int type); //发送命令
    void order_release();      //鼠标释放

    void Input(int,int);//接受命令，输入队列一二之中
    void Output(int);
    void MoveBus(int);
    void slot_open_setting();
    void res_reload();


private:
    Ui::MainWindow *ui;

    double station_pos[2][125];
    QString type_name[4]={"顺时针方向","逆时针方向","目标","停运"};

    QColor color_list[15];

    int type_pos=1;
    int num_pos=1;

    void drawlabel();


    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;

};

extern int MoveBus_fromidle_fix;
extern int SLEEP_TIME; //是秒来着
extern int THEME;
extern int is_running;//线程是否启动
#endif // MAINWINDOW_H
