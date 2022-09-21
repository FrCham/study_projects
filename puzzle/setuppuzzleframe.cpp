#include "setuppuzzleframe.h"

#include <QApplication>
#include <QPainter>
#include <QMouseEvent>

setupPuzzleFrame::setupPuzzleFrame(QWidget *parent) :QFrame(parent)
{
    setDefMin(QSize(2, 2));
    setDefVal(QSize(5, 5));
    setDefMax(QSize(8, 8));
}

void setupPuzzleFrame::setVal(const QSize &s){
    if (mval == s) return;
    if (s.width() > mmax.width() || s.height() > mmax.height() ||
            mmin.width() > s.width() || mmin.height() > s.height())
        return;
    QSize prev = mval;
    mval = s;
    emit valChanged(s);
    if (prev.width() != s.width())
        emit horValChanged(s.width());
    if (prev.height() != s.height())
        emit verValChanged(s.height());
    update();
}

void setupPuzzleFrame::setDefVal(const QSize &val){
    mval = val;
    update();
}

void setupPuzzleFrame::setDefMax(const QSize &max){
    mmax = max;
    update();
}

void setupPuzzleFrame::setDefMin(const QSize &min){
    mmin = min;
    update();
}

void setupPuzzleFrame::setPixmap(const QPixmap &pixmap){
    mpixmap = pixmap;
    update();
}

void setupPuzzleFrame::paintEvent(QPaintEvent *){
    QPainter painter(this);
    buildValue(&painter);
    buildGrid(&painter);
}

void setupPuzzleFrame::buildValue(QPainter *p){
    QSize cell = cellSize();
    QSize picture(cell.width()*val().width(),
                  cell.height()*val().height());
    if  (mpixmap.isNull())
        p->fillRect(0, 0, picture.width(), picture.height(), QBrush(Qt::darkGreen));
    else
        p->drawPixmap(0, 0, mpixmap.scaled(picture));
}

void setupPuzzleFrame::buildGrid(QPainter *p){
    QSize cell = cellSize();
    p->setBrush(Qt::NoBrush);
    for(int i = 0; i < max().height(); i++)
        for(int j = 0; j < max().width(); j++)
            p->drawRect(j*cell.width(), i*cell.height(), cell.width(), cell.height());
}

void setupPuzzleFrame::mousePressEvent(QMouseEvent *e){
    setVal(cellAt(e->pos()));
}

void setupPuzzleFrame::mouseMoveEvent(QMouseEvent *e){
    if (e->buttons()&Qt::LeftButton)
        setVal(cellAt(e->pos()));
}

QSize setupPuzzleFrame::cellSize() const{
    return QSize(qMin(width()/max().width(),height()/max().height()),
                 qMin(width()/max().width(), height()/max().height())).expandedTo(QApplication::globalStrut()).expandedTo(QSize(4,4));
}

QSize setupPuzzleFrame::cellAt(const QPoint &pos) const{
    return QSize(pos.x()/cellSize().width()+1,
                 pos.y()/cellSize().height()+1);
}

QSize setupPuzzleFrame::val() const{
    return mval;
}

QSize setupPuzzleFrame::max() const{
    return mmax;
}

QSize setupPuzzleFrame::min() const{
    return mmin;
}

QPixmap setupPuzzleFrame::pixmap() const{
    return mpixmap;
}
