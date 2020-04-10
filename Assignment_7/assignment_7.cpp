/*
Assignment 7
Date: 19/03/2020
Author: Enrico Zammit Lonardelli
Contains a general class vector and children classes
minkowski_four_vector and cartesian_three_vector
with appropriate arithmetic operations and appropriate
constructors and destructors. Aslo contains a class called particle
which implements these two and calculates attributes such as energy and
momentum.
*/
#include <cmath>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <tuple>

class vector {
  friend std::ostream &operator<<(std::ostream &os, const vector &v);

protected:
  size_t length{0};
  double *data{nullptr};

public:
  vector() = default;
  vector(const size_t n) {
    length = n;
    data = new double[n];
  };
  vector(const vector &v);
  vector &operator=(const vector &v);
  vector(vector &&v);
  vector &operator=(vector &&v);
  size_t get_length() const { return length; };
  double get_squared() const {
    double sum_squared{0};
    for (size_t i{1}; i <= length; i += 1) {
      sum_squared += std::pow(data[index(i)], 2);
    }
    return sum_squared;
  }
  double get_magnitude() const { return std::sqrt(vector::get_squared()); }
  size_t index(size_t pos) const {
    if (pos > 0 && pos <= length)
      return pos - 1;
    else {
      throw "Error: Out of range.";
    }
  };
  void set_element(size_t pos, double value) { data[index(pos)] = value; };
  double &operator()(const size_t pos) const { return data[index(pos)]; };
  double dot(const vector v) const {
    if (v.get_length() != length) {
      throw "Vector sizes incompatible.";
    }
    double product{0};
    for (size_t i{1}; i <= length; i += 1) {
      product += data[index(i)] * v(i);
    }
    return product;
  }
  ~vector() { delete[] data; };
};

std::ostream &operator<<(std::ostream &os, const vector &v) {
  if (v.get_length() == 0) {
    os << "Vector is empty!";
    return os;
  }
  for (size_t i{1}; i <= v.get_length(); i += 1) {
    if (i == 1) {
      os << "(";
    }
    os << v(i);
    if (i == v.get_length()) {
      os << ")";
    } else {
      os << ",";
    }
  }
  return os;
}
vector::vector(const vector &v) {
  delete[] data;
  data = nullptr;
  length = v.get_length();
  data = new double[length];
  for (size_t i{1}; i <= length; i += 1) {
    data[index(i)] = v(i);
  }
}
vector &vector::operator=(const vector &v) {
  if (&v == this)
    return *this;
  delete[] data;
  data = nullptr;
  length = v.get_length();
  data = new double[length];
  for (size_t i{1}; i <= length; i += 1) {
    data[index(i)] = v(i);
  }
  return *this;
}
vector::vector(vector &&v) {
  length = v.length;
  data = v.data;
  v.length = 0;
  v.data = nullptr;
}
vector &vector::operator=(vector &&v) {
  std::swap(length, v.length);
  std::swap(data, v.data);
  return *this;
}

class cartesian_three_vector : public vector {
  friend cartesian_three_vector &operator*(double multiplier,
                                           cartesian_three_vector &v);

public:
  cartesian_three_vector() : vector(3){};
  cartesian_three_vector(double x1, double x2, double x3) : vector(3) {
    data[0] = x1;
    data[1] = x2;
    data[2] = x3;
  };
  cartesian_three_vector &operator+(const cartesian_three_vector &v) const;
  cartesian_three_vector &operator*(const double multiplier) const;
  double get_gamma() const {
    double beta_square{0};
    for (size_t i{1}; i <= length; i += 1) {
      beta_square += std::pow(data[index(i)], 2);
    }
    double result{1 / std::sqrt(1 - beta_square)};
    return result;
  };
};
cartesian_three_vector &cartesian_three_vector::
operator+(const cartesian_three_vector &v) const {
  if (v.get_length() != length) {
    throw "Vector sizes incompatible.";
  }
  cartesian_three_vector *sum = new cartesian_three_vector();
  for (size_t i{1}; i <= 3; i += 1) {
    sum->set_element(i, data[index(i)] + v(i));
  }
  return *sum;
};
cartesian_three_vector &cartesian_three_vector::
operator*(const double multiplier) const {
  cartesian_three_vector *product = new cartesian_three_vector();
  for (size_t i{1}; i <= 3; i += 1) {
    product->set_element(i, data[index(i)] * multiplier);
  }
  return *product;
};
cartesian_three_vector operator*(const double multiplier,
                                 const cartesian_three_vector &v) {
  cartesian_three_vector *product = new cartesian_three_vector();
  for (size_t i{1}; i < 3; i += 1) {
    product->set_element(i, v(i) * multiplier);
  }
  return *product;
}

class minkowski_four_vector : public vector {
public:
  minkowski_four_vector() : vector(4){};
  minkowski_four_vector(double x1, double x2, double x3, double x4)
      : vector(4) {
    data[0] = x1;
    data[1] = x2;
    data[2] = x3;
    data[3] = x4;
  };
  minkowski_four_vector(double x0, cartesian_three_vector v3) : vector(4) {
    data[0] = x0;
    for (size_t i{1}; i <= 3; i += 1) {
      data[i] = v3(i);
    }
  };
  minkowski_four_vector &lorentz_boost(const cartesian_three_vector &beta);
  double dot(const minkowski_four_vector v) const {
    if (v.get_length() != length) {
      throw "Vector sizes incompatible.";
    }
    double product{data[index(1)] * v(1)};
    for (size_t i{2}; i <= length; i += 1) {
      product -= data[index(i)] * v(i);
    }
    return product;
  };
  minkowski_four_vector(const minkowski_four_vector &v);
  minkowski_four_vector &operator=(const minkowski_four_vector &v);
  minkowski_four_vector(minkowski_four_vector &&v);
  minkowski_four_vector &operator=(minkowski_four_vector &&v);
  cartesian_three_vector &get_space_component() const;
  double get_time_component() const;
};

minkowski_four_vector::minkowski_four_vector(const minkowski_four_vector &v) {
  delete[] data;
  data = nullptr;
  length = v.get_length();
  data = new double[length];
  for (size_t i{1}; i <= length; i += 1) {
    data[index(i)] = v(i);
  }
}
minkowski_four_vector &minkowski_four_vector::
operator=(const minkowski_four_vector &v) {
  if (&v == this)
    return *this;
  delete[] data;
  data = nullptr;
  length = v.get_length();
  data = new double[length];
  for (size_t i{1}; i <= length; i += 1) {
    data[index(i)] = v(i);
  }
  return *this;
}
minkowski_four_vector::minkowski_four_vector(minkowski_four_vector &&v) {
  length = v.length;
  data = v.data;
  v.length = 0;
  v.data = nullptr;
}
minkowski_four_vector &minkowski_four_vector::
operator=(minkowski_four_vector &&v) {
  std::swap(length, v.length);
  std::swap(data, v.data);
  return *this;
}
minkowski_four_vector &
minkowski_four_vector::lorentz_boost(const cartesian_three_vector &beta) {
  cartesian_three_vector *r_old =
      new cartesian_three_vector(data[1], data[2], data[3]);
  double ct_new = beta.get_gamma() * (data[0] - r_old->dot(beta));
  cartesian_three_vector r_new =
      *r_old +
      (beta.get_gamma() - 1) * beta * ((r_old->dot(beta)) / beta.get_squared());
  minkowski_four_vector *result = new minkowski_four_vector(ct_new, r_new);
  return *result;
};
cartesian_three_vector &minkowski_four_vector::get_space_component() const {
  cartesian_three_vector *space = new cartesian_three_vector();
  for (size_t i{1}; i <= 3; i += 1) {
    space->set_element(i, data[i]);
  }
  return *space;
}
double minkowski_four_vector::get_time_component() const { return data[0]; }

class particle {
private:
  double mass{0};
  cartesian_three_vector *beta = new cartesian_three_vector();
  minkowski_four_vector *position = new minkowski_four_vector();

public:
  particle() = default;
  particle(double m, cartesian_three_vector &b, minkowski_four_vector &pos) {
    mass = m;
    beta = &b;
    position = &pos;
  };
  std::tuple<double, std::string> get_mass() {
    return std::tuple<double, std::string>{mass, "MeV/c^2"};
  };
  cartesian_three_vector get_beta() { return *beta; };
  minkowski_four_vector get_position() { return *position; };
  std::tuple<double, std::string> get_total_energy() {
    double energy = beta->get_gamma() * mass;
    return std::tuple<double, std::string>{energy, "MeV"};
  };
  std::tuple<cartesian_three_vector, std::string> get_momentum() {
    cartesian_three_vector momentum = *beta * beta->get_gamma() * mass;
    return std::tuple<cartesian_three_vector, std::string>{momentum, "MeV/c"};
  };
  void display_details() {
    std::tuple<double, std::string> energy{get_total_energy()};
    std::tuple<cartesian_three_vector, std::string> momentum{get_momentum()};
    std::cout << "\tX:" << get_position() << "\n\tVelocity (v/c):" << get_beta()
              << "\n\tEnergy:" << std::get<0>(energy) << std::get<1>(energy)
              << "\n\tMomentum:" << std::get<0>(momentum)
              << std::get<1>(momentum) << std::endl;
  };
  ~particle() = default;
};

int main() {
  std::cout << "########Vector Class Demonstrations#########" << std::endl;
  minkowski_four_vector *v0 = new minkowski_four_vector(1, 2.3, 3.4, -4.0);
  std::cout << *v0 << std::endl;
  std::cout << "Space component: " << v0->get_space_component() << std::endl;
  std::cout << "Time component: " << v0->get_time_component() << std::endl;
  cartesian_three_vector *x1 = new cartesian_three_vector(1, 2, 3);
  minkowski_four_vector *v1 = new minkowski_four_vector(5, *x1);
  minkowski_four_vector v2 = *v1;
  minkowski_four_vector v3{v2};
  std::cout << *v1 << std::endl;
  std::cout << v2 << std::endl;
  std::cout << v3 << std::endl;
  std::cout << "Moving operations" << std::endl;
  minkowski_four_vector v4{std::move(v2)};
  minkowski_four_vector v5 = std::move(v3);
  std::cout << v2 << std::endl;
  std::cout << v3 << std::endl;
  std::cout << v4 << std::endl;
  std::cout << v5 << std::endl;
  std::cout << v4.dot(v5) << std::endl;
  std::cout << "########Particle Class Demonstration#########" << std::endl;
  minkowski_four_vector *position_1 = new minkowski_four_vector(15, 2, 3, 4);
  minkowski_four_vector *position_2 = position_1;
  cartesian_three_vector *velocity_1 = new cartesian_three_vector(0.8, 0, 0);
  cartesian_three_vector *velocity_2 = new cartesian_three_vector(-0.3, 0.1, 0);
  particle *a = new particle(10, *velocity_1, *position_1);
  particle *b = new particle(5, *velocity_2, *position_2);
  std::cout << "------------------BEFORE BOOST--------------" << std::endl;
  std::cout << "Particle A:\n";
  a->display_details();
  std::cout << "Particle B:\n";
  b->display_details();
  std::cout << "------------------AFTER BOOST--------------" << std::endl;
  cartesian_three_vector *boost_1 = new cartesian_three_vector(0.1, 0, 0.2);
  cartesian_three_vector *boost_2 = new cartesian_three_vector(0.3, 0.2, -0.2);
  std::cout << "Boost A:" << *boost_1 << std::endl;
  std::cout << "Boost B:" << *boost_2 << std::endl;
  particle *a_boosted = new particle(10, *velocity_1 + *boost_1,
                                     position_1->lorentz_boost(*boost_1));
  particle *b_boosted = new particle(5, *velocity_2 + *boost_2,
                                     position_2->lorentz_boost(*boost_2));
  std::cout << "Particle A:\n";
  a_boosted->display_details();
  std::cout << "Particle B:\n";
  b_boosted->display_details();
}