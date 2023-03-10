//ESE 224 Project 2nd Submission
//Copyright by the following
//Brian Cheung 112797337
//Beryl Chen 112691811
//Sila Atalar 113165359
//Hardik Shahu 170060996

#include "Reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#include "Book.h"

//Reader Text File Format: username, password, copies, penalties, reserved books

istream& operator >> (istream& readerFile,  Reader& readerObj)  {
	//declare variables used to temporarily hold information to be loaded into the object
	static string inUsername, inPassword;
	static int inCopies, inNumbOfReservedBooks, inPenalties;
	static string bookName;
	static string tempBookName;

	//take input up to copies to find how many books checked out by the teacher

	readerFile >> inUsername >> inPassword >> inCopies  >> inPenalties >> inNumbOfReservedBooks;

	readerObj.Username = inUsername;
	readerObj.Password = inPassword;
	readerObj.copies = inCopies;
	readerObj.penalties = inPenalties;
	readerObj.numbOfReservedBooks = inNumbOfReservedBooks;

	//checks that the teacher has checked out books, if not then the teacher has not checked out any books
	if (inCopies > 0) {
		//gets and load the books into the list(vector) of books(titles) for the teacher
		for (int counter(0); counter < inCopies; counter++) {
			readerFile >> bookName;
			readerObj.titlesVec.push_back(bookName);
		}
	}

	readerObj.numbOfReservedBooks = inNumbOfReservedBooks;
	for (int i = 0; i < readerObj.numbOfReservedBooks; i++) {
		readerFile >> tempBookName;
		readerObj.bookReservationList.push_back(tempBookName);
	} 
	return readerFile;
}

//takes the information from the teacher object and outputs it into the teacher file
//ie. teacherObj >> teacherFile, Teacher class object stores its information into the teacher file

ostream& operator << (ostream& outputStream,  Reader& readerObj) {
	string outUsername = readerObj.getUsername();
	string outPassword = readerObj.getPassword();
	int OutCopies = readerObj.getCopies();
	int outPenalties = readerObj.getPenalties();
	int outNumberofReservedBook = readerObj.getNumbOfReservedBooks();


		
	outputStream << left << setw(10) << outUsername << left << setw(20) << outPassword <<
		left << setw(20) << OutCopies << left << setw(25) << outPenalties << left << setw(25) << outNumberofReservedBook << endl;
		
	//loops through all titles in the vector and outputs them to the console
		for (size_t i = 0; i < readerObj.getTitlesVec().size(); i++) {
			
			outputStream << left << setw(100) << " " << readerObj.getTitlesVec().at(i) << endl;
		}
		
	
	outputStream << "\n"; //seperates each teacher to a different line
	return outputStream;
}


int Reader::getCopies()
{
	return copies;
}
string Reader::getTitle(int select)
{
	return titlesVec.at(select);
}
vector<string> Reader::getTitlesVec() {
	return titlesVec;
}

vector<string> Reader::getReservationList() {
	return bookReservationList;
}

int Reader:: getPenalties() {
	return penalties;
}

int Reader::getNumbOfReservedBooks() {
	return numbOfReservedBooks;
}


void Reader::setCopies(int inCopies)
{
	this->copies = inCopies;
}

void Reader::setPenalties(int inPenalties)
{
	penalties = inPenalties;
}

void Reader::setNumbOfReservedBooks(int inNumbOfReservedBook) {
	numbOfReservedBooks = inNumbOfReservedBook;

}

//set a title for a particular location of the vector for a Reader
void Reader::setSingleTitle(string inTitles, int location) {
	this->titlesVec.at(location) = inTitles;
}

//set the entire vector of titles for the Reader
void Reader::setTitlesVec(vector<string>& titlesVec) {
	this->titlesVec = titlesVec;
}

void Reader::setReservationList(vector<string>& bookReservationList) {
	this->bookReservationList = bookReservationList;
}
 
//adds the title to the vector of book titles
void Reader::addTitle(string inTitle) {
	this->titlesVec.push_back(inTitle);
}

//removes the title of the book
void Reader::removeTitle(string inTitle) {
	static int eraseBookLocation;// stores the location for its offset in the vector to erase it from the vector

	//loops through all of the book titles
	for (size_t i = 0; i < titlesVec.size(); i++) {
		//checks for the location of the title in the vector
		if (inTitle.compare(titlesVec.at(i)) == 0) {

			eraseBookLocation = (int)i;

			break;
		}
	}

	titlesVec.erase(titlesVec.begin() + eraseBookLocation);// erases the title
}

//lets the Reader borrow a book if they are able to
void Reader:: borrowCopy(vector<Book>& bookList, int currentDay) {
	//declare variables
	static int inISBN;// holds the input for the ISBN input from the user
	static int inID;// holds the ID for the specific ISBN (book) the user wants to checkout
	static int bookIndex; //gives index location of book in the book vector
	static int copyIndex; //gives index location of copy in the copy vector of the book object
	bool flag = false; // defaults to false, there ýs not a duplýcate copy of a book ýf false
	static int borrowPeriod{}; //holds the calculated barrow period

	//prompts the user for an ISBN input for the book they want
	cout << "\nInput ISBN: ";
	cin >> inISBN;

	//checks if the user can checkout a book
	if (canCheckOut(bookList, currentDay)) {
		
		maxCopies = (maxCopies - (penalties / 5));

		maxCopies = (maxCopies + (penalties / 5));

		//checks if the Reader is checking out a book they have already checked out
		if (checkForDuplicateBook(bookList, inISBN)) {
			//find the bookLocation 
			bookIndex = findBookLocation(bookList,inISBN);
			cout << "test " << bookList.at(bookIndex).getISBN() << endl;
			// if there is a bookIndex with that ISBN, check the copies 
			if (bookIndex >= 0) {	
				// if there is avaliable copies checks reserveeList
					if (showAvailableCopies(bookList, inISBN)>0) {
						// check the reservee list to borrow the book
						if (checkReserveList(bookList, bookIndex)>0) {

						//prompts the user for an ID input for the specific book (copy) they want
						cout << "\nInput ID: ";
						cin >> inID;

						//searches for a copy of the book
						copyIndex = searchCopyR(bookList, inISBN, inID);
				
						//checks if the student has already checked out the book
						if (!(checkForDuplicateBook (bookList, inISBN))) {
							cout << "\nYou cannot check-out a book you already checked out" << endl;
							return;
						}
						
					
						//add the title to the student's vector (list) of books checked out and increment the total number of copies
						addTitle((bookList.at(bookIndex).getTitle()));// update student vector and add in the title
						copies++;// update total number of copies

								 //set the reader's name, checkout date, and expiration date for the book checked out
						bookList.at(bookIndex).borrowCopy(copyIndex, Username, currentDay, (currentDay + maxTime - bookList.at(bookIndex).getFavor()));
						cout << "Username:" << Username << endl;

					}
					else
						cout << " You should make a reservation for this book!" << endl;
			    }
			
			}
			else
				cout << "There is no book with that ISBN! " << endl;
		}
		else
			cout << "\nYou have already checked out that book!" << endl;
	}
}



 //checks to make sure no book is overdue, and under max copies copies
bool Reader::canCheckOut(vector<Book>& bookList ,int currentDay) {
	int checkOutFlag = 1; // 1 (default) - can checkout book, 2 - overdue books, 3 - to many books


   // Check maxCopies depends on the penalties w'th every 5 penalties decrease number of the maxCopies
	//cout << "maxCopies: " << maxCopies
	
	if (copies < maxCopies) {
		if (overdueCopies(bookList, currentDay) > 0)
			checkOutFlag = 2;
		else
			checkOutFlag = 1;
	}
	else
		checkOutFlag = 3; //the user has the maximum number of books allowed

	//checks what the checkout flag, if they can or cannot checkout books
	switch (checkOutFlag) {
	case 1:
		cout << "\nYou can checkout books!" << endl;
		return true;// user can checkout books
		break;
	case 2:
		cout << "\n It is day " << currentDay << ". You cannot checkout any books, you have overdue books" << endl;
		break;
	case 3:
		cout << "\nYou cannot checkout any books, you have checked out the maximum number of books" << endl;
		break;
	}
	return false;// user cannot checkout books
}

//checks if the Reader is trying to check out another copy of the same book
bool Reader::checkForDuplicateBook(vector<Book>& bookList, int ISBNsearch) {
	//check all titles the Reader has checked out for a duplicate book
	for (size_t i = 0; i < titlesVec.size(); i++) {
		for (size_t j = 0; j < bookList.size(); j++) {
			//if a duplicate book is found then return false
			if ((ISBNsearch == bookList.at(j).getISBN()) && (titlesVec.at(i).compare(bookList.at(j).getTitle()) == 0)) {
				cout << "\nDuplicate found!" << endl; //testing
				return false;
			}
		}
	}
	cout << "\nNo duplicate!" << endl; //testing
	return true;// no duplicate book found, return true
}


int Reader ::findBookLocation(vector<Book>& bookList, int ISBN) {
	
    int bookIndex = -1; // there is no book with that ISBN 

	// loop for all books inside bookList
	for (size_t i = 0; i < bookList.size(); i++) {
		cout << bookList.at(i).getISBN() << endl;
		// if ISBN matches, return the location index of the books
		if (ISBN == bookList.at(i).getISBN()) {
			bookIndex = (int)i;
			break;
		}
	}
	return bookIndex;
}

//displays avaliable copies, returns -1 when no copies and returns 1 when there are copies
int Reader::showAvailableCopies(vector<Book>& bookList, int ISBN) {

	//declare variable
	int flag = 1; //1- Copie are unavailable, 2- book can be borrowed
	vector<Copy> availableCopies; // temp keeps the copy books to print them

	
	for (size_t i = 0; i < bookList.size(); i++) {	
		if (ISBN == bookList.at(i).getISBN()) {
			// loops the copy of the book to check they are avalible or not
			for (size_t j = 0; j < bookList.at(i).getCopyList().size(); j++) {
				// check book if its available
				if ((bookList.at(i).getCopyList().at(j).getReaderName().compare("[available]")) == 0) {	
					flag = 2;
					availableCopies.push_back(bookList.at(i).getCopyList().at(j));
				}

			}
		}
	}
    	
	//shows the user whether there are books available or not
	switch (flag) {
	case 1:
		cout << "\nNo available copies. You should reserve the book" << endl;

		return -1;
		break;
	case 2:
		cout << "\nAvailable Copies:" << endl;
		for (size_t i = 0; i < availableCopies.size(); i++) {
			cout << "ISBN: " << availableCopies.at(i).getISBN() << ", ID: " << availableCopies.at(i).getID()
				<< ", Title: " << availableCopies.at(i).getTitle() << ", Author: " << availableCopies.at(i).getAuthor() << endl;
				//<< " [Available]" << endl;
		}
		return 1;
		break;
		/*default:
			cout << "\nYou should not be seeing this, please report if this is seen." << endl;
			return -1;
		break;*/
	}
}

int Reader::overdueCopies(vector<Book>& bookList, int currentDay) { // to make code more modular, replace with this function wherever needed

	int overdueCounter = 0; // keeps track of how many overdue copies reader has
	for (size_t i = 0; i < this->titlesVec.size(); i++) {
		// cheack each book for a matching title
		for (size_t j = 0; j < bookList.size(); j++) {
			if (bookList.at(j).getTitle().compare(titlesVec.at(i)) == 0) {
				//check each copy for a matcher reader
				for (size_t k = 0; k < bookList.at(j).getCopyList().size(); k++) {
					//find username for a copy of a book
					if ((bookList.at(j).getCopyList().at(k).getReaderName().compare(this->Username)) == 0) {
						//check due date of book and compare to current date
						if (currentDay >= bookList.at(j).getCopyList().at(k).getExpiration()) {
							overdueCounter++; // overdue copy detected
						}
					}
				}
			}
		}
	}
	cout << "\nYou have " << overdueCounter << " overdue copies." << endl; //testing
	return overdueCounter;
}

//searches for a specific copy of a book and gives the index location of the book
int Reader::searchCopyR(vector<Book>& bookList, int ISBNSearch, int IDSearch) {
	for (size_t i = 0; i < bookList.size(); i++) {
		if (ISBNSearch == bookList.at(i).getISBN()) {
			for (size_t j = 0; j < bookList.at(i).getCopyList().size(); j++) {
				if (IDSearch == bookList.at(i).getCopyList().at(j).getID()) {

					return (int)j;

				}
			}
		}
	}
	return -1;
}

//returns a book that a Reader has checked out
void Reader::returnCopy(vector<Book>& bookList, int currentDay) {
	//declare variables

	int ridISBN; // the ISBN of book user would like to return
	string ridTitle; // the title of the book the user would like to return
	bool flag = true; // defaults to true, means that there is no books found
	int bookIndex; //stores index location for book vector
	size_t copyIndex;
	int counter = 0;

	//maxCopies = (maxCopies - (penalties / 5));

	// prompt the user for ISBN input for the book they would like to return
	cout << "\nEnter ISBN: ";
	cin >> ridISBN; // store in rid

	//get book index using ISBN
	bookIndex = findBookLocation(bookList, ridISBN);

	if (bookIndex == -1)
	{
		cout << "Book does not exist." << endl;
		return; // no need to do more
	}
	else
	{
		//get the title of the book
		ridTitle = bookList.at(bookIndex).getTitle();

		// loop through all copies to find the book with the same reader
		for (copyIndex = 0; copyIndex < bookList.at(bookIndex).getCopyList().size(); copyIndex++) {
			if (Username.compare(bookList.at(bookIndex).getCopyList().at(copyIndex).getReaderName()) == 0) {
				
				flag = false;
				break;
			}
		}

		//checks if the book flag is set, if it is then the book as not been found
		if (flag) {
			cerr << "\nBook not found." << endl; // error message
			return;
		}

		if (currentDay > (bookList.at(bookIndex).getCopyList().at(copyIndex).getExpiration())) {
			penalties++; // increase penalties
			counter = 1;
		}

		//update Reader information
		removeTitle(ridTitle);// removes the title from the list(vector) of books(titles) of the Reader
		copies--; //Reader has returned to book and has one less copy

		//update book information
		bookList.at(bookIndex).returnCopy((int)copyIndex);

		//update penalty
		setPenalties(penalties);

		if (((counter + penalties) / 5) != (penalties / 5)) {
			maxCopies = (maxCopies - (penalties / 5));
		}
		else
		{
			maxCopies = (maxCopies + (penalties / 5));
		}

		// update maxCpýes
	//	if ((penalties/5) != newPenalties) {
	//		maxCopies = (maxCopies - (penalties / 5));
	//	}
		
	//	if (maxCopies % 5 == 0) {
	//		maxCopies--;43
	//	}
	}
}

void Reader::cancelReservation(vector<Book>& bookList)//removed from the book’s reservee list and reader’s reservation list
{
	bool flag = true; // false = book found, true = book not found

	string bookTitle; // title of book in book res list

	static int eraseReserveeLocation;// stores the location for its offset in the vector to erase it from the vector
	int cancelReservationISBN; //will store the user input ISBN of book they want to cancel reservation for
	cout << "Enter the ISBN of the book: " << endl;
	cin >> cancelReservationISBN;

	int bookIndex = findBookLocation(bookList, cancelReservationISBN);
	//get title of book
	bookTitle = bookList.at(bookIndex).getTitle();
		
	bookList.at(bookIndex).cancelReservation(Username);

	for (int bookIndex = 0; bookIndex < numbOfReservedBooks; bookIndex++) {
		//find title match in book reservation list
		if (bookTitle.compare(bookReservationList.at(bookIndex)) == 0) {
			bookReservationList.erase(bookReservationList.begin() + bookIndex);
			break;
		}
	}
}

void Reader::removeFromReservation(string inTitle) {

	for (size_t i = 0; i < numbOfReservedBooks; i++) {
		//find title match in book reservation list
		if (inTitle.compare(this->bookReservationList.at(i)) == 0) {
			bookReservationList.erase(bookReservationList.begin() + i);
			this->numbOfReservedBooks--;
			return;
		}
	}
}

void Reader::renewBook(vector<Book>& bookList, int currentDay, int renewISBN, int renewCopyID) {
//	int renewCopyID; // will store the user input ID for the copy reader wants to renew
	int renewCopyIndex; // will store the index of the copy reader wants to renew
	int bookIndexRenew;
	int expDay; // current expiration day for copy
	int inISBN, inID;

	bookIndexRenew = findBookLocation(bookList, renewISBN);

	if (bookIndexRenew >= 0) {
		if ((overdueCopies(bookList, currentDay) == 0) && (bookList.at(bookIndexRenew).getNumbOfReservees() == 0))// can only renew if no reservees and no overdue copies
		{
			
			renewCopyIndex = searchCopyR(bookList, renewISBN, renewCopyID);

			//expDay = bookList.at(bookIndexRenew).getCopyList().at(renewCopyIndex).getExpiration();
			bookList.at(bookIndexRenew).setExpirationForCopyInList(renewCopyIndex, currentDay + maxTime); // max time added to current exp day

			cout << "Book successfully renewed!" << endl;
			return;
		}
		else
			cout << "You cannot renew this book." << endl; //conditions do not check out
	}
	else
	cout << "There is no book with this ISBN!" << endl;
}

void Reader::searchCopyS(vector<Book>& bookList) {//searches for books regardless by any keywords
	//declares the variables
	string inputTitle, inputAuthor, inputCat; //varibles for the inputs they might enter depending on which case they pick
	int inputISBN, inputSelect;				 //^^
	int cond = 1; //so they enter a wrong input it will allow them to try again
	int anyBooks = 0; //flag for if any books are found with a case


	while (cond == 1) {
		cin.clear();
		//inputSelect = 1;
		anyBooks = 0;
		cout << "\nHow would you like to search for a book?\n";
		cout << "(1) - By Title\n";
		cout << "(2) - By ISBN\n";
		cout << "(3) - By Category\n";
		cout << "(4) - By Author\n";
		cout << "(5) - Quit\n";
		cin >> inputSelect;
		cout << "\ninput seelction: " << inputSelect << endl;

		if (inputSelect == 1) {//if they want to search by title
			cin.clear();
			//cin.sync();
			//cond = 0;
			cout << "Enter a title:(Use '-' for spaces)\n";
			cin >> inputTitle;
			//cout << "cin: |" << inputTitle << "|"<< endl;
			for (size_t i = 0; i < bookList.size(); i++) { //loops through the book class and searches for the matching title
				if (inputTitle.compare(bookList.at(i).getTitle()) == 0) {
					anyBooks = 1;
					cout << "\nISBN: " << bookList.at(i).getISBN() << endl;
					cout << "Title: " << bookList.at(i).getTitle() << endl;
					cout << "Author: " << bookList.at(i).getAuthor() << endl;
					cout << "Category: " << bookList.at(i).getCategory() << endl;
					break;

				}
			}
			if (anyBooks == 0)
				cout << "\nNo books were found with that title!\n";


		}

		else if (inputSelect == 2) { //if they want to search by ISBN
			//cond = 0;
			cout << "Enter an ISBN: ";
			cin >> inputISBN;
			for (size_t i = 0; i < bookList.size(); i++) {//loops through the book class and searches for the matching ISBN
				if (inputISBN == bookList.at(i).getISBN()) {
					anyBooks = 1;
					cout << "\nISBN: " << bookList.at(i).getISBN() << endl;
					cout << "Title: " << bookList.at(i).getTitle() << endl;
					cout << "Author: " << bookList.at(i).getAuthor() << endl;
					cout << "Category: " << bookList.at(i).getCategory() << endl;
					break;
				}
			}
			if (anyBooks == 0)
				cout << "\nNo books were found with that ISBN!\n";
		}

		else if (inputSelect == 3) { //if they want to search by category
			//cond = 0;
			cout << "Enter a Category: ";
			cin >> inputCat;
			for (size_t i = 0; i < bookList.size(); i++) { //loops through the book class and searches for the matching Category
				if (inputCat.compare(bookList.at(i).getCategory()) == 0) {
					anyBooks = 1;
					cout << "\nISBN: " << bookList.at(i).getISBN() << endl;
					cout << "Title: " << bookList.at(i).getTitle() << endl;
					cout << "Author: " << bookList.at(i).getAuthor() << endl;
					cout << "Category: " << bookList.at(i).getCategory() << endl;
					//break;
				}
			}
			if (anyBooks == 0)
				cout << "\nNo books were found with that Category!\n";
		}
		else if (inputSelect == 4) { //if they want to search by author
			//cond = 0;
			cout << "Enter a Author: ";
			cin >> inputAuthor;
			for (size_t i = 0; i < bookList.size(); i++) {  //loops through the book class and searches for the matching author
				if (inputAuthor.compare(bookList.at(i).getAuthor()) == 0) {
					anyBooks = 1;
					cout << "\nISBN: " << bookList.at(i).getISBN() << endl;
					cout << "Title: " << bookList.at(i).getTitle() << endl;
					cout << "Author: " << bookList.at(i).getAuthor() << endl;
					cout << "Category: " << bookList.at(i).getCategory() << endl;
					//break;
				}
			}
			if (anyBooks == 0)
				cout << "\nNo books were found with that Author!\n";
		}

		else if (inputSelect == 5) { //if they want to  quit the search program
			cout << "Quiting the search books program!";
			cond = 0;
		}
		else { //if they enter a wrong input
			cout << "\nIncorrect input, Please Try Again\n";
		}
	}
}

void Reader::reserveBook(vector<Book>& bookList, int currentDay) { //reserve when no copies available, cannot have overdue, once available cancels in 5 days
	int reserveBookISBN; // stores user input ISBN of book they want to reserve
	int reservationExpDay; // the day the book reservation expires
	int bookIndex; // index of the book
	string tempReserveeList;

	cout << "Enter the ISBN:" << endl;
	cin >> reserveBookISBN;

	if (overdueCopies(bookList, currentDay) > 0) {// if overdue copies detected, stops reader from reserving
		cout << "You have overdue copies! Please return them before proceeding." << endl;
		return; // exit
	}
	if (showAvailableCopies(bookList, reserveBookISBN) > 1) {// if there are available copies, stops reader from reserving
		cout << "There are available copies for this book! Try checking out instead." << endl;
		return; // exit
	}

	bookIndex = findBookLocation(bookList, reserveBookISBN); // finding book index

	//adding reader to reservation list of book
	bookList.at(bookIndex).addToReserveeList(this->Username);
	bookList.at(bookIndex).checkReserveeList(currentDay);
	
	
	//adding book to reader reserved books list
	this->bookReservationList.push_back(bookList.at(bookIndex).getTitle());
	this->numbOfReservedBooks++;
	
	

}



// check reserveeList is empty or the user is the first one who can get the book
int Reader::checkReserveList(vector<Book>& bookList, int bookIndex) {

	// if reserveeList is empty return 1
	if (bookList.at(bookIndex).getReserveeList().empty()) {
		cout << "There is no reservation for this book" << endl;
		return 1;
	}
	
	// if the user is the fisr one on the reserve list return 1
	else if ( Username == (bookList.at(bookIndex).getReserveeList().at(0))) {
		cout << "Book you reserved is available"<<endl;
			return 1;
	}

	else {
		cout << "There are other reservations for this book\nYou need to make a reservation" << endl;
		return 0;
	}	
}

int  calculateBorrowingPeriod (vector<Book>&bookList ,int bookIndex, int CopyIndex) {
	//int bookIndex{};// keeps the book Location
	
	int expirationDate = bookList.at(bookIndex).getCopyList().at(CopyIndex).getExpiration();
	int Favor = bookList.at(bookIndex).getFavor(); // keeps the ratio for the favor when checking out the book for the book
	
	//calculate expiration date depends on the popularity of the book
	int calculatedPeriod =  (expirationDate - Favor);
	

	return calculatedPeriod;

}

void Reader::recommendBooks(vector<Book>& bookList) { //bookList Must be sorted before calling this function 
	int indexName; //index
	string cat; //category that we will use
	int cond = 0; //0 is they have no copies borrowed 1 means they have some copies borrowed
	int  maxPrint = 10; //max numebr of the books


	cout << "Some books we recommend for you are: \n(Note,you may see less than ten books if the category doesn't have 10 books(If applicable to your case))\n";

	string bookCategory;

	cout << left << setw(10) << "ISBN" << left << setw(30) << "Title" <<
		left << setw(20) << "Author" << left << setw(10) << "Category" << left << setw(20) << "Available Copies" <<
		left << setw(10) << "Favor" << left << setw(10) << "Number of reservees" << endl;


	if (this->copies == 0) { //if they had no copies checked out

		//loop for top 10
		for (int i = 0; i < 10; i++) { //will print the top most popular ten books
			cout << bookList.at(i);
		}
	}
	else if (this->copies >= 0) {//if they have copies checked out
		for (size_t i = 0; i < bookList.size(); i++) {
			if (bookList.at(i).getTitle().compare(this->titlesVec.back()) == 0) {
				bookCategory = bookList.at(i).getCategory(); //find the category
				break;
			}
		}
		//loop for top 10
		for (size_t i = 0; i < bookList.size(); i++) { //will print the most popular books for their category
			if (bookCategory.compare(bookList.at(i).getCategory()) == 0) { //checks the condition
				cout << bookList.at(i);
				maxPrint--; //so it only prints 10 and no more than 10
			}
			if (maxPrint == 0) { //will stop at 10

				break;
			}
		}
	}
	else
		cout << "ERROR! SOMETHING WENT WRONG!" << endl; //if something went wrong, it prints error message!
}
