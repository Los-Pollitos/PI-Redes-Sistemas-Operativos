#ifndef SOCKET0_H
#define SOCKET0_H
#include <QTcpSocket>
#include <QDebug>

class Socket0
{
public:
    Socket0();

    void Connect();
    QTcpSocket *socket ;
};

#endif // SOCKET0_H
