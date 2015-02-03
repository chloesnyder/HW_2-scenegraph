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
  geom_cube.destroy();
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
  geom_sphere.setColor(vec4(1,0,0,1));
  geom_sphere.create();

  geom_sphere.setColor(vec4(0,1,0,1));
  geom_sphere.create();

  geom_cube.setColor(vec4(0,0,1,1));
  geom_cube.create();

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
#if 0
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
 // prog_lambert.draw(*this, geom_sphere);

  //Draw the example cube using our lambert shader
  prog_lambert.draw(*this, geom_cube);
  //Now do the same to render the cylinder
  //We've rotated it -45 degrees on the Z axis, then translated it to the point <2,2,0>
  model = transpose(mat4::translate(2,2,0) * mat4::rotate(-45,0,0,1));
  prog_lambert.setModelMatrix(model);
  geom_cylinder.setColor(vec4(1,0,0,1));//Set its color to red
  prog_lambert.draw(*this, geom_cylinder);

  //^^^ CLEAR THIS CODE WHEN YOU IMPLEMENT SCENE GRAPH TRAVERSAL ^^^
#endif
mat4 ident = mat4::identity();
node* cube = new node(&geom_cube, 0, 3, 0, 0, 0, 0, 1,1,1);
node* cube2 = new node(&geom_cube, 0, 0, 0, 0, 0, 0, 1,1,1);
traverse(cube, ident);
traverse(cube2, ident);


  //Here is a good spot to call your scene graph traversal function.
//node* b = new node(&geom_sphere, 0.f, 0.f, 4.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f);
//node* c = new node(&geom_sphere, -2.f, 0.f, -1.f, 0.f, 90.f, 0.f, 1.f, 1.f, 1.f);
//node* d = new node(&geom_cylinder, 0.f, -1.f, -1.f, -90.f, 0.f, 180.f, 1.f, 1.f, 1.f);
//node* a = new node(b, &geom_cylinder, 1.f, 4.f, 0.f, 90.f, 0.f, 0.f, 2.f, 2.f, 2.f);
//b->setChild(c);
//b->setParent(d);
//mat4 ident = mat4::identity();
//traverse(d, ident);
//node* h = new node(&geom_sphere);
//traverse(h, ident);

  ///-------------------------
  /// SCENE GRAPH CODE
  /// -------------------------
    //mat4 ident = mat4::identity();
  //everything originates from here, so this will be the overall root node
//  node* torso = new node(&geom_cylinder, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 3.f, 1.f);
//  node* unscale_head = new node(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f, -3.f, -1.f);
//  //child of torso, only torso
  //node* head = new node(torso, &geom_sphere, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 2.f, 2.f, 2.f);
 // head->setParent(unscale_head);
  //torso->setChild(unscale_head);
 // traverse(torso, ident);
//  //upper right arm, parent of lower arm
//  node* UR_Arm = new node(&geom_cylinder, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 2.f, 2.f, 2.f);
//  node* LR_Arm;
//  //upper left arm, parent of lower arm
//  node* LR_Arm;
//  node* LL_Arm;
}

///My traverse function. Traverses from root to all children, applying transformation matrices
void MyGL::traverse(node* &n, mat4 &transf) {
      mat4 t = transf * n->getTransform();
      vector<node*> children = n->getChildren();
      if(!children.empty()) {
          for(node* child : children) {
              traverse(child, t);
          }
      }
      if(n->getGeometry() != NULL) {
          prog_lambert.setModelMatrix(transpose(t));
          prog_lambert.draw(*this, *(n->getGeometry()));
      }
}

void MyGL::keyPressEvent(QKeyEvent *e) {
  // http://doc.qt.io/qt-5/qt.html#Key-enum
  if (e->key() == Qt::Key_Escape) {
    QApplication::quit();
  }
}
