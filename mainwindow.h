#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "smtp.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void mailSent(QString);
    void on_pushButton_Send_clicked();
    void on_pushButton_Exit_clicked();
    void on_pushButton_Browser_clicked();

private:
    Ui::MainWindow *ui;
    QStringList Files;
    QSettings *Setting;
};

#endif // MAINWINDOW_H
