#include "Book.h"

using namespace std;

book::book()
{
	ISBN = "None";
	title = "None";
	author = "None";
	date = "0";
	newPrice = -1;
	usedPrice = -1;
	rentPrice = -1;
	ePrice = -1;
	lowestPrice = -1;
	highestPrice = -1;
	courseName = "None";
	courseNum = "None";
	sectionNum = "None";
	deptNum = "None";
	edition = 0;
	month = 0;
	year = 0;
}

//Setter functions
void book::setISBN(string nISBN)
{
	ISBN = nISBN;
}
void book::setTitle(string ntitle)
{
	title = ntitle;
}
void book::setAuthor(string nauthor)
{
	author = nauthor;
}
void book::setDate(string ndate)
{
	date = ndate;
}
void book::setNewPrice(double nprice)
{
	newPrice = nprice;
}
void book::setUsedPrice(double nprice)
{
	usedPrice = nprice;
}
void book::setRentPrice(double nprice)
{
	rentPrice = nprice;
}
void book::setEPrice(double nprice)
{
	ePrice = nprice;
}
void book::setCourseName(string ncourseName)
{
	courseName = ncourseName;
}
void book::setCourseNum(string ncourseNum)
{
	courseNum = ncourseNum;
}
void book::setDeptNum(string ndeptNum)
{
	deptNum = ndeptNum;
}
void book::setEdition(int nedition)
{
	edition = nedition;
}
void book::setDeptCode(string nDeptCode)
{
	deptCode = nDeptCode;
}
void book::setRequired(string nRequired)
{
	required = nRequired;
}
void book::setMonth(int nMonth) 
{
	month = nMonth;
}
void book::setYear(int nYear)
{
	year = nYear;
}

void book::setSectionNum(string nSectionNum)
{
	sectionNum = nSectionNum;
}

void book::setLowestPrice(double nprice)
{
	lowestPrice = nprice;
}

void book::setHighestPrice(double nprice)
{
	highestPrice = nprice;
}

//Getter functions
string book::getISBN()
{
	return ISBN;
}
string book::getTitle()
{
	return title;
}
string book::getDate()
{
	return date;
}
double book::getNewPrice()
{
	return newPrice;
}
double book::getUsedPrice()
{
	return usedPrice;
}
double book::getRentPrice()
{
	return rentPrice;
}
double book::getEPrice()
{
	return ePrice;
}
double book::getLowestPrice()
{
	return lowestPrice;
}
double book::getHighestPrice()
{
	return highestPrice;
}
string book::getCourseName()
{
	return courseName;
}
string book::getCourseNum()
{
	return courseNum;
}
string book::getSectionNum()
{
	return sectionNum;
}
string book::getAuthor()
{
	return author;
}
string book::getDeptNum()
{
	return deptNum;
}
int book::getEdition()
{
	return edition;
}
string book::getDeptCode()
{
	return deptCode;
}
string book::getRequired()
{
	return required;
}

int book::getMonth()
{
	return month;
}

int book::getYear()
{
	return year;
}
