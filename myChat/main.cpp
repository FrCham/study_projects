#include "mainwindow.h"
#include "chat.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QStringList arg;
  QCommandLineParser parser;
  QCommandLineOption port_(QStringList() << "p" << "port", ".");
  QCommandLineOption nick_(QStringList() << "n" << "nick", ".");
  parser.addOption(port_);
  parser.addOption(nick_);
  parser.process(a);
  arg = parser.positionalArguments();
  if (!parser.isSet(port_))
    arg.insert(1, "1024");
  if (!parser.isSet(nick_))
    arg.insert(0, "User");
  if (arg.at(0).toInt())
    arg.swap(0, 1);
  chat chat(arg.at(0));
  if (arg.at(1).toInt() < 1024){
    qDebug() << arg.at(1).toInt();
    arg[1] = QString::number(arg.at(1).toInt() + 2000);
    qDebug() << "Your port was increase with 2000 points";
    }
  chat.setWindowTitle(QString("myChat. [%1@%2]").arg(arg.at(0)).arg(arg.at(1)));
  chat.power(arg.at(1).toInt());
  chat.show();

  MainWindow w;

  return a.exec();
}
