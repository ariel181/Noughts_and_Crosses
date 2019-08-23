#ifndef MARKGRAPHICITEM_H
#define MARKGRAPHICITEM_H

#include <QGraphicsObject>
#include <QObject>
#include <QRectF>

class MarkGraphicItem : public QGraphicsObject
{
public:
    MarkGraphicItem(QObject *parent);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QRectF _rect;
};

#endif // MARKGRAPHICITEM_H
