//ESE 224 Project 2nd Submission
//Copyright by the following
//Brian Cheung 112797337
//Beryl Chen 112691811
//Sila Atalar 113165359
//Hardik Shahu 170060996

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Book.h"

//book.txt file format:
//ISBN ID Title Author Category max_number_of_copies available_copies <copy vector inputted later>
//favor number_of_reservees reservee_list

Book::Book(){}

Book::Book(int ISBN, string title, string author, string category, int maxCount, int availableCount, vector<Copy> copyList, int reserveDate, int favor, int numbOfReservee, vector<string> reserveeList) {
	this->ISBN = ISBN;
	this->title = title;
	this->author = author;
	this->category = category;
	this->maxCount = maxCount;
	this->availableCount = availableCount;
	this->copyList = copyList;
	this->favor = favor;
	this->reserveDate = reserveDate;
	this->numbOfReservee = numbOfReservee;
	this->reserveeList = reserveeList;
}

//takes information from istream and sets the object with those values
istream& operator >> (istream& inputStream, Book& bookObj) {
	//declare variables to hold information being read from the Copy file
	static int inISBN, inID, inCheckOut, inExpiration;
	static string inTitle, inAuthor, inCategory, inReaderName;

	//takes information from Copy file and loads it into the object
	inputStream >> inISBN >> inTitle >> inAuthor >> inCategory;
	bookObj.setISBN(inISBN);
	bookObj.setTitle(inTitle);
	bookObj.setAuthor(inAuthor);
	bookObj.setCategory(inCategory);
	bookObj.setMaxCount(0);
	bookObj.setAvailableCount(1);
	bookObj.setFavor(0);
	return inputStream;
}

//takes the information of the object and outputs it to the console
ostream& operator << (ostream& outputStream, Book& bookObj) {
	/* header for book
	outputStream << left << setw(10) << "ISBN" << left << setw(30) << "Title" << 
		left << setw(20) << "Author" << left << setw(10) << "Category" << left << setw(20) << "Available Copies" << 
		left << setw(10) << "Favor" << left << setw(10) << "Number of reservees" << endl;
	*/
	outputStream << left << setw(10) << bookObj.getISBN() << left << setw(30) << bookObj.getTitle() <<
		left << setw(20) << bookObj.getAuthor() << left << setw(10) << bookObj.getCategory() <<
		left << setw(20) << bookObj.getAvailableCount() << left << setw(10) << bookObj.getFavor() << 
		left << setw(10) << bookObj.getNumbOfReservees();
	outputStream << "\n"; //seperates each book to a different line

	return outputStream;
}

//Accessor methods
int Book::getISBN() {
	return ISBN;
}
string Book::getTitle() {
	return title;
}
string Book::getAuthor() {
	return author;
}
string Book::getCategory() {
	return category;
}
int Book::getMaxCount() {
	return maxCount;
}
int Book::getAvailableCount() {
	return availableCount;
}
vector<Copy> Book::getCopyList() {
	return copyList;
}
int Book::getReserveDate() {
	return reserveDate;
}
int Book::getFavor() {
	return favor;
}
int Book::getNumbOfReservees() {
	return numbOfReservee;
}
vector<string> Book::getReserveeList() {
	return reserveeList;
}

//Mutator methods
void Book::setISBN(int inISBN) {
	this->ISBN = inISBN;
}
void Book::setTitle(string inTitle) {
	this->title = inTitle;
}
void Book::setAuthor(string inAuthor) {
	this->author = inAuthor;
}
void Book::setCategory(string inCategory) {
	this->category = inCategory;
}
void Book::setMaxCount(int inMaxCount) {
	this->maxCount = inMaxCount;
}
void Book::setAvailableCount(int inAvailableCount) {
	this->availableCount = inAvailableCount;
}
void Book::setCopyList(vector<Copy> inCopyList) {
	this->copyList = inCopyList;
}
void Book::setReserveeList(int inReserveDate) {
	this->reserveDate = inReserveDate;
}
void Book::setFavor(int inFavor) {
	this->favor = inFavor;
}
void Book::setNumbOfReservee(int inNumbOfReservee) {
	this->numbOfReservee = inNumbOfReservee;
}
void Book::setReserveeList(vector<string> inReserveeList) {
	this->reserveeList = inReserveeList;
}

void Book::addToReserveeList(string inUsername) {
	this->reserveeList.push_back(inUsername);
	this->numbOfReservee++;
	this->favor = (this->numbOfReservee / 2);
}

//mutator methods for copy vector
void Book::setISBNForCopyInList(int inCopyIndex, int inISBN) {
	this->copyList.at(inCopyIndex).setISBN(inISBN);
}
void Book::setIDForCopyInList(int inCopyIndex, int inID) {
	this->copyList.at(inCopyIndex).setID(inID);
}
void Book::setTitleForCopyInList(int inCopyIndex, string inTitle) {
	this->copyList.at(inCopyIndex).setTitle(inTitle);
}
void Book::setAuthorForCopyInList(int inCopyIndex, string inAuthor) {
	this->copyList.at(inCopyIndex).setAuthor(inAuthor);
}
void Book::setCategoryForCopyInList(int inCopyIndex, string inCategory) {
	this->copyList.at(inCopyIndex).setCategory(inCategory);
}
void Book::setReaderForCopyInList(int inCopyIndex, string inUsername) {
	this->copyList.at(inCopyIndex).setReaderName(inUsername);
}
void Book::setCheckOutForCopyInList(int inCopyIndex, int inCheckOut) {
	this->copyList.at(inCopyIndex).setCheckOut(inCheckOut);
}
void Book::setExpirationForCopyInList(int inCopyIndex, int inExpiration) {
	this->copyList.at(inCopyIndex).setExpiration(inExpiration);
}

void Book::borrowCopy(int inCopyIndex, string inUserName, int inCheckout, int inExpiration) {
	setReaderForCopyInList(inCopyIndex, inUserName);
	setCheckOutForCopyInList(inCopyIndex, inCheckout);
	setExpirationForCopyInList(inCopyIndex, inExpiration);
	this->availableCount--;
}

void Book::returnCopy(int inCopyIndex) {
	setReaderForCopyInList(inCopyIndex, "[available]"); // empty reader slot
	setCheckOutForCopyInList(inCopyIndex, 0); // empty checkout date
	setExpirationForCopyInList(inCopyIndex, 0); // empty expiration date
	this->availableCount++;
}

void Book::removeCopyByID(int inID) {
	static int eraseCopyOffset;// stores the location for its offset in the vector to erase it from the vector

	//loops through all of the copy IDs of the book
	for (size_t i = 0; i < this->copyList.size(); i++) {
		//checks for the location of the ID in the vector
		if (inID == this->copyList.at(i).getID()) {
			eraseCopyOffset = (int)i;
			break;
		}
	}

	this->copyList.erase(this->copyList.begin() + eraseCopyOffset);// erases the copy in the vector for the book
}

void Book::checkReserveeList(int currentDay) {
	int numPastReserveDate;
	//checks if the people who reserve the book are past the reserve date
	//remove those who are past reserve date
	//if there is people reserving and ther eare books available, set the reserve date
	if (this->numbOfReservee > 0 && this->availableCount > 0 && currentDay > (this->reserveDate + 5)) {
		//finds the number of people would be past the reserve date
		numPastReserveDate = (currentDay - this->reserveDate) / 5;
		//checks if there is more people expected to be removed from reservee list then the number of reservees
		if ((this->numbOfReservee - numPastReserveDate) < 0)
			numPastReserveDate = this->numbOfReservee;
		//loops to remove people who are past the reserve date to check otu the book
		for (int i = 0; i < numPastReserveDate; i++) {
			this->reserveeList.erase(reserveeList.begin());
			this->numbOfReservee--;
		}
		//set current date as the reserve date
		this->reserveDate = currentDay;
	}
	this->favor = (this->reserveDate / 2);
}

void Book::cancelReservation(string inUserName) {
	int cancelResOffset;
	bool userFoundFlag = false;

	for (size_t i = 0; i < this->reserveeList.size(); i++) {
		if (inUserName.compare(reserveeList.at(i)) == 0) {
			cancelResOffset = (int)i;
			userFoundFlag = true;
			break;
		}
	}

	if (userFoundFlag) {
		this->reserveeList.erase(this->reserveeList.begin() + cancelResOffset);
		this->numbOfReservee--;
		cout << "The user " << inUserName << " has been removed from the reservation list for the book " << this->title << endl;
	}
	else
		cout << "The user " << inUserName << " was not found" << endl;
}
