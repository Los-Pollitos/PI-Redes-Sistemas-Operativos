#include "mainwindow.h"

#include <QApplication>
#include "socket0.h"
#include "server0.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Server0 *server= new Server0() ;

//    Socket0 *client= new Socket0() ;
//    client->Connect();

    w.show();
    return a.exec();
}
