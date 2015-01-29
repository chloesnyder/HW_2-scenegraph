#include "la.h"

QMatrix4x4 la::to_qmat(const mat4 &m) {
  float* val = new float[16];
  val[0] = m[0][0]; val[4] = m[0][1]; val[8] = m[0][2]; val[12] = m[0][3];
  val[1] = m[1][0]; val[5] = m[1][1]; val[9] = m[1][2]; val[13] = m[1][3];
  val[2] = m[2][0]; val[6] = m[2][1]; val[10] = m[2][2]; val[14] = m[2][3];
  val[3] = m[3][0]; val[7] = m[3][1]; val[11] = m[3][2]; val[15] = m[3][3];
  return QMatrix4x4(val); //May have to change this
}


QVector4D la::to_qvec(const vec4 &v) {
  return QVector4D(v[0], v[1], v[2], v[3]);
}


mat4 la::inverse(const mat4& m) {
  float detInv = determinant4x4(m);

  float a11 = m[0][0]; float a12 = m[0][1]; float a13 = m[0][2]; float a14 = m[0][3];
  float a21 = m[1][0]; float a22 = m[1][1]; float a23 = m[1][2]; float a24 = m[1][3];
  float a31 = m[2][0]; float a32 = m[2][1]; float a33 = m[2][2]; float a34 = m[2][3];
  float a41 = m[3][0]; float a42 = m[3][1]; float a43 = m[3][2]; float a44 = m[3][3];

  float b11 = a22*a33*a44 + a23*a34*a42 + a24*a32*a43
    - a22*a34*a43 - a23*a32*a44 - a24*a33*a42;

  float b12 = a12*a34*a43 + a13*a24*a44 + a14*a33*a44
    - a12*a33*a44 - a13*a34*a42 - a14*a32*a43;

  float b13 = a12*a23*a44 + a13*a24*a42 + a14*a22*a43
    - a12*a24*a43 - a13*a22*a44 - a14*a23*a42;

  float b14 = a12*a24*a33 + a13*a22*a34 + a14*a23*a32
    - a12*a23*a34 - a13*a24*a32 - a14*a22*a33;

  float b21 = a21*a34*a43 + a23*a31*a44 + a24*a33*a41
    - a21*a33*a44 - a23*a34*a41 - a24*a31*a43;

  float b22 = a11*a33*a44 + a13*a34*a41 + a14*a31*a43
    - a11*a34*a43 - a13*a31*a44 - a14*a33*a41;

  float b23 = a11*a24*a43 + a13*a21*a44 + a14*a23*a41
    - a11*a23*a44 - a13*a24*a41 - a14*a21*a43;

  float b24 = a11*a23*a34 + a13*a24*a31 + a14*a21*a33
    - a11*a24*a33 - a13*a21*a34 - a14*a23*a31;

  float b31 = a21*a32*a44 + a22*a34*a41 + a24*a31*a42
    - a21*a34*a42 - a22*a31*a44 - a24*a32*a41;

  float b32 = a11*a34*a42 + a12*a31*a44 + a14*a32*a41
    - a11*a32*a44 - a12*a34*a41 - a14*a31*a42;

  float b33 = a11*a22*a44 + a12*a24*a41 + a14*a21*a42
    - a11*a24*a42 - a12*a21*a44 - a14*a22*a41;

  float b34 = a11*a24*a32 + a12*a21*a34 + a14*a22*a31
    - a11*a22*a34 - a12*a24*a31 - a14*a21*a32;

  float b41 = a21*a33*a42 + a22*a31*a43 + a23*a32*a41
    - a21*a32*a43 - a22*a33*a41 - a23*a31*a42;

  float b42 = a11*a32*a43 + a12*a33*a41 + a13*a31*a42
    - a11*a33*a42 - a12*a31*a43 - a13*a32*a41;

  float b43 = a11*a23*a42 + a12*a21*a43 + a13*a22*a41
    - a11*a22*a43 - a12*a23*a41 - a13*a21*a42;

  float b44 = a11*a22*a33 + a12*a23*a31 + a13*a21*a32
    - a11*a23*a32 - a12*a21*a33 - a13*a22*a31;

  vec4 r1(b11, b12, b13, b14);
  vec4 r2(b21, b22, b23, b24);
  vec4 r3(b31, b32, b33, b34);
  vec4 r4(b41, b42, b43, b44);

  return detInv * mat4(r1, r2, r3, r4);
}

// Row major
float la::determinant2x2(const float(&m)[2][2]) {
  return m[0][0]*m[1][1] - m[0][1]*m[1][0];
}

// Row major
float la::determinant3x3(const float(&m)[3][3]) {
  float a1[2][2];
  a1[0][0] = m[1][1]; a1[0][1] = m[1][2];
  a1[1][0] = m[2][1]; a1[1][1] = m[2][2];

  float a2[2][2];
  a2[0][0] = m[1][0]; a2[0][1] = m[1][2];
  a2[1][0] = m[2][0]; a2[1][1] = m[2][2];

  float a3[2][2];
  a3[0][0] = m[1][0]; a3[0][1] = m[1][1];
  a3[1][0] = m[2][0]; a3[1][1] = m[2][1];

  return m[0][0]*determinant2x2(a1)
    + m[0][1]*determinant2x2(a2)
    + m[0][2]*determinant2x2(a3);
}

float la::determinant4x4(const mat4& m) {
  float a1[3][3];
  a1[0][0] = m[1][1]; a1[0][1] = m[1][2]; a1[0][2] = m[1][3];
  a1[1][0] = m[2][1]; a1[1][1] = m[2][2]; a1[1][2] = m[2][3];
  a1[2][0] = m[3][1]; a1[2][1] = m[3][2]; a1[2][2] = m[3][3];

  float a2[3][3];
  a2[0][0] = m[1][0]; a2[0][1] = m[1][2]; a2[0][2] = m[1][3];
  a2[1][0] = m[2][0]; a2[1][1] = m[2][2]; a2[1][2] = m[2][3];
  a2[2][0] = m[3][0]; a2[2][1] = m[3][2]; a2[2][2] = m[3][3];

  float a3[3][3];
  a3[0][0] = m[1][0]; a3[0][1] = m[1][1]; a3[0][2] = m[1][3];
  a3[1][0] = m[2][0]; a3[1][1] = m[2][1]; a3[1][2] = m[2][3];
  a3[2][0] = m[3][0]; a3[2][1] = m[3][1]; a3[2][2] = m[3][3];

  float a4[3][3];
  a4[0][0] = m[1][0]; a4[0][1] = m[1][1]; a4[0][2] = m[1][2];
  a4[1][0] = m[2][0]; a4[1][1] = m[2][1]; a4[1][2] = m[2][2];
  a4[2][0] = m[3][0]; a4[2][1] = m[3][1]; a4[2][2] = m[3][2];

  return m[0][0]*determinant3x3(a1)
    + m[0][1]*determinant3x3(a2)
    + m[0][2]*determinant3x3(a3)
    + m[0][3]*determinant3x3(a4);
}
