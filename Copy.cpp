#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Copy.h"

//copy.txt file format:
//ISBN ID Title Author Category Reader's_Name Start_Date_of_borrowing_period Expiration_Date

Copy::Copy() {}

Copy::Copy(int ISBN, int ID, string title, string author, string category, string readerName, int checkOut, int expiration) {
	this->ISBN = ISBN;
	this->ID = ID;
	this->title = title;
	this->author = author;
	this->category = category;
	this->readerName = readerName;
	this->checkOut = checkOut;  // the day 
	this->expiration = expiration; // expiration will be different for each book so can I think this one as calculatedTimePeriof

}

//takes information from istream and sets the object with those values
istream& operator >> (istream& inputStream, Copy& copyObj) {
	//declare variables to hold information being read from the Copy file
	static int inISBN, inID, inCheckOut, inExpiration;
	static string inTitle, inAuthor, inCategory, inReaderName;

	//takes information from Copy file and loads it into the object
	inputStream >> inISBN >> inID >> inTitle >> inAuthor >> inCategory >> inReaderName >> inCheckOut >> inExpiration;
	copyObj.setISBN(inISBN);
	copyObj.setID(inID);
	copyObj.setTitle(inTitle);
	copyObj.setAuthor(inAuthor);
	copyObj.setCategory(inCategory);
	copyObj.setReaderName(inReaderName);
	copyObj.setCheckOut(inCheckOut);
	copyObj.setExpiration(inExpiration);
	return inputStream;
}

//takes the information of the object and outputs it to the console
ostream& operator << (ostream& outputStream, Copy& copyObj) {
	//outputs all information into the Copy file from the object
	/* header for copy
	outputStream << left << setw(10) << "ISBN" << left << setw(5) << "ID" <<
		left << setw(30) << "Title" << left << setw(20) << "Author" <<
		left << setw(10) << "Category" << endl;
	*/
	outputStream << left << setw(10) << copyObj.getISBN() << left << setw(5) << copyObj.getID() <<
		left << setw(30) << copyObj.getTitle() << left << setw(20) << copyObj.getAuthor() <<
		left << setw(10) << copyObj.getCategory();
	outputStream << "\n"; //seperates each student to a different line
	return outputStream;
}

//Accessor methods
int Copy::getISBN() {
	return ISBN;
}
int Copy::getID() {
	return ID;
}
string Copy::getTitle() {
	return title;
}
string Copy::getAuthor() {
	return author;
}
string Copy::getCategory() {
	return category;
}
string Copy::getReaderName() {
	return readerName;
}
int Copy::getCheckOut() {
	return checkOut;
}
int Copy::getExpiration() {
	return expiration;
}

//Mutator methods
void Copy::setISBN(int inISBN) {
	this->ISBN = inISBN;
}
void Copy::setID(int inID) {
	this->ID = inID;
}
void Copy::setTitle(string inTitle) {
	this->title = inTitle;
}
void Copy::setAuthor(string inAuthor) {
	this->author = inAuthor;
}
void Copy::setCategory(string inCategory) {
	this->category = inCategory;
}
void Copy::setReaderName(string inReaderName) {
	this->readerName = inReaderName;
}
void Copy::setCheckOut(int inCheckOut) {
	this->checkOut = inCheckOut;
}
void Copy::setExpiration(int inExpiration) {
	this->expiration = inExpiration;
}
