/*
Equipo: Los Pollitos
Cristopher Hernández (C13632)
Luis Solano (C17634)
Angie Solís (C17686)
Emilia Víquez (C18625)
*/

#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon icon(":/icons/icon.gif");
    a.setWindowIcon(icon);
    a.setApplicationName("LosPollitosIncorporated");

    MainWindow w;
    w.hide();
    return a.exec();
}
