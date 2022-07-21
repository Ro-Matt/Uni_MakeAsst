#include "catalog.h"
#include "unittest.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;


UnitTest(CatalogConstructor) {
	CourseCatalog cat;
	assertThat (cat.end(), isEqualTo(cat.begin()));
}

UnitTest(CatalogAddCourse) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	CourseCatalog cat;
	cat.addCourses(cs250, cs150);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(2));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertFalse(cat.containsCourse(cs361));
	assertFalse(cat.containsCourse(cs330));
	assertFalse(cat.containsCourse(cs350));

	set<CourseName> expected1 {cs150, cs250};
	set<CourseName> observed1;
	transform(cat.begin(), cat.end(), inserter(observed1, observed1.begin()),
			[] (Course* c) {return c->getName();});
	assertThat(observed1, isEqualTo(expected1));

	cat.addCourses(cs350, cs361);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(4));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertFalse(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

	set<CourseName> expected2 {cs150, cs250, cs361, cs350};
	set<CourseName> observed2;
	transform(cat.begin(), cat.end(), inserter(observed2, observed2.begin()),
			[] (Course* c) {return c->getName();});
	assertThat(observed2, isEqualTo(expected2));

	cat.addCourses(cs350, cs330);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(5));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertTrue(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

	cat.addCourses(cs330, cs250);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(5));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertTrue(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

	cat.addCourses(cs361, cs250);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(5));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertTrue(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

	set<CourseName> expected3 {cs150, cs250, cs330, cs361, cs350};
	set<CourseName> observed3;
	transform(cat.begin(), cat.end(), inserter(observed3, observed3.begin()),
			[] (Course* c) {return c->getName();});
	assertThat(observed3, isEqualTo(expected3));

	auto c = cat.getCourse(cs250);
    assertThat (c->getName(), isEqualTo(cs250));
    assertThat(c->getNumberOfPrereqs(), isEqualTo(1));

    c = cat.getCourse(cs350);
    assertThat (c->getName(), isEqualTo(cs350));
    assertThat(c->getNumberOfPrereqs(), isEqualTo(2));

}

UnitTest(CatalogRemoveCourse) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	CourseCatalog cat;
	cat.addCourses(cs250, cs150);
	cat.addCourses(cs350, cs361);
	cat.addCourses(cs350, cs330);
	cat.addCourses(cs330, cs250);
	cat.addCourses(cs361, cs250);

	cat.removeCourse(cs330);

	assertThat (distance(cat.begin(), cat.end()), isEqualTo(4));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertFalse(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

    auto c = cat.getCourse(cs350);
    assertThat (c->getName(), isEqualTo(cs350));
    assertThat(c->getNumberOfPrereqs(), isEqualTo(1));
}

UnitTest(CatalogCopy) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	CourseCatalog cat;
	cat.addCourses(cs250, cs150);
	cat.addCourses(cs350, cs361);
	cat.addCourses(cs350, cs330);
	cat.addCourses(cs330, cs250);
	cat.addCourses(cs361, cs250);

	CourseCatalog cat2 (cat);

	assertThat(cat2, isEqualTo(cat));

	cat.removeCourse(cs330);

	assertThat(cat2, isNotEqualTo(cat));

	assertThat (distance(cat2.begin(), cat2.end()), isEqualTo(5));
	assertTrue(cat2.containsCourse(cs150));
	assertTrue(cat2.containsCourse(cs250));
	assertTrue(cat2.containsCourse(cs361));
	assertTrue(cat2.containsCourse(cs330));
	assertTrue(cat2.containsCourse(cs350));

    auto c = cat2.getCourse(cs350);
    assertThat (c->getName(), isEqualTo(cs350));
    assertThat(c->getNumberOfPrereqs(), isEqualTo(2));
}



UnitTest(CatalogAssign) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	CourseCatalog cat;
	cat.addCourses(cs250, cs150);
	cat.addCourses(cs350, cs361);
	cat.addCourses(cs350, cs330);
	cat.addCourses(cs330, cs250);
	cat.addCourses(cs361, cs250);

	CourseCatalog cat2;

	CourseCatalog cat3 (cat2 = cat);

	assertThat(cat2, isEqualTo(cat));
	assertThat(cat3, isEqualTo(cat));

	cat.removeCourse(cs330);

	assertThat(cat2, isNotEqualTo(cat));

	assertThat (distance(cat2.begin(), cat2.end()), isEqualTo(5));
	assertTrue(cat2.containsCourse(cs150));
	assertTrue(cat2.containsCourse(cs250));
	assertTrue(cat2.containsCourse(cs361));
	assertTrue(cat2.containsCourse(cs330));
	assertTrue(cat2.containsCourse(cs350));

    auto c = cat2.getCourse(cs350);
    assertThat (c->getName(), isEqualTo(cs350));
    assertThat(c->getNumberOfPrereqs(), isEqualTo(2));
}





UnitTest(CatalogRead) {
	CourseName cs100 ("cs", 100);
	CourseName cs150 ("cs", 150);
	CourseName cs200 ("cs", 200);
	CourseName cs300 ("cs", 300);

	string testIn =
			string("cs100\n") +
			"cs200 cs100\n" +
			"cs300 cs200 cs100\n";
	istringstream in (testIn);
	CourseCatalog cat;
	cat.read(in);

	assertTrue (cat.containsCourse(cs100));
	assertTrue (cat.containsCourse(cs200));
	assertTrue (cat.containsCourse(cs300));
	assertFalse (cat.containsCourse(cs150));

    assertThat(cat.getCourse(cs100)->getNumberOfPrereqs(), isEqualTo(0));
    assertThat(cat.getCourse(cs200)->getNumberOfPrereqs(), isEqualTo(1));
    assertThat(cat.getCourse(cs300)->getNumberOfPrereqs(), isEqualTo(2));

}



