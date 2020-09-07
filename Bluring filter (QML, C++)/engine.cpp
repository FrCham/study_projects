#include "engine.h"

Engine* Engine::staticEngine = NULL;

Engine::Engine(QObject *parent) :QObject(parent)
{
    Engine::m_futureWatcher = new QFutureWatcher<void> (this);
    Engine::staticEngine = this;
}

void Engine::power(QString srcImgPath, int blurRad){
    Engine::stopBlur();
    Engine::m_srcImg = Engine::m_blurImg = QImage(srcImgPath.remove(0, 8));
    Engine::m_xSize = Engine::m_srcImg.width();
    Engine::m_ySize = Engine::m_srcImg.height();
    Engine::m_blurRad = blurRad;

    for (int x = 0; x < Engine::m_xSize; ++x)
        for (int y = 0; y < Engine::m_ySize; ++y)
            Engine::m_pointVec << QPoint(x, y);


    auto future = QtConcurrent::map(Engine::m_pointVec, Engine::staticBlurring);
    Engine::m_futureWatcher->setFuture(future);
}

void Engine::staticBlurring(QPoint &pnt){
    Engine::staticEngine->blurring(pnt);
}

void Engine::blurring(QPoint &pnt){
    int redTot = 0, greenTot = 0, blueTot = 0;
    for (int x = pnt.x() - Engine::m_blurRad; x <= pnt.x() + Engine::m_blurRad; ++x){
        int xNormal = std::max(0, std::min(Engine::m_xSize - 1, x));
        for (int y = pnt.y() - Engine::m_blurRad; y <= pnt.y() + Engine::m_blurRad; ++y){
            int yNormal = std::max(0, std::min(Engine::m_ySize - 1, y));
            QRgb pixelTmp = Engine::m_srcImg.pixel(xNormal, yNormal);

            redTot += qRed(pixelTmp);
            greenTot += qGreen(pixelTmp);
            blueTot += qBlue(pixelTmp);
        }
    }

    long long pixCnt = (2 * Engine::m_blurRad + 1) * (2 * Engine::m_blurRad + 1);
    QRgb pixel = qRgb(redTot / pixCnt, greenTot / pixCnt, blueTot / pixCnt);
    Engine::m_blurImg.setPixelColor(pnt.x(), pnt.y(), pixel);
}

void Engine::stopBlur(){

    if (Engine::m_futureWatcher->isRunning()){
        Engine::m_futureWatcher->cancel();
        Engine::m_futureWatcher->waitForFinished();
    }
}

Engine::~Engine(){
    Engine::stopBlur();
    delete m_futureWatcher;
}
