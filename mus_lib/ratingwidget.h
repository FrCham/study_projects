#ifndef RATINGWIDGET_H
#define RATINGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "item.h"

class RatingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RatingWidget(QWidget *par = 0);
    int rate_;
    void setRate(int rate);
    int rate(void);
    QSize sizeHint() const;
    int rateAt(int pos);
signals:
    void editingFinished();
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};
#endif // RATINGWIDGET_H
