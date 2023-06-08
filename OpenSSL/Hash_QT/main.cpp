#include <QApplication>

#include <string>

#include <QCryptographicHash>

#include <iostream>

std::string hash(QString password) {
    QString answer = QString(QCryptographicHash::hash((password.toStdString()),QCryptographicHash::Md5).toHex());
    return answer.toStdString();
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::cout << hash("luis") << "\n";

    return 0;
}
