#ifndef MARKGRAPHICITEM_H
#define MARKGRAPHICITEM_H

#include <QGraphicsObject>
#include <QObject>
#include <QRectF>
#include "item.h"

class MarkGraphicItem : public QGraphicsObject
{

    Q_OBJECT
public:
    MarkGraphicItem(QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPlayer(const Item item);
    void reset();

signals:
    void NotifyClicked();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString getActualMark();

    QRectF _rect;
    bool _isHover;
    bool _isMakred;
    QString _mark;
    Item _player; /**< Actual player*/

    // QGraphicsItem interface
protected:
};

#endif // MARKGRAPHICITEM_H
