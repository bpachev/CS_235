#include "GPA.h"
#include <ctype.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#define STATE_MAGIC if(c=='\n') {state++; continue;}
#define LOAD_ERR(err) {cout << err << endl; clear_buf(buf); fclose(f); return false;}

//helper functions
bool load_students(string filename,vector<Student*> &buf);
void clear_buf(vector<Student*> &buf);
void add_to_map(Student* s,GPA* self);
void add_to_set(Student* s,GPA* self);
string set_query_string(StudentInterface* s, GPA* self);
string map_query_string(StudentInterface* s, GPA* self);

bool load_students(string filename,vector<Student*> &buf)
{
  const char* fname = filename.c_str();
  FILE* f = fopen(fname,"r");
  if(!f) 
  {
  //  cout << "bad fname" << endl;
    return false;
  }
  
  char c;
  char fbuf[20];
  string name="";
  string phone="";
  string adr="";
  int ID=0;
  int i=0;
  //double s_GPA = 0.0;
  int state = SID;
  while ((c=fgetc(f))!=EOF)
  {
  //  cout << state << c << endl;
    switch(state)
    {
      case SID:
        STATE_MAGIC
  //      cout <<  "char" << c << endl;
        if (isdigit(c)) ID = ID*10 + c - '0';
        else {LOAD_ERR("Invalid ID")}
        break;
      case NAME:
        STATE_MAGIC
        name += c;
 //       cout << name << endl;
        break;
      case ADR:
        STATE_MAGIC
        adr += c;
        break;
      case PHONE:
        if (c == '\n')
        {
   //       cout << name << endl;
          Student* tempS = new Student(ID,0,name,adr,phone);
          buf.push_back(tempS);
          state = SID;
          name = "";
          phone = "";
          adr = "";
          ID = 0;
          continue;
        }
        phone += c;
        break;
      default:
        break;
    }
  }
  if(state != SID) 
  {
    LOAD_ERR("Not Enough Lines")
  }
  fclose(f);
  return true;
}

void clear_buf(vector<Student*> &buf)
{
  for (int i = 0; i < buf.size(); i++)
  {
    delete buf[i];
  }
  buf.clear();
}

void add_to_map(Student* s,GPA* self)
{
  self->student_map[s->getID()] = s;
}

void add_to_set(Student* s,GPA* self)
{
  self->student_set.insert(s);
}

string set_query_string(unsigned int ID, GPA* self)
{
  stringstream str;
  set<StudentInterface*,Comparator>::iterator i;
  for (i = self->student_set.begin(); i != self->student_set.end(); ++i)
  {
    if((*i)->getID()==ID)
    {
      StudentInterface* s = *i;
      str.precision(2);
      str.setf(ios::fixed,ios::floatfield);
      str << ID << " " << s->getGPA() << " " << s->getName() << "\n";
      return str.str();
    }
  }

  return str.str();  
}

string map_query_string(unsigned int ID, GPA* self)
{
  if(self->student_map.find(ID) == self->student_map.end()) return "";
  StudentInterface* s = self->student_map[ID];
  stringstream str;
  str.precision(2);
  str.setf(ios::fixed,ios::floatfield);
  str << ID << " " << s->getGPA() << " " << s->getName() << "\n";
  return str.str();
}


//member functions


GPA::~GPA()
{
  map<unsigned long long int,StudentInterface*>::iterator it;
  for (it = student_map.begin(); it!=student_map.end(); ++it)
  {
    delete it->second;
  }
  
  set<StudentInterface*,Comparator>::iterator i;
  for (i = student_set.begin(); i != student_set.end(); ++i)
  {
    delete *i;
  }
}

map<unsigned long long int,StudentInterface*> GPA::getMap()
{
  return student_map; 
}

set<StudentInterface*,Comparator> GPA::getSet()
{
  return student_set;  
}

bool GPA::importStudents(string mapFileName, string setFileName)
{
//  cout << "Called importSTudents with " << mapFileName << " and " << setFileName << endl;
  vector<Student*> buf_set;
  vector<Student*> buf_map;
  if(!load_students(mapFileName,buf_map)||!load_students(setFileName,buf_set))
  {
    clear_buf(buf_set);
    clear_buf(buf_map);
 //   cout << "didn't upload" << endl;
    return false;
  }
  else
  {
    for (int i = buf_map.size() - 1; i>=0; i--)
    {
      add_to_map(buf_map[i],this);
    }
    
    for (int j = buf_set.size() - 1; j>=0; j--)
    {
      add_to_set(buf_set[j],this);
    }
    
    return true;
  }
}

bool GPA::importGrades(string fileName)
{
  const char* fname = fileName.c_str();
  FILE* f = fopen(fname, "r");  

  if (!f) return false;
  
  int state = SGID;
 /* map<string,int> grades;
  grades["A"] = 40;
  grades["A-"] = 37;	
  grades["B+"] = 34;
  grades["B"] = 30;
  grades["B-"] = 27;
  grades["C+"] = 24;
  grades["C"] = 20;
  grades["C-"] = 17;
  grades["D+"] = 14;
  grades["D"] = 10;
  grades["D-"] = 07;
  grades["E"] = 00; */
  map<string,double> grades;
  grades["A"] = 4.00;
  grades["A-"] = 3.70;	
  grades["B+"] = 3.40;
  grades["B"] = 3.00;
  grades["B-"] = 2.70;
  grades["C+"] = 2.40;
  grades["C"] = 2.00;
  grades["C-"] = 1.70;
  grades["D+"] = 1.40;
  grades["D"] = 1.00;
  grades["D-"] = 0.70;
  grades["E"] = 0.00; 

  char c;
  int ID = 0;
  string g = "";
  while ((c=fgetc(f))!=EOF)
  {
    switch (state)
    {
      case SGID:
       // cout << ID << "id" << endl;
        STATE_MAGIC
        if(isdigit(c)) ID  = 10*ID + c - '0';
        else
        {
          fclose(f);
          return false; 
        }
        break;
      case COURSE_NAME:
        STATE_MAGIC
        break;
      case GRADE:
        if (c == '\n')
        {
          //cout << "Grade " << g << endl;
          if (student_map.find(ID) != student_map.end())
          {
            student_map[ID]->addGPA(grades[g]);
          }
          else
          {
            set<StudentInterface*,Comparator>::iterator i;
            for (i = student_set.begin(); i != student_set.end(); ++i)
            {
              if ((*i)->getID() == ID) {(*i)->addGPA(grades[g]);}
            }

          }

          ID = 0;
          g = "";
          state = SGID;
          continue;
        }
        
        g += c;
        break;
      default:
        break;
    }
  }
  if (ID != 0)
  {
    if (student_map.find(ID) != student_map.end())
    {
      student_map[ID]->addGPA(grades[g]);
    }
    set<StudentInterface*,Comparator>::iterator i;
    for (i = student_set.begin(); i != student_set.end(); ++i)
    {
      if ((*i)->getID() == ID) 
      {
        //cout << "adding " << g << " for " << (*i)->getName() << endl;
        (*i)->addGPA(grades[g]);
        break;
      }
    }
  }
  fclose(f);
  return true;
}

string GPA::querySet(string fileName)
{
  FILE* f = fopen(fileName.c_str(),"r");

  if (!f) return "";

  char c;
  stringstream str;
  unsigned int ID = 0;
  vector<unsigned int> IDS;
  
  while ((c=fgetc(f)) != EOF)
  {
    if (c == '\n')
    {
   //   cout << "adding ID: " << ID << endl; 
      IDS.push_back(ID);
      ID = 0;
      continue;
    }
    
    if (isdigit(c)) ID = 10*ID + c - '0';
    else return "";
  }
  fclose(f);

  for (int i = 0; i < IDS.size(); i++)
  {
    str << set_query_string(IDS[i],this);
  }
  return str.str();
}

string GPA::queryMap(string fileName)
{
  FILE* f = fopen(fileName.c_str(),"r");

  if (!f) return "";

  char c;
  stringstream str;
  unsigned int ID = 0;
  vector<unsigned int> IDS;
  
  while ((c=fgetc(f)) != EOF)
  {
 //    cout << "reading char: " << c << endl;
    if (c == '\n')
    {
 //     cout << "adding ID: " << ID << endl; 
      IDS.push_back(ID);
      ID = 0;
      continue;
    }
    
    if (isdigit(c)) ID = 10*ID + c - '0';
    else return "";
  }
  fclose(f);

  for (int i = 0; i < IDS.size(); i++)
  {
    str << map_query_string(IDS[i],this);
  }
  return str.str();
}

void GPA::clear()
{
  map<unsigned long long int,StudentInterface*>::iterator it;
  for (it = student_map.begin(); it != student_map.end(); ++it)
  {
    delete it->second;
  }
  student_map.clear(); 
  
  set<StudentInterface*,Comparator>::iterator i;
  for (i = student_set.begin(); i != student_set.end(); ++i)
  {
    delete *i;
  }
  student_set.clear();
}
