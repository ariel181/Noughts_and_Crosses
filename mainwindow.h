#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include <QGraphicsScene>
#include "item.h"



namespace Ui {
class MainWindow;
}


/**
 * @brief
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    /**
     * @brief Information about what user made the move and where.
     *
     * @param int
     * @param Item
     */
    void NotifyUserMove(int,Item);

public slots:
    /**
     * @brief
     *
     */
    void userWin();
    /**
     * @brief
     *
     */
    void userDraw();

private slots:
    /**
     * @brief Start game after check users data.
     *
     */
    void on_pbStartGame_clicked();
    /**
     * @brief Executed when user clicked on board
     *
     * @param idx
     */
    void clicked(int idx );
    /**
     * @brief
     *
     * @return bool
     */
    bool isValid();

    /**
     * @brief
     *
     */
    void on_pbBackMenu_clicked();

    void on_pbBackMenu_2_clicked();

    void on_pbPlay_clicked();

    void on_stackedWidget_currentChanged(int arg1);

private:
    /**
     * @brief Change the current user to the next player.
     *
     */
    void changeUser();
    /**
     * @brief Window is adjusted to the initial state.
     *
     */
    void resetBord();
    void showMessage(const QString text);
    void init();

    Ui::MainWindow *ui;
    QSignalMapper* _signalMapper; /**< Mapper storing signals buttons */
    Item _player; /**< Actual player*/
    int _scoreCross;
    int _scoreNoughts;
    QGraphicsScene* _screen;



    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
};

#endif // MAINWINDOW_H
