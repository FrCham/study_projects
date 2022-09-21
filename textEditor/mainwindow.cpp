#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

QFont MainWindow::font = *new QFont("Times", 12);
QList<MainWindow*> MainWindow::windows = QList<MainWindow*>();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(documentModified()));

    ui->copy->setEnabled(false);
    ui->cut->setEnabled(false);
    ui->undo->setEnabled(false);
    ui->redo->setEnabled(false);

    this->setCentralWidget(ui->textEdit);
    this->setWindowIcon(QIcon(":/icons/Icons/favorites.png"));
    this->setWindowTitle("Новый Файл.txt");
    loadFont();

    file_path_ = "";
    windows.push_back(this);
    //this -> haveChanged = false;
    this->canceled = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeFont()
{
    QSettings settings("./settings.conf", QSettings::IniFormat);
    settings.beginGroup("Font");
    settings.setValue("font", ui->textEdit->font());
    settings.endGroup();
}

void MainWindow::loadFont()
{
    QSettings settings("settings.conf", QSettings::IniFormat);

    settings.beginGroup("Font");
    QFont font = qvariant_cast<QFont>(settings.value("font", -1));
    settings.endGroup();

    ui->textEdit->setFont(font);
}

void MainWindow::on_newFile_triggered()
{
    nWin = new MainWindow;
    nWin->haveChanged = false;
    nWin->ui->textEdit->setFont(this->font);
    nWin->show();
    windows.push_back(new MainWindow());
}

void MainWindow::on_open_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл");
    QFile file(file_name);
    file_path_ = file_name;
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"Внимание", "Файл не был открыт");
        return;
    }
    QString fileName = QFileInfo(file).fileName();
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    this->setWindowTitle(fileName);
    this->haveChanged = false;
    file.close();
}

void MainWindow::on_save_triggered()
{
    QFile file(file_path_);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        MainWindow::on_saveAs_triggered();
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    QString fileName = QFileInfo(file).fileName();
    this->setWindowTitle(fileName);
    this->haveChanged = false;
    file.flush();
    file.close();
}

void MainWindow::on_saveAs_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Открыть файл");
    QFile file(file_name);
    file_path_ = file_name;
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"Внимание", "Файл не был сохранён");
        this->canceled = true;
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    QString fileName = QFileInfo(file).fileName();
    this->setWindowTitle(fileName);
    this->haveChanged = false;
    file.flush();
    file.close();
}

void MainWindow::on_closeFile_triggered()
{
//     if (!maybeSave() && this->canceled) return;
//     if (!maybeSave())
//         close();
//             else on_save_triggered();
    close();
}

void MainWindow::on_exit_triggered()
{
   MainWindow::closeAllWindows();
}

void MainWindow::on_copy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_undo_triggered()
{
    ui->textEdit->undo();
}
void MainWindow::on_redo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->font(), nullptr, QString::fromUtf8("Выберите шрифт"));

    if (ok) {
        MainWindow::font = font;
        ui->textEdit->setFont(font);
    }

    writeFont();
}

void MainWindow::on_about_triggered()
{
    QString about_text;
    about_text = "Выполнил: Матвеев Александр\n";
    about_text += "Группа: Б17-501";
    QMessageBox::about(this,"Информация об авторе",about_text);
}

void MainWindow::on_about_Qt_triggered()
{
    QMessageBox::aboutQt(this, qVersion());
}

void MainWindow::on_textEdit_textChanged()
{
    if (!this->haveChanged)
        this->setWindowTitle("*"+windowTitle());
    this->setWindowModified(true);
    this->haveChanged = true;
}

bool MainWindow::maybeSave()
{
    if (!this->haveChanged)  return false;
    else{

        this->canceled = false;
        const QMessageBox::StandardButton ret
            = QMessageBox::warning(this, tr("Закрытие файла"),
                                   tr("Содержимое файла было изменено.\n"
                                      "Сохранить эти изменения?"),
                                   QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::No);
        switch (ret) {
        case QMessageBox::Yes:
            this->canceled = false;
            MainWindow::on_save_triggered();
            return true;
        case QMessageBox::No:
            this ->haveChanged = false;
            this->canceled = false;
            return false;
        default:
            this->canceled = true;
            return true;
        }

        //this ->haveChanged = false;
        //return;
    }
    return false;

}

void MainWindow::closeAllWindows(){
    foreach(QWidget *widget, QApplication::topLevelWidgets()){
        if (!widget->isWindowModified())
            widget->close();
    }
    foreach(QWidget *widget, QApplication::topLevelWidgets()){
       // if (!widget->isWindowModified())
       //    widget->close();
       if(!widget->close()) break;
    }

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (maybeSave()) event->ignore();
            else event->accept();

}

