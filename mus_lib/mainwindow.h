#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "musicmodel.h"
#include <QCloseEvent>
#include <QLibraryInfo>
#include <QTranslator>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString curr_lang;
    QTranslator translator;
    QTranslator translator_qt;
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();
    void changeEvent(QEvent *event);
public slots:
    void setModified();
    void update_active_actions(QModelIndex ind);
private slots:
    void on_actionOpen_triggered();

    bool on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionEdit_triggered();

    void on_actionAdd_artist_triggered();

    void on_actionAdd_album_triggered();

    void on_actionAdd_track_triggered();

    void on_actionDelete_triggered();

    void on_actionRu_triggered();

    void on_actionEn_triggered();

private:
    Ui::MainWindow *ui;
    MusicModel *model_;
};

#endif // MAINWINDOW_H
