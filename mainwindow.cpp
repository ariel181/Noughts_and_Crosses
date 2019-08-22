#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  ,_signalMapper(new QSignalMapper(parent))
  ,_player(Item::Crosses)
  ,_scoreCross(0)
  ,_scoreNoughts(0)
{
    ui->setupUi(this);


    QFont font;
    font.setPointSize(32);

    QGridLayout* lay = qobject_cast<QGridLayout*>(ui->frBoard->layout());

    for (int i = 0; i < 9; ++i) {
        QPushButton *pb = new QPushButton("");
        const QString objName = "pb_" + QString::number(i+1);
        pb->setObjectName(objName);
        pb->setMinimumSize(QSize(128, 128));
        pb->setMaximumSize(QSize(128, 128));
        pb->setFont(font);

        connect(pb, SIGNAL(clicked()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(pb, i);

        lay->addWidget(pb, i / 3, i % 3);

    }

    connect(_signalMapper, SIGNAL(mapped(int)),
            this, SLOT(clicked(int)));


    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userWin()
{
    qDebug()<<"win"<<(_player == Item::Crosses ? "X" : "O");

    QString userName;

    if(_player == Item::Crosses) {

        _scoreCross += 1;
        ui->laScoreCross->setText(QString::number(_scoreCross));
        userName = ui->leX->text();

    } else {

        _scoreNoughts += 1;
        ui->laScoreNought->setText(QString::number(_scoreNoughts));
        userName = ui->leO->text();
    }


    const QString text = tr("Won by: %1.\n\nDo you want to start a new game?").arg(userName);
   int rec =  QMessageBox::information(this,tr("Congratulations"),text,QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);

   if(rec==QMessageBox::Yes) {
       resetBord();
       emit NotifyResetGame();
   } else {
       close();
   }


}

void MainWindow::userDraw()
{
    qDebug()<<"Draw";
}

void MainWindow::on_pbStartGame_clicked()
{
    if(isValid()) {

        ui->laNoughts->setText(ui->leO->text());
        ui->laCross->setText(ui->leX->text());

        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::clicked(int idx)
{

    QObject* obj = _signalMapper->mapping(idx);

    QPushButton* pb = qobject_cast<QPushButton*>(obj);

    const QString text = pb->text();

    if(text.isEmpty())
    {
        const QString text = (_player == Item::Crosses ? "X" : "O");
        pb->setText(text);
        emit NotifyUserMove(idx,_player);
        changeUser();
    }

}

bool MainWindow::isValid()
{
    bool pom = true;
    const QString text = tr("The name cannot be empty.");
    const QString text_0 = ui->leO->text();
    const QString text_X = ui->leX->text();

    ui->laO->setText("");
    ui->laX->setText("");

    if(text_0.isEmpty())
    {
        ui->laO->setText(text);
        pom = false;
    }

    if(text_X.isEmpty())
    {
        ui->laX->setText(text);
        pom = false;
    }

    if(pom and (text_0 == text_X) ) {

        ui->laO->setText(tr("The names can't be the same "));
        pom = false;

    }

    return pom;
}

void MainWindow::changeUser()
{
    const QString name = (_player == Item::Crosses ) ? ui->leX->text() : ui->leO->text();
    const QString text = QString("Make the next move %1").arg(name);

    ui->laMove->setText(text);

    if(_player == Item::Crosses) {
        _player = Item::Noughts;
    } else {
        _player = Item::Crosses;
    }

}

void MainWindow::resetBord()
{

    for(int i = 0 ;i<9;i++) {

        QObject* obj = _signalMapper->mapping(i);
        QPushButton* pb = qobject_cast<QPushButton*>(obj);
        pb->setText("");

    }

}
