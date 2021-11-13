//AUTHOR: GURPREET SINGH
#include <iostream>
#include <cmath>

using namespace std;

class Vec3d {
private:
double x = 0;
double y = 0;
double z = 0;
public:
    Vec3d() {
       // cout << "(0, 0, 0)" << endl;
    }
    Vec3d(double x, double y, double z) : x(x), y(y), z(z) {
       // cout << "(" << x << ", " << y << ", " << z << ")";
    }
    Vec3d(double x) : x(x) {
       // cout << "(" << x << ", 0, 0)";
    }
    Vec3d(double x, double y) : x(x), y(y) {
       // cout << "(" << x << ", " << y << ", 0)";
    }
   static double dot(const Vec3d& a, const Vec3d& b){
     return (a.x * b.x + a.y * b.y + a.z * b.z);
   };

    double dot(Vec3d a) const {
        double result = a.x * x + a.y * y + a.z * z;
        return result;
    }
    double mag() const {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    double magSq() const {
        return (this->x * this->x + this->y * this->y + this->z * this->z);
    }
    double dist(Vec3d f) const {
        return sqrt((this->x * this->x + this->y * this->y + this->z * this->z) - (f.x * f.x + f.y * f.y + f.z * f.z));
    }
    friend Vec3d operator +(Vec3d a, Vec3d b);
    friend Vec3d operator -(Vec3d a, Vec3d b);
    friend Vec3d operator -(Vec3d a);
    friend ostream& operator <<(ostream& s, Vec3d a);
    friend double dot(Vec3d a, Vec3d b);
};

Vec3d operator +(Vec3d a, Vec3d b) {
    return Vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec3d operator -(Vec3d a, Vec3d b) {
    return Vec3d(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec3d operator -(Vec3d a) {
    return Vec3d(-a.x, -a.y, -a.z);
}
ostream& operator <<(ostream& s, Vec3d a){
    return s << "(" << a.x << ", " << a.y << ", " << a.z << ")";
}
double dot(Vec3d a, Vec3d b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int main() {
	// Main() Section 1
	const Vec3d a(1.0,2.5,3.5); // double precision!
	const Vec3d b(2.0);         //(2,0,0)
	const Vec3d c(2.0,3.5);     //(2,3.5,0)
	const Vec3d d;              //(0,0,0)

	// Main() Section 2
	const Vec3d e = a + d;  // use friend
	const Vec3d f = c - b;	// use friend
	const Vec3d g = -e;     // use friend
	
	// Main() Section 3	
	double r = dot(e, f); // regular function  e.x*f.x + e.y*f.y + e.z*f.z  (friend)
	double s = e.dot(f); // method
	double t = Vec3d::dot(e,f); // static function

	// Main() Section 4	
	double x = e.mag(); // square root of sum of square
	double y = e.magSq(); // sum of square
	double z = e.dist(f); // sqrt or sum of square of diff

	// Main() Section 5	
	cout << "a: " << a << '\n';
	cout << "b: " << b << '\n';
	cout << "c: " << c << '\n';
	cout << "d: " << d << '\n';
	cout << "e: " << e << '\n';
	cout << "f: " << f << '\n';
	cout << "g: " << g << '\n';
	cout << "r: " << r << '\n';
	cout << "s: " << s << '\n';
	cout << "x: " << x << '\n';
	cout << "y: " << y << '\n';
	cout << "z: " << z << '\n'; 

}	






