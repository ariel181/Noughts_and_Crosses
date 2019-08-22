#include "mainwindow.h"
#include <QApplication>
#include "nacmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NACModel nac;
    MainWindow w;

    QObject::connect(&w,SIGNAL(NotifyUserMove(int,Item)),&nac,SLOT(userMove(int,Item)));

    QObject::connect(&nac,SIGNAL(NotifyUserWin()),&w,SLOT(userWin()));
    QObject::connect(&nac,SIGNAL(NotifyUserDraw()),&w,SLOT(userDraw()));

    w.show();

    return a.exec();
}
