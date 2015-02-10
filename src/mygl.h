#ifndef MYGL_H
#define MYGL_H

#include "node.h"
#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>
#include <scene/cube.h>
#include <scene/cone.h>
#include <scene/pipe.h>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>


class MyGL
: public GLWidget277 {
 private:
  QOpenGLVertexArrayObject vao;

  Cylinder geom_cylinder;//The instance of a unit cylinder we can use to render any cylinder
  Sphere geom_sphere;//The instance of a unit sphere we can use to render any sphere
  Cube geom_cube;//The instance of a unit cube we can use to render any cube
  Cone geom_cone; //the instance of a unit cone
  Pipe geom_pipe; //instance of a unit pipe
  ShaderProgram prog_lambert;
  ShaderProgram prog_wire;

 public:
  explicit MyGL(QWidget *parent = 0);
  ~MyGL();

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  //my traverse function
  void traverse(node* &n, mat4 &transf);
  void sceneGraph(float angle, float translate);
  void cloud(float r1, float r2, float r3, float r4, float px, float py, float pz);

 protected:
  void keyPressEvent(QKeyEvent *e);
};


#endif // MYGL_H
