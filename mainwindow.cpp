#include "mainwindow.h"
#include <iostream>
#include <sys/time.h>

const int ImageWidth = 320;//640;
const int ImageHeight = 240;//480;

MainWindow::MainWindow(int devleft, int devright, QWidget *parent)
  : QMainWindow(parent)
{
  camleft = new QCamera(devleft, ImageWidth, ImageHeight, this);
  camright = new QCamera(devright, ImageWidth, ImageHeight, this);
  scene = new QSceneWidget(camleft->rgbImage(), camright->rgbImage(), this);
  
  QObject::connect(camleft, SIGNAL(frameSignal()), this, SLOT(refresh()));
  QObject::connect(camright, SIGNAL(frameSignal()), this, SLOT(refresh()));
  camleft->start(QThread::LowPriority);
  camright->start(QThread::LowPriority);
}

MainWindow::~MainWindow()
{
  camleft->finish();
  camleft->wait(1000);
  camright->finish();
  camright->wait(1000);
}

void MainWindow::refresh()
{
  scene->repaint();
  //repaint();
}
