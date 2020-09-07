#include "qmlconnector.h"
#include <QString>
#include <QFileDialog>

QmlConnector::QmlConnector(QObject *parent):QObject(parent){};

void QmlConnector::start(QString path, QString blurRad, QString threadCnt){
    QThreadPool::globalInstance()->setMaxThreadCount(std::max(1,std::min(8, threadCnt.toInt())));
    QmlConnector::m_tot = (2 * blurRad.toInt() + 1);
    QmlConnector::m_tot *= QmlConnector::m_tot;
    QmlConnector::engine = new Engine();
    connect(engine->m_futureWatcher, SIGNAL(finished()), this, SLOT(futureFinished()));
    connect(engine->m_futureWatcher, SIGNAL(progressRangeChanged(int, int)), this, SLOT(setRange(int, int)));
    connect(engine->m_futureWatcher, SIGNAL(progressValueChanged(int)), this, SLOT(setValue(int)));
    connect(this, SIGNAL(stopSignal()), engine, SLOT(stopBlur()));
    QmlConnector::m_time.start();
    engine->power(path, blurRad.toInt());
    qDebug() << "Okey)";
}

void QmlConnector::futureFinished(){
    QmlConnector::m_gtime = QmlConnector::m_time.elapsed();
    QImage bluredImg = engine->getBlurImg();
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    bluredImg.save(&buffer, "JPEG");
    QString imgBytes("data:image/jpg;base64,");
    imgBytes.append(QString::fromLatin1(byteArray.toBase64().data()));
    emit imgBytesChanged(imgBytes);
    qDebug() << "Done";
}

void QmlConnector::setValue(int value){
    QmlConnector::m_progress = value;
    emit progressChanged(value);
}

void QmlConnector::setRange(int from, int to){
    QmlConnector::m_from = from;
    QmlConnector::m_cnt = to;
    emit fromChanged(from);
    emit cntChanged(to);
}

void QmlConnector::stopQML(){
    emit stopSignal();
};


void QmlConnector::stop(){
    engine->stopBlur();
};
