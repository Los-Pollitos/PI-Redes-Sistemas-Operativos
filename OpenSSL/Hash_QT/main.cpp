#include <QApplication>

#include <string>

#include <QCryptographicHash>

#include <iostream>

std::string hash_string(std::string password) {
    QString answer = QString(QCryptographicHash::hash((password),QCryptographicHash::Md5).toHex());
    return answer.toStdString();
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::cout << "cjimenez :"<< hash_string("(e!zR$Y6/8TSgRs$") << "\n\n";	std::cout << "gmora :"<< hash_string("d{QbnP8(}kp") << "\n\n";	std::cout << "jnuñez :"<< hash_string("Ly=)Z6P4eUE") << "\n\n";	std::cout << "eguzman :"<< hash_string("3526283_eg@1998") << "\n\n";	std::cout << "alopez :"<< hash_string("&trabajoFeliz34!") << "\n\n";	std::cout << "respinoza :"<< hash_string("bRc=Q+->6$") << "\n\n";	std::cout << "gherrera :"<< hash_string("contrasena?DeAs1stenteMuySegura") << "\n\n";	std::cout << "rgang :"<< hash_string("r1cardo@gAng_?}") << "\n\n";	std::cout << "dcabezas :"<< hash_string("kfc&pollo_las_24horas!") << "\n\n";	std::cout << "d_gmora :"<< hash_string("3526283_e@g1998") << "\n\n";	return 0;

    return 0;
}
