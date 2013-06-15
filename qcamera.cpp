#include "qcamera.h"

#include <iostream>
#include <sys/time.h>

QCamera::QCamera(int dev, int width, int height, QObject *parent)
  : QThread(parent), cap(dev)
{
  result r;

  cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);

  r = pixel_image_create(&rgb, p_U8, RGB, width, height, 3, 3 * width);
  if (r != SUCCESS) {
    std::cout << "pixel_image_create " << (int)r << std::endl;
  }
  r = pixel_image_create(&grey, p_U8, RGB, width, height, 1, 1 * width);
  if (r != SUCCESS) {
    std::cout << "pixel_image_create " << (int)r << std::endl;
  }

  running = false;
}

QCamera::~QCamera()
{
  pixel_image_destroy(&grey);
  pixel_image_destroy(&rgb);
}

pixel_image *QCamera::greyImage()
{
  return &grey;
}

pixel_image *QCamera::rgbImage()
{
  return &rgb;
}

void QCamera::run()
{
  struct timeval start, finish;
  double timediff;
  cv::Mat frame;
  cv::Mat gr(grey.height, grey.width, CV_8UC3, grey.data, grey.stride);
  cv::Mat co(rgb.height, rgb.width, CV_8UC3, rgb.data, rgb.stride);

  running = true;
  while (running) {
    gettimeofday(&start, NULL);

    cap >> frame;
    cv::cvtColor(frame, co, CV_BGR2RGB);
    /*cv::resize(gr, co, co.size(), 0, 0, cv::INTER_LINEAR);*/
    //cv::cvtColor(frame, co, CV_BGR2RGB);

    if (!running) break;
    gettimeofday(&finish, NULL);
    timediff = (finish.tv_sec - start.tv_sec) + ((double)(finish.tv_usec - start.tv_usec) / 1000000.0);
    //std::cout << "update+convert time taken " << timediff << std::endl;
    emit frameSignal();
    usleep(5);
  }
}

void QCamera::finish()
{
  //std::cout << "finish" << std::endl;
  running = false;
}
