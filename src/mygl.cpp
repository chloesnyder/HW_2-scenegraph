#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>


MyGL::MyGL(QWidget *parent)
  : GLWidget277(parent) {
}

MyGL::~MyGL() {
  makeCurrent();

  vao.destroy();
  geom_cylinder.destroy();
  geom_sphere.destroy();
}

void MyGL::initializeGL() {
  // Create an OpenGL context
  initializeOpenGLFunctions();

  // Print out some information about the current OpenGL context
  debugContextVersion();

  // Set a few settings/modes in OpenGL rendering
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

  // Set the size with which points should be rendered
  glPointSize(5);

  // Set the color with which the screen is filled at the start of each render call.
  glClearColor(0.5, 0.5, 0.5, 1);

  printGLErrorLog();

  // Create a Vertex Attribute Object
  vao.create();

  //Create the example sphere (you should delete this when you add your own code elsewhere)
  geom_cylinder.setColor(vec4(1,0,0,1));
  geom_cylinder.create();

  geom_sphere.setColor(vec4(0,1,0,1));
  geom_sphere.create();

  // Create and set up the diffuse shader
  prog_lambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");

  // Create and set up the wireframe shader
  prog_wire.create(":/glsl/wire.vert.glsl", ":/glsl/wire.frag.glsl");

  // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
  // using multiple VAOs, we can just bind one once.
  vao.bind();
}

void MyGL::resizeGL(int w, int h) {
  // vvv TODO REPLACE THIS CODE IN HW3
  vec4 r1(1.1933f, 0, 1.1933f, 0);
  vec4 r2(0.9856f, 1.9712f, -0.9856f, 0);
  vec4 r3(0.5785f, -0.5785f, -0.5785f, 11.9484f);
  vec4 r4(0.5774f, -0.5774f, -0.5774f, 12.1244f);
  mat4 viewproj(r1, r2, r3, r4);
  viewproj = transpose(viewproj);
  // ^^^ TODO REPLACE THIS CODE IN HW3

  // Upload the projection matrix
  QMatrix4x4 qviewproj = la::to_qmat(viewproj);

  prog_lambert.prog.bind();
  prog_lambert.prog.setUniformValue(prog_lambert.unifViewProj, qviewproj);

  prog_wire.prog.bind();
  prog_wire.prog.setUniformValue(prog_wire.unifViewProj, qviewproj);

  printGLErrorLog();
}

// This function is called by Qt any time your GL window is supposed to update
// For example, when the function updateGL is called, paintGL is called implicitly.
void MyGL::paintGL() {
  // Clear the screen so that we only see newly drawn images
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //VVV CLEAR THIS CODE WHEN YOU IMPLEMENT SCENE GRAPH TRAVERSAL VVV

  //Create a model matrix. This one scales the sphere uniformly by 3, then translates it by <-2,0,0>.
  //Note that we have to transpose the model matrix before passing it to the shader
  //This is because OpenGL expects column-major matrices, but you've
  //implemented row-major matrices.
  mat4 model = transpose(mat4::translate(-2,0,0) * mat4::scale(3,3,3));

  //Send the geometry's transformation matrix to the shader
  prog_lambert.setModelMatrix(model);

  //Set the color with which we want to draw the sphere (green in this case)
  geom_sphere.setColor(vec4(0,1,0,1));

  //Draw the example sphere using our lambert shader
  prog_lambert.draw(*this, geom_sphere);

  //Now do the same to render the cylinder
  //We've rotated it -45 degrees on the Z axis, then translated it to the point <2,2,0>
  model = transpose(mat4::translate(2,2,0) * mat4::rotate(-45,0,0,1));
  prog_lambert.setModelMatrix(model);
  geom_cylinder.setColor(vec4(1,0,0,1));//Set its color to red
  prog_lambert.draw(*this, geom_cylinder);

  //^^^ CLEAR THIS CODE WHEN YOU IMPLEMENT SCENE GRAPH TRAVERSAL ^^^

  //Here is a good spot to call your scene graph traversal function.
}

void MyGL::keyPressEvent(QKeyEvent *e) {
  // http://doc.qt.io/qt-5/qt.html#Key-enum
  if (e->key() == Qt::Key_Escape) {
    QApplication::quit();
  }
}
