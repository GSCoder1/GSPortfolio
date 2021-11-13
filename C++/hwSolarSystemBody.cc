#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <iomanip>

#define PI 3.14159265358979

using namespace std;
/*class Vec3d;
class Body;
void xy(Vec3d, Body); */

class Vec3d {
private:
	double x;
	double y;
	double t;
public:
	friend ostream &operator << (ostream& s, Vec3d& v) {
		cout << setprecision(3) << "(" << v.x << ", " << v.y << ", " << v.t << ")";
		return s; 
	}
	double randomFunction() {
		srand(time(0));
		//return ((double)rand()* 2.0 * pi )/ RAND_MAX;
		//return ((double)rand() % (2.0 * pi));

		double random_integer = (double)rand()/(double)RAND_MAX;
		return random_integer * (2 * PI);
	}

	void cal_xy(double radius) {
		this->t = randomFunction();
		this->x = radius * cos(t);
		this->y = radius * sin(t);
	}
};

class Body {
private:
	string name;
	double mass;   // mass of the body
	double radius; // size of the body (assumes spherical)
	double p_dist; //perihelion
	double a_dist; //aphelion
	Vec3d pos;     // pos = (x,y,0) ignore z for now. x,y should be based on orbital radius
	Vec3d v;       // v = 0 next week we have to calculate
	Vec3d a;       // a = 0 next week we compute gravitational acceleration due to all other bodies
public:
	vector<string> get(ifstream& fileInput) {
		vector <string> result;
		string data;
		int counter = 0;
		
		while(counter < 10 && fileInput >> data) {
			result.push_back(data);
			counter++;
		}
		return result;
	}
	double stringToDouble(string str) { //to convert string inputs to double
		istringstream iss(str);
		double d;
		if( !(iss >> d)) {
			throw "Can not convert string to double \n";
			return 0;
		}
		return d;
	}
	void setter(string name, string mass, string diam, string p_dist, string a_dist) {
		this->name = name;
		this->mass = stringToDouble(mass);
		this->radius = stringToDouble(diam)/2.0;
		this->p_dist = stringToDouble(p_dist);
		this->a_dist = stringToDouble(a_dist);
	}
	friend ostream &operator << (ostream& s, Body& b) {
		cout << "Name: " << b.name << endl;
		//cout << "Mass: " << b.mass << endl;
		//cout << "radius: " << b.radius << endl;
		cout << "Average Distance from Sun: " << (b.p_dist + b.a_dist) / 2 << endl;
		b.pos.cal_xy(b.radius);
		cout << "Position Vector" << b.pos << endl;
		return s;
	}
	friend ifstream &operator >> (ifstream& in, Body& b) {
		vector <string> lineData = b.get(in);
		b.setter(lineData[0], lineData[2], lineData[3], lineData[4], lineData[5]);
		return in;
	}
};



int main() {
	ifstream solarsystem("solarsystem.dat");
	char buf[1024];
	solarsystem.getline(buf, sizeof(buf)); // throw out first line

	Body sun, mercury, venus, earth, moon;
	solarsystem >> sun >> mercury >> venus >> earth;
	//Vec3d random;
	//cout << random << endl;
	// read in the name of each body
	// compute average distance of each body from sun (average of perihelion and aphelion)
	// pick t = a random number from 0 to 2*pi
	// 
	// calculate x,y = r cos t, r sin t
	// put into pos vector (x,y, 0)

	// next step (not necessary this week)
	// calculate V
	// pretend all orbits are circular
	// calculate the length of the circular path around the sun 2*pi * r
	// look up time it takes to orbit
	// convert to meters and seconds
	// v = distance around the sun / orbital period in seconds
	cout << sun << mercury << venus << earth;

}
