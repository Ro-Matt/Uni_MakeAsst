#include "course.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using namespace std;


//	CourseName name;
//	int numberOfPrerequisites;
//	int maxPrerequisites;
//	CourseName * prereqs;

/**
 * Create a new course named CourseName() and having no
 * known prerequisites;
 */
Course::Course()
: name(), numberOfPrerequisites(0), maxPrerequisites(0), prereqs(nullptr)
{

}

/**
 * Create a new course named cname and having no
 * known prerequisites;
 */
Course::Course (const CourseName& cname)
: name(cname), numberOfPrerequisites(0), maxPrerequisites(10),
  prereqs(new CourseName[maxPrerequisites])
{

}


/**
 * @return the number of known prerequisites to this course.
 */
int Course::getNumberOfPrereqs() const
{
	return numberOfPrerequisites;
}

/**
 * Adds cname to the list of prerequisites for this course.
 * If this name is already in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */
void Course::addPrereq(const CourseName& cname)
{
	for (int i = 0; i < numberOfPrerequisites; ++i)
		if (prereqs[i] == cname)
			return;
	assert (numberOfPrerequisites < maxPrerequisites);
	prereqs[numberOfPrerequisites] = cname;
	++numberOfPrerequisites;
}

/**
 * Removes cname from the list of prerequisites for this course.
 * If this name is not in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */
void Course::removePrereq(const CourseName& cname)
{
	for (int i = 0; i < numberOfPrerequisites; ++i)
		if (prereqs[i] == cname)
		{
			for (int j = i+1; j < numberOfPrerequisites; ++j)
				prereqs[j-1] = prereqs[j];
			--numberOfPrerequisites;
			break;
		}
}

/**
 * Get the name of the i_th prerequisite.
 *
 * @precondition 0 <= i && i < getNumberofPrereqs()
 * @param i index of the prerequisite to retrieve
 * @return name of the prerequisite course
 */
CourseName Course::getPrereq(int i) const
{
	assert (i >= 0 && i < numberOfPrerequisites);
	return prereqs[i];
}

/**
 * Compare two courses for equality.
 */
bool Course::operator== (const Course& right) const
{
	using namespace std::rel_ops;

	if (name != right.name)
		return false;
	if (numberOfPrerequisites != right.numberOfPrerequisites)
		return false;
	for (int i = 0; i < numberOfPrerequisites; ++i)
		if (prereqs[i] != right.prereqs[i])
			return false;
	return true;
}

/**
 * Compare two courses for ordering.
 */
bool Course::operator< (const Course& right) const
{
	using namespace std::rel_ops;

	if (name != right.name)
		return name < right.name;
	if (numberOfPrerequisites != right.numberOfPrerequisites)
		return numberOfPrerequisites < right.numberOfPrerequisites;
	for (int i = 0; i < numberOfPrerequisites; ++i)
		if (prereqs[i] != right.prereqs[i])
			return prereqs[i] < right.prereqs[i];
	return false;
}



Course::Course (const Course& c)
: name(c.name), numberOfPrerequisites(c.numberOfPrerequisites),
  maxPrerequisites(c.maxPrerequisites)
{
	prereqs = new CourseName[maxPrerequisites];
	for (int i = 0; i < numberOfPrerequisites; ++i)
		prereqs[i] = c.prereqs[i];
}

Course::~Course()
{
	delete [] prereqs;
}


const Course& Course::operator= (const Course& c)
{
	if (&c != this)
	{
		name = c.name;
		numberOfPrerequisites = c.numberOfPrerequisites;
		maxPrerequisites = c.maxPrerequisites;
		delete [] prereqs;
		prereqs = new CourseName[maxPrerequisites];
		for (int i = 0; i < numberOfPrerequisites; ++i)
			prereqs[i] = c.prereqs[i];
	}
	return *this;
}
