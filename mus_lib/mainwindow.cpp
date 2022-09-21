#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "albumdialog.h"
#include "artistdialog.h"
#include "ratingdelegate.h"
#include <QDebug>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString str1=QLocale::system().name();
    QString tsfile = QString("MusicLib_")+str1;
    translator.load(tsfile,QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&translator);
    QString tsfile2 = QString("qt_")+str1;
    translator_qt.load(tsfile2,QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&translator_qt);
    str1.remove(2,3);
    curr_lang=str1;

    ui->setupUi(this);
    setCentralWidget(ui->treeView);

    if(curr_lang=="ru") ui->actionRu->setEnabled(false);
    else ui->actionEn->setEnabled(false);

    model_ = new MusicModel();
    ui->treeView->setModel(model_);

    const int RatingColumn = 2;
    RatingDelegate *delegate = new RatingDelegate(ui->treeView);
    ui->treeView->setItemDelegateForColumn(RatingColumn, delegate);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);


    ui->actionEdit->setEnabled(false);
    ui->actionDelete->setEnabled(false);
    ui->actionAdd_album->setEnabled(false);
    ui->actionAdd_track->setEnabled(false);

    connect(model_, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(setModified()));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(update_active_actions(QModelIndex)));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(isWindowModified())
    {
        QMessageBox::StandardButton choose = QMessageBox::warning(this, tr("Save"), tr("Do you want to save changes?"),
                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
        switch (choose)
        {
          case QMessageBox::Yes:
              if(!this->on_actionSave_triggered())
              {
                  event->ignore();
                  return;
              }
              event->accept();
              return;
          case QMessageBox::No:
              event->accept();
              return;
          case QMessageBox::Cancel:
              event->ignore();
              return;
        }
    }
    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModified()
{
    setWindowModified(true);
}

void MainWindow::update_active_actions(QModelIndex ind)
{
    Item *curritem=static_cast<Item*>(ind.internalPointer());
    if(!curritem or !ind.isValid())
    {
        ui->actionEdit->setEnabled(false);
        ui->actionDelete->setEnabled(false);
        ui->actionAdd_album->setEnabled(false);
        ui->actionAdd_track->setEnabled(false);
        return;
    }
    if(curritem->toAlbum())
    {
        ui->actionEdit->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        ui->actionAdd_album->setEnabled(false);
        ui->actionAdd_track->setEnabled(true);
    }
    if(curritem->toTrack())
    {
        ui->actionEdit->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        ui->actionAdd_album->setEnabled(false);
        ui->actionAdd_track->setEnabled(true);
    }
    if(curritem->toArtist())
    {
        ui->actionEdit->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        ui->actionAdd_album->setEnabled(true);
        ui->actionAdd_track->setEnabled(false);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open"),tr("/"), tr("*.mlib"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly))
        {
            QDataStream in(&file);
            delete model_->root_;
            setWindowModified(false);
            model_->root_ = new Item();
            ui->treeView->reset();
            in >> *(model_->root_);
            file.close();
            ui->actionEdit->setEnabled(false);
            ui->actionDelete->setEnabled(false);
            ui->actionAdd_album->setEnabled(false);
            ui->actionAdd_track->setEnabled(false);
        }

    }
    ui->treeView->reset();
}

bool MainWindow::on_actionSave_triggered()
{
    QString fName;
    fName = QFileDialog::getSaveFileName(this, tr("Save"), tr("/"), tr("*.mlib"));
    if (fName.isEmpty()) return false;
    else
    {
        QFile file(fName);
        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            out << *(model_->root_);
            file.close();
            setWindowModified(false);
            return true;
        }

    }
    return false;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionEdit_triggered()
{
    Item *curitem=static_cast<Item*>(ui->treeView->selectionModel()->currentIndex().internalPointer());
    QModelIndex currindex = ui->treeView->selectionModel()->currentIndex();
    QModelIndex parent = ui->treeView->selectionModel()->currentIndex().parent();

    if(curitem->toAlbum())
    {
            AlbumDialog *album = new AlbumDialog();
            album->setModel(model_);
            album->setModelIndex(currindex);
            album->show();
    }
    else
    if(curitem->toArtist())
    {
            ArtistDialog *artist = new ArtistDialog();
            artist->setModel(model_);
            artist->setModelIndex(currindex);
            artist->show();
    }
    else
    if(curitem->toTrack()) return;
}

void MainWindow::on_actionAdd_artist_triggered()
{
    ArtistDialog *dialog = new ArtistDialog();
    dialog->addArtist(model_, QModelIndex());
    setModified();
}

void MainWindow::on_actionAdd_album_triggered()
{
    QModelIndex currindex = ui->treeView->selectionModel()->currentIndex();
    AlbumDialog *album= new AlbumDialog();
    album->addAlbum(model_, currindex);
    setModified();
}

void MainWindow::on_actionAdd_track_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();

    Item *item = static_cast<Item*>(cur_index.internalPointer());

    if(item->toAlbum())
    {
        int row = model_->rowCount(cur_index);
        model_->insertRow(row, cur_index);
    }
    else if(item->toTrack())
    {
        int row = model_->rowCount(cur_index.parent());
        model_->insertRow(row, cur_index.parent());
    }

    setModified();
}

void MainWindow::on_actionDelete_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    model_->removeRow(cur_index.row(), cur_index.parent());
    update_active_actions(ui->treeView->selectionModel()->currentIndex());
    setModified();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}
void MainWindow::on_actionRu_triggered()
{
    if(curr_lang=="ru")
        return;
    curr_lang="ru";
    ui->actionRu->setEnabled(false);
    ui->actionEn->setEnabled(true);
    qApp->removeTranslator(&translator);
    if(translator.load("MusicLib_ru",QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        qApp->installTranslator(&translator);
    if(translator_qt.load("qt_ru",QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        qApp->installTranslator(&translator_qt);
}

void MainWindow::on_actionEn_triggered()
{
    if(curr_lang=="en")
        return;
    curr_lang="en";
    ui->actionEn->setEnabled(false);
    ui->actionRu->setEnabled(true);
    qApp->removeTranslator(&translator);
    if(translator.load("MusicLib_en",QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        qApp->installTranslator(&translator);
    if(translator_qt.load("qt_en",QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        qApp->installTranslator(&translator_qt);
}
