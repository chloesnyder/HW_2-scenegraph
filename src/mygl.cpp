#include "mygl.h"
#include <la.h>
#include <cstdlib>
#include <iostream>
#include <QApplication>
#include <QKeyEvent>

float t = 1;
float turn = 0;

MyGL::MyGL(QWidget *parent)
  : GLWidget277(parent) {
}

MyGL::~MyGL() {
  makeCurrent();

  vao.destroy();
  geom_cylinder.destroy();
  geom_sphere.destroy();
  geom_cube.destroy();
  geom_pipe.destroy();
  //geom_cone.destroy();
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

  geom_cylinder.setColor(vec4(0,1,0,1));
  geom_cylinder.create();

  geom_cube.setColor(vec4(0,0,1,1));
  geom_cube.create();

  geom_cone.setColor(vec4(0,1,1,1));
  geom_cone.create();

  geom_pipe.setColor(vec4(0,1,1,1));
  geom_pipe.create();

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
    float direction = 1;
    float r1 = rand();
    //animates
    if (t < 120 && t > 0) {
        t += 1; //using this on the arm to only move to a certain point, thesn stop
    }

    if(turn <= 360 && turn >= 0) {
        turn += .05;
    } else {
        turn = 0;
    }
  // Clear the screen so that we only see newly drawn images
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



  //Fun Times
  prog_lambert.prog.bind();
  prog_lambert.prog.setUniformValue(prog_lambert.unifTime, time);

  sceneGraph(t, turn);
 // cloud()


}

void MyGL::sceneGraph(float angle, float translate) {
    mat4 ident = mat4::identity();
    //TORSO CODE
    node* torso = new node(&geom_cube, 1, 2 * sin(translate), 1, 5* cos(translate), 0.f, 3* sin(translate), 1.f, 2.f, 1.25f);

    //HEAD CODE
    node* unscale_head = new node(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, .5f, .8f);
    node* head = new node(&geom_sphere, 0.f, 1.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f);
    head->setParent(unscale_head);
    torso->setChild(unscale_head);

    //LEFT LEG CODE
    node* left_hip = new node(0, -1.25, -.4, 0, 0, -90, 1, 1, 1); //places leg in right place and rotates it
    node* left_leg_upper = new node(&geom_cylinder, 0, -0.5, 0, 0, 0, 0, .5, 1.25,.5); //creates limb, scales and moves pivot point
    node* unscale_left_leg_upper = new node(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, .5, .8f); //undoes scale from the torso

    node* left_knee = new node(0, -.75, 0, 0, 0, 30, 1, 1, 1); //places lower leg in right spot and rotates it
    node* left_leg_lower = new node(&geom_cylinder, 0, -.5, 0, 0, 0, 0, .5, 1.25, .5); //creates limb, scales and moves pivot point
    node* unscale_left_leg_lower = new node(0, 0, 0, 0, 0, 0, 2, .8, 2); //undoes scale from upper leg

    unscale_left_leg_upper->setChild(left_hip);
    left_leg_upper->setParent(left_hip);

    unscale_left_leg_lower->setChild(left_knee);
    left_leg_lower->setParent(left_knee);

    left_leg_upper->setChild(unscale_left_leg_lower);
    torso->setChild(unscale_left_leg_upper);


    //RIGHT LEG CODE
    node* right_hip = new node(0, -1.25, .4, 0, 0, 70, 1, 1, 1); //places leg in right place and rotates it
    node* right_leg_upper = new node(&geom_cylinder, 0, -0.5, 0, 0, 0, 0, .5, 1.25,.5); //creates limb, scales and moves pivot point
    node* unscale_right_leg_upper = new node(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, .5, .8f); //undoes scale from the torso

    node* right_knee = new node(0, -.75, 0, 0, 0, 45, 1, 1, 1); //places lower leg in right spot and rotates it
    node* right_leg_lower = new node(&geom_cylinder, 0, -.5, 0, 0, 0, 0, .5, 1.25, .5); //creates limb, scales and moves pivot point
    node* unscale_right_leg_lower = new node(0, 0, 0, 0, 0, 0, 2, .8, 2); //undoes scale from upper arm

    unscale_right_leg_upper->setChild(right_hip);
    right_leg_upper->setParent(right_hip);

    unscale_right_leg_lower->setChild(right_knee);
    right_leg_lower->setParent(right_knee);

    right_leg_upper->setChild(unscale_right_leg_lower);
    torso->setChild(unscale_right_leg_upper);


    //RIGHT ARM CODE
    node* right_shoulder = new node(0, .5, 1, angle, 0, 0, 1, 1, 1); //places arm in right place and rotates it
    node* right_arm_upper = new node(&geom_cylinder, 0, .5, 0, 0, 0, 0, .5, 1.25,.5); //creates limb, scales and moves pivot point
    node* unscale_right_arm_upper = new node(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, .5, .8f); //undoes scale from the torso

    node* right_elbow = new node(0, .75, 0, 0, 0, angle * .5, 1, 1, 1); //places lower arm in right spot and rotates it
    node* right_arm_lower = new node(&geom_cylinder, 0, .5, 0, 0, 0, 0, .5, 1.25, .5); //creates limb, scales and moves pivot point
    node* unscale_right_arm_lower = new node(0, 0, 0, 0, 0, 0, 2, .8, 2); //undoes scale from upper arm

    unscale_right_arm_upper->setChild(right_shoulder);
    right_arm_upper->setParent(right_shoulder);

    unscale_right_arm_lower->setChild(right_elbow);
    right_arm_lower->setParent(right_elbow);

    right_arm_upper->setChild(unscale_right_arm_lower);
    torso->setChild(unscale_right_arm_upper);

    //LEFT ARM CODE
    node* left_shoulder = new node(0, .5, 1, 160, -30, -80, 1, 1, 1); //places arm in right place and rotates it
    node* left_arm_upper = new node(&geom_cylinder, 0, .5, 0, 0, 0, 0, .5, 1.25,.5); //creates limb, scales and moves pivot point
    node* unscale_left_arm_upper = new node(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f, .5, -.8f); //undoes scale from the torso

    node* left_elbow = new node(0, .75, 0, 0, 0, 0, 1, 1, 1); //places lower arm in right spot and rotates it
    node* left_arm_lower = new node(&geom_cylinder, 0, .5, 0, 0, 0, 0, .5, 1.25, .5); //creates limb, scales and moves pivot point
    node* unscale_left_arm_lower = new node(0, 0, 0, 0, 0, 0, 2, .8, 2); //undoes scale from upper arm

    unscale_left_arm_upper->setChild(left_shoulder);
    left_arm_upper->setParent(left_shoulder);

    unscale_left_arm_lower->setChild(left_elbow);
    left_arm_lower->setParent(left_elbow);

    left_arm_upper->setChild(unscale_left_arm_lower);
    torso->setChild(unscale_left_arm_upper);

    //WIZARD HAT!!!
    node* wizard_hat_brim = new node(&geom_cylinder, 0, .5, 0, 0, 0, 0, 2, .1, 2);
    node* place_wizard_hat_brim = new node(0, .5, 0, 0, 0, 0, 1, 1, 1);
    node* wizard_hat_point = new node(&geom_cone, 0, .5, 0, 0, 0, 0, .5, 6, .5);
    node* place_wizard_hat_point = new node(0, 2.5, 0, 0, 0, 0, 1, 1, 1);

    wizard_hat_point->setParent(place_wizard_hat_point);
    wizard_hat_brim->setChild(place_wizard_hat_point);
    wizard_hat_brim->setParent(place_wizard_hat_brim);
    torso->setChild(place_wizard_hat_brim);

    //Wand
    node* wand = new node(&geom_pipe, 0, .5, 0, 0, 0, 0, .1, 2, .1);
    node* place_wand = new node(-.25, .6, .5, 0, 0, 45, 1, 1, 1);
    right_arm_lower->setChild(place_wand);
    wand->setParent(place_wand);

    //Broom
    node* unscale_stick = new node(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, .5f, .8f);
    node* stick = new node(&geom_cylinder, 0, .5, 0, 0, 0, -40, .3, 7, .3);
    node* place_stick = new node(0, -1.25, 0, 0, 0, 90, 1, 1, 1);
    node* straw = new node(&geom_cone, 0, .5, 0, 0, 0, 0, 6, .5, 6);
    node* place_straw = new node(0, -1.5, .5, 3*cos(translate)*cos(translate), 3*sin(translate)*sin(translate), 0, 1, 1.5, .5);
    straw->setParent(place_straw);
    place_straw->setParent(stick);
    stick->setParent(place_stick);
    place_stick->setParent(unscale_stick);
    unscale_stick->setParent(torso);


    traverse(torso, ident);
}



///Traverses from root to all children, applying transformation matrices
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
