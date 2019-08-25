#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsItem>
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

    ui->stackedWidget->setCurrentIndex(0);

    init();
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
    emit NotifyUserMove(idx,_player);
    changeUser();
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

    for(int i = 0 ;i<9;i++) {
        QObject* obj = _signalMapper->mapping(i);
        MarkGraphicItem* pb = qobject_cast<MarkGraphicItem*>(obj);
        pb->setPlayer(_player);
    }
}

void MainWindow::resetBord()
{

    for(int i = 0 ;i<9;i++) {
        QObject* obj = _signalMapper->mapping(i);
        MarkGraphicItem* pb = qobject_cast<MarkGraphicItem*>(obj);
        pb->reset();
    }

}

void MainWindow::showMessage(const QString text)
{
    ui->laMessage->setText(text);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::init()
{
    int poxX = 0;
    int poxY = 0;
    int height = 128;
    int width = 128;
    int margin = 16;
    int k = 0;

    int recH = (3*height) + (2*margin)-4;
    int recW = (3*width) + (2*margin)-4;

    QRect rec(2,2,recW,recH);
    _screen->addRect(rec,QColor("#000"),QBrush(QColor("#000")));

    for (int i = 0; i < 3; ++i)
    {

        for(int j =0; j<3; ++j)
        {
            MarkGraphicItem* obj = new MarkGraphicItem();
            _screen->addItem(obj);
            obj->moveBy(poxX,poxY);
            poxX += margin;
            poxX += width;
            connect(obj, SIGNAL(NotifyClicked()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(obj, k);
            k+=1;
        }
        poxY += margin;
        poxY += height;
        poxX = 0;
    }

    connect(_signalMapper, SIGNAL(mapped(int)),
            this, SLOT(clicked(int)));
}

void MainWindow::showEvent(QShowEvent *event)
{
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(),Qt::KeepAspectRatio);
    QMainWindow::showEvent(event);
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

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    if(arg1 == 1) {
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(),Qt::KeepAspectRatio);
    }
}
