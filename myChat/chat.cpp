#include "chat.h"
#include <QTime>
#include <QTextEdit>
#include <QLabel>
#include <QListWidget>
#include <QLayout>
#include <QLineEdit>

chat::chat(QString nick, QWidget *parent): QWidget(parent){
  socket = nullptr;
  nickname = nick;
  QHBoxLayout *layout = new QHBoxLayout(this);
  QVBoxLayout *messageLay = new QVBoxLayout;
  online = new QListWidget(this);
  online->setMaximumWidth(180);
  messages = new QTextEdit;
  post = new QLineEdit;
  messages -> setReadOnly(true);
  messageLay->addWidget(messages);
  messageLay->addWidget(post);
  layout->addWidget(online);
  layout->addLayout(messageLay);
  connect(post, SIGNAL(returnPressed()), this, SLOT(send()));
}

void chat::screen(const QString &nick, const QString &message){
  QTime time = QTime::currentTime();
  QString msg;
  if (nick == nickname)
    msg = QString("<font color=\"%1\">[%2] <b>%3</b></font>: %4").arg("#CC0033").arg(time.toString()).arg(nick).arg(message);
  else
    msg = QString("<font color=\"%1\">[%2] <b>%3</b></font>: %4").arg("#6699FF").arg(time.toString()).arg(nick).arg(message);
  messages->append(msg);
  post->clear();
}

QByteArray chat::readMessage(const QString &nick, const QString &message) const{
  QByteArray tmp;
  QDataStream stream(&tmp, QIODevice::WriteOnly);
  stream<<nick<<message;
  return tmp;
}

QPair <QString, QString> chat::comPAIRmessage(const QByteArray &mesg){
  QString nick, msg;
  QDataStream stream(mesg);
  stream >> nick >> msg;
  return qMakePair(nick, msg);
}

void chat::send(){
  QByteArray tmp = readMessage(nickname, post->text());
  socket->writeDatagram(tmp, QHostAddress::Broadcast, port_socket);
}

void chat::power(int port){
  socket = new QUdpSocket;
  port_socket = port;
  socket-> bind(port_socket,QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
  qDebug() << "Your port " << port_socket;
  connect(socket, SIGNAL(readyRead()), this, SLOT(Datagrams()));
  QByteArray ptr = readMessage(nickname, "#Welcome#");
  socket->writeDatagram(ptr, QHostAddress::Broadcast, port_socket);
}

void chat::Datagrams(){
  QByteArray tmp;
  //QPair <QString, QString> pair = comPAIRmessage(tmp);
  while (socket->hasPendingDatagrams()){
      tmp.resize(socket->pendingDatagramSize());
      socket->readDatagram(tmp.data(), tmp.size());
      QPair <QString, QString> pair = comPAIRmessage(tmp);
      if (pair.second == "#Welcome#"){
          if (pair.first != nickname){
              QList <QListWidgetItem*> au = online->findItems(pair.first, Qt::MatchExactly);
              if (au.empty()){
                  online->addItem(pair.first);
                  QByteArray tmp = readMessage(nickname, "#Welcome#");
                  socket->writeDatagram(tmp, QHostAddress::Broadcast, port_socket);
                }
            }
        } else if (pair.second == "#GoodBye#"){
          for (int i = 0; i < online->count(); ++i){
              if (online->item(i)->text() == pair.first){
                  online->takeItem(i);
                  break;
                }
            }
        }
      else screen(pair.first, pair.second);
    }
}

chat::~chat(){
  QByteArray tmp = readMessage(nickname, "#GoodBye#");
  socket->writeDatagram(tmp, QHostAddress::Broadcast, port_socket);
}
