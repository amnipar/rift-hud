#ifndef QSCENEWIDGET_H
#define QSCENEWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QPaintEvent>
#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtOpenGL>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/qglshaderprogram.h>
#include "cvsu/cvsu_pixel_image.h"

class QSceneWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit QSceneWidget(pixel_image *left, pixel_image *right, QWidget *parent = 0);
  virtual ~QSceneWidget();
  virtual void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *event);
protected: // from QGLWidget
  virtual void paintGL();
  virtual void initializeGL();
  virtual void resizeGL(int width, int height);
private:
  void paintTriangle();
  void paintTexturedQuad(GLuint texture);
  QColor colorKey;
  QImage leftImage;
  QImage rightImage;
  pixel_image *left;
  pixel_image *right;
  GLuint  m_uiTexture;
  GLuint  m_leftTexture;
  GLuint  m_rightTexture;
  qreal   m_fAngle;
  qreal   m_fScale;
  QMatrix4x4 perspectiveMatrix;
  QMatrix4x4 cameraMatrix;
  QGLShaderProgram program1;
  QGLShaderProgram program2;
  int vertexAttr1;
  int colorAttr1;
  int normalAttr1;
  int texCoordAttr1;
  int matrixUniform1;
  int textureUniform1;
  int vertexAttr2;
  int colorAttr2;
  int normalAttr2;
  int texCoordAttr2;
  int matrixUniform2;
  int textureUniform2;
signals:
  //
public slots:
  void refresh();
};

#endif // QSCENEWIDGET_H
