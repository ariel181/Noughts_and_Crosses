#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "markgraphicitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  ,_signalMapper(new QSignalMapper(parent))
  ,_player(Item::Crosses)
  ,_scoreCross(0)
  ,_scoreNoughts(0)
  ,_screen(new QGraphicsScene())
{
    ui->setupUi(this);

    ui->graphicsView->setScene(_screen);
    ui->graphicsView->setMouseTracking(true);
    _screen->addItem(new MarkGraphicItem(this));

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

    changeUser();
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
    showMessage(text);

}

void MainWindow::userDraw()
{

   qDebug()<<"Draw";
   const QString text = tr("The game ended in a draw.\n\nDo you want to start a new game?");
   showMessage(text);

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

    if(_player == Item::Crosses) {
        _player = Item::Noughts;
    } else {
        _player = Item::Crosses;
    }

    const QString name = (_player == Item::Crosses ) ? ui->leX->text() : ui->leO->text();
    const QString text = QString("Make the move %1").arg(name);
    ui->laMove->setText(text);
}

void MainWindow::resetBord()
{

    for(int i = 0 ;i<9;i++) {

        QObject* obj = _signalMapper->mapping(i);
        QPushButton* pb = qobject_cast<QPushButton*>(obj);
        pb->setText("");

    }

}

void MainWindow::showMessage(const QString text)
{
    ui->laMessage->setText(text);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pbBackMenu_clicked()
{
    resetBord();
    const QString text("-----");
    ui->laScoreCross->setText(text);
    ui->laScoreNought->setText(text);
    ui->laCross->setText(text);
    ui->laNoughts->setText(text);
    ui->laMove->setText(text);

    ui->leO->setText("");
    ui->leX->setText("");

    ui->laMessage->setText(text);

    _scoreCross = 0;
    _scoreNoughts = 0;

    ui->stackedWidget->setCurrentIndex(0);


}

void MainWindow::on_pbBackMenu_2_clicked()
{
    on_pbBackMenu_clicked();
}

void MainWindow::on_pbPlay_clicked()
{
    resetBord();
    ui->stackedWidget->setCurrentIndex(1);
}
