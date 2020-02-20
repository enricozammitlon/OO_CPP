// PHYS 30762 Programming in C++
// Assignment 4
// Simple demonstration of a C++ class

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
  //According to the hubble classification allowed values E0 to E7, S0, Sa, Sb, Sc, SBa, SBb, SBc and Irr
  std::string hubble_type{"E0"}; 
  //In range [0,10]
  double redshift{5};
  //In range [10e7,10e12]*M0
  double total_mass{10e10};
  //In range [0,0.05]
  double stellar_mass_fraction{0.025};
  std::vector<galaxy> satellites{};

public:
  // Default constructor
  galaxy() = default;
  // Parameterized constructor
  galaxy(std::string ht, double r, double tm,double smf){
    hubble_type=ht, redshift=r, total_mass=tm, 
    stellar_mass_fraction=smf; 
  };
  // Destructor
  ~galaxy() = default;

  // Return stellar mass (M_* = f_* x M_tot)
  double stellar_mass(){
    return stellar_mass_fraction*total_mass;
  };

  // Change galaxy's Hubble type
  void change_type(std::string new_type){
    hubble_type=new_type;
  };
  // Prototype for function to print out an object's data
  void print_data(int parenthood_depth);

  // Add satellite galaxy
  void add_satellite(galaxy satellite){
    satellites.push_back(satellite);
  };
};

// Print out a galaxy's data
void galaxy::print_data(int parenthood_depth=0){
  std::string padding{""};
  for (size_t i = 0; i < parenthood_depth; i++)
  {
    padding+='\t';
  }
  std::cout.setf(std::ios::scientific, std::ios::floatfield);
  std::cout<<padding<<"Hubble Type: "<<hubble_type<<std::endl;
  std::cout<<padding<<"Redshift: "<<std::setprecision(2)<<redshift<<std::endl;
  std::cout<<padding<<"Stellar Mass Fraction: "<<std::setprecision(2)<<stellar_mass_fraction<<std::endl;
  std::cout<<padding<<"Total Mass: "<<std::setprecision(2)<<total_mass<<" M0"<<std::endl;
  if(satellites.size()!=0){
    std::cout<<padding<<"Satellites in this galaxy: "<<std::endl;
  }
  for(auto iterator=satellites.begin(); iterator!=satellites.end();iterator++){
    std::cout<<"*******\tBEGIN SATELLITE\t******"<<std::endl;
    galaxy current_satellite{*iterator};
    current_satellite.print_data(parenthood_depth+1);
    std::cout<<"*******\tEND SATELLITE\t******"<<std::endl;
  };
}
// End of class and associated member functions

// Main program
int main()
{
  // Example using default constructor
  galaxy main_galaxy; 

  // Example using parameterised constructor
  galaxy other_galaxy("S0",1,10e7,0.01);

  // Add satellite galaxies
  main_galaxy.add_satellite(other_galaxy);
  // print out data
  main_galaxy.print_data();
  // Get and print out stellar mass
  std::cout.setf(std::ios::scientific, std::ios::floatfield);
  std::cout<<"\nStellar mass for satellite: "<<std::setprecision(2)<<other_galaxy.stellar_mass()<<" M0\n"<<std::endl;
  // Change Hubble type from Irr to S0
  main_galaxy.change_type("Sbc");
  main_galaxy.print_data();
  
  return 0;
}