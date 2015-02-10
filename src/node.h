#ifndef NODE
#define NODE
#include <vector>
#include <iostream>
#include "linear_algebra/mat4.h"
#include "shaderprogram.h"

///NODE contains:
///A pointer to the node's parent.
///A set of pointers to the node's children. We recommend using STL vectors to store the pointers, since they are in essence dynamically resizeable arrays.
///A pointer to one instance of geometry.
///A floating point value to represent each of the following (nine floats in total):
///Translation on the X, Y, and Z axes
///Rotation on the X, Y, and Z axes
///Scale on the X, Y, and Z axes

using namespace std;

class node {
 private:
    node* parent;
    vector<node*> children;
    ShaderProgram::Drawable* geometry;
    mat4 trans; //translation matrix

 public:

    ///----------------------------------------------------------------------
    /// Constructors
    ///----------------------------------------------------------------------

    //all info known
    node(node* parent, vector<node*> children, ShaderProgram::Drawable* geometry,
         float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);
    //don't know parent and children
    node(ShaderProgram::Drawable* geometry,
         float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);
    //don't know parent
    node(vector<node*> children, ShaderProgram::Drawable* geometry,
         float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);
    //don't know chidlren
    node(node* parent, ShaderProgram::Drawable* geometry,
         float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);
    //don't know parent, children, geometry
    node(float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);
    //don't know parent, geometry
    node(vector<node*> children, float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);
    //don't know children, geometry
    node(node* parent, float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);
    //only know geometry
    node(ShaderProgram::Drawable* geometry);
    //only know parent
    node(node* parent);
    //only know children
    node(vector<node*> children);
    //know parent and geo
    node(node* parent, ShaderProgram::Drawable* geometry);
    //know children and geo
    node(vector<node*> children, ShaderProgram::Drawable* geometry);
    //don't know anything
    node();
    node(const node &n); // copy constructor
    ~node();

    ///----------------------------------------------------------------------
    /// Getters/Setters
    ///----------------------------------------------------------------------

    float t(unsigned int i, unsigned int j);
    node* getParent();
    vector<node*> getChildren();
    ShaderProgram::Drawable* getGeometry();
    float getRX();
    float getRY();
    float getRZ();
    float getTX();
    float getTY();
    float getTZ();
    float getSX();
    float getSY();
    float getSZ();

    void setChild(node* &n);
    void setChildren(vector<node*> children);
    void setParent(node* &n);
    void setGeometry(ShaderProgram::Drawable* &g);
    void setRX(float rx);
    void setRY(float ry);
    void setRZ(float rz);
    void setTX(float tx);
    void setTY(float ty);
    void setTZ(float tz);
    void setSX(float sx);
    void setSY(float sy);
    void setSZ(float sz);
    void rotateAroundNewPoint(float px, float py, float pz);
    mat4 getTransform();

};
#endif // NODE

