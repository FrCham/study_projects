#ifndef SETUPPUZZLEFRAME_H
#define SETUPPUZZLEFRAME_H

#include <QObject>
#include <QFrame>
#include <QPixmap>
#include <QObject>

class setupPuzzleFrame: public QFrame{
    Q_OBJECT

public:
explicit setupPuzzleFrame(QWidget *parent = nullptr);
QSize max() const;
QSize min() const;
QSize val() const;
QPixmap pixmap() const;

public slots:
void setVal(const QSize &val);
void setDefVal(const QSize &val);
void setDefMax(const QSize &max);
void setDefMin(const QSize &min);
void setPixmap(const QPixmap &pixmap);

signals:
void valChanged(const QSize &);
void horValChanged(int);
void verValChanged(int);

private:
QSize mval;
QSize mmin;
QSize mmax;
QSize cellSize() const;
QSize cellAt(const QPoint &pos) const;
QPixmap mpixmap;
void paintEvent(QPaintEvent *);
void buildValue(QPainter * p);
void buildGrid(QPainter * p);
void mousePressEvent(QMouseEvent *e);
void mouseMoveEvent(QMouseEvent *e);
};

#endif // SETUPPUZZLEFRAME_H
