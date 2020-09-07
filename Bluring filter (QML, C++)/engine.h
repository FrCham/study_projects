#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QImage>
#include <QtConcurrent>
#include <QString>
#include <cmath>
#include <QQmlApplicationEngine>
#include <QtGui/QGuiApplication>
#include <QtQuick>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine();

    static void staticBlurring(QPoint& pnt);
    void power(QString srcImgPath, int blurRad);
    QImage getBlurImg() const { return m_blurImg; };
    QFutureWatcher <void> *m_futureWatcher;


private:
    void blurring(QPoint& pnt);
    int m_xSize, m_ySize;
    int m_blurRad;
    QImage m_srcImg, m_blurImg;
    QList <QPoint> m_pointVec;
    static Engine *staticEngine;

public slots:
    void stopBlur();
};

#endif // ENGINE_H
