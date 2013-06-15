#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include "qoverlaywidget.h"
#include "qscenewidget.h"
#include "qcamera.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  QCamera *camleft;
  QCamera *camright;
  QSceneWidget *scene;
public:
  MainWindow(int devleft, int devright, QWidget *parent = 0);
  ~MainWindow();
private slots:
  void refresh();
};

#endif // MAINWINDOW_H
