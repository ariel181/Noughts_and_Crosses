#ifndef MARKGRAPHICITEM_H
#define MARKGRAPHICITEM_H

#include <QGraphicsObject>
#include <QObject>
#include <QRectF>
#include "item.h"

class MarkGraphicItem : public QGraphicsObject
{
public:
    MarkGraphicItem(QObject *parent);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPlayer(const Item item);
    void reset();

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
