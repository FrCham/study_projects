#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_newFile_triggered();

    void on_open_triggered();

    void on_save_triggered();

    void on_saveAs_triggered();

    void on_closeFile_triggered();

    void on_exit_triggered();

    void on_copy_triggered();

    void on_cut_triggered();

    void on_paste_triggered();

    void on_undo_triggered();

    void on_redo_triggered();

    void on_font_triggered();

    void on_about_triggered();

    void on_about_Qt_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    MainWindow *nWin;
    QString file_path_;
    static QFont font;
    void writeFont();
    void closeEvent(QCloseEvent* event);
    void loadFont();
    bool maybeSave();
    bool haveChanged;
    bool canceled;
    void closeAllWindows();
    static QList<MainWindow*> windows;

};
#endif // MAINWINDOW_H
