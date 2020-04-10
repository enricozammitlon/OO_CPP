// PHYS 30762 Programming in C++
// Author: Enrico Zammit Lonardelli
// Date: 01/03/2020
// Assignment 5 - A class to store complex numbers and provide
// basic operations defined on this number set

#include <cmath>
#include <iostream>
#include <string>
#include <regex>

class complex {
  // Make functions to overload operator<< and >> as friends
  friend std::ostream &operator<<(std::ostream &os, const complex &z);
  friend std::istream &operator>>(std::istream &is, complex &z);

  private:
    double re{0};
    double im{0};
  public:
    complex() = default;
    complex(double real_part, double im_part) {
      re = real_part;
      im = im_part;
    }
    ~complex() = default;
    double real(){
      return re;
    }
    double imaginary(){
      return im;
    }
    double modulus(){
      return sqrt(pow(re,2)+pow(im,2));
    }
    double argument(){
      return atan2(im,re);
    }
    complex complex_conjugate(){
      complex conjugate{re,-im};
      return conjugate;
    }
    complex operator+(const complex &vector) const
    {
      complex sum{re+vector.re,im+vector.im};
      return sum;
    }
    complex operator-(const complex &vector) const
    {
      complex diff{re-vector.re,im-vector.im};
      return diff;
    }
    complex operator*(const complex &vector) const;
    complex operator/(const complex &vector) const;
};
complex complex::operator*(const complex &vector) const{
  double a{re},b{im},c{vector.re},d{vector.im};
  double result_re=(a*c)-(b*d);
  double result_im=(a+b)*(c+d)-(a*c)-(b*d);
  complex mult{result_re,result_im};
  return mult;
}
complex complex::operator/(const complex &vector) const{
  double a{re},b{im},c{vector.re},d{vector.im};
  double result_multiplier=pow(c,2)+pow(d,2);
  double result_re=(a*c)+(b*d);
  double result_im=(b*c)-(a*d);
  complex quotient{result_re/result_multiplier,result_im/result_multiplier};
  return quotient;
}
// Function to overload << operator for complex numbers
std::ostream &operator<<(std::ostream &os, const complex &z){
  std::string sign{"+i"};
  if(z.im<0.0){
    sign = "-i";
  }
  os<<' '<<z.re<<sign<<std::abs(z.im);
  return os;
}
// Function to overload >> operator for complex numbers
std::istream &operator>>(std::istream &is, complex &z){
  std::string input;
  std::getline(is,input);
  std::smatch match;
  const std::regex find_re{"[+-]?[^i][0-9]+"};
  const std::regex find_imaginary{"[+-]?[i][0-9]+"};
  std::string real_part;

  if (!std::regex_search(input, match, find_imaginary)){
    z.im=0;
    if (!std::regex_search(input, match, find_re)){
      z.re=0;
      return is;
    }
    else{
      real_part= match[0].str();
    }
  }
  else{
    real_part= match.prefix().str();
    std::string imaginary_part{match[0].str()};
    if(imaginary_part[0]=='-'){
      z.im=-1*stod(imaginary_part.substr(2,imaginary_part.length()));
    }
    else if(imaginary_part[0]=='+'){
      z.im=stod(imaginary_part.substr(2,imaginary_part.length()));
    }
    else{
      z.im=stod(imaginary_part.substr(1,imaginary_part.length()));
    }
  }
  if(real_part==""){
    z.re=0;
  }
  else{
    if(real_part[0]=='-'){
      z.re=-1*stod(real_part.substr(1,real_part.length()));
    }
    else if(real_part[0]=='+'){
      z.re=stod(real_part.substr(1,real_part.length()));
    }
    else{
      z.re=stod(real_part.substr(0,real_part.length()));
    }
  }
  return is;
}

int main() {
  std::cout.precision(3);
  complex a{};
  complex b{};

  std::cout<<"Please enter a complex number in format a+ib or a-ib:"<<std::endl;
  std::cin>>a;
  std::cout<<"Please enter a complex number in format a+ib or a-ib:"<<std::endl;
  std::cin>>b;

  std::cout<<"\nFor the complex number:"<<a<<std::endl;
  std::cout<<"Real Part: "<<a.real()<<std::endl;
  std::cout<<"Imaginary Part: "<<a.imaginary()<<std::endl;
  std::cout<<"Modulus: "<<a.modulus()<<std::endl;
  std::cout<<"Argument: "<<a.argument()<<std::endl;
  std::cout<<"\nCongjugate of"<<a<<" is"<<a.complex_conjugate()<<std::endl;
  std::cout<<"\nFor the following 2 complex numbers: "<<a<<" and "<<b<<" :"<<std::endl;
  std::cout<<"Sum: "<<(a+b)<<std::endl;
  std::cout<<"Difference: "<<(a-b)<<std::endl;
  std::cout<<"Product: "<<(a*b)<<std::endl;
  std::cout<<"Quotient: "<<(a/b)<<std::endl;
  return 0;
}