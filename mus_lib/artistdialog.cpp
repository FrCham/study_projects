#include "artistdialog.h"
#include "ui_artistdialog.h"

ArtistDialog::ArtistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArtistDialog)
{
    ui->setupUi(this);
    mapper_.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
}

void ArtistDialog::setModel(MusicModel *model)
{
    mapper_.setModel(model);
}

void ArtistDialog::setModelIndex(const QModelIndex &model)
{
    QModelIndex parent = model.parent();
    mapper_.setRootIndex(parent);
    mapper_.setCurrentModelIndex(model);
    mapper_.addMapping(ui->NlineEdit,0);
    mapper_.addMapping(ui->ClineEdit,1);
    mapper_.addMapping(ui->comment,2);
    mapper_.addMapping(ui->Imglabel,3, "pixmap");
    mapper_.setCurrentIndex(model.row());
}

void ArtistDialog::accept()
{
    mapper_.submit();
    QDialog::accept();
}

bool ArtistDialog::addArtist(MusicModel *model, const QModelIndex &par)
{
    setModel(model);
    int row = model->rowCount(par);
    if(!model->insertRow(row, par))
        return false;
    QModelIndex index = model->index(row, 0, par);
    setModelIndex(index);
    if(!exec()){
        model->removeRow(row, par);
        return false;
    }
    return true;
}

ArtistDialog::~ArtistDialog()
{
    delete ui;
}

void ArtistDialog::on_BrowseButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), tr("/"), tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.isEmpty()) return;
    else
    {
        if (!image_.load(fileName))
        {
            QMessageBox::warning(this, tr("Open Image"), tr("The image file could not be loaded."),  QMessageBox::Close);
            return;
        }
        ui->Imglabel->setPixmap(image_.scaled(150,150));
    }
}
