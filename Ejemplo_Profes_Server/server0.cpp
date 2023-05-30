#include "server0.h"


Server0::Server0(QObject *parent)
    : QObject{parent}
{
    server= new QTcpServer(this) ;
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection())) ;



    if (!server->listen(QHostAddress::Any,1337)){
        qDebug() << "Server problem" ;
    } else {
        qDebug() << "Server started..." ;
    }
}

void Server0::newConnection(){
    QTcpSocket *socket= server->nextPendingConnection() ;

    socket->write("hello client\r\n") ;
    socket->flush() ;
    qDebug() << "Server send" ;

    if (socket->waitForReadyRead(3000)) {
        qDebug() << socket->readAll() ;
        qDebug() << "Recibiendo:" << socket->bytesAvailable() ;
    }
}

