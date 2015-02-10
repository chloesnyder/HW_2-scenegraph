#include "pipe.h"
#include<la.h>
#include <iostream>

static const int PIPE_IDX_COUNT = 240;
static const int PIPE_VERT_COUNT = 80;

Pipe::Pipe()
  : bufIdx(QOpenGLBuffer::IndexBuffer),
    bufPos(QOpenGLBuffer::VertexBuffer),
    bufNor(QOpenGLBuffer::VertexBuffer),
    bufCol(QOpenGLBuffer::VertexBuffer) {
}

// These are functions that are only defined in this cpp file. They're used for organizational purposes
// when filling the arrays used to hold the vertex and index data.
void createPipeVertexPositions(vec4 (&pipe_vert_pos)[PIPE_VERT_COUNT]) {
  // Create two rings of vertices
  // We'll be using 20-sided polygons to approximate circles
  // for the endcaps

  // Store top cap verts (IDX 0 - 19)
//  for(int i = 0; i < 20; i++) {
//    vec4 v = mat4::rotate(i * 18.0f, 0, 1, 0) * vec4(0.5f, 0.5f, 0,1);
//    cone_vert_pos[i] = v;
//  }

//  // Store bottom cap verts (IDX 20 - 39)
//  for(int i = 20; i < 40; i++) {
//    vec4 v = mat4::rotate((i-20) * 18.0f, 0, 1, 0) * vec4(0.5f, -0.5f, 0,1);
//    cone_vert_pos[i] = v;
//  }

  // Create two more rings of vertices, this time for the barrel faces
  // We could use the same vertex rings as above, but GL only supports one normal per vertex
  // so we have to have two vertices per position in order to have sharp edges between the endcaps
  // and the barrel

  // Store top cap verts (IDX 40 - 59)
  for(int i = 0; i < 20; i++) {
    vec4 v = mat4::rotate(i * 18.0f, 0, 1, 0) * vec4(0.5f, 0.5f, 0,1);
    pipe_vert_pos[i + 40] = v;
  }

  // Store bottom cap verts (IDX 60 - 79)
  for(int i = 20; i < 40; i++) {
    vec4 v = mat4::rotate((i - 20) * 18.0f, 0, 1, 0) * vec4(0.5f, -0.5f, 0, 1);
    pipe_vert_pos[i + 40] = v;
  }
}


void createPipeVertexNormals(vec4 (&pipe_vert_nor)[PIPE_VERT_COUNT]){

  //Store top of barrel normals (IDX 40 - 59)
  for(int i = 0; i < 20; i++){
    vec4 v = mat4::rotate(i*18.0f, 0, 1, 0) * vec4(1,0,0,0);
    pipe_vert_nor[i + 40] = v;
  }
  //Store bottom of barrel normals (IDX 60 - 79)
  for(int i = 20; i < 40; i++){
    vec4 v = mat4::rotate((i-20)*18.0f, 0, 1, 0) * vec4(1,0,0,0);
    pipe_vert_nor[i + 40] = v;
  }
}


void createPipeIndices(GLuint (&pipe_idx)[PIPE_IDX_COUNT]){
  //Build indices for the top cap (18 tris, indices 0 - 53, up to vertex 19)
//  for(int i = 0; i < 18; i++){
//    cone_idx[i*3] = 0;
//    cone_idx[i*3 + 1] = i+1;
//    cone_idx[i*3 + 2] = i+2;
//  }
  //Build indices for the top cap (18 tris, indices 54 - 107, up to vertex 39)
  for(int i = 18; i < 36; i++){
    pipe_idx[i*3] = 20;
    pipe_idx[i*3 + 1] = i+3;
    pipe_idx[i*3 + 2] = i+4;
  }
  //Build indices for the barrel of the cylinder
  for(int i = 0; i < 19; i++){
    pipe_idx[108 + i*6] = i + 40;
    pipe_idx[109 + i*6] = i + 41;
    pipe_idx[110 + i*6] = i + 60;
    pipe_idx[111 + i*6] = i + 41;
    pipe_idx[112 + i*6] = i + 61;
    pipe_idx[113 + i*6] = i + 60;
  }
  //Build the last quad of the barrel, which has looping indices
  pipe_idx[234] = 59;
  pipe_idx[235] = 40;
  pipe_idx[236] = 79;
  pipe_idx[237] = 40;
  pipe_idx[238] = 60;
  pipe_idx[239] = 79;
}

void Pipe::create()
{
  GLuint pipe_idx[PIPE_IDX_COUNT];
  vec4 pipe_vert_pos[PIPE_VERT_COUNT];
  vec4 pipe_vert_nor[PIPE_VERT_COUNT];

  createPipeVertexPositions(pipe_vert_pos);
  createPipeVertexNormals(pipe_vert_nor);
  createPipeIndices(pipe_idx);

  count = PIPE_IDX_COUNT;

  bufIdx.create();
  bufIdx.bind();
  bufIdx.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufIdx.allocate(pipe_idx, PIPE_IDX_COUNT * sizeof(GLuint));

  bufPos.create();
  bufPos.bind();
  bufPos.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufPos.allocate(pipe_vert_pos,PIPE_VERT_COUNT * sizeof(vec4));

  bufNor.create();
  bufNor.bind();
  bufNor.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufNor.allocate(pipe_vert_nor, PIPE_VERT_COUNT * sizeof(vec4));
}

void Pipe::destroy()
{
  bufIdx.destroy();
  bufPos.destroy();
  bufNor.destroy();
  bufCol.destroy();
}

GLenum Pipe::drawMode()
{
  return GL_TRIANGLES;
}

int Pipe::elemCount()
{
  return count;
}

bool Pipe::bindIdx()
{
  return bufIdx.bind();
}

bool Pipe::bindPos()
{
  return bufPos.bind();
}

bool Pipe::bindNor()
{
  return bufNor.bind();
}

bool Pipe::bindCol()
{
  return bufCol.bind();
}

