#include "courseName.h"

#include <iostream>
#include <string>

using namespace std;

CourseName::CourseName ()
: dept(""), num(0)
{
}

CourseName::CourseName (string theDept, int theNum)
  : dept(theDept), num(theNum)
{
}


bool CourseName::operator== (const CourseName& right) const
{
	return dept == right.dept && num == right.num;
}

bool CourseName::operator< (const CourseName& right) const
{
	if (dept != right.dept)
		return dept < right.dept;
	return num < right.num;
}


ostream& operator<< (ostream& out, const CourseName& c)
{
  out << c.dept << c.num;
  return out;
}

