#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataWidgetMapper>
#include <musicmodel.h>

namespace Ui {
class AlbumDialog;
}

class AlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumDialog(QWidget *par = 0);
    void setModel(MusicModel*model);
    void accept();
    bool addAlbum(MusicModel *model, const QModelIndex &par);
    ~AlbumDialog();
    void setModelIndex(QModelIndex &index);
private slots:
    void on_BrowseButton_clicked();

private:
    Ui::AlbumDialog *ui;
    QDataWidgetMapper mapper_;
    QPixmap image_;
    QModelIndex index_;
    Item *item_;
};

#endif // ALBUMDIALOG_H
