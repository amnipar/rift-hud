#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int devleft, devright;
  if (argc < 3) {
    devleft = 0;
    devright = 1;
  }
  else {
    devleft = QString(argv[1]).toInt();
    devright = QString(argv[2]).toInt();
  }
  MainWindow w(devleft, devright);
  w.showFullScreen();

  return a.exec();
}
