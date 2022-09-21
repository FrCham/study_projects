#include "puzpiece.h"
#include "welcompage.h"
#include "gamerule.h"
#include <QMessageBox>
#include <QSet>
#include <QVariant>

void puzPiece::buildPuz(QPainterPath &puz){
    flag = true;
    puz.moveTo(-1*size/2, -1*size/2);
    if (posType[Top] == In){
        puz.lineTo(-1*size/4, -1*size/2);
        puz.arcTo(-1*size/4, -3*size/4, size/2, size/2, 180, 180);
        //puz.moveTo(size/4, -1*size/2);
        puz.lineTo(size/2, -1*size/2);
    } else
        if (posType[Top] == Out){
            puz.lineTo(-1*size/4, -1*size/2);
            puz.arcTo(-1*size/4, -3*size/4, size/2, size/2, 180, -180);
           // puz.moveTo(size/4, -1*size/2);
            puz.lineTo(size/2, -1*size/2);
        } else
            puz.lineTo(size/2, -1*size/2);

    if (posType[Right] == In){
        puz.lineTo(size/2, -1*size/4);
        puz.arcTo(size/4, -1*size/4, size/2, size/2, 90, 180);
        //puz.moveTo(size/2, size/4);
        puz.lineTo(size/2, size/2);
    } else
        if (posType[Right] == Out){
            puz.lineTo(size/2, -1*size/4);
            puz.arcTo(size/4, -1*size/4, size/2, size/2, 90, -180);
            //puz.moveTo(size/2, size/4);
            puz.lineTo(size/2, size/2);
        } else
            puz.lineTo(size/2, size/2);

    if (posType[Floor] == In){
        puz.lineTo(size/4, size/2);
        puz.arcTo(-1*size/4, size/4, size/2, size/2, 0, 180);
       // puz.moveTo(-1*size/4, size/2);
        puz.lineTo(-1*size/2, size/2);
    } else
        if (posType[Floor] == Out){
            puz.lineTo(size/4, size/2);
            puz.arcTo(-1*size/4, size/4, size/2, size/2, 0, -180);
            //puz.moveTo(-1*size/4, size/2);
            puz.lineTo(-1*size/2, size/2);
        } else
            puz.lineTo(-1*size/2, size/2);

    if (posType[Left] == In){
        puz.lineTo(-1*size/2, size/4);
        puz.arcTo(-3*size/4, -1*size/4, size/2, size/2, 270, 180);
       // puz.moveTo(-1*size/2, -1*size/4);
        puz.lineTo(-1*size/2, -1*size/2);
    } else
        if (posType[Left] == Out){
            puz.lineTo(-1*size/2, size/4);
            puz.arcTo(-3*size/4, -1*size/4, size/2, size/2, 270, -180);
          //  puz.moveTo(-1*size/2, -1*size/4);
            puz.lineTo(-1*size/2, -1*size/2);
        } else
            puz.lineTo(-1*size/2, -1*size/2);

    puz.closeSubpath();
}

puzPiece::puzPiece(puzPiece::ConnectType top, puzPiece::ConnectType right, puzPiece::ConnectType floor, puzPiece::ConnectType left){
    posType[Top] = top;
    posType[Right] = right;
    posType[Floor] = floor;
    posType[Left]  =left;
    Adjacent[0] = nullptr;
    Adjacent[1] = nullptr;
    Adjacent[2] = nullptr;
    Adjacent[3] = nullptr;
    size = 80;
    QPainterPath puzz;
    buildPuz(puzz);
    setPath(puzz);
}

void puzPiece::setCount(QSize size){
    count = size.width() * size.height();
}

void puzPiece::setPixmap(QPixmap pixmap){
    mpixmap = pixmap;
    update();
}

void puzPiece::setXOY(QPoint XOY){
    xoy = XOY;
}

void puzPiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipPath(path());
    QRect rect = boundingRect().toRect();
    painter->drawPixmap(rect.x(), rect.y(), pixmap());
    painter->drawPath(path());
}

void puzPiece::link(puzPiece *puz, ConnectPos cpos){
    this->Adjacent[cpos] = puz;
    if (cpos == Top)
        puz->Adjacent[Floor] = this;
    if (cpos == Floor)
        puz->Adjacent[Top] = this;
    if (cpos == Left)
        puz->Adjacent[Right] = this;
    if (cpos == Right)
        puz->Adjacent[Left] = this;
}

void puzPiece::searchAdj(ConnectPos cpos){
    puzPiece* puz;
    if (Adjacent[cpos])
        return;
    if (cpos == Top){
        puz = (puzPiece*)(scene()->itemAt(pos().x(), pos().y() - 80, QTransform()));
        if (!puz) return;
        if ((puz->XOY().x() == XOY().x()) && (puz->XOY().y() == XOY().y() -1)){
            link(puz, cpos);
            puz->setPos(pos().x(), pos().y() - 80);
        }
    }
    if (cpos == Floor){
        puz = (puzPiece*)(scene()->itemAt(pos().x(), pos().y() + 80, QTransform()));
        if (!puz) return;
        if ((puz->XOY().x() == XOY().x()) && (puz->XOY().y() == XOY().y() +1)){
            link(puz, cpos);
            puz->setPos(pos().x(), pos().y() + 80);
        }
    }
    if (cpos == Right){
        puz = (puzPiece*)(scene()->itemAt(pos().x() + 80, pos().y() , QTransform()));
        if (!puz) return;
        if ((puz->XOY().x() == XOY().x() + 1) && (puz->XOY().y() == XOY().y())){
            link(puz, cpos);
            puz->setPos(pos().x() + 80, pos().y());
        }
    }
    if (cpos == Left){
        puz = (puzPiece*)(scene()->itemAt(pos().x() - 80, pos().y(), QTransform()));
        if (!puz) return;
        if ((puz->XOY().x() == XOY().x() -1) && (puz->XOY().y() == XOY().y())){
            link(puz, cpos);
            puz->setPos(pos().x() - 80, pos().y());
        }
    }
}

void puzPiece::checkAdj(QVector<QPoint> &checked){
    if (checked.contains(XOY()))
        return;
    checked.insert(checked.begin(), XOY());
    searchAdj(Top);
    searchAdj(Right);
    searchAdj(Floor);
    searchAdj(Left);
    if (Adjacent[Top])
        Adjacent[Top]->checkAdj(checked);
    if (Adjacent[Right])
        Adjacent[Right]->checkAdj(checked);
    if (Adjacent[Floor])
        Adjacent[Floor]->checkAdj(checked);
    if (Adjacent[Left])
        Adjacent[Left]->checkAdj(checked);
}

void puzPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QVector<QPoint> check;
    checkAdj(check);
    if((flag)&&(check.count()==count))
    {
        QMessageBox::information(0,"Challenge","Completed");
        flag = false;
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant puzPiece::itemChange(GraphicsItemChange change, const QVariant &value){
    if (change == ItemPositionHasChanged){
        QPoint npos = value.toPoint();
        if(Adjacent[Top])
            Adjacent[Top]->setPos(npos.x(), npos.y()-80);
        if(Adjacent[Floor])
            Adjacent[Floor]->setPos(npos.x(), npos.y()+80);
        if(Adjacent[Left])
            Adjacent[Left]->setPos(npos.x()-80, npos.y());
        if(Adjacent[Right])
            Adjacent[Right]->setPos(npos.x()+80, npos.y());
    }
    return QGraphicsItem::itemChange(change, value);
}

QPixmap puzPiece::pixmap(){
    return mpixmap;
}

QPoint puzPiece::XOY(){
    return xoy;
}
