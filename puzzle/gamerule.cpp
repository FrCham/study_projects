#include "gamerule.h"

#include <QVector>
#include <QRect>
#include <QTime>

gameRule::gameRule()
{

}

puzPiece::ConnectType gameRule::reverse(puzPiece::ConnectType ctype){
    if (ctype == puzPiece::In)
        return puzPiece::Out;
    if (ctype == puzPiece::Out)
        return puzPiece::In;
    if (ctype == puzPiece::None)
        return puzPiece::None;
}

void gameRule::run(QSize size, QPixmap pixmap){
    qsrand(QTime::currentTime().msec());
    this->clear();
    puzPiece::ConnectType lastRight = puzPiece::ConnectType::None;
    QPixmap img = pixmap.scaled(80*size.width(), 80*size.height());
    QVector<puzPiece::ConnectType> last(size.width(), puzPiece::None);
    for (int i = 0; i < size.height(); ++i){
        //lastLeft = puzPiece::ConnectType::None;
        for (int j = 0; j < size.width(); ++j){
            puzPiece::ConnectType type[4];
            type[0] = reverse(last[j]);
            if (qrand() % 2)
                type[1] = puzPiece::In;
            else
                type[1] = puzPiece::Out;
            if (qrand() % 2)
                type[2] = puzPiece::In;
            else
                type[2] = puzPiece::Out;
            type[3] = reverse(lastRight);

            if (j == size.width()-1)
                type[1] = puzPiece::None;
            if (i == size.height() -1)
                type[2] = puzPiece::None;

            puzPiece* npuz = new puzPiece(type[0], type[1], type [2], type[3]);


            lastRight = type[1];
            last[j] = type[2];

            npuz->setFlag(QGraphicsItem::ItemIsMovable);
            npuz->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
            npuz->setPos(qrand()%560, qrand()%360);

            QRect rect = npuz->boundingRect().toRect();
            rect.translate(80/2 + 80*j, 80/2 + 80*i);
            QPixmap pict = img.copy(rect);
            npuz->setPixmap(pict);
            npuz->setXOY(QPoint(j, i));
            npuz->setCount(size);
            addItem(npuz);
         }
    }
}
