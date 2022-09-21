#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QProcess>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_Open_clicked();

  void on_Run_clicked();

  void on_Open_line_textEdited(const QString &arg1);

  void on_Stop_clicked();

  void Time_();

  void Exit_code();

  void Read_to_out();

  void Read_to_err();

  void Proc_finish();

private:
  Ui::MainWindow *ui;
  QString file_name;
  QStringList argu;
  QProcess myProcess;
  QTime time;
};
#endif // MAINWINDOW_H
