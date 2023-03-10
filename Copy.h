#include <iostream>
#include <fstream>
class Copy
{
private:
	//copy.txt file format:
	//ISBN ID Title Author Category Reader's_Name Start_Date_of_borrowing_period Expiration_Date

	//data attributes for book
	int ISBN{};// ISBN of the book (unique to other books)
	int ID{};// ID of the book (unique to the other books of the same ISBN)
	string title{};// title of the book
	string author{};// author of the book
	string category{};// category the book is in
	string readerName{};// the name of the reader who checked out the book
	int checkOut{};// the date the book was checked out at
	int expiration{};// the date that the book becomes overdue

public:
	//constructors
	Copy();
	Copy(int ISBN, int ID, string title, string author, string category, string readerName, int checkOut, int expiration);

	//overload operators with access to information of the object and file to input and output information
	friend istream& operator >> (istream& copyFile, Copy& copyObj);
	friend ostream& operator << (ostream& copyFile, Copy& copyObj);

	//accessor methods
	int getISBN();
	int getID();
	string getTitle();
	string getAuthor();
	string getCategory();
	string getReaderName();
	int getCheckOut();
	int getExpiration();

	//mutator methods
	void setISBN(int inISBN);
	void setID(int inID);
	void setTitle(string inTitle);
	void setAuthor(string inAuthor);
	void setCategory(string inCategory);
	void setReaderName(string inReaderName);
	void setCheckOut(int inCheckOut);
	void setExpiration(int inExpiration);

};
