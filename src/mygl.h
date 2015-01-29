#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>


class MyGL
: public GLWidget277 {
 private:
  QOpenGLVertexArrayObject vao;

  Cylinder geom_cylinder;//The instance of a unit cylinder we can use to render any cylinder
  Sphere geom_sphere;//The instance of a unit sphere we can use to render any sphere
  //TODO: Add a cube instance
  ShaderProgram prog_lambert;
  ShaderProgram prog_wire;

 public:
  explicit MyGL(QWidget *parent = 0);
  ~MyGL();

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

 protected:
  void keyPressEvent(QKeyEvent *e);
};


#endif // MYGL_H
