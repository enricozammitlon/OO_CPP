// Assignment 1
// Enrico Zammit Lonardelli - 29/01/2020
// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include <cmath>

// Compute energy level spacing for Bohr model, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
double get_energy_spacing(int atomic_number,int initial_quantum_number,int final_quantum_number){
  double photon_energy{13.6*std::pow(atomic_number,2)*((std::pow(initial_quantum_number,-2.0)-std::pow(final_quantum_number,-2.0)))};
  return photon_energy;
}

int main()
{
  // Declaration of variables here
  int atomic_number{0};
  int initial_quantum_number{0};
  int final_quantum_number{0};
  char units{'e'};
  bool repeat_loop{true};
  const double conversion_e_to_J = 1.602e-19;
  char response{'y'};
  double photon_energy{0};

  while(response=='y'){
    // Ask user to enter variables
    std::cout<<"****\n"<<"Welcome to Assignment 1: It will calculate the transition energy between states for an atom.\n"<<"****\n"<<std::endl;
    std::cout<<"Please enter the atomic number, the initial and final quantum numbers and the units the final answer should be given in (e or J) separated by spaces."<<std::endl;
    std::cin>>atomic_number>>initial_quantum_number>>final_quantum_number>>units;

    //Validation step
    while(std::cin.fail() || (atomic_number<1) || (initial_quantum_number <1 || final_quantum_number <= initial_quantum_number) || (units!='e' && units!='J')) {
      std::cout <<"Sorry, your input was not valid. "; 
      std::cout<<"Please enter the atomic number, the non-zero initial and final quantum numbers and the units the final answer should be given in (e or J) separated by spaces."<<std::endl;
      // Clear fail bit and ignore bad input
      std::cin.clear();
      std::cin.ignore(512,'\n');

      std::cin>>atomic_number>>initial_quantum_number>>final_quantum_number>>units;
    }
    // Compute photon energy
    photon_energy=get_energy_spacing(atomic_number,initial_quantum_number,final_quantum_number);

    if(units=='J'){
      photon_energy*=conversion_e_to_J;
    }
    
    // Output answer
    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    std::cout<<"Photon energy is "
      <<std::setprecision(2)<<photon_energy<<" "<<units<<std::endl;
    
    //Ask if to quit or not
    std::cout<<"Would you like to restart (y) or quit (n)?"<<std::endl;
    std::cin>>response;
    while(std::cin.fail() || (response!='y' && response!='n')) {
    std::cout<<"Sorry, your input was not valid. "; 
    std::cout<<"Would you like to restart (y) or quit (n)?"<<std::endl;
    // Clear fail bit and ignore bad input
    std::cin.clear(); 
    std::cin.ignore(512,'\n'); 
    std::cin>>response;
    }
  }
  return 0;
}