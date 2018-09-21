#include "Course.h"
#include "Book.h"

using namespace std;

course::course()
{
	courseNameC = "";
	courseNumC = "";
	deptNumC = "";
	sectionNumC = "";
}

//Setter functions
void course::setCourseNameC(string ncourseNameC)
{
	courseNameC = ncourseNameC;
}
void course::setCourseNumC(string ncourseNumC)
{
	courseNumC = ncourseNumC;
}
void course::setDeptNumC(string ndeptNumC)
{
	deptNumC = ndeptNumC;
}
void course::setSectionNumC(string nsectionNumC)
{
	sectionNumC = nsectionNumC;
}
void course::setDeptCodeC(string nDeptCodec)
{
	deptCodeC = nDeptCodec;
}
void course::setTextbook(book nTextbook)
{
	textbook = nTextbook;
}

//Getter functions
string course::getCourseNameC()
{
	return courseNameC;
}
string course::getCourseNumC()
{
	return courseNumC;
}
string course::getDeptNumC()
{
	return deptNumC;
}
string course::getSectionNumC()
{
	return sectionNumC;
}
string course::getDeptCodeC()
{
	return deptCodeC;
}

book course::getTextbook()
{
	return textbook;
}
