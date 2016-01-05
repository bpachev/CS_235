#include "Student.h"
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <sstream>

unsigned long long int Student::getID()
{
  return ID;
}

string Student::getName()
{
  return name;
}

string Student::getGPA()
{
  char buf[32];
  snprintf(buf, sizeof(buf), "%.2f", (double)(s_GPA)/(num_courses));
  return string(buf);
}


void Student::addGPA(double classGrade)
{
  s_GPA += classGrade;
  num_courses++;
/*  if (ID == 562466352) 
  {
    cout.precision(5);
    cout << num_courses << " " << s_GPA <<  " rounded:" << (double)(s_GPA)/(10*num_courses) << endl;
  } */
}



string Student::toString()
{
  char buf1[32];
//  char buf2[32];
  snprintf(buf1, sizeof(buf1), "%llu", ID);
  stringstream str;
  str << string(buf1) << '\n' << name << '\n' << adr << '\n' << phone << '\n';
  if(!s_GPA)
  {
    str << "0.00";
    return str.str();
  }
  str.precision(2);
  str.setf(ios::fixed,ios::floatfield);
  //cout.precision(20);
  //cout.setf(ios::fixed,ios::floatfield);
 // cout << "More precise: "<< (double)(s_GPA)/(num_courses) << endl;
  //cout.precision(2);
  //cout << "Returned: " << (double)(s_GPA)/(num_courses) << endl;
  str << ((double)(s_GPA)/(num_courses));  
  return str.str();
}
