#pragma once

#include <shaderprogram.h>
#include "linear_algebra/vec4.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class Cone : public ShaderProgram::Drawable
{
 private:
  int count;
  QOpenGLBuffer bufIdx;
  QOpenGLBuffer bufPos;
  QOpenGLBuffer bufNor;
  QOpenGLBuffer bufCol; // Can be used to pass per-vertex color information to the shader, but is currently unused.

 public:
  Cone();

  void create();
  void destroy();

  virtual GLenum drawMode();
  virtual int elemCount();
  virtual bool bindIdx();
  virtual bool bindPos();
  virtual bool bindNor();
  virtual bool bindCol();
};
