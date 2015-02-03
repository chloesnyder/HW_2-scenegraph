#include "node.h"
#include <assert.h>


////node constructor
node::node(node* parent, vector<node*> children, ShaderProgram::Drawable* geometry,
     float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz) {
    this->setParent(parent);
    this->setChildren(children);
    this->geometry = geometry;
    this->trans[0][0] = tx;
    this->trans[0][1] = ty;
    this->trans[0][2] = tz;
    this->trans[1][0] = rx;
    this->trans[1][1] = ry;
    this->trans[1][2] = rz;
    this->trans[2][0] = sx;
    this->trans[2][1] = sy;
    this->trans[2][2] = sz;

}

//don't know parent and children
node::node(ShaderProgram::Drawable* geometry,
     float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz) {
    this->geometry = geometry;
    this->trans[0][0] = tx;
    this->trans[0][1] = ty;
    this->trans[0][2] = tz;
    this->trans[1][0] = rx;
    this->trans[1][1] = ry;
    this->trans[1][2] = rz;
    this->trans[2][0] = sx;
    this->trans[2][1] = sy;
    this->trans[2][2] = sz;
}

//don't know parent
node::node(vector<node*> children, ShaderProgram::Drawable* geometry,
     float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz) {
    this->setChildren(children);
    this->geometry = geometry;
    this->trans[0][0] = tx;
    this->trans[0][1] = ty;
    this->trans[0][2] = tz;
    this->trans[1][0] = rx;
    this->trans[1][1] = ry;
    this->trans[1][2] = rz;
    this->trans[2][0] = sx;
    this->trans[2][1] = sy;
    this->trans[2][2] = sz;
}

//don't know chidlren
node::node(node* parent, ShaderProgram::Drawable* geometry,
     float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz){
    this->setParent(parent);
    this->geometry = geometry;
    this->trans[0][0] = tx;
    this->trans[0][1] = ty;
    this->trans[0][2] = tz;
    this->trans[1][0] = rx;
    this->trans[1][1] = ry;
    this->trans[1][2] = rz;
    this->trans[2][0] = sx;
    this->trans[2][1] = sy;
    this->trans[2][2] = sz;
}

//don't know parent, children, geometry
node::node(float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz){
    this->trans[0][0] = tx;
    this->trans[0][1] = ty;
    this->trans[0][2] = tz;
    this->trans[1][0] = rx;
    this->trans[1][1] = ry;
    this->trans[1][2] = rz;
    this->trans[2][0] = sx;
    this->trans[2][1] = sy;
    this->trans[2][2] = sz;
}

//don't know parent, geometry
node::node(vector<node*> children, float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz){
    this->setChildren(children);
    this->trans[0][0] = tx;
    this->trans[0][1] = ty;
    this->trans[0][2] = tz;
    this->trans[1][0] = rx;
    this->trans[1][1] = ry;
    this->trans[1][2] = rz;
    this->trans[2][0] = sx;
    this->trans[2][1] = sy;
    this->trans[2][2] = sz;
}

//don't know children, geometry
node::node(node* parent, float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz){
    this->setParent(parent);
    this->trans[0][0] = tx;
    this->trans[0][1] = ty;
    this->trans[0][2] = tz;
    this->trans[1][0] = rx;
    this->trans[1][1] = ry;
    this->trans[1][2] = rz;
    this->trans[2][0] = sx;
    this->trans[2][1] = sy;
    this->trans[2][2] = sz;
}

//only know geometry
node::node(ShaderProgram::Drawable* geometry) {
    this->geometry = geometry;
    this->trans[0][0] = 0;
    this->trans[0][1] = 0;
    this->trans[0][2] = 0;
    this->trans[1][0] = 0;
    this->trans[1][1] = 0;
    this->trans[1][2] = 0;
    this->trans[2][0] = 1;
    this->trans[2][1] = 1;
    this->trans[2][2] = 1;
}

//only know parent
node::node(node* parent){
    this->setParent(parent);
    this->trans[0][0] = 0;
    this->trans[0][1] = 0;
    this->trans[0][2] = 0;
    this->trans[1][0] = 0;
    this->trans[1][1] = 0;
    this->trans[1][2] = 0;
    this->trans[2][0] = 1;
    this->trans[2][1] = 1;
    this->trans[2][2] = 1;
}

//only know children
node::node(vector<node*> children){
     this->setChildren(children);
    this->trans[0][0] = 0;
    this->trans[0][1] = 0;
    this->trans[0][2] = 0;
    this->trans[1][0] = 0;
    this->trans[1][1] = 0;
    this->trans[1][2] = 0;
    this->trans[2][0] = 1;
    this->trans[2][1] = 1;
    this->trans[2][2] = 1;
}

//know parent and geo
node::node(node* parent, ShaderProgram::Drawable* geometry){
    this->geometry = geometry;
    this->setParent(parent);
    this->trans[0][0] = 0;
    this->trans[0][1] = 0;
    this->trans[0][2] = 0;
    this->trans[1][0] = 0;
    this->trans[1][1] = 0;
    this->trans[1][2] = 0;
    this->trans[2][0] = 1;
    this->trans[2][1] = 1;
    this->trans[2][2] = 1;
}

//know children and geo
node::node(vector<node*> children, ShaderProgram::Drawable* geometry){
    this->geometry = geometry;
    this->setChildren(children);
    this->trans[0][0] = 0;
    this->trans[0][1] = 0;
    this->trans[0][2] = 0;
    this->trans[1][0] = 0;
    this->trans[1][1] = 0;
    this->trans[1][2] = 0;
    this->trans[2][0] = 1;
    this->trans[2][1] = 1;
    this->trans[2][2] = 1;
}

//don't know anything
node::node(){
    this->trans[0][0] = 0;
    this->trans[0][1] = 0;
    this->trans[0][2] = 0;
    this->trans[1][0] = 0;
    this->trans[1][1] = 0;
    this->trans[1][2] = 0;
    this->trans[2][0] = 1;
    this->trans[2][1] = 1;
    this->trans[2][2] = 1;
}

////copy constructor
node::node(const node &n2) {
    *this = n2;
}

///destructor
node::~node(){
    //TODO: how to delete geometry?
    delete geometry;
    children.erase(children.begin(), children.end());
}

///----------------------------------------------------------------------
/// Getters/Setters
///----------------------------------------------------------------------

///gets information about transformations from node
///column 0 = x, 1 = y, 2 = z
/// row 0 = translate, row 1 = rotate angles, row 2 = scale
float node::t(unsigned int i, unsigned int j) {
    assert(i >=0 && i < 4 && j >=0 && j < 4);
    return trans[i][j];
}

node* node::getParent(){
    return parent;
}

vector<node*> node::getChildren(){
    return children;
}

ShaderProgram::Drawable* node::getGeometry(){
    return geometry;
}

float node::getRX(){
    return trans[1][0];
}
float node::getRY(){
    return trans[1][1];
}
float node::getRZ(){
    return trans[1][2];
}
float node::getTX(){
    return trans[0][0];
}
float node::getTY(){
    return trans[0][1];
}
float node::getTZ(){
    return trans[0][2];
}
float node::getSX(){
    return trans[2][0];
}
float node::getSY(){
    return trans[2][1];
}
float node::getSZ(){
    return trans[2][2];
}

void node::setChild(node* &n){
    this->children.push_back(n); //add n to this's children
    n->parent = this; //make this the parent of n
}

void node::setChildren(vector<node*> children) {
    for(node* child : children) {
        this->setChild(child);
    }
}

void node::setParent(node* &n){
    this->parent = n; //set the parent to n
    n->children.push_back(this); //add this to n's children
}

void node::setGeometry(ShaderProgram::Drawable* &g) {
    this->geometry = g;
}

void node::setRX(float &rx){
    this->trans[1][0] = rx;
}
void node::setRY(float &ry){
    this->trans[1][1] = ry;
}
void node::setRZ(float &rz){
    this->trans[1][2] = rz;
}
void node::setTX(float &tx){
    this->trans[0][0] = tx;
}
void node::setTY(float &ty){
    this->trans[0][1] = ty;
}
void node::setTZ(float &tz){
    this->trans[0][2] = tz;
}
void node::setSX(float &sx){
    this->trans[2][0] = sx;
}
void node::setSY(float &sy){
    this->trans[2][1] = sy;
}
void node::setSZ(float &sz){
    this->trans[2][2] = sz;
}

//returns the transformation matrix
mat4 node::getTransform() {
    mat4 translate = mat4::translate(this->trans[0][0], this->trans[0][1], this->trans[0][2]);
    mat4 rotate_x = mat4::rotate(this->trans[1][0], 1, 0, 0);
    mat4 rotate_y = mat4::rotate(this->trans[1][1], 0, 1, 0);
    mat4 rotate_z = mat4::rotate(this->trans[1][2], 0, 0, 1);
    mat4 scale = mat4::scale(this->trans[2][0], this->trans[2][1], this->trans[2][2]);

    return translate * rotate_x * rotate_y * rotate_z * scale;
}


