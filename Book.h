#pragma once
#include <string>

using namespace std;

class book
{
private:
	string ISBN;
	string title;
	string author;
	string date;
	double newPrice;
	double usedPrice;
	double rentPrice;
	double ePrice;
	double lowestPrice;
	double highestPrice;
	string courseName;
	string courseNum;
	string sectionNum;
	string deptNum;
	string deptCode;
	string required;
	int edition;
	int month;
	int year;
public:
	book();

	//Setter functions
	void setISBN(string nISBN);
	void setTitle(string ntitle);
	void setAuthor(string nauthor);
	void setDate(string ndate);
	void setNewPrice(double nprice);
	void setUsedPrice(double nprice);
	void setRentPrice(double nprice);
	void setEPrice(double nprice);
	void setCourseName(string ncourseName);
	void setCourseNum(string ncourseNum);
	void setDeptNum(string ndeptNum);
	void setEdition(int nedition);
	void setDeptCode(string nDeptCode);
	void setRequired(string nRequired);
	void setMonth(int nMonth);
	void setYear(int nYear);
	void setSectionNum(string nSectionNum);
	void setLowestPrice(double nprice);
	void setHighestPrice(double nprice);

	//Getter functions
	string getISBN();
	string getTitle();
	string getDate();
	double getNewPrice();
	double getUsedPrice();
	double getRentPrice();
	double getEPrice();
	double getLowestPrice();
	double getHighestPrice();
	string getCourseName();
	string getCourseNum();
	string getSectionNum();
	string getDeptNum();
	int getEdition();
	string getDeptCode();
	string getRequired();
	int getMonth();
	int getYear();
	string getAuthor();
};