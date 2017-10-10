#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Smtp smtp = new Smtp("your_username@gmail.com", "your_password", "smtp.gmail.com");
    Smtp *smtp = new Smtp("browniz1004", "fdb5b33a51", "smtp.naver.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    smtp->sendMail("browniz1004@naver.com", "browniz1004@naver.com" , tr("This is a subject"), tr("This is a body"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mailSent(QString Message)
{
    qDebug()<<Message;
}
