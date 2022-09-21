#ifndef PUZPIECE_H
#define PUZPIECE_H

#include <QGraphicsPathItem>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QPoint>
#include <QApplication>
#include <QObject>

class puzPiece : public QGraphicsPathItem
{

public:    
    enum ConnectType {In, Out, None};
    enum ConnectPos {Top, Right, Floor, Left};
    puzPiece* Adjacent[4];
    ConnectType posType[4];
    puzPiece(ConnectType Top, ConnectType Right, ConnectType Floor, ConnectType Left);
    int count;
    bool flag;
    int size;
    QPixmap pixmap();
    QPoint XOY();
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void setCount(QSize size);
    void setPixmap(QPixmap pixmap);
    void setXOY(QPoint XOY);

    void link(puzPiece* puz, ConnectPos cpos);
    void searchAdj(ConnectPos cpos);
    void checkAdj(QVector<QPoint> &checked);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    void buildPuz(QPainterPath &puz);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPoint xoy;
    QPixmap mpixmap;

};

#endif // PUZPIECE_H
