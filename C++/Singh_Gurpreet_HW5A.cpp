//AUTHOR: Gurpreet Singh
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
	suggestion:
for this assignment:
*/
class Shape {
private:
    //int numShapes = 0;
public:
  virtual void draw(ostream& s) = 0;
 // virtual ~Shape() {} //makes destructor polymorphic as long as every child has its own destructor
};


class Drawing {
private:
	ofstream f;
	vector<Shape*> shapes;
    int numShapes = 0;
    int r;
    int g;
    int b;
public:
    Drawing() {}
	Drawing(string filename) : f(filename.c_str()), shapes(), r(r), g(g), b(b) {
	}

	void add( Shape* s ) {
    shapes.push_back(s);
    ++numShapes;
	}
	void draw() {
		for (int i = 0; i < numShapes; i++) {//numshapes is 0
			shapes[i]->draw(f); //this calls void draw(ostream &s)
            }
	}
    void setrgb(int r, int g, int b) { //void because otherwise there is no suitable conversion for <<
        //this->f;
        f << r << " " << g << " " << b << " setrgbcolor\n"; //ofstream f in private class. this->?
    }
    friend ostream& operator <<(ostream& s, Drawing& file) {
        return s;
    }
   void draw(ostream& s) {
    } 
};

class Polygon : public Shape {
private:
    Drawing d;
    int w, x;
    int y, z;
public:
    Polygon(int w, int x, int y, int z) : w(w), x(x), y(y), z(z) {}
   /*  friend ostream& operator <<(ostream& s, Polygon& file) {
        return s << file.w << " " << file.x << " moveto\n" << file.x << " " << file.y << " lineto\n" 
            << file.x << " " << file.z << " lineto\n" << file.w << " " << file.z << "lineto\n" << "closepath stroke\n";
    } */
    void draw(ostream& s) {
        s << w << " " << x << " moveto\n" << x << " " << y << " lineto\n" 
            << x << " " << z << " lineto\n" << w << " " << z << " lineto\n" << "closepath stroke\n";
        d.draw(s);
    }
};
 
class FilledRect : public Shape {
private: 
    Drawing d;
    double x1;
    double x2;
    double y1;
    double y2;
public:
    FilledRect(double x1, double x2, double y1, double y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}
    void draw(ostream& s) {
        s << x1 << " " << y1 << " moveto\n" << x2 << " " << y1 << " lineto\n" 
            << x2 << " " << y2 << " lineto\n" << x1 << " " << y2 << " lineto\n" << " stroke fill\n"; //closepath stroke fill
        d.draw(s);
    }
};

class Rect : public Shape {
private:
    Drawing d;
    double x1;
    double x2;
    double y1;
    int y2;
public:
    Rect(double x1, double x2, double y1, int y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}
        
    void draw(ostream& s) {
        s << x1 << " " << y1 << " moveto\n" << x2 << " " << y1 << " lineto\n" 
            << x2 << " " << y2 << " lineto\n" << x1 << " " << y2 << " lineto\n" << "closepath stroke\n";
        d.draw(s);
    }
};

class FilledCircle : public Shape {
private: 
    Drawing d;
    int x;
    int y;
    double r;
public:
    FilledCircle(int x, int y, double r) : x(x), y(y), r(r) {}
    friend ostream& operator <<(ostream& f, FilledCircle& file) {
        return f;
    }
    void draw(ostream& s) {
        s << x << " " << y << " " << r << " 0 360 arc fill\n"; //closepath arc
        d.draw(s);
    }
};

class Circle : public Shape {
private:
    Drawing d;
    int x;
    int y;
    double r;
public:
    Circle(int x, int y, double r) : x(x), y(y), r(r) {}

    void draw(ostream& s) {
        s << x << " " << y << " " << r << " 0 360 arc\n";
        d.draw(s);
    }
};

class Line : public Shape {
private:
    Drawing d;
    int x1;
    int x2;
    int y1;
    int y2;
public:
    Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    void draw(ostream& s) {
        s << x1 << " " << y1 << " moveto\n" << x2 << " " << y2 << " lineto\n";
        d.draw(s);
    }
};

int main() {
	ofstream f(  );
	Drawing d("test2.ps");
	d.setrgb(1,0,0); // set drawing color to be bright red:  1 0 0 setrgbcolor
	d.add(new FilledRect(100.0, 150.0, 200.0, 50)); // x y moveto x y lineto ... fill
	d.add(new Rect(100.0, 150.0, 200.0, 50));       // x y moveto x y lineto ... stroke
	for (int x = 0; x < 600; x += 100)
		d.add(new FilledCircle(x,200,50.0)); // x y r 0 360 arc fill
	d.setrgb(0,1,0); // the rest are green

	d.add(new Circle(0,0, 100)); // 0 0 100 0 360 stroke
	d.add(new Line(400,500, 600,550));
	d.add(new Polygon(200,200, 50, 6));
	d.draw();
}
