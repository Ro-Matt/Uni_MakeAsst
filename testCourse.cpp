#include "course.h"
#include "unittest.h"
#include <sstream>

using namespace std;


UnitTest(CourseDefaultConstructor) {
	Course c;
	assertThat (c.getName(), isEqualTo(CourseName()));
	assertThat (c.getNumberOfPrereqs(), isEqualTo(0));
	assertThat (c, isEqualTo(Course()));
	assertThat (c, not(isLessThan(Course())));
	assertThat (c, not(isGreaterThan(Course())));
}

UnitTest(CourseConstructor) {
	CourseName cs150 ("CS", 150);
	CourseName math150 ("MATH", 150);
	CourseName cs250 ("CS", 250);
	Course c (cs150);

	assertThat (c.getName(), isEqualTo(cs150));
	assertThat (c.getNumberOfPrereqs(), isEqualTo(0));
	assertThat (c, isNotEqualTo(Course()));
	assertThat (c, isLessThan(Course(math150)));
	assertThat (c, isLessThan(Course(cs250)));

	ostringstream out;
	out << c;
	assertThat (out.str(), contains("CS150"));
}

UnitTest(CourseAddPrereq) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	Course c0(cs350);
	Course c (cs350);
	assertThat (c, isEqualTo(c0));

	c.addPrereq(cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c, isNotEqualTo(c0));
	assertThat (c.getPrereq(0), isEqualTo(cs361));

	c.addPrereq(cs330);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertThat (c.getPrereq(0), isEqualTo(cs361));
	assertThat (c.getPrereq(1), isEqualTo(cs330));

	c.addPrereq(cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertThat (c.getPrereq(0), isEqualTo(cs361));
	assertThat (c.getPrereq(1), isEqualTo(cs330));

	ostringstream out;
	out << c;
	string outStr = out.str();
	assertThat (outStr, contains("CS350"));
	assertThat (outStr, contains("CS330"));
	assertThat (outStr, contains("CS361"));

}

UnitTest(CourseRemovePrereq) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	Course c0(cs350);
	Course c (cs350);
	assertThat (c, isEqualTo(c0));

	c.addPrereq(cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c, isNotEqualTo(c0));
	assertThat (c.getPrereq(0), isEqualTo(cs361));

	c.addPrereq(cs330);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertThat (c.getPrereq(0), isEqualTo(cs361));
	assertThat (c.getPrereq(1), isEqualTo(cs330));

	c.removePrereq(cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c.getPrereq(0), isEqualTo(cs330));

	ostringstream out;
	out << c;
	string outStr = out.str();
	assertThat (outStr, contains("CS350"));
	assertThat (outStr, contains("CS330"));
	assertThat (outStr, not(contains("CS361")));

}

UnitTest(CourseCopy) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	Course c(cs350);
	c.addPrereq(cs361);
	c.addPrereq(cs330);

	Course c2 (c);
	assertThat(c2, isEqualTo(c));

	c2.addPrereq(cs150);
	assertThat(c2, isNotEqualTo(c));

	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertThat (c2.getNumberOfPrereqs(), isEqualTo(3));
	assertThat (c.getPrereq(0), isEqualTo(cs361));
	assertThat (c2.getPrereq(0), isEqualTo(cs361));
	assertThat (c.getPrereq(1), isEqualTo(cs330));
	assertThat (c2.getPrereq(1), isEqualTo(cs330));
	assertThat (c2.getPrereq(2), isEqualTo(cs150));

	c.removePrereq(cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c2.getNumberOfPrereqs(), isEqualTo(3));
	assertThat (c.getPrereq(0), isEqualTo(cs330));
	assertThat (c2.getPrereq(0), isEqualTo(cs361));
	assertThat (c2.getPrereq(1), isEqualTo(cs330));
	assertThat (c2.getPrereq(2), isEqualTo(cs150));
}

UnitTest(CourseAssign) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	Course c(cs350);
	c.addPrereq(cs361);
	c.addPrereq(cs330);

	Course c2;
	Course c3(c2 = c);
	assertThat(c2, isEqualTo(c));
	assertThat(c3, isEqualTo(c));

	c2.addPrereq(cs150);
	assertThat(c2, isNotEqualTo(c));

	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertThat (c2.getNumberOfPrereqs(), isEqualTo(3));
	assertThat (c.getPrereq(0), isEqualTo(cs361));
	assertThat (c2.getPrereq(0), isEqualTo(cs361));
	assertThat (c.getPrereq(1), isEqualTo(cs330));
	assertThat (c2.getPrereq(1), isEqualTo(cs330));
	assertThat (c2.getPrereq(2), isEqualTo(cs150));

	c.removePrereq(cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c2.getNumberOfPrereqs(), isEqualTo(3));
	assertThat (c.getPrereq(0), isEqualTo(cs330));
	assertThat (c2.getPrereq(0), isEqualTo(cs361));
	assertThat (c2.getPrereq(1), isEqualTo(cs330));
	assertThat (c2.getPrereq(2), isEqualTo(cs150));


}

UnitTest(zzCheckForMemoryLeaks) {
	assertThat(MemoryChecked::getCurrentCount(), isEqualTo(0));
}


