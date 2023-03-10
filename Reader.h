//ESE 224 Project 2nd Submission
//Copyright by the following
//Brian Cheung 112797337
//Beryl Chen 112691811
//Sila Atalar 113165359
//Hardik Shahu 170060996

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Reader.h"
#include "User.h"
#include<time.h> 
using namespace std;
class Book;

class Reader : public User
{
protected:
	
	int copies{ 0 }; // current number of copies readers has
	vector<string> titlesVec{}; // stored the titles of the books the readers has checked out
	vector<string> bookReservationList{}; // vector that holds the book titles reserved by a reader
	int numbOfReservedBooks{}; //number of books reserved by user
	int maxTime{};  //keeps the maxTime as default 30 for student and 50 for teacher
	int maxCopies{}; //keeps the maxCopy as default 5 for student and 10 for teacher
	int penalties{}; // keeps the overdues that reader have

public:
	
	//constructors
	Reader() : User() {};

	Reader(string username, string password, int copies, int numReservedBook, int penalties, int R_maxTime, int R_maxCopies) : User(username, password) {
		this->copies = copies;
		this->numbOfReservedBooks = numReservedBook;
		this->penalties = penalties;
		this->maxTime = R_maxTime;
		this->maxCopies = R_maxCopies;
	}


	Reader(string username, string password, int copies, int numReservedBook, int penalties, vector<string> titlesVec, vector<string> bookReservationList, int R_maxTime, int R_maxCopies) : User(username, password) {

		this->copies = copies;
		this->titlesVec = titlesVec;
		this->bookReservationList = bookReservationList;
		this->numbOfReservedBooks = numReservedBook;
		this->penalties = penalties;
		this->maxTime = R_maxTime;
		this->maxCopies = R_maxCopies;
	}


	//overload operators with access to information of the object and file to input and output information
	friend istream& operator >> (istream& studentFile, Reader& studentObj);
	friend ostream& operator << (ostream& studentFile,  Reader& studentObj);


	
	int getCopies();
	int getPenalties();
	int getNumbOfReservedBooks();
	string getTitle(int select);
	vector<string> getTitlesVec();
    vector<string> getReservationList();

	void setCopies(int inCopies);
	void setPenalties(int inPenalties);
	void setNumbOfReservedBooks(int inNumbOfReservedBook);
	void setSingleTitle(string inTitles, int location);// set a single title at a specific location
    void setTitlesVec(vector<string>& titlesVec);// sets the title vector of the reader
	void setReservationList(vector<string>& bookReservationList);

	void addTitle(string inTitle);// adds a title to the list(vector) of books teh student has checked out
	void removeTitle(string inTitle);// remoes a title from the list(vector) of books the student has checked out
	void borrowCopy(vector<Book>& bookList, int CurrentDay); // Borrow a copy if under 5 copies
	bool canCheckOut(vector<Book>& bookList, int CurrentDay); // checks initial conditons
	bool checkForDuplicateBook(vector<Book>& bookList, int ISBNsearch);// check if the student has the book checked out already
	int showAvailableCopies(vector<Book>& bookList, int ISBNsearch);// shows all available copies of the book 
	int searchCopyR(vector<Book>& bookList, int ISBNSearch, int IDSearch); // search for title by ISBN
	void searchCopyS(vector<Book>& bookList);
	void returnCopy(vector<Book>& bookList, int currentDay); //Return a borrowed copy
	void cancelReservation(vector<Book>& bookList); //cancels book reservation
	void removeFromReservation(string InTitle);
	void renewBook( vector<Book>& bookList, int currentDay, int renewISBN, int renewCopyID); // if conditions are met, reader's book is renewed
	void reserveBook(vector<Book>& bookList, int currentDay);
//	bool copiesAvailable(vector<Book>& bookList, int ISBNsearch); //return false when no copies are available for the specific book and returns true when there are copies available
	int overdueCopies(vector<Book>& bookList, int currentDay); // function returns number of overdue copies
	int checkReserveList(vector<Book>& bookList, int bookIndex);
	int findBookLocation(vector<Book>& bookList, int ISBN);
	int calculateBorrowingPeriod(vector<Book>& bookList, int bookIndex, int CopyIndex);


	void recommendBooks(vector<Book>& bookList);
};
