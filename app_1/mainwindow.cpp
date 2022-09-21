#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->Run->setEnabled(false);
  ui->Stop->setEnabled(false);
  connect(&myProcess, SIGNAL(finished(int)), this, SLOT(Time_()));
  connect(&myProcess, SIGNAL(finished(int)), this, SLOT(Exit_code()));
  connect(&myProcess, SIGNAL(finished(int)), this, SLOT(Proc_finish()));
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_Open_clicked()
{
    file_name = QFileDialog::getOpenFileName(this, tr("Open file"), "..", "Any file (*)");
    ui->Open_line->setText(file_name);
    if (!file_name.isEmpty()) ui->Run->setEnabled(true);
}

void MainWindow::on_Run_clicked()
{
  argu = ui->arguments->text().split(" ");
  connect(&myProcess, SIGNAL(readyReadStandardError()), this, SLOT(Read_to_err()));
  connect(&myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(Read_to_out()));
  ui->stderr_->clear();
  ui->stdout_->clear();
  time.start();
  myProcess.start(file_name, argu);
  ui->Run->setEnabled(false);
  ui->Stop->setEnabled(true);
}

void MainWindow::on_Open_line_textEdited(const QString &arg1)
{
    if (ui->Open_line->text() == "")
      ui->Run->setEnabled(false);
    else ui->Run->setEnabled(true);
}

void MainWindow::on_Stop_clicked()
{
  myProcess.terminate();
  ui->Run->setEnabled(true);
  ui->Stop->setEnabled(false);
}

void MainWindow::Time_(){
  double t = time.elapsed();
  ui->Time->setText(QString::number((t / 1000), 'g', 2) + " sec");
}

void MainWindow::Exit_code(){
  ui->Error->setText(QString::number(myProcess.exitCode()));
}

void MainWindow::Read_to_err(){
  QByteArray err = myProcess.readAllStandardError();
  ui->stderr_->appendPlainText(QString(err));
}

void MainWindow::Read_to_out(){
  QByteArray out = myProcess.readAllStandardOutput();
  ui->stdout_->appendPlainText(QString(out));
}

void MainWindow::Proc_finish(){
  ui->Run->setEnabled(true);
  ui->Stop->setEnabled(false);
}
