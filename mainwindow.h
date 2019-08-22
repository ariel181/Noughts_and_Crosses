#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include "item.h"



namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void NotifyUserMove(int,Item);
    void NotifyResetGame();

public slots:
    void userWin();
    void userDraw();

private slots:
    void on_pbStartGame_clicked();
    void clicked(int idx );
    bool isValid();

    private:
    void changeUser();
    bool isUserWon();
    void resetBord();
    Ui::MainWindow *ui;
    QSignalMapper* _signalMapper;
    Item _player;
    QVector<QPushButton*> _board;
    int _scoreCross;
    int _scoreNoughts;


};

#endif // MAINWINDOW_H