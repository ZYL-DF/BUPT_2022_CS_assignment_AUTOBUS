#include "mainwindow.h"
#include "Input.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    read();

    QApplication a(argc, argv);
    MainWindow w;

    w.show();




    return a.exec();
}
