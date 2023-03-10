//ESE 224 Project 2nd Submission
//Copyright by the following
//Brian Cheung 112797337
//Beryl Chen 112691811
//Sila Atalar 113165359
//Hardik Shahu 170060996
#include <iostream>
#include<string>
#include <fstream>
#include <vector>
#include "Copy.h"
class Book
{
private:
	//book.txt file format:
	//ISBN ID Title Author Category max_number_of_copies available_copies <copy vector inputted later>
	//favor number_of_reservees reservee_list

	//data attributes for book
	int ISBN{};// ISBN of the book (unique to other books)
	string title{};// title of the book
	string author{};// author of the book
	string category{};// category the book is in
	int maxCount{};// gives the total number of copies of the book in the system
	int availableCount{};// gives the total available copies of teh book
	vector<Copy> copyList;// the copy vector will be populated when the copy file is read in LSM main
	int favor{};// represents teh popularity of the book
	int reserveDate{};// gives the date the book that is reserved has an available copy
	int numbOfReservee{};// gives the number of reservees
	vector<string> reserveeList;// the list of reservees for the book


public:
	//constructors
	Book();
	Book(int ISBN, string title, string author, string category, int maxCount, int availableCount, vector<Copy> copyList, 
		int favor, int reserveDate, int numbOfReservee, vector<string> reserveeList);

	//overload operators with access to information of the object and file to input and output information
	friend istream& operator >> (istream& bookFile, Book& bookObj);
	friend ostream& operator << (ostream& bookFile, Book& bookObj);

	//accessor methods
	int getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	int getMaxCount();
	int getAvailableCount();
	vector<Copy> getCopyList();
	int getReserveDate();
	int getFavor();
	int getNumbOfReservees();
	vector<string> getReserveeList();


	//mutator methods
	void setISBN(int inISBN);
	void setTitle(string inTitle);
	void setAuthor(string inAuthor);
	void setCategory(string inCategory);
	void setMaxCount(int inMaxCount);
	void setAvailableCount(int inAvaiableCount);
	void setCopyList(vector<Copy> inCopyList);
	void setReserveeList(int inReserveDate);
	void setFavor(int inFavor);
	void setNumbOfReservee(int inNumbOfReservee);
	void setReserveeList(vector<string> inReserveeList);

	void addToReserveeList(string inUsername);

	//mutator methods for copy vector
	void setISBNForCopyInList(int inCopyIndex, int inISBN);
	void setIDForCopyInList(int inCopyIndex, int inID);
	void setTitleForCopyInList(int inCopyIndex, string inTitle);
	void setAuthorForCopyInList(int inCopyIndex, string inAuthor);
	void setCategoryForCopyInList(int inCopyIndex, string inCategory);
	void setReaderForCopyInList(int inCopyIndex, string inUsername);
	void setCheckOutForCopyInList(int inCopyIndex, int inCheckOut);
	void setExpirationForCopyInList(int inCopyIndex, int inExpiration);

	void borrowCopy(int inCopyIndex, string inUserName, int inCheckout, int inExpiration);//borrows a copy of a book, needs username, date it's checked out and when it expires
	void returnCopy(int inCopyIndex);//returns a copy of a book
	void removeCopyByID(int inID);//removes a copy when given a ID
	void checkReserveeList(int currentDay);//checks if there are any reservee's who did not check out their book within 5 days
	void cancelReservation(string inUserName);//cancels the reservation based on the input username
	
	
};
