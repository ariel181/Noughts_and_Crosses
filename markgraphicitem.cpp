#include "markgraphicitem.h"
#include <QPainter>
#include <QDebug>


MarkGraphicItem::MarkGraphicItem(QObject* parent):QGraphicsObject()
  ,_rect(0,0,128,128)
{

}

QRectF MarkGraphicItem::boundingRect() const
{
    return _rect;

}

void MarkGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->save();
    QPen pen = painter->pen();
    pen.setColor(QColor("#FF0000"));

    painter->setPen(pen);

    painter->drawRect(_rect);
    painter->drawText(_rect,"X");

    painter->restore();

}

void MarkGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<<__PRETTY_FUNCTION__;

}

void MarkGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}
