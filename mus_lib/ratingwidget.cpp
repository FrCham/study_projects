#include "ratingwidget.h"

RatingWidget::RatingWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);
}

void RatingWidget::setRate(int rate)
{
    rate_=rate;
}

int RatingWidget::rate()
{
    return rate_;
}

QSize RatingWidget::sizeHint() const
{
    return QSize(100, 20);
}

int RatingWidget::rateAt(int pos)
{
    int rate = (pos / (100 / 5)) + 1;
    if (rate < 0 || rate > 5)
        return -1;
    return rate;
}

void RatingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush b_inner(Qt::gray);
    QBrush b_outer(Qt::NoBrush);
    painter.setPen(QPen(Qt::black, 1));
    int rate = 0;
    rate = rate_;
    if(rate > 5) rate = 5;
    if(rate < 0) rate = 0;
    int top;
    int left;
    top = 0;
    left = 0;
    for(int counter = 0; counter < 5; counter++)
    {
        if(rate > 0 && counter < rate)
            painter.setBrush(b_inner);
        else
            painter.setBrush(b_outer);
        painter.drawEllipse(QPoint(left + 10, top + 10), 8, 8);
        left += 20;
    }
}

void RatingWidget::mouseMoveEvent(QMouseEvent *event)
{
    int rate = rateAt(event->x());
    if (rate != -1)
    {
        rate_ = rate;
        update();
    }
}

void RatingWidget::mousePressEvent(QMouseEvent *event)
{
    emit editingFinished();
}
