#include "StudentInterface.h"


class Student : public StudentInterface
{
public:
  Student(unsigned long long int i, double g, string n, string a, string p): ID(i), s_GPA(g), name(n), adr(a), phone(p), num_courses(0)
  {}
  unsigned long long int getID();
  string getName();
  string getGPA();
  void addGPA(double classGrade);
  string toString();

  unsigned long long int ID;
  //int s_GPA;
  double s_GPA;
  string name;
  string adr;
  string phone;
  int num_courses;
};
