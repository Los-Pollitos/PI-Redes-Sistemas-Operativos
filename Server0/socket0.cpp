#include "socket0.h"

Socket0::Socket0()
{

}

void Socket0::Connect()
{
    socket= new QTcpSocket() ;
    socket->connectToHost("localhost",1337) ;

    if (socket->waitForConnected(3000)) {
        qDebug() << "Connected" ;

        if (socket->waitForReadyRead(3000)) {
            qDebug() << socket->readAll() ;
            qDebug() << "Recibiendo:" << socket->bytesAvailable() ;
            socket->write("hello server\r\n\r\n\r\n\r\n");
            socket->waitForBytesWritten(1000) ;
        }
        qDebug() << "Connected" ;

        socket->close();
    } else {
        qDebug() << "Disconnected" ;
    }
}
