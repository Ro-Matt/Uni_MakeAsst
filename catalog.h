#ifndef CATALOG_H
#define CATALOG_H

#include "course.h"
#include <iostream>
#include <vector>

/**
 * A University Dept course catalog, with information
 * on courses offered and their pre-requisite structure.
 */
class CourseCatalog {

public:

	typedef std::vector<Course*>::iterator iterator;
	typedef std::vector<Course*>::const_iterator const_iterator;


    /**
     *  Create a new course catalog.
     */
	CourseCatalog();


	CourseCatalog (const CourseCatalog& c);
	~CourseCatalog();
	const CourseCatalog& operator= (const CourseCatalog& cat);


	/**
	 * Provide access to the courses in the catalog.
	 */
	iterator begin() {return coursesOffered.begin();}
	iterator end() {return coursesOffered.end();}

	const_iterator begin() const {return coursesOffered.begin();}
	const_iterator end() const {return coursesOffered.end();}


	/**
	 * Adds a pair of courses to the catalog if they have not previously been
	 * encountered, and records that one course is an immediate pre-requisite
	 * of the other.
	 *
	 * @param course1  a course, possibly never seen before
	 * @param prereqOfC1  another course that is an immediate pre-requisite
	 *                    of this one.
	 */
	void addCourses (
			const CourseName& course1,
			const CourseName& prereqOfCourse1);

	/**
	 * Remove a course from the catalog, including any
	 * relationships in which it enables other courses.
	 */
	void removeCourse (const CourseName& c);

	/**
	 * See if a course is already in the catalog.
	 *
	 * @param cname name of a course
	 * @return true iff cname is in the catalog
	 */
	bool containsCourse (const CourseName& cname) const;

	/**
	 * Fetch a course by name.
	 * @param cname a course name
	 * @return the course with that name, or nullptr if no such course is
	 *     in the catalog.
	 */
	Course* getCourse (const CourseName& cname);
	const Course* getCourse (const CourseName& cname) const;


	/**
	 * Read a catalog from an input stream.
	 *
	 * Input is repeated lines of
	 *
	 *   course prereq1OfCourse prereq2OfCourse ...
	 *
	 * @param input the input stream
	 */
	void read (istream& input);


	bool operator== (const CourseCatalog& right) const;

private:

	/**
	 * All of the courses offered by this Dept or
	 * required as part of their degree program.
	 */
	std::vector<Course*> coursesOffered;

	Course* findOrAdd (const CourseName& cname);
	CourseName parseCourseName (string combined);


};

std::ostream& operator<< (std::ostream& out, const CourseCatalog& cat);

#endif
