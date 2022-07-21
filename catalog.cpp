#include "catalog.h"

#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;


CourseCatalog::CourseCatalog()
{

}

CourseCatalog::CourseCatalog (const CourseCatalog& cat)
{
	for (const Course* course: cat.coursesOffered)
	{
		coursesOffered.push_back(new Course(*course));
	}
}

CourseCatalog::~CourseCatalog()
{
	for (const Course* course: coursesOffered)
	{
		delete course;
	}
}

const CourseCatalog& CourseCatalog::operator= (const CourseCatalog& cat)
{
	if (&cat != this)
	{
		for (const Course* course: coursesOffered)
		{
			delete course;
		}
		coursesOffered.clear();
		for (const Course* course: cat.coursesOffered)
		{
			coursesOffered.push_back(new Course(*course));
		}
	}
	return *this;
}



void CourseCatalog::read (istream& input)
{
  string line;
  getline (input, line);
  while (input) {
    istringstream in (line);
    string word;
    in >> word;
    CourseName c1 = parseCourseName(word);
    findOrAdd(c1);
    while (in >> word)
      {
    	CourseName c2 = parseCourseName(word);
    	addCourses (c1, c2);
      }
    getline (input, line);
  }
}


/**
 * Adds a pair of courses to the catalog if they have not previously been
 * encountered, and records that one course is an immediate pre-requisite
 * of the other.
 *
 * @param course1  a course, possibly never seen before
 * @param prereqOfC1  another course that is an immediate pre-requisite
 *                    of this one.
 */
void CourseCatalog::addCourses (
        const CourseName& course1,
        const CourseName& prereqOfCourse1)
{
	Course* c1 = findOrAdd(course1);
	Course* c2 = findOrAdd(prereqOfCourse1);
	c1->addPrereq(c2->getName());
}


/**
 * Remove a course from the catalog, including any
 * relationships in which it enables other courses.
 */
void CourseCatalog::removeCourse (const CourseName& c)
{
	for (Course* course: coursesOffered)
	{
		course->removePrereq (c);
	}
	auto pos = find_if(coursesOffered.begin(), coursesOffered.end(),
			[&] (Course* course){return course->getName() == c;});
	if (pos != coursesOffered.end()) {
		delete (*pos);
		coursesOffered.erase(pos);
	}
}


Course* CourseCatalog::getCourse (const CourseName& cname)
{
	for (Course* course: coursesOffered)
	{
		if (course->getName() == cname)
			return course;
	}
	return nullptr;
}

const Course* CourseCatalog::getCourse (const CourseName& cname) const
{
	for (const Course* course: coursesOffered)
	{
		if (course->getName() == cname)
			return course;
	}
	return nullptr;
}

bool CourseCatalog::containsCourse (const CourseName& cname) const {
	return getCourse(cname) != nullptr;
}

Course* CourseCatalog::findOrAdd (const CourseName& cname)
{
	for (Course* c: coursesOffered)
	{
		if (c->getName() == cname)
			return c;
	}
	Course* newCourse = new Course(cname);
	coursesOffered.push_back(newCourse);
	return newCourse;
}



CourseName CourseCatalog::parseCourseName (string combined)
{
  int i = 0;
  while (combined[i] >= 'a')
    ++i;
  string dept = combined.substr(0, i);
  istringstream numIn (combined.substr(i));
  int num;
  numIn >> num;
  return CourseName(dept, num);
}

bool CourseCatalog::operator== (const CourseCatalog& right) const
{
	auto rightItr = right.begin();
	for (Course* c1: coursesOffered)
	{
		if (rightItr == right.end())
			return false;
		if (!(*c1 == *(*rightItr)))
			return false;
		++rightItr;
	}
	return (rightItr == right.end());
}


std::ostream& operator<< (std::ostream& out, const CourseCatalog& cat)
{
	for (const Course* c: cat)
	{
		out << *c << endl;
	}
	return out;
}

ostream& operator<< (ostream& out, const Course& c)
{
	out << c.name << " (";
	for (int i = 0; i < c.numberOfPrerequisites; ++i)
	{
		if (i > 0)
			out << ',';
		out << c.prereqs[i];
	}
	out << ')';
	return out;
}
