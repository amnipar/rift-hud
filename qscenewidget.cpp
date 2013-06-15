#include <QtGui/QPainter>
#include <QtGui/QPaintEngine>
#include "qscenewidget.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <assert.h>

int g_argc;
char *g_argv;

QSceneWidget::QSceneWidget(pixel_image *left, pixel_image *right, QWidget *parent)
  : QGLWidget(parent)
{
  this->left = left;
  this->right = right;
  /*
  this->leftImage = new QImage((data_pointer)left->data, left->width, 
                               left->height, QImage::Format_RGB888);
  this->rightImage = new QImage((data_pointer)right->data, right->width, 
                                right->height, QImage::Format_RGB888);
  */
  this->setFixedSize(1280, 800);
  // make Qt do the work of keeping the overlay the magic color
  setAttribute(Qt::WA_PaintOnScreen);
  QWidget::setBackgroundRole(QPalette::Window);
  QWidget::setAutoFillBackground(true);
}

QSceneWidget::~QSceneWidget()
{
  //
}

void QSceneWidget::refresh()
{
  update();
}

/*
void QSceneWidget::paintEvent(QPaintEvent *)
{
  QPainter painter;
  painter.begin(this);

  painter.end();
}
*/

void QSceneWidget::paintTriangle()
{
  GLfloat afVertices[] = {
    0.0f,  0.0f,  0.0f,
    0.5f,  0.0f,  0.0f,
    0.0f,  0.5f,  0.0f,

    0.0f,  0.0f,  0.0f,
    0.5f,  0.0f,  0.0f,
    0.0f,  0.0f,  0.5f,

    0.0f,  0.0f,  0.0f,
    0.0f,  0.5f,  0.0f,
    0.0f,  0.0f,  0.5f,

    0.0f,  0.0f,  0.0f,
    0.0f,  0.5f,  0.0f,
    0.5f,  0.0f,  0.0f,

    0.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  0.5f,
    0.5f,  0.0f,  0.0f,

    0.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  0.5f,
    0.0f,  0.5f,  0.0f
  };
  GLfloat afColors[] = {
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f
  };
  program1.setAttributeArray(vertexAttr1, afVertices, 3);
  program1.setAttributeArray(colorAttr1, afColors, 4);
  program1.enableAttributeArray(vertexAttr1);
  program1.enableAttributeArray(colorAttr1);
  glDrawArrays(GL_TRIANGLES, 0, 18);
  program1.disableAttributeArray(vertexAttr1);
  program1.disableAttributeArray(colorAttr1);
}

void QSceneWidget::paintTexturedQuad(GLuint texture)
{
  GLfloat afVertices[] = {
    /*
    -0.999f, -0.999f,  0.999f,
     0.999f,  0.999f,  0.999f,
    -0.999f,  0.999f,  0.999f,

    -0.999f, -0.999f,  0.999f,
     0.999f, -0.999f,  0.999f,
     0.999f,  0.999f,  0.999f,
     */
    -0.999f, -0.750f,  0.999f,
    -0.999f,  0.750f,  0.999f,
     0.999f,  0.750f,  0.999f,
     
    -0.999f, -0.750f,  0.999f,
     0.999f,  0.750f,  0.999f,
     0.999f, -0.750f,  0.999f
  };
  program2.setAttributeArray(vertexAttr2, afVertices, 3);
  
  GLfloat afColors[] = {
    /*
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    */
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f
  };
  program2.setAttributeArray(colorAttr2, afColors, 4);
  
  GLfloat afTexCoord[] = {
    /*
    0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f,
    0.0f,0.0f, 1.0f,0.0f, 1.0f,1.0f,
    */
    0.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f,
    0.0f,0.0f, 1.0f,1.0f, 1.0f,0.0f
  };
  program2.setAttributeArray(texCoordAttr2, afTexCoord, 2);
  
  GLfloat afNormals[] = {
    0,0,-1, 0,0,-1, 0,0,-1,
    0,0,-1, 0,0,-1, 0,0,-1,
    0,0,-1, 0,0,-1, 0,0,-1,
    0,0,-1, 0,0,-1, 0,0,-1
  };
  program2.setAttributeArray(normalAttr2, afNormals, 3);
  
  
  program2.enableAttributeArray(vertexAttr2);
  program2.enableAttributeArray(normalAttr2);
  program2.enableAttributeArray(colorAttr2);
  program2.enableAttributeArray(texCoordAttr2);
  glBindTexture(GL_TEXTURE_2D, texture);
  program2.setUniformValue(textureUniform2, 0); // use texture unit 0
  glDrawArrays(GL_TRIANGLES, 0, 6);
  program2.disableAttributeArray(vertexAttr2);
  program2.disableAttributeArray(normalAttr2);
  program2.disableAttributeArray(colorAttr2);
  program2.disableAttributeArray(texCoordAttr2);
}

void QSceneWidget::initializeGL ()
{
  QGLShader *vshader1 = new QGLShader(QGLShader::Vertex, this);
  const char *vsrc1=
      "attribute highp   vec4 vertex;\n"
      "attribute mediump vec3 normal;\n"
      "attribute mediump vec4 color;\n"
      "uniform   mediump mat4 matrix;\n"
      "varying   mediump vec4 vcolor;\n"
      "void main(void)\n"
      "{\n"
      "    gl_Position = matrix * vertex;\n"
      "    vcolor = color;\n"
      "}\n";

  //"attribute mediump vec4 color;\n"
  //"varying   mediump vec4 g_vVSColor;\n"
  //"attribute mediump vec3 normal;\n"
  //"    g_vVSColor = color;\n"

  vshader1->compileSourceCode(vsrc1);

  QGLShader *fshader1 = new QGLShader(QGLShader::Fragment, this);
  const char *fsrc1 =
      "varying mediump vec4 vcolor;\n"
      "void main (void)\n"
      "{\n"
      "    gl_FragColor = vcolor;\n"
      "}\n";

  //vec4(1.0, 1.0, 0.66 ,1.0);\n"
  //"varying mediump vec4 g_vVSColor;\n"
  //g_vVSColor;\n"
  //"out mediump vec3 min;\n"
  //"out mediump vec3 max;\n"
  //"    if (gl_FragCoord.x < min.x) min.x = gl_FragCoord.x;"
  //"    if (gl_FragCoord.x > max.x) max.x = gl_FragCoord.x;"
  //"    if (gl_FragCoord.y < min.y) min.y = gl_FragCoord.y;"
  //"    if (gl_FragCoord.y > max.y) max.y = gl_FragCoord.y;"
  //"    mediump float visible = 1.0;\n"
  //"    if (gl_FragCoord.y > 240.0) gl_FragColor = vec4(0.0, 1.0, 0.0, 0.0);\n"
  //"    else gl_FragColor = vcolor;\n"
  //"    gl_FragColor = vcolor;\n"

  fshader1->compileSourceCode(fsrc1);

  program1.addShader(vshader1);
  program1.addShader(fshader1);
  program1.link();

  vertexAttr1 = program1.attributeLocation("vertex");
  normalAttr1 = program1.attributeLocation("normal");
  colorAttr1 = program1.attributeLocation("color");
  matrixUniform1 = program1.uniformLocation("matrix");

  QGLShader *vshader2 = new QGLShader(QGLShader::Vertex);
  const char *vsrc2 =
      "attribute highp vec4 vertex;\n"
      "attribute highp vec4 texCoord;\n"
      "attribute mediump vec3 normal;\n"
      "uniform mediump mat4 matrix;\n"
      "varying highp vec4 texc;\n"
      "varying mediump float angle;\n"
      "void main(void)\n"
      "{\n"
      "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
      "    angle = max(dot(normal, toLight), 0.0);\n"
      "    gl_Position = matrix * vertex;\n"
      "    texc = texCoord;\n"
      "}\n";
  vshader2->compileSourceCode(vsrc2);

  QGLShader *fshader2 = new QGLShader(QGLShader::Fragment);
  const char *fsrc2 =
      "varying highp vec4 texc;\n"
      "uniform sampler2D tex;\n"
      "varying mediump float angle;\n"
      "void main(void)\n"
      "{\n"
      "    highp vec3 color = texture2D(tex, texc.st).rgb;\n"
      "    color = color * 0.2 + color * 0.8 * angle;\n"
      "    gl_FragColor = vec4(clamp(color, 0.0, 1.0), 1.0);\n"
      "}\n";
  fshader2->compileSourceCode(fsrc2);

  program2.addShader(vshader2);
  program2.addShader(fshader2);
  program2.link();

  vertexAttr2 = program2.attributeLocation("vertex");
  normalAttr2 = program2.attributeLocation("normal");
  texCoordAttr2 = program2.attributeLocation("texCoord");
  matrixUniform2 = program2.uniformLocation("matrix");
  textureUniform2 = program2.uniformLocation("tex");
  
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glDepthFunc(GL_LESS);
  glDepthMask(GL_FALSE);

  glDepthRange( -1.0f, 1.0f );
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glDisable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glShadeModel(GL_SMOOTH);
  /*
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_MULTISAMPLE);
  static GLfloat lightPosition[4] = {-0.5, 1.0, -1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  */
  //glFrontFace( GL_CW );
  //glDisable( GL_CULL_FACE );

  //glBlendEquation( GL_FUNC_ADD );
  //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  //glEnable( GL_BLEND );

  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  m_fAngle = 0;
  m_fScale = 1;
  g_argc = 0;
  glutInit(&g_argc, &g_argv);
}

/*
bool QSceneWidget::event(QEvent *event)
{
  return QGLWidget::event(event);
}
*/

void QSceneWidget::paintGL()
{
  //makeCurrent();
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  
  /*glGenTextures(1, &m_leftTexture);*/
  m_leftTexture = bindTexture(QImage((data_pointer)left->data, left->width, 
                               left->height, QImage::Format_RGB888),
                               GL_TEXTURE_2D
                             );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  /*glGenTextures(1, &m_rightTexture);*/
  m_rightTexture = bindTexture(QImage((data_pointer)right->data, right->width, 
                               right->height, QImage::Format_RGB888),
                               GL_TEXTURE_2D
                              );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  painter.beginNativePainting();
  //glGetIntegerv(GL_VIEWPORT, params);
  //glGetFloatv(GL_DEPTH_RANGE, depth);
  //glDepthRangef(1.0f, 500.0f);

  /* may need to remove clearing color buffer if draw image */
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  glFrontFace(GL_CCW);
  
  glCullFace(GL_FRONT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);
  
  double ipd = 0.064;
  double leftEye[3] = { -0.5*ipd, 0.15, 0.1 };
  double rightEye[3] = { 0.5*ipd, 0.15, 0.1 };
  
  float hscreensize = 0.14976f;
  float lensseparation = 0.0635f;
  float viewCenter = hscreensize * 0.25f;
  float eyeProjectionShift = viewCenter - lensseparation*0.5f;
  double offs = 4.0f * eyeProjectionShift / hscreensize;
  GLsizei halfwidth = this->width() / 2;
  GLsizei yoff = (this->height() - halfwidth) / 2;
  QMatrix4x4 mproj, mview, mobj;
  
  /* render left eye view */
  glViewport(0, yoff, halfwidth, halfwidth);
  //std::cout << offs << std::endl;
  mproj.setToIdentity();
  // offset translate operation for left eye
  mproj.translate(offs, 0.0f, 0.0f);
  mproj *= perspectiveMatrix;
  
  mview.setToIdentity();
  /*mview.translate(offs, 0.1f, -0.2f);*/
  
  mobj.setToIdentity();
  //mobj.translate(0.1f, 0.1f, 0.1f);
  mobj *= mview;
  mobj *= mproj;
  
  program2.bind();
  program2.setUniformValue(matrixUniform2, mobj);
  paintTexturedQuad(m_leftTexture);
  program2.release();

  program1.bind();
  program1.setUniformValue(matrixUniform1, mobj);
  paintTriangle();
  program1.release();
  
  glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
  glPushMatrix();
  glTranslatef(10.0f, 100.0f, 0.8f);
  //glScalef(0.5, -0.5, 0.5);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'T');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 's');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
  glPopMatrix();
  
  /* render right eye view */
  glViewport(halfwidth, yoff, halfwidth, halfwidth);
  
  mproj.setToIdentity();
  // offset translate operation for left eye
  mproj.translate(-offs, 0.0f, 0.0f);
  mproj *= perspectiveMatrix;
  
  mview.setToIdentity();
  /*mview.translate(0.0f, 0.1f, -0.2f);*/
  
  mobj.setToIdentity();
  //mobj.translate(0.1f, 0.1f, 0.1f);
  mobj *= mview;
  mobj *= mproj;
  
  program2.bind();
  program2.setUniformValue(matrixUniform2, mobj);
  paintTexturedQuad(m_rightTexture);
  program2.release();
  
  program1.bind();
  program1.setUniformValue(matrixUniform1, mobj);
  paintTriangle();
  program1.release();
  
  glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
  glPushMatrix();
  glTranslatef(10.0f, 100.0f, 0.8f);
  //glScalef(0.5, -0.5, 0.5);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'T');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 's');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
  glPopMatrix();

  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  //glFrontFace(GL_CCW);
  
  //glCullFace(GL_FRONT);
  //glEnable(GL_CULL_FACE);
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);

  // load identity matrix
  // set the viewport (should be set already?)
  // disable stencil buffer (?)
  
  //glDisable(GL_BLEND);
  //glDisable(GL_DEPTH_TEST);
  //glDisable(GL_CULL_FACE);

  painter.endNativePainting();
  
  //painter.setPen(QPen(Qt::yellow));
  //painter.drawText(QPoint(5, 20), this->fps);
  
  painter.end();
  swapBuffers();
}

void QSceneWidget::paintEvent(QPaintEvent *e)
{
  updateGL();
}

void QSceneWidget::resizeEvent(QResizeEvent *event)
{
  resizeGL(event->size().width(), event->size().height());
}

void QSceneWidget::resizeGL(int width, int height)
{
  //makeCurrent();
  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glDepthRange(0.0f, 1.0f);
  glClearDepth(1.0f);
  
  double znear = 0.1;
  double zfar = 500.0;
  double aspect = (double)width / (double)height;
  double fov = 90.0 / aspect;
#if !defined(QT_OPENGL_ES_2)
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  const double DEG2RAD = 3.14159265 / 180;

  double tangent = tan(fov/2 * DEG2RAD);   // tangent of half fovY
  double h = znear * tangent;          // half height of near plane
  double w = h * aspect;      // half width of near plane
  // params: left, right, bottom, top, near, far
  glFrustum(-w, w, -h, h, znear, zfar);
#else
  perspectiveMatrix.setToIdentity();
  perspectiveMatrix.perspective(fov, aspect, znear, zfar);
  std::cout << "OpenGL ES 2" << std::endl;
  glOrthof(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
#endif
  glMatrixMode(GL_MODELVIEW);
}
