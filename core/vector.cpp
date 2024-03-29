#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

Vector::Vector(float x, float y, float z)
{
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

Vector::Vector(const Float4& f4)
{
    assert(f4[3]==0);
    this -> x = f4[0];
    this -> y = f4[1];
    this -> z = f4[2];
}

Vector Vector::operator + (const Vector& b) const {
    return Vector(this -> x + b.x, this -> y + b.y, this -> z + b.z);
}

Vector Vector::operator - (const Vector& b) const {
    return Vector(this -> x - b.x, this -> y - b.y, this -> z - b.z);
}

Vector Vector::operator - () const {
    return Vector(this -> x * (-1), this -> y * (-1), this -> z * (-1));
}

Vector Vector::normalize() const {
    float length = sqrt(lensqr());
    assert(length > epsilon);
    return Vector(this -> x / length, this -> y / length, this -> z / length);
}

Vector operator * (float scalar, const Vector& b) {
    return Vector(b.x * scalar, b.y * scalar, b.z * scalar);
}

Vector operator * (const Vector& a, float scalar) {
    return Vector(a.x * scalar, a.y * scalar, a.z * scalar);
}

Vector operator / (const Vector& a, float scalar) {
    assert(scalar > epsilon);
    return Vector(a.x / scalar, a.y / scalar, a.z / scalar);
}

Vector cross(const Vector& a, const Vector& b) {
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float dot(const Vector& a, const Vector& b) {
    return b.x * a.x + b.y * a.y + b.z * a.z;
}

float Vector::lensqr() const {
    return dot(*this, *this);
}

float Vector::length() const {
    return sqrt(lensqr());
}

bool Vector::operator == (const Vector& b) const {
    return (fabs(this->x - b.x) <= epsilon && fabs(this->y - b.y) <= epsilon 
            && fabs(this->z - b.z)<=epsilon);
}

bool Vector::operator != (const Vector& b) const {
    return !(fabs(this->x - b.x) <= epsilon && fabs(this->y - b.y) <= epsilon 
            && fabs(this->z - b.z)<=epsilon);
}

Vector min(const Vector& a, const Vector& b) {
    return Vector(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Vector max(const Vector& a, const Vector& b) {
    return Vector(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Point operator + (const Point& a, const Vector& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector reflect(Vector in, Vector normal) {
    return 2*dot(normal, in)*normal - in;
}

Point operator + (const Vector& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator - (const Point& a, const Vector& b) {
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point operator * (const Float4& scale, const Point& p) {
   return Point(scale * Float4(p));
}

}
