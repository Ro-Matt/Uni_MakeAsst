#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "course.h"
#include "catalog.h"
#include "memoryChecked.h"

using namespace std;


/**
 * Make a list of courses having no prerequisites,
 * Then remove those courses from the catalog.
 */
vector<CourseName> getCoursesToTake (CourseCatalog& fromCatalog)
{
    vector<CourseName> results;
    for (const Course* course: fromCatalog)
    {
    	if (course->getNumberOfPrereqs() == 0)
    		results.push_back(course->getName());
    }
    for (const CourseName& cname: results)
    {
    	fromCatalog.removeCourse(cname);
    }
    return results;
}

/**
 * List the courses that can be taken in a single semester.
 */
void listSemester (const CourseCatalog& catalog,
					vector<CourseName>& courses,
					int semester)
{
	cout << "Semester " << semester << endl;
	sort (courses.begin(), courses.end());
	for (const CourseName& cname: courses)
	{
		const Course* course = catalog.getCourse(cname);
		cout << "   " << *course << endl;
	}
}

/**
 * Print a possible schedule under which a student can take
 * all courses in a major without violating prerequisite
 * requirements.
 */
void listMajor(CourseCatalog& catalog)
{
	CourseCatalog tempCatalog = catalog;
	int semester = 1;
    while (tempCatalog.begin() != tempCatalog.end())
    {
      vector<CourseName> thisSemester = getCoursesToTake (tempCatalog);
      if (thisSemester.empty())
      {
    	  cout << "No schedule is possible." << endl;
    	  break;
      }
      listSemester (catalog, thisSemester, semester);
      ++semester;
    }
}



int main (int argc, char** argv)
{
	{
		CourseCatalog catalog;
		if (argc > 1)
		{
			ifstream in (argv[1]);
			catalog.read (in);
		}
		else
		{
			catalog.read (cin);
		}
		listMajor (catalog);
	}
  if (MemoryChecked::getCurrentCount() > 0)
  {
	  cout << "**Memory leaks detected: " << MemoryChecked::getCurrentCount()
	  << endl;
  }
  return 0;
 
}
