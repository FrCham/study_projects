#include "welcompage.h"
#include "gamerule.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomPage w;
    w.show();
    return a.exec();
}
