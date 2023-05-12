#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    // Allows to create signals and slots to widgets
    Q_OBJECT

public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);
    // Destructor
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    // UI object, handles all widgets
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
