#ifndef CHAT_H
#define CHAT_H

#include <QtWidgets>
#include <QUdpSocket>
#include <QListWidget>

class QLineEdit;
class QTextEdit;
class QUdpSocket;
class chat: public QWidget
{
  Q_OBJECT
public:
  chat(QString nick, QWidget *parent = nullptr);
  ~chat();
  void power (int port = 1024);
signals:

public slots:
  void send();
  void screen(const QString &nick, const QString &message);
  void Datagrams();

private:
  QString nickname;
  QByteArray readMessage(const QString &nick, const QString &message)const;
  QPair<QString,QString> comPAIRmessage(const QByteArray &mesg);
  QListWidget *online;
  QTextEdit *messages;
  QLineEdit *post;
  QUdpSocket *socket;
  quint16 port_socket;

};

#endif // CHAT_H
