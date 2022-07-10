#include "setting_window.h"
#include <QPainter>
#include<mainwindow.h>
#include<QSettings>
#include "ui_setting_window.h"
//int is_running,SLEEP_TIME,THEME;
setting_window::setting_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_window)
{
    ui->setupUi(this);
    setting_background.load(":/setting/godskin/setting_background.png");

this->setWindowIcon(QIcon(":/setting/godskin/logo.ico"));




}

setting_window::~setting_window()
{
    delete ui;
}
void setting_window::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,400,300,setting_background);
}

void setting_window::setvalue(){
    if(is_running==1){
        ui->spinBox->setEnabled(0);
    }
    else{
        ui->spinBox->setEnabled(1);
    }

    ui->spinBox->setValue(SLEEP_TIME);
    ui->comboBox->setCurrentIndex(THEME);
}



void setting_window::on_pushButton_accept_clicked()
{

    if(SLEEP_TIME!=ui->spinBox->value()){

        SLEEP_TIME=ui->spinBox->value();

        QSettings settings("config.ini",QSettings::IniFormat);

        settings.beginGroup("setting");//进入到节

        settings.setValue("interval",ui->spinBox->value());

        settings.endGroup();  //beginGroup后必须endGroup
    }

    if(THEME!=ui->comboBox->currentIndex()){

        THEME=ui->comboBox->currentIndex();

        QSettings settings("config.ini",QSettings::IniFormat);

        settings.beginGroup("setting");//进入到节

        settings.setValue("theme",ui->comboBox->currentIndex());
        //QColor color=settings.value("color",0).value<QColor>();
        //qDebug()<<color;

        settings.endGroup();  //beginGroup后必须endGroup

        emit theme_changed();
    }

    this->close();
}


void setting_window::on_pushButton_cancel_clicked()
{
    this->close();
}

