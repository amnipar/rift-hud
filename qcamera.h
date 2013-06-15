#ifndef QCAMERA_H
#define QCAMERA_H

#include <QThread>

#include "cvsu/cvsu_pixel_image.h"
#include <opencv2/opencv.hpp>

class QCamera : public QThread
{
  Q_OBJECT
public:
  explicit QCamera(int dev, int width, int height, QObject *parent = 0);
  virtual ~QCamera();

  virtual void run();
  void finish();

  pixel_image *greyImage();
  pixel_image *rgbImage();
protected:
  cv::VideoCapture cap;
  pixel_image rgb;
  pixel_image grey;
  bool running;
signals:
  void frameSignal();
public slots:

};

#endif // QCAMERA_H
