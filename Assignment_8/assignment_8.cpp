/*
Assignment 8
Date: 24/03/2020
Author: Enrico Zammit Lonardelli
Contains an abstract shapes class used as an interface for all shapes
Also an abstract derived class for a) 2D shapes and b) 3D shapes
Finally, derived classes for 2D and 3D shapes implementations
with a demonstration of the classes capabilities
*/
#include <cmath>
#include <iostream>
#include <string>
// Unless specified, gneeral dimensions of any shapes will be unit.
class shape {
protected:
  const double PI = 3.14159265358979323846264338327950288;
  size_t dimensionality{0};

public:
  shape() = default;
  shape(double d) { dimensionality = d; };
  virtual std::string get_name() = 0;
  virtual double area() = 0;
  virtual double volume() = 0;
  virtual ~shape(){};
};

class shape_2_d : public shape {
public:
  shape_2_d() { dimensionality = 2; };
  double volume() { return 0; };
  virtual ~shape_2_d(){};
};

class shape_3_d : public shape {
public:
  shape_3_d() { dimensionality = 3; };
  virtual ~shape_3_d(){};
};

class ellipse : public shape_2_d {
private:
  double semi_major_axis{1};
  double semi_minor_axis{1};

public:
  ellipse() = default;
  ellipse(double major, double minor) {
    semi_major_axis = major;
    semi_minor_axis = minor;
  };
  std::string get_name() { return "Ellipse"; };
  double area() { return PI * semi_minor_axis * semi_major_axis; };
  ~ellipse(){};
};

class circle : public ellipse {
public:
  circle() = default;
  std::string get_name() { return "Circle"; };
  circle(double r) : ellipse(r, r){};
  ~circle(){};
};

class rectangle : public shape_2_d {
private:
  double length{1};
  double breadth{1};

public:
  rectangle() = default;
  rectangle(double l, double b) {
    length = l;
    breadth = b;
  };
  std::string get_name() { return "Rectangle"; };
  double area() { return length * breadth; };
  ~rectangle(){};
};

class square : public rectangle {
public:
  square() = default;
  std::string get_name() { return "Square"; };
  square(double s) : rectangle(s, s){};
  ~square(){};
};

class ellipsoid : public shape_3_d {
protected:
  // Here axes are called a,b,c as often named in literature
  double a{1};
  double b{1};
  double c{1};

public:
  ellipsoid() = default;
  ellipsoid(double axis_1, double axis_2, double axis_3) {
    a = axis_1;
    b = axis_2;
    c = axis_3;
  };
  std::string get_name() { return "Ellipsoid"; };
  // This is surface area for a 3d shape
  double volume() { return (PI * a * b * c * 4) / 3; };
  double area();
  ~ellipsoid(){};
};
// Using the approximate formula of a general (tri-axial) ellipsoid
// which yields a relative error of at most 1.061% for p=1.6075.
double ellipsoid::area() {
  double p{1.6075};
  double inner_root = (pow(a * b, p) + pow(a * c, p) + pow(b * c, p)) / 3;
  double S = 4 * PI * std::pow(inner_root, 1 / p);
  return S;
}
class sphere : public ellipsoid {
public:
  sphere() = default;
  std::string get_name() { return "Sphere"; };
  sphere(double radius) : ellipsoid(radius, radius, radius){};
  double area() { return 4 * PI * std::pow(a, 2); };
};
class cuboid : public shape_3_d {
private:
  double length{1};
  double breadth{1};
  double depth{1};

public:
  cuboid() = default;
  cuboid(double axis_1, double axis_2, double axis_3) {
    length = axis_1;
    breadth = axis_2;
    depth = axis_3;
  };
  std::string get_name() { return "Cuboid"; };
  // This is surface area for a 3d shape
  double volume() { return length * breadth * depth; };
  double area() { return length * breadth * 6; };
  ~cuboid(){};
};
class cube : public cuboid {
public:
  cube() = default;
  cube(double s) : cuboid(s, s, s){};
  std::string get_name() { return "Cube"; };
};
class prism : public shape_3_d {
private:
  double depth{0};
  shape_2_d *base_shape;

public:
  prism() = default;
  prism(shape_2_d *prism_2d_shape, double d) {
    base_shape = prism_2d_shape;
    depth = d;
  };
  std::string get_name() {
    return "Prism with face shape: " + base_shape->get_name();
  };
  // Unlike other 3d shapes this is the base area of the volume
  double area() { return base_shape->area(); };
  double volume() { return depth * base_shape->area(); };
  ~prism() { delete base_shape; };
};
int main() {
  shape **all_shapes = new shape *[9];
  all_shapes[0] = new circle();
  all_shapes[1] = new ellipse();
  all_shapes[2] = new rectangle(2, 2);
  all_shapes[3] = new square(3);
  all_shapes[4] = new ellipsoid(1, 2, 3);
  all_shapes[5] = new sphere(2);
  all_shapes[6] = new cube();
  all_shapes[7] = new cuboid();
  all_shapes[8] = new prism(new square(), 2);
  for (size_t i{}; i < 9; i += 1) {
    std::cout << "****NEW SHAPE****" << std::endl;
    std::cout << "Current shape: " << all_shapes[i]->get_name() << std::endl;
    if (i <= 3) {
      std::cout << "Area of shape: ";
    } else if (i == 8) {
      std::cout << "Area of base shape: ";
    } else {
      std::cout << "Surface area of shape: ";
    }
    std::cout << all_shapes[i]->area() << std::endl;
    std::cout << "Volume of shape: " << all_shapes[i]->volume() << std::endl;
  }
  for (size_t i{}; i < 9; i += 1) {
    delete all_shapes[i];
  }
  delete[] all_shapes;
  return 0;
}