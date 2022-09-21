#include "welcompage.h"
#include "ui_welcompage.h"
#include "setuppuzzleframe.h"
#include "gamerule.h"

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QtWidgets>

WelcomPage::WelcomPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WelcomPage)
{
    ui->setupUi(this);
}

WelcomPage::~WelcomPage()
{
    delete ui;
}

void WelcomPage::on_pushButton_clicked(){
    filename = QFileDialog::getOpenFileName(this, "Open image", QDir::currentPath(), "*.jpg *.jpeg *.png *.bmp *.ico");
         if(filename.isNull()) return;
         ui->lineEdit->setText(filename);
         ui->frame->setPixmap(QPixmap(filename));
         update();
}

void WelcomPage::on_buttonBox_accepted()
{
    if (filename.isNull()){
        QMessageBox::warning(this, "ERROR", "Image don't select");
        QDialog::exec();
    }
    else{
        QGraphicsView* v = new QGraphicsView;
        gameRule* scene = new gameRule;
        scene->run(pSize(), QPixmap(imgFileName()));
        v->setScene(scene);
        v->resize(600, 400);
        v->show();
        this->close();
    }
}

void WelcomPage::on_buttonBox_rejected(){
    this->close();
}

QSize WelcomPage::pSize(){
    return ui->frame->val();
}

QString WelcomPage::imgFileName(){
    return ui->lineEdit->text();
}
