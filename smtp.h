#ifndef SMTP_H
#define SMTP_H

#include <QtWidgets>
#include <QObject>
#include <QAbstractSocket>
#include <QSslSocket>

class Smtp : public QObject
{
    Q_OBJECT


public:
    Smtp( const QString &user, const QString &pass,
          const QString &host, const int &port, int timeout = 30000 );
    ~Smtp();

    void sendMail( const QString &from, const QString &to,
                   const QString &subject, const QString &body,
                   QStringList Files=QStringList());

signals:
    void status( const QString &);

private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();

private:
    int timeout;
    QString message;
    QTextStream *t;
    QSslSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;
    int port;
    enum states{Tls, HandShake ,Auth,User,Pass,Rcpt,Mail,Data,Init,Body,Quit,Close};
    int state;

};
#endif
