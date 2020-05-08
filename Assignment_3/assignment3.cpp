
// Simple code to store courses using vectors and strings

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<regex>
#include<algorithm>
//This funxtion using regex to find particular characters and return indexes
//I will use this to find arbitrary separators between course number and name
int custom_search(std::string whole_string,std::regex r){
  std::smatch match_object;
  size_t index{0};
  if(std::regex_search(whole_string, match_object,r)){
    index=match_object.position();
  }
  else{
    index=std::string::npos;
  }
  return index;
}
/*
This method is used as a comparator between vector elements
in the sort function. It will sort by names of courses
*/
bool comparator_name(std::string a,std::string b){
  std::regex r{"[^(a-zA-Z0-9)][(a-zA-Z0-9)]"};
  //Get the indexes where the names start
  int a_delimeter_pos{custom_search(a,r)+1};
  int b_delimeter_pos{custom_search(b,r)+1};
  //Substring to get the course names
  std::string a_name{a.substr(a_delimeter_pos)};
  std::string b_name{b.substr(b_delimeter_pos)};
  if(a_name.compare(b_name)<0){
    return true;
  }
  return false;
}
/*
This method is used as a comparator between vector elements
in the sort function. It will sort by codes of courses
*/
bool comparator_code(std::string a,std::string b){
  //The number 4 comes from the degree code length
  if(a[4]<b[4]){
    return true;
  }
  return false;
}

int main()
{
  const std::string degree_code{"PHYS"};
  // Gather list of courses and their codes from user,
  // storing data as a vector of strings
  bool not_finished{true};
  std::ostringstream string_stream;
  std::vector <std::string> all_courses; 
  do
    {
      std::string course_details;
      std::cout<<"Please enter course details as course id followed by some non alphanumeric delimeter followed by a course name. Enter x to finish: "<<std::endl;
      std::getline(std ::cin,course_details);
      //Quit loop
      if(course_details=="x"){
        not_finished=false;
        continue;
      }
      //Search for index of numeric char followed by non alphanumeric
      std::regex r1{"[0-9][^(a-zA-Z0-9)]"};
      int first_delimeter_pos{custom_search(course_details,r1)};
      //Substring to get the course code
      int course_code{std::stoi(course_details.substr(0,first_delimeter_pos+1))};

      //Search for index of non alphanumeric char followed by an alphanumeric
      std::regex r2{"[^(a-zA-Z0-9)][(a-zA-Z0-9)]"};
      int second_delimeter_pos{custom_search(course_details,r2)+1};
      //Substring to get the course name
      std::string course_name{course_details.substr(second_delimeter_pos)};

      //Join everything together
      string_stream<<degree_code<<course_code<<":"<<course_name;
      //Append to end of vector
      all_courses.push_back(string_stream.str());
      //Empty string stream
      string_stream.str("");
    } while(not_finished);

  // Print out full list of courses
  std::cout<<"\nList of courses:"<<std::endl;
  std::cout<<"\n";
  for(auto iterator=all_courses.begin(); iterator!=all_courses.end();iterator++){
    std::cout << *iterator <<std::endl;
  };

  // Extract courses belonging to a certain year
  std::string year_choice;
  std::cout<<"\nPlease enter year: ";
  std::cin>>year_choice;
  std::cout<<"\n";
  for(auto iterator=all_courses.begin(); iterator!=all_courses.end();iterator++){
    std::string current_element{*iterator};
    if((current_element[degree_code.length()])==year_choice[0]){
      std::cout << *iterator <<std::endl;
    }
  };

  std::string sort_option;
  std::cout<<"\nSort by code(c) or name(n): ";
  std::cin>>sort_option;
  if(sort_option=="c"){
    std::sort(all_courses.begin(), all_courses.end(), comparator_code); 
  }
  else if(sort_option=="n"){
    std::sort(all_courses.begin(), all_courses.end(), comparator_name);
  }

  std::cout<<"\nList of sorted courses by ("<<sort_option<<") :"<<std::endl;
  std::cout<<"\n";
  for(auto iterator=all_courses.begin(); iterator!=all_courses.end();iterator++){
    std::cout << *iterator <<std::endl;
  };

  return 0;
}