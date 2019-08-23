#include "markgraphicitem.h"
#include <QPainter>
#include <QDebug>


MarkGraphicItem::MarkGraphicItem(QGraphicsItem* parent):QGraphicsObject(parent)
  ,_rect(0,0,128,128)
  ,_isHover(false)
  ,_isMakred(false)
  ,_mark("")
  ,_player(Item::Non)
{
    setAcceptHoverEvents(true);
}

QRectF MarkGraphicItem::boundingRect() const
{
    return _rect;

}

void MarkGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    QPen pen = painter->pen();
    QTextOption texOpt(Qt::AlignCenter);
    QBrush brush(QColor("#FFF"));
    QFont font;
    font.setPointSize(32);
    pen.setColor(QColor("#000"));

    painter->setPen(Qt::NoPen);
    painter->setBrush(brush);
    painter->drawRect(_rect);

    painter->setPen(pen);
    painter->setFont(font);

    if(_isHover and !_isMakred) {
        pen.setColor(QColor("#FF0000"));
        painter->setPen(pen);
        QString pom  = getActualMark();
        painter->drawText(_rect,pom,texOpt);
    } else {
        painter->drawText(_rect,_mark,texOpt);
    }

    painter->restore();

}

void MarkGraphicItem::setPlayer(const Item item)
{
    _player = item;
}

void MarkGraphicItem::reset()
{
    _isMakred = false;
    _mark = "";
    update();
}

void MarkGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    _isHover = true;
    update();
    QGraphicsObject::hoverEnterEvent(event);
}

void MarkGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _isHover = false;
    update();
    QGraphicsObject::hoverLeaveEvent(event);
}

void MarkGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!_isMakred) {
        _isMakred = true;
        _mark = getActualMark();
        update();
        emit NotifyClicked();
    }
    QGraphicsObject::mousePressEvent(event);
}

QString MarkGraphicItem::getActualMark()
{
    switch (_player) {
    case Item::Crosses: return "X";
    case Item::Noughts: return "O";
    default: return "";
    }
}
