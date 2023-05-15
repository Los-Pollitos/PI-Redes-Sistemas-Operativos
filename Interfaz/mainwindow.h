#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "login.h"
#include "../File_System/file_system.h"

#include <QMainWindow>
#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow* ui;
    login* loginPage;
    FS* file_system;
};
#endif // MAINWINDOW_H
