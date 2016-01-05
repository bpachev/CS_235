#include "GPAInterface.h"
#include "Student.h"
using namespace std;
enum {SID=0,NAME,ADR,PHONE,SGPA};
enum {SGID=0,COURSE_NAME,GRADE};
class GPA : public GPAInterface
{
public:
  ~GPA(void);
  map<unsigned long long int,StudentInterface*> getMap();
  set<StudentInterface*,Comparator> getSet();
  bool importStudents(string mapFileName, string setFileName);
  bool importGrades(string fileName);
  string querySet(string fileName);
  string queryMap(string fileName);
  void clear();
  map<unsigned long long int, StudentInterface*> student_map;
  set<StudentInterface*,Comparator> student_set;
  
};
  
