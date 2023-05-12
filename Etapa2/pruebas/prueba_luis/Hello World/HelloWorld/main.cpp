#include <QApplication>
#include <QLabel>

int main(int argc, char ** argv) {
  // Define the QApplication and QLabel
  QApplication app(argc, argv);
  QLabel* label = new QLabel("Hello World");

  // Use label methods to show text and change title
  label->setWindowTitle("Label");
  label->show();
  label->resize(400, 400);

  app.exec();
  delete label;

  return 0;
}
