#pragma once
#include <string>
#include <vector>
#include "Book.h"

using namespace std;

class course
{
private:
	string courseNameC;
	string courseNumC;
	string deptNumC;
	string sectionNumC;
	string deptCodeC;
	
	
public:
	book textbook;
	course();

	//Setter functions
	void setCourseNameC(string ncourseNameC);
	void setCourseNumC(string ncourseNumC);
	void setDeptNumC(string ndeptNumC);
	void setSectionNumC(string nsectionNumC);
	void setDeptCodeC(string nDeptCodec);
	void setTextbook(book nTextbook);

	//Getter functions
	string getCourseNameC();
	string getCourseNumC();
	string getDeptNumC();
	string getSectionNumC();
	string getDeptCodeC();
	book getTextbook();
};
