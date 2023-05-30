#ifndef SERVER0_H
#define SERVER0_H
#include <QTcpServer>
#include <QTcpSocket>

#include <QObject>

class Server0 : public QObject
{
    Q_OBJECT
public:
    explicit Server0(QObject *parent = nullptr);

signals:

public slots:
   void newConnection() ;

private:
   QTcpServer *server ;
};

#endif // SERVER0_H
