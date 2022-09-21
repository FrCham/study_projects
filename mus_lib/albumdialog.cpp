#include "albumdialog.h"
#include "ui_albumdialog.h"

AlbumDialog::AlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlbumDialog)
{
    ui->setupUi(this);
    ui->AlineEdit->setReadOnly(true);
    mapper_.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
}

void AlbumDialog::setModel(MusicModel *model)
{
    mapper_.setModel(model);
}

void AlbumDialog::accept()
{
    mapper_.submit();
    QDialog::accept();
}

bool AlbumDialog::addAlbum(MusicModel *model, const QModelIndex &par)
{
    setModel(model);
    int row = model->rowCount(par);
    if(!model->insertRow(row, par))
        return false;
    index_ = model->index(row, 0, par);
    setModelIndex(index_);
    if(!exec()){
        model->removeRow(row, par);
        return false;
    }
    return true;
}

AlbumDialog::~AlbumDialog()
{
    delete ui;
}

void AlbumDialog::setModelIndex(QModelIndex &index)
{
    QModelIndex parent = index.parent();
    Item *item = static_cast<Item*>(index.internalPointer());

    ui->AlineEdit->setText(item->parent()->name());

    mapper_.setRootIndex(parent);
    mapper_.setCurrentModelIndex(index);

    mapper_.addMapping(ui->NlineEdit,0);
    mapper_.addMapping(ui->GlineEdit,1);
    mapper_.addMapping(ui->YspinBox,2);
    mapper_.addMapping(ui->comment,3);
    mapper_.setCurrentIndex(index.row());

    ui->NlineEdit->setText(item->name());
    ui->GlineEdit->setText(item->toAlbum()->getGenre());
    ui->YspinBox->setValue(item->toAlbum()->getYear());
    ui->Imglabel->setPixmap(item->toAlbum()->getImage());
    ui->comment->document()->setPlainText(item->description());
}

void AlbumDialog::on_BrowseButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), tr("/"), tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.isEmpty()) return;
    else
    {
        if (!image_.load(fileName))
        {
            QMessageBox::warning(this, tr("Open Image"), tr("The image file could not be loaded."), QMessageBox::Close);
            return;
        }
        ui->Imglabel->setPixmap(image_.scaled(150,150));
    }
}

