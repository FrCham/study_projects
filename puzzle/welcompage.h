#ifndef WELCOMPAGE_H
#define WELCOMPAGE_H

#include <QDialog>

namespace Ui { class WelcomPage; }

class WelcomPage : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomPage(QWidget *parent = nullptr);
    ~WelcomPage();
    QString imgFileName();
    QSize pSize();

private slots:

    void on_pushButton_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::WelcomPage *ui;
    QString filename;
};
#endif // WELCOMPAGE_H
