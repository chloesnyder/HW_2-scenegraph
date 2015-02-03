#include "cube.h"
#include<la.h>
#include <iostream>

static const int CUBE_IDX_COUNT = 72;
static const int CUBE_VERT_COUNT = 24;

Cube::Cube()
  : bufIdx(QOpenGLBuffer::IndexBuffer),
    bufPos(QOpenGLBuffer::VertexBuffer),
    bufNor(QOpenGLBuffer::VertexBuffer),
    bufCol(QOpenGLBuffer::VertexBuffer) {
}


// These are functions that are only defined in this cpp file. They're used for organizational purposes
// when filling the arrays used to hold the vertex and index data.
void createCubeVertexPositions(vec4 (&cube_vert_pos)[CUBE_VERT_COUNT]) {
    //6 faces
    //4 sided shapes

    //RightSquare (IDX 0-3)
    vec4 v00 = vec4(0, 0, 0, 1);
    vec4 v01 = vec4(0, 1, 0, 1);
    vec4 v02 = vec4(1, 1, 0, 1);
    vec4 v03 = vec4(1, 0, 0, 1);
    cube_vert_pos[0] = v00;
    cube_vert_pos[1] = v01;
    cube_vert_pos[2] = v02;
    cube_vert_pos[3] = v03;

    //Front Square (IDX 4-7)
    vec4 v10 = vec4(0, 0, 0, 1) * mat4::rotate(90, 0, 1, 0);
    vec4 v11 = vec4(0, 1, 0, 1) * mat4::rotate(90, 0, 1, 0);
    vec4 v12 = vec4(1, 1, 0, 1) * mat4::rotate(90, 0, 1, 0);
    vec4 v13 = vec4(1, 0, 0, 1) * mat4::rotate(90, 0, 1, 0);
    cube_vert_pos[4] = v10;
    cube_vert_pos[5] = v11;
    cube_vert_pos[6] = v12;
    cube_vert_pos[7] = v13;

    //Back Square (IDX 8-11)
   vec4 v20 = vec4(0, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::translate(1, 0, 0);
   vec4 v21 = vec4(0, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::translate(1, 0, 0);
   vec4 v22 = vec4(1, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::translate(1, 0, 0);
   vec4 v23 = vec4(1, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::translate(1, 0, 0);
   cube_vert_pos[8] = v20;
   cube_vert_pos[9] = v21;
   cube_vert_pos[10] = v22;
   cube_vert_pos[11] = v23;

   //Bottom Square (IDX 12-15)
   vec4 v30 = vec4(0, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1);
   vec4 v31 = vec4(0, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1);
   vec4 v32 = vec4(1, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1);
   vec4 v33 = vec4(1, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1);
   cube_vert_pos[12] = v30;
   cube_vert_pos[13] = v31;
   cube_vert_pos[14] = v32;
   cube_vert_pos[15] = v33;

   //Top Square (IDX 16-19)
   vec4 v40 = vec4(0, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1) * mat4::translate(0,1,0);
   vec4 v41 = vec4(0, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1) * mat4::translate(0,1,0);
   vec4 v42 = vec4(1, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1) * mat4::translate(0,1,0);
   vec4 v43 = vec4(1, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1) * mat4::translate(0,1,0);
    cube_vert_pos[16] = v40;
   cube_vert_pos[17] = v41;
   cube_vert_pos[18] = v42;
   cube_vert_pos[19] = v43;

   //Left Square (IDX 20-23)
//   vec4 v50 = vec4(-1, 0, 0, 1);
//   vec4 v51 = vec4(-1, 1, 0, 1);
//   vec4 v52 = vec4(0, 1, 0, 1);
//   vec4 v53 = vec4(0, 0, 0, 1);

//   vec4 v00 = vec4(0, 0, 0, 1);
//   vec4 v01 = vec4(0, 1, 0, 1);
//   vec4 v02 = vec4(1, 1, 0, 1);
//   vec4 v03 = vec4(1, 0, 0, 1);
//   cube_vert_pos[20] = v50;
//   cube_vert_pos[21] = v51;
//   cube_vert_pos[22] = v52;
//   cube_vert_pos[23] = v53;



}


void createCubeVertexNormals(vec4 (&cube_vert_nor)[CUBE_VERT_COUNT]){
    //Right Square (IDX 0-3)
    vec4 v00 = vec4(0, 0, 0, 1);
    vec4 v01 = vec4(0, 1, 0, 1);
    vec4 v02 = vec4(1, 1, 0, 1);
    vec4 v03 = vec4(1, 0, 0, 1);
    cube_vert_nor[0] = v00;
    cube_vert_nor[1] = v01;
    cube_vert_nor[2] = v02;
    cube_vert_nor[3] = v03;

    //Front Square (IDX 4-7)
    vec4 v10 = vec4(0, 0, 0, 1) * mat4::rotate(90, 0, 1, 0);
    vec4 v11 = vec4(0, 1, 0, 1) * mat4::rotate(90, 0, 1, 0);
    vec4 v12 = vec4(1, 1, 0, 1) * mat4::rotate(90, 0, 1, 0);
    vec4 v13 = vec4(1, 0, 0, 1) * mat4::rotate(90, 0, 1, 0);
    cube_vert_nor[4] = v10;
    cube_vert_nor[5] = v11;
    cube_vert_nor[6] = v12;
    cube_vert_nor[7] = v13;

   //Back Square (IDX 8-11)
   vec4 v20 = vec4(0, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::translate(1, 0, 0);
   vec4 v21 = vec4(0, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::translate(1, 0, 0);
   vec4 v22 = vec4(1, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::translate(1, 0, 0);
   vec4 v23 = vec4(1, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::translate(1, 0, 0);
   cube_vert_nor[8] = v20;
   cube_vert_nor[9] = v21;
   cube_vert_nor[10] = v22;
   cube_vert_nor[11] = v23;

   //Bottom Square (IDX 12-15)
   vec4 v30 = vec4(0, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1);
   vec4 v31 = vec4(0, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1);
   vec4 v32 = vec4(1, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1);
   vec4 v33 = vec4(1, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1);
   cube_vert_nor[12] = v30;
   cube_vert_nor[13] = v31;
   cube_vert_nor[14] = v32;
   cube_vert_nor[15] = v33;

   //Top Square (IDX 16-19)
   vec4 v40 = vec4(0, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1) * mat4::translate(0,1,0);
   vec4 v41 = vec4(0, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1) * mat4::translate(0,1,0);
   vec4 v42 = vec4(1, 1, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1) * mat4::translate(0,1,0);
   vec4 v43 = vec4(1, 0, 0, 1) * mat4::rotate(90, 0, 1, 0) * mat4::rotate(-90, 0, 0, 1) * mat4::translate(0,1,0);
   cube_vert_nor[16] = v40;
   cube_vert_nor[17] = v41;
   cube_vert_nor[18] = v42;
   cube_vert_nor[19] = v43;


//   vec4 v50 = vec4(-1, 0, 0, 1);
//   vec4 v51 = vec4(-1, 1, 0, 1);
//   vec4 v52 = vec4(0, 1, 0, 1);
//   vec4 v53 = vec4(0, 0, 0, 1);
//   cube_vert_nor[20] = v50;
//   cube_vert_nor[21] = v51;
//   cube_vert_nor[22] = v52;
//   cube_vert_nor[23] = v53;

}


void createCubeIndices(GLuint (&cube_idx)[CUBE_IDX_COUNT]){
    for(int i = 0; i < 24; i++) {
        cube_idx[i*3] = 0;
        cube_idx[i*3 + 1] = i+1;
        cube_idx[i*3 + 2] = i+2;
    }

//    for(int i = 4; i < 8; i++) {
//        cube_idx[i*3] = 8;
//        cube_idx[i*3 + 1] = i+3;
//        cube_idx[i*3 + 2] = i+4;
//    }

//    for(int i = 8; i < 12; i++) {
//        cube_idx[i*3] = 20;
//        cube_idx[i*3 + 1] = i+3;
//        cube_idx[i*3 + 2] = i+4;
//    }

//    for(int i = 12; i < 16; i++) {
//        cube_idx[i*3] = 20;
//        cube_idx[i*3 + 1] = i+3;
//        cube_idx[i*3 + 2] = i+4;
//    }

//    for(int i = 16; i < 20; i++) {
//        cube_idx[i*3] = 20;
//        cube_idx[i*3 + 1] = i+3;
//        cube_idx[i*3 + 2] = i+4;
//    }

//    for(int i = 20; i < 24; i++) {
//        cube_idx[i*3] = 20;
//        cube_idx[i*3 + 1] = i+3;
//        cube_idx[i*3 + 2] = i+4;
//    }

}

void Cube::create()
{
  GLuint cube_idx[CUBE_IDX_COUNT];
  vec4 cube_vert_pos[CUBE_VERT_COUNT];
  vec4 cube_vert_nor[CUBE_VERT_COUNT];

  createCubeVertexPositions(cube_vert_pos);
  createCubeVertexNormals(cube_vert_nor);
  createCubeIndices(cube_idx);

  count = CUBE_IDX_COUNT;

  bufIdx.create();
  bufIdx.bind();
  bufIdx.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufIdx.allocate(cube_idx, CUBE_IDX_COUNT * sizeof(GLuint));

  bufPos.create();
  bufPos.bind();
  bufPos.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufPos.allocate(cube_vert_pos,CUBE_VERT_COUNT * sizeof(vec4));

  bufNor.create();
  bufNor.bind();
  bufNor.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufNor.allocate(cube_vert_nor, CUBE_VERT_COUNT * sizeof(vec4));
}

void Cube::destroy()
{
  bufIdx.destroy();
  bufPos.destroy();
  bufNor.destroy();
  bufCol.destroy();
}

GLenum Cube::drawMode()
{
  return GL_TRIANGLES;
}

int Cube::elemCount()
{
  return count;
}

bool Cube::bindIdx()
{
  return bufIdx.bind();
}

bool Cube::bindPos()
{
  return bufPos.bind();
}

bool Cube::bindNor()
{
  return bufNor.bind();
}

bool Cube::bindCol()
{
  return bufCol.bind();
}
