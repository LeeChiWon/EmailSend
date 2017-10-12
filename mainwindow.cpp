#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Setting=new QSettings("Smtp","EmailSender",this);

    ui->lineEdit_SmtpServer->setText(Setting->value("Configuration/SmtpServer").toString());
    ui->lineEdit_ServerPort->setText(Setting->value("Configuration/SmtpPort").toString());
    ui->lineEdit_UserName->setText(Setting->value("Configuration/UserName").toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    Setting->setValue("Configuration/SmtpServer",ui->lineEdit_SmtpServer->text());
    Setting->setValue("Configuration/SmtpPort",ui->lineEdit_ServerPort->text());
    Setting->setValue("Configuration/UserName",ui->lineEdit_UserName->text());
    event->accept();
}

void MainWindow::mailSent(QString Message)
{    
    QMessageBox::warning( 0, tr( "Email Send Result" ), Message);
}

void MainWindow::on_pushButton_Send_clicked()
{
    QString From=QString("%1@%2").arg(ui->lineEdit_UserName->text(),ui->lineEdit_SmtpServer->text().replace("smtp.",""));
    Smtp *smtp = new Smtp(ui->lineEdit_UserName->text(), ui->lineEdit_Password->text(), ui->lineEdit_SmtpServer->text(),ui->lineEdit_ServerPort->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    if(!Files.isEmpty())
    {
        smtp->sendMail(From, ui->lineEdit_To->text() , ui->lineEdit_Title->text(), ui->textEdit_Memo->toPlainText(),Files);
    }
    else
    {
        smtp->sendMail(From, ui->lineEdit_To->text() , ui->lineEdit_Title->text(), ui->textEdit_Memo->toPlainText());
    }

    ui->lineEdit_Title->setText("");
    ui->lineEdit_To->setText("");
    ui->lineEdit_Attachment->setText("");
    ui->textEdit_Memo->setText("");
}

void MainWindow::on_pushButton_Exit_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_Browser_clicked()
{
    Files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        Files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, Files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->lineEdit_Attachment->setText( fileListString );
}

