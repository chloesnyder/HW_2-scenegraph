#include "mat4.h"
#include <cmath>
#include <math.h>
#include <assert.h>

////isEqual method
bool mat4isEqual(float f1, float f2) {
    //http://www.parashift.com/c++-faq/floating-point-arith.html
    const float epsilon = .0001;
    return std::abs(f1 - f2) <= epsilon * std::abs(f1);
 }

////helper function to normalize vectors
vec4 normalize(vec4 v) {
    return (v / length(v));
}

///helper function to convert from degrees to radians
float convertDegToRad(float d) {
    return d * (M_PI / 180);
}

///----------------------------------------------------------------------
/// Constructors
///----------------------------------------------------------------------
/// Default Constructor.  Initialize to matrix of all 0s.
mat4::mat4() {
    data[0] = vec4();
    data[1] = vec4();
    data[2] = vec4();
    data[3] = vec4();
}

/// Initializes the diagonal values of the matrix to diag. All other values are 0.
mat4::mat4(float diag){
    data[0] = vec4(diag, 0, 0, 0);
    data[1] = vec4(0, diag, 0, 0);
    data[2] = vec4(0, 0, diag, 0);
    data[3] = vec4(0, 0, 0, diag);
}

/// Initializes matrix with each vector representing a row in the matrix
mat4::mat4(const vec4 &row0, const vec4 &row1, const vec4 &row2, const vec4& row3){
    data[0] = vec4(row0);
    data[1] = vec4(row1);
    data[2] = vec4(row2);
    data[3] = vec4(row3);
}

mat4::mat4(const mat4 &m2) { // copy constructor
    data[0] = m2[0];
    data[1] = m2[1];
    data[2] = m2[2];
    data[3] = m2[3];
}

///----------------------------------------------------------------------
/// Getters
///----------------------------------------------------------------------
/// Returns the values of the row at the index
vec4 mat4::operator[](unsigned int index) const{
    assert(index >= 0 && index <= 3);
    return data[index];
}

/// Returns a reference to the row at the index
vec4 &mat4::operator[](unsigned int index){
    assert(index >= 0 && index <= 3);
    return data[index];
}

///----------------------------------------------------------------------
/// Static Initializers
///----------------------------------------------------------------------


/// Creates a 3-D rotation matrix.
/// Takes an angle in degrees and an axis represented by its xyz components, and outputs a 4x4 rotation matrix
/// You may choose to only handle the three cardinal axes of rotation.
mat4 mat4::rotate(float angle, float x, float y, float z) {
    //For now, only handle cardinal rotation matrixes
    assert((mat4isEqual(x, 1) && mat4isEqual(y, 0) && mat4isEqual(z, 0)) ||
           (mat4isEqual(x, 0) && mat4isEqual(y, 1) && mat4isEqual(z, 0)) ||
           (mat4isEqual(x, 0) && mat4isEqual(y, 0) && mat4isEqual(z, 1)));

    //normalize the input vector, will be useful for future assignments
    vec4 norm = normalize(vec4(x, y, z, 0));
    x = norm[0];
    y = norm[1];
    z = norm[2];
    //convert angle from degrees to radians
    angle = convertDegToRad(angle);

    vec4 v0x = vec4(1, 0, 0, 0);
    vec4 v1x = vec4(0, x*cos(angle), -x*sin(angle), 0);
    vec4 v2x = vec4(0, x*sin(angle), x*cos(angle), 0);
    vec4 v3x = vec4(0, 0, 0, 1);

    vec4 v0y = vec4(y*cos(angle), 0, y*sin(angle), 0);
    vec4 v1y = vec4(0, 1, 0, 0);
    vec4 v2y = vec4(-y*sin(angle), 0, y*cos(angle), 0);
    vec4 v3y = vec4(0, 0, 0, 1);

    vec4 v0z = vec4(z*cos(angle), -z*sin(angle), 0, 0);
    vec4 v1z = vec4(z*sin(angle), z*cos(angle), 0, 0);
    vec4 v2z = vec4(0, 0, 1, 0);
    vec4 v3z = vec4(0, 0, 0, 1);

    mat4 rx = mat4(v0x, v1x, v2x, v3x);
    mat4 ry = mat4(v0y, v1y, v2y, v3y);
    mat4 rz = mat4(v0z, v1z, v2z, v3z);

   // return (rx*ry*rz);
    if(mat4isEqual(x, 1) && mat4isEqual(y, 0) && mat4isEqual(z, 0)) {
        return rx;
    } else if(mat4isEqual(x, 0) && mat4isEqual(y, 1) && mat4isEqual(z, 0)) {
        return ry;
    } else if(mat4isEqual(x, 0) && mat4isEqual(y, 0) && mat4isEqual(z, 1)) {
        return rz;
    }
}

/// Takes an xyz displacement and outputs a 4x4 translation matrix
mat4 mat4::translate(float x, float y, float z){
    vec4 v0 = vec4(1, 0, 0, x);
    vec4 v1 = vec4(0, 1, 1, y);
    vec4 v2 = vec4(0, 0, 1, z);
    vec4 v3 = vec4(0, 0, 0, 1);
    return mat4(v0, v1, v2, v3);
}

/// Takes an xyz scale and outputs a 4x4 scale matrix
mat4 mat4::scale(float x, float y, float z){
    vec4 v0 = vec4(x, 0, 0, 0);
    vec4 v1 = vec4(0, y, 0, 0);
    vec4 v2 = vec4(0, 0, z, 0);
    vec4 v3 = vec4(0, 0, 0, 1);
    return mat4(v0, v1, v2, v3);
}

/// Generates a 4x4 identity matrix
mat4 mat4::identity(){
    return mat4(1);
}


///----------------------------------------------------------------------
/// Operator Functions
///----------------------------------------------------------------------

/// Assign m2 to this and return it
mat4 &mat4::operator=(const mat4 &m2){
    for(int i = 0; i < 4; i++) {
        this->data[i] = m2.data[i];
    }
    return *this;
}

/// Test for equality
bool mat4::operator==(const mat4 &m2) const{
    bool b = true;
    for(int i = 0; i < 4; i++){
        if (this->data[i] != m2.data[i]) {
            b = false;
        }
    }
    return b;
}

/// Test for inequality
bool mat4::operator!=(const mat4 &m2) const{
    return !this->operator==(m2);
}

/// Element-wise arithmetic
/// e.g. += adds the elements of m2 to this and returns this (like regular +=)
///      +  returns a new matrix whose elements are the sums of this and v2
mat4 &mat4::operator+=(const mat4 &m2){
    for(int i = 0; i < 4; i++) {
        this->data[i]+=m2.data[i];
    }
    return *this;
}
mat4 &mat4::operator-=(const mat4 &m2){
    for(int i = 0; i < 4; i++) {
        this->data[i]-=m2.data[i];
    }
    return *this;
}
mat4 &mat4::operator*=(float c){ // multiplication by a scalar
    for(int i = 0; i < 4; i++) {
        this->data[i]*=c;
    }
    return *this;
}
mat4 &mat4::operator/=(float c){// division by a scalar
    assert(c != 0);
    for(int i = 0; i < 4; i++) {
        this->data[i]/=c;
    }
    return *this;
}
mat4 mat4::operator+(const mat4 &m2) const{
    mat4 result = *this;
    return (result+=m2);
}
mat4 mat4::operator-(const mat4 &m2) const{
    mat4 result = *this;
    return result-=m2;
}
mat4 mat4::operator*(float c) const{// multiplication by a scalar
    mat4 result = *this;
    return result*=c;
}
mat4 mat4::operator/(float c) const{ // division by a scalar
    mat4 result = *this;
    return result/=c;
}

//TODO: CHECK
/// Matrix multiplication (m1 * m2)
mat4 mat4::operator*(const mat4 &m2) const{
    vec4 c0 = column(m2, 0);
    vec4 c1 = column(m2, 1);
    vec4 c2 = column(m2, 2);
    vec4 c3 = column(m2, 3);

    vec4 v0 = vec4(dot((*this)[0], c0), dot((*this)[0], c1), dot((*this)[0], c2), dot((*this)[0], c3));
    vec4 v1 = vec4(dot((*this)[1], c0), dot((*this)[1], c1), dot((*this)[1], c2), dot((*this)[1], c3));
    vec4 v2 = vec4(dot((*this)[2], c0), dot((*this)[2], c1), dot((*this)[2], c2), dot((*this)[2], c3));
    vec4 v3 = vec4(dot((*this)[3], c0), dot((*this)[3], c1), dot((*this)[3], c2), dot((*this)[3], c3));

    return mat4(v0, v1, v2, v3);
}

/// Matrix/vector multiplication (m * v)
/// Assume v is a column vector (ie. a 4x1 matrix)
vec4 mat4::operator*(const vec4 &v) const{
    return vec4(dot((*this)[0], v), dot((*this)[1], v), dot((*this)[2], v), dot((*this)[3], v));
}


///----------------------------------------------------------------------
/// Matrix Operations
///----------------------------------------------------------------------
/// Returns the transpose of the input matrix (v_ij == v_ji)
mat4 transpose(const mat4 &m){
    //row becomes a column
    vec4 r0 = column(m, 0);
    vec4 r1 = column(m, 1);
    vec4 r2 = column(m, 2);
    vec4 r3 = column(m, 3);
    return mat4(r0, r1, r2, r3);
}

/// Returns a column of the input matrix
vec4 column(const mat4 &m, unsigned int index){
    assert(index >=0 && index <= 3);
    vec4 column = vec4();
    for(int i = 0; i < 4; i++) {
         column[i] = m[i][index];
    }
    return column;
}

/// Scalar multiplication (c * m)
mat4 operator*(float c, const mat4 &m){
     return m*c;
}

/// Vector/matrix multiplication (v * m)
/// Assume v is a row vector (ie. a 1x3 matrix)
vec4 operator*(const vec4 &v, const mat4 &m){
    return m*v;
}

/// Prints the matrix to a stream in a nice format
std::ostream &operator<<(std::ostream &o, const mat4 &m) {
    o << std::endl << m[0] << std::endl << m[1] << std::endl << m[2] << std::endl << m[3] << std::endl;
    return o;
}
