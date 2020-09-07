#ifndef QMLCONNECTOR_H
#define QMLCONNECTOR_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QtGui>
#include <engine.h>
#include <math.h>
#include <QTime>

class QmlConnector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(QString imgBytes READ imgBytes NOTIFY imgBytesChanged)
    Q_PROPERTY(float from READ from NOTIFY fromChanged)
    Q_PROPERTY(float count READ count NOTIFY cntChanged)
    Q_PROPERTY(int time READ time)
public:
    explicit QmlConnector(QObject* parent = nullptr);
    ~QmlConnector(){};

    float progress(){ return std::ceil((100.0 * m_progress) / (m_cnt - m_from)); };
    int from() {return m_from;};
    int count() {return m_cnt;};
    int time() {return QmlConnector::m_time.elapsed();};

    Q_INVOKABLE void start(QString path, QString blurRad, QString threadCnt);
    Q_INVOKABLE void stopQML();

    QString imgBytes(){return m_imgBytes;};
    void stop();
private:
    Engine* engine;
    int m_progress = 0;
    float m_tot;
    int m_from, m_to, m_cnt;
    QString m_imgBytes;
    QTime m_time;
    int m_gtime = 0;

signals:
    void fromChanged(int from);
    void cntChanged(int cnt);
    void progressChanged(float prog);
    void imgBytesChanged(QString imgBytes);
    void stopSignal();

private slots:
    void futureFinished();
    void setValue(int value);
    void setRange(int from, int to);


};

#endif // QMLCONNECTOR_H
