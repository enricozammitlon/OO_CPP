
// Assignment 1
// Enrico Zammit Lonardelli - 8/02/2020

// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>

// Functions to compute mean and standard deviation
void calculate_mean(double& mean,double* data_points,int number_of_points){
  double summation{0};
  for(int i{};i<number_of_points;i++) 
      summation+= *(data_points+i);
  mean= (1/float(number_of_points))*summation;
}

void calculate_std(double& standard_deviation,double& standard_error,double mean,double* data_points,int number_of_points){
  double summation{0};
  for(int i{};i<number_of_points;i++) 
      summation+= std::pow((*(data_points+i)-mean),2);
  standard_deviation=std::sqrt((1/float((number_of_points-1)))*summation);
  standard_error=standard_deviation/std::sqrt(number_of_points);
}

// Main function
int main()
{
  // Ask user to enter number of data points
  int number_of_values{};
  int number_of_read_values{0};
  // Ask user to enter filename
  std::string name_of_file{};
  std::cout<<"Enter name of file: "<<std::endl;
  std::cin>>name_of_file;
  // Open file and check if successful
  std::ifstream data_file;
  data_file.open(name_of_file);
  if(!data_file.good()) {
    // Print error message and exit
    std::cerr <<"Error: File "<<name_of_file<<" could not be opened."<<std::endl;
    return 1;
  }
  double *data_points; //Holds pointer to array which will hold the data

  // Read data from file, ignoring any additional bad data
  while(!data_file.eof()) {
    //A temporary pointer to an array of a new length
    double *values{new double[number_of_read_values+1]};
    //Iterate over old array and get all the values
    for (int i = 0; i < number_of_read_values; i++)
    {
      values[i]=data_points[i];
    }
    data_file >> values[number_of_read_values];
    if(data_file.fail()) {
      data_file.clear(); // take stream out of fail state
      data_file.ignore(512,'\n'); // ignore unwanted line
      std::cout<<"Warning: Illegal value of charge at line ";
      std::cout<<(number_of_read_values+1)<<std::endl;
      continue;
    }
    //Free memory
    //delete[] data_points;
    //Assign the new pointer to the old one
    data_points=values;
    number_of_read_values+=1;

  }
  // Close file
  data_file.close();
  // Print number of measurements read in
  std::cout<<"Number of valid measurements read in: "<<number_of_read_values<<std::endl;
  // Compute mean
  double mean{0};
  calculate_mean(mean,data_points,number_of_read_values);
  // Compute standard deviation and standard error of mean
  double standard_deviation{0};
  double standard_error{0};
  calculate_std(standard_deviation,standard_error,mean,data_points,number_of_read_values);
  mean*=pow(10,-19);
  standard_deviation*=pow(10,-19);
  standard_error*=pow(10,-19);
  std::cout.setf(std::ios::scientific, std::ios::floatfield);
  std::cout<<"Mean is "<<std::setprecision(4)<<mean<<" C"<<std::endl;
  std::cout<<"Standard error of the mean is "<<std::setprecision(4)<<standard_error<<" C"<<std::endl;
  std::cout<<"Standard deviation of the mean is "<<std::setprecision(4)<<standard_deviation<<" C"<<std::endl;

  // Free memory
  delete[] data_points;
  
  return 0;
}