#ifndef GAMERULE_H
#define GAMERULE_H

#include <QPixmap>
#include <QSize>
#include <QGraphicsScene>
#include "puzpiece.h"

class gameRule : public QGraphicsScene
{
public:
    gameRule();
    puzPiece::ConnectType reverse(puzPiece::ConnectType ctype);
    void run(QSize size, QPixmap pixmap);
};

#endif // GAMERULE_H
