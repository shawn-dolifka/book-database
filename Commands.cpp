#include "Commands.h"
#include "Course.h"
#include "Book.h"

using namespace std;

vector<book> library;
vector<course> courses;

void commands(string input)
{
	//Determine the command entered in the line by the first 1-2 characters
	vector<char> vCommand;
	for (int i = 0; i < 2; i++)
	{
		vCommand.push_back(input[i]);
	}
	string sCommand(vCommand.begin(), vCommand.end());
	sCommand.erase(remove(sCommand.begin(), sCommand.end(), ' '), sCommand.end());

	//List of the Regex patterns, with 'p' meaning "pattern"
	regex pIBSN { R"(\d\d\d\d\d\d\d\d\d\d\d\d\d)" };
	regex pDeptCode { R"([A-Z][A-Z][A-Z][A-Z])" };
	regex pPrice { R"(\d+\.\d\d)" };
	regex pTitle { R"([A-Z]\w.+)" };
	regex pAuthor { R"([A-Z]\w.+)" };
	regex pCourseName { R"([A-Z][a-z]\w.+)" };
	regex pCourseNum{ R"(\b\d\d\d\b)" };
	regex pSectionNum{ R"(\b\d\d\d\b\s[OR])" };
	//Extra section number pattern for the GS Command
	regex pSectionNum2{ R"(\b\d\d\d\b\n)" };
	regex pDate{ R"([0-9][0-9]\/[0-9][0-9][0-9][0-9])" };
	regex pMonth{ R"(\d\d(?=[/]))" };
	regex pYear{ R"(\b\d\d\d\d\b)" };

	//List of the matches
	smatch ISBNmatch;
	smatch deptCodeMatch;
	smatch priceMatch;
	smatch titleMatch;
	smatch authorMatch;
	smatch courseNameMatch;
	smatch courseNumMatch;
	smatch sectionNumMatch;
	smatch dateMatch;
	smatch monthMatch;
	smatch yearMatch;
	

	//Variables to contain the matches
	string ISBN;
	string deptCode;
	double price;
	string title;
	string author;
	string courseName;
	string courseNum;
	string sectionNum;
	string date;
	string monthS;
	string yearS;
	int month;
	int year;

	//Create a new book
	if (sCommand == "B")
	{
		string to_search = input;
		//Format is regex_search(to_search, smatch, pattern)
		regex_search(to_search, titleMatch, pTitle);
		regex_search(to_search, ISBNmatch, pIBSN);
		title = titleMatch[0];
		ISBN = ISBNmatch[0];
		book newBook;
		newBook.setISBN(ISBN);
		newBook.setTitle(title);
		library.push_back(newBook);
	}
	//Assign details to a book
	else if (sCommand == "D")
	{
		regex subCommand{ R"([AE])" };
		//Create a special regex for D sub-command to prevet matching with D main command
		regex subCommandD{ R"([D](?=\s\d\d[/]))" };
		smatch subMatch;
		smatch subMatchD;
		string subLetter;
		string subLetterD;
		string to_search = input;
		string to_searchD = input;
		regex_search(to_search, ISBNmatch, pIBSN);
		regex_search(to_search, subMatch, subCommand);
		regex_search(to_searchD, subMatchD, subCommandD);
		ISBN = ISBNmatch[0];
		subLetter = subMatch[0];
		subLetterD = subMatchD[0];

		//Actions for the characteristics of the book
		//A is for Author
		if (subLetter == "A")
		{
			regex_search(to_search, authorMatch, pAuthor);
			author = authorMatch[0];
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setAuthor(author);
				}
			}
		}
		//E is for book Edition
		else if (subLetter == "E")
		{
			regex pEdition{ R"(\b[1-9]+[\n])" };
			smatch editionMatch;
			string edition = editionMatch[0];
			edition.erase(std::remove(edition.begin(), edition.end(), '\n'), edition.end());
			int editionNum;
			regex_search(to_search, editionMatch, pEdition);
			cout << "This is edition " << edition << endl;
			editionNum = stoi(edition);
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setEdition(editionNum);
				}
			}
		}
		//D is for book Date of Publication
		else if (subLetterD == "D")
		{
			regex pDate{ R"([0-9][0-9]\/[0-9][0-9][0-9][0-9])" };
			regex_search(to_search, dateMatch, pDate);
			date = dateMatch[0];
			string to_search = date;
			regex_search(to_search, monthMatch, pMonth);
			regex_search(to_search, yearMatch, pYear);
			monthS = monthMatch[0];
			yearS = yearMatch[0];
			month = stoi(monthS);
			year = stoi(yearS);
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setDate(date);
					i->setMonth(month);
					i->setYear(year);
				}
			}
		}
		else
		{
			cout << "Invalid command for D." << endl;
		}
	}
	//Assign a price to a book
	else if (sCommand == "M")
	{
		string to_search = input;
		string sPrice;
		string subLetter;
		regex_search(to_search, ISBNmatch, pIBSN);
		ISBN = ISBNmatch[0];
		regex_search(to_search, priceMatch, pPrice);
		sPrice = priceMatch[0];
		price = stod(sPrice);
		regex subCommand{ R"([NURE])" };
		smatch subMatch;
		regex_search(to_search, subMatch, subCommand);
		subLetter = subMatch[0];
		if (subLetter == "N")
		{
			//This price is for the New version
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setNewPrice(price);
				}
			}
		}
		else if (subLetter == "U")
		{
			//This price is for the Used version
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setUsedPrice(price);
				}
			}
		}
		else if (subLetter == "R")
		{
			//This price is for the Rental version
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setRentPrice(price);
				}
			}
		}
		else if (subLetter == "E")
		{
			//This price is for the E-Book version
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setEPrice(price);
				}
			}
		}
		else
		{
			cout << "Invalid command for M." << endl;
		}
	}
	//Create a new course
	else if (sCommand == "C")
	{
		string to_search = input;
		regex_search(to_search, deptCodeMatch, pDeptCode);
		deptCode = deptCodeMatch[0];
		regex_search(to_search, courseNumMatch, pCourseNum);
		courseNum = courseNumMatch[0];
		regex_search(to_search, courseNameMatch, pCourseName);
		courseName = courseNameMatch[0];
		course newCourse;
		newCourse.setCourseNameC(courseName);
		newCourse.setCourseNumC(courseNum);
		newCourse.setDeptNumC(deptCode);
		courses.push_back(newCourse);

	}
	//Assign a book to a course
	else if (sCommand == "A")
	{
		string to_search = input;
		string subLetter;
		regex_search(to_search, ISBNmatch, pIBSN);
		ISBN = ISBNmatch[0];
		regex_search(to_search, deptCodeMatch, pDeptCode);
		deptCode = deptCodeMatch[0];
		regex_search(to_search, courseNumMatch, pCourseNum);
		courseNum = courseNumMatch[0];
		regex_search(to_search, sectionNumMatch, pSectionNum);
		sectionNum = sectionNumMatch[0];
		//Removes the extra Space, R and O charaters caught by the Course Number Regex pattern. 
		sectionNum.erase(remove(sectionNum.begin(), sectionNum.end(), ' '), sectionNum.end());
		sectionNum.erase(remove(sectionNum.begin(), sectionNum.end(), 'R'), sectionNum.end());
		sectionNum.erase(remove(sectionNum.begin(), sectionNum.end(), 'O'), sectionNum.end());
		regex subCommand{ R"([RO])" };
		smatch subMatch;
		regex_search(to_search, subMatch, subCommand);
		subLetter = subMatch[0];
		if (subLetter == "R")
		{
			//Make this book labeled Required
			int vIndex = 0;
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setDeptCode(deptCode);
					i->setCourseNum(courseNum);
					i->setSectionNum(sectionNum);
					i->setRequired("Required");
					for (auto ii = courses.begin(); ii != courses.end(); ++ii)
					{
						if ((i->getDeptCode() == ii->getDeptCodeC()) && (i->getCourseNum() == ii->getCourseNumC()))
						{
							ii->setTextbook(i[vIndex]);
						}
					}
				}
				vIndex++;
			}
		}
		else if (subLetter == "O")
		{
			//Make this book labeled Optional
			int vIndex = 0;
			for (auto i = library.begin(); i != library.end(); ++i)
			{
				if (i->getISBN() == ISBN)
				{
					i->setDeptCode(deptCode);
					i->setCourseNum(courseNum);
					i->setSectionNum(sectionNum);
					i->setRequired("Optional");
					for (auto ii = courses.begin(); ii != courses.end(); ++ii)
					{
						if ((i->getDeptCode() == ii->getDeptCodeC()) && (i->getCourseNum() == ii->getCourseNumC()))
						{
							ii->setTextbook(i[vIndex]);
						}
					}
				}
				vIndex++;
			}
		}
		else
		{
			cout << "Invalid command for A." << endl;
		}
	}
	//Print the books required and optional for a given course
	else if (sCommand == "GC")
	{
		string to_search = input;
		regex_search(to_search, deptCodeMatch, pDeptCode);
		deptCode = deptCodeMatch[0];
		regex_search(to_search, courseNumMatch, pCourseNum);
		courseNum = courseNumMatch[0];
		cout << "These books are required and optional for " << deptCode << " " << courseNum << endl;
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			if ((i->getDeptCode() == deptCode) && (i->getCourseNum() == courseNum))
			{
				cout << i->getTitle() << endl;
			}
		}
		cout << endl;
	}
	//Print required and optional books for a given course and section number
	else if (sCommand == "GS")
	{
		string to_search = input;
		regex_search(to_search, deptCodeMatch, pDeptCode);
		deptCode = deptCodeMatch[0];
		regex_search(to_search, courseNumMatch, pCourseNum);
		courseNum = courseNumMatch[0];
		regex_search(to_search, sectionNumMatch, pSectionNum2);
		sectionNum = sectionNumMatch[0];
		sectionNum.erase(remove(sectionNum.begin(), sectionNum.end(), '\n'), sectionNum.end());
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			if ((i->getDeptCode() == deptCode) && (i->getCourseNum() == courseNum) && (i->getSectionNum() == sectionNum))
			{
				cout << "These books are optional for the given course: " << endl;
				cout << i->getTitle()  << endl;
			}
		}

	}
	//Print all information known about a book
	else if (sCommand == "GB")
	{
		string to_search = input;
		regex_search(to_search, ISBNmatch, pIBSN);
		ISBN = ISBNmatch[0];
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			if (i->getISBN() == ISBN)
			{
				cout << "This is all of the information known." << endl << endl;
				cout << "This is the ISBN: " << i->getISBN() << endl;
				cout << "This is the title: " << i->getTitle() << endl;
				cout << "This is the author: " << i->getAuthor() << endl;
				cout << "This is the date of publication : " << i->getDate() << endl;
				cout << "This is the new price: " << i->getNewPrice() << endl;
				cout << "This is the used price: " << i->getUsedPrice() << endl;
				cout << "This is the rental price: " << i->getRentPrice() << endl;
				cout << "This is the electronic price: " << i->getEPrice() << endl;
				cout << "This is the edition: " << i->getEdition() << endl;
				cout << endl << "This is the end of the information known." << endl << endl;

			}
		}
	}
	//Print a list of all the defined books
	else if (sCommand == "PB")
	{
		cout << "These are all of the defined books " << endl;
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			if (i->getISBN() != "")
			{
				cout << i->getTitle() << endl;
			}
		}
		cout << endl;
	}
	//Print a list of all the defined courses
	else if (sCommand == "PC")
	{
		cout << "These are all of the defined courses " << endl;
for (auto i = courses.begin(); i != courses.end(); ++i)
{
	if (i->getCourseNameC() != "")
	{
		cout << i->getCourseNameC() << endl;
	}
}
cout << endl;
	}
	//Print all books with known publication dates in the given Month/Year or later
	else if (sCommand == "PY")
	{
		string to_search = input;
		regex_search(to_search, dateMatch, pDate);
		date = dateMatch[0];
		//Search for the month and year to compare
		string to_search2 = date;
		regex_search(to_search2, monthMatch, pMonth);
		regex_search(to_search2, yearMatch, pYear);
		monthS = monthMatch[0];
		yearS = yearMatch[0];
		month = stoi(monthS);
		year = stoi(yearS);
		cout << "These books have a publication date on or after " << date << endl;
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			if (i->getDate() == date)
			{
				cout << i->getTitle() << endl;
			}
			else if (i->getYear() >= year)
			{
				cout << i->getTitle() << endl;
			}
			else if ((i->getYear() == year) && (i->getMonth() >= month))
			{
				cout << i->getTitle() << endl;
			}
		}
		cout << endl;

	}
	//Print all textbooks used in a department
	else if (sCommand == "PD")
	{
		string to_search = input;
		regex_search(to_search, deptCodeMatch, pDeptCode);
		deptCode = deptCodeMatch[0];
		cout << "These are all of the textbook used in the " << deptCode << " department." << endl;
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			if (i->getDeptCode() == deptCode)
			{
				cout << i->getTitle() << endl;
			}
		}
		cout << endl;
	}
	//Calculate the average minimum and maximum of the books across all departments
	else if (sCommand == "PM")
	{

		string to_search = input;
		regex_search(to_search, deptCodeMatch, pDeptCode);
		deptCode = deptCodeMatch[0];
		vector<string> sections;
		vector<double> prices1, prices2;
		vector<double> lowprices;
		vector<double> hiprices;
		//Get a vector of all the sections, then delete duplicate sections
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			sections.push_back(i->getSectionNum());
		}
		sections.erase(unique(sections.begin(), sections.end()), sections.end());
		sort(sections.begin(), sections.end());
		//Find the lowest prices of the textbooks
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			if ((i->getNewPrice() > 0) && (i->getRequired() == "Required"))
			{
				prices1.push_back(i->getNewPrice());
			}
			if ((i->getUsedPrice() > 0) && (i->getRequired() == "Required"))
			{
				prices1.push_back(i->getUsedPrice());
			}
			if ((i->getRentPrice()) > 0 && (i->getRequired() == "Required"))
			{
				prices1.push_back(i->getRentPrice());
			}
			if ((i->getEPrice()) > 0 && (i->getRequired() == "Required"))
			{
				prices1.push_back(i->getEPrice());
			}
			sort(prices1.begin(), prices1.end());
			i->setLowestPrice(prices1.front());
		}

		//Find the highest price of the textbooks
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			if (i->getNewPrice() > 0)
			{
				prices2.push_back(i->getNewPrice());
			}
			if (i->getUsedPrice() > 0)
			{
				prices2.push_back(i->getUsedPrice());
			}
			if (i->getRentPrice() > 0)
			{
				prices2.push_back(i->getRentPrice());
			}
			if (i->getEPrice() > 0 )
			{
				prices2.push_back(i->getEPrice());
			}
			sort(prices2.begin(), prices2.end());
			i->setHighestPrice(prices2.back());
		}
		
		//Calculate minimum prices
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			double costLow = 0;
			int priceCount = 0;
			for (int x = 0; x < sections.size(); x++)
			{
				if ((i->getSectionNum() == sections[x]) && (i->getLowestPrice() > 0))
				{
					costLow = costLow + i->getLowestPrice();
					priceCount++;
				}
			}
			if (priceCount == 0)
			{
				break;
			}
			lowprices.push_back(costLow/priceCount);
		}

		//Calculate maximum prices
		for (auto i = library.begin(); i != library.end(); ++i)
		{
			double costHi = 0;
			int priceCount = 0;
			for (int x = 0; x < sections.size(); x++)
			{
				if ((i->getSectionNum() == sections[x]) && (i->getHighestPrice() > 0))
				{
					costHi = costHi + i->getHighestPrice();
					priceCount++;
				}
			}
			if (priceCount == 0)
			{
				break;
			}
			hiprices.push_back(costHi/priceCount);
		}

		for (int i = 0; i < sections.size(); i++)
		{
			cout << "Section " << sections[i] << " lowest average is " << lowprices[i] << endl;
			cout << "Section " << sections[i] << " highest average is " << hiprices[i] << endl;
		}
		
		//Access object method inside vector
		/*
		for (auto c: courses)
		{
			c.textbook.getISBN();
		}
		*/

		//Calculate the minimum price across all sections
		double lowMean = 0;
		for (int i = 0; i < lowprices.size(); i++)
		{
			lowMean = lowMean + lowprices[i];
		}
		lowMean = lowMean / lowprices.size();
		cout << "The average minimum across all sections is " << lowMean << endl;

		//Calculate the maximum price across all sections
		double hiMean = 0;
		for (int i = 0; i < hiprices.size(); i++)
		{
			hiMean = hiMean + hiprices[i];
		}
		hiMean = hiMean / hiprices.size();
		cout << "The average maximum across all sections is " << hiMean << endl;
	}
	else
	{
		cout << "Not a command" << endl;
	}

}

