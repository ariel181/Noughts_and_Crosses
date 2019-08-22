#ifndef NACMODEL_H
#define NACMODEL_H

#include <QObject>
#include <QVector>
#include "item.h"

class NACModel : public QObject
{
    Q_OBJECT
public:
    explicit NACModel(QObject *parent = 0);

signals:
    void NotifyUserWin();
    void NotifyUserDraw();

public slots:
    void userMove(int index, Item item);

private:
    bool isWin(Item item);
    bool isDraw();
    QVector<Item> _board;

};

#endif // NACMODEL_H
