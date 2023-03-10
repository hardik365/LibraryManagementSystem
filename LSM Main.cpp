//ESE 224 Project 2nd Submission
//Copyright by the following
//Brian Cheung 112797337
//Beryl Chen 112691811
//Sila Atalar 113165359
//Hardik Shahu 170060996

#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "Student.h"
#include "Book.h"
#include "Teacher.h"
#include "Librarian.h"
#include "User.h"
#include<string>
#include <conio.h>
using namespace std;

#ifdef _MSC_VER
#define getch() _getch()
#endif

using namespace std;

//global variable for LSM Main
clock_t start, finish;

//string names of the book and student .txt files
const string bookFileName = "book.txt";
const string copyFileName = "copy.txt";
const string studentFileName = "student.txt";
const string teacherFileName = "teacher.txt";
const string librarianFileName = "Librarian.txt";

//declaration of templates and functions using templates
template<typename T_vector>
int verify(vector<T_vector>& List);
string maskPassword();

template<typename tReader>
void loadReaderVector(ifstream& readerFile, vector<tReader>& readerList);// loads the student vector with student objects
template <typename tReader>
void readerControlPanel(vector<Book>& bookList, vector<tReader>& readerList, tReader& readerObj);// control panel for readers
template <typename tReader>
void showCheckedOutBooks(vector<Book>& bookList, tReader& readerObj);// displays the book titles the user has checked out
template<typename tReader>
void storeReaderToFile(ofstream& file, vector<tReader>& list);// stores the student vector into the file
template <typename tReader>
void removeReaderFromReservations(vector<Book>& bookList, vector<tReader> &readerList, int dayCount);


int main() {
	//declaration of functions
	bool openReadFiles(ifstream & fileObj, string fileName);// opens the file to read information from at the start of the program
	void loadBookAndCopyVector(ifstream & bookFile, ifstream & copyFile, vector<Book> & bookList);// store book and copy into the file
	void loadStudentVector(ifstream & studentFile, vector<Student> & studentList);// loads the student vector with student objects
	void loadLibrarianVector(ifstream & librarianFile, vector<Librarian> & librarianList);
	bool openWriteFiles(ofstream& fileObj, string fileName);// opens the file to write into at the end of the program
	void storeBookAndCopyToFile(ofstream & bookFile, ofstream & copyFile, vector<Book> & bookList);// stores the book and copy vectors into the file
	void storeLibrarianToFile(ofstream & lilbrarianFile, vector<Librarian> & lilbrarianList);
	void librarianControlPanel(vector<Book> & bookList, vector<Librarian> & librarianList, Librarian & librarianObj, vector<Student> & studentList, vector<Teacher> & teacherList);// control panel for librarian
	void sort(vector<Book> & bookList, int sortType);
	//declarations of vectors and streams
	vector<Book> bookList;
	vector<Student> studentList;
	vector<Teacher> teacherList;
	vector<Librarian>librarianList;
	ifstream inBookFile, inCopyFile, inStudentFile, inTeacherFile, inLibrarianFile;
	ofstream outBookFile, outCopyFile, outStudentFile, outTeacherFile, outLibrarianFile;

	//declare and initialize variables
	char userType = '0';// stores the information of the user inputs for their user type
	int userIndexLocation;// contains the index location of the user in the vector

	int test = 1;

	//start the day
	start = clock(); // put the start in borrow book function  
	//opens the file that information will be read from
	openReadFiles(inBookFile, bookFileName);
	openReadFiles(inCopyFile, copyFileName);
	openReadFiles(inStudentFile, studentFileName);
	openReadFiles(inTeacherFile, teacherFileName);
	openReadFiles(inLibrarianFile, librarianFileName);
	//loads the book and student vector with the information from their respective files
	
	loadBookAndCopyVector(inBookFile, inCopyFile, bookList);
	loadReaderVector(inStudentFile, studentList);
	loadReaderVector(inTeacherFile, teacherList);
	loadLibrarianVector(inLibrarianFile, librarianList);

	sort(bookList, 1); //sorts book list by ISBN

	cout << "\nOnly alpha-numberic characters are used for inputs unless otherwise mentioned" <<endl;
	
	//loops until the user wants to quit the program
	while (userType != 'q') {
		//prompts the user with the options they can choose
		cout << "\nAre you a Student, Teacher, or Librarian? (Only student is implemented for the first submission)" << endl;
		cout << "\n(1) - Student" << endl;
		cout << "(2) - Teacher" << endl;
		cout << "(3) - Librarian" << endl;
		cout << "(q) - Quit Program\n" << endl;

		//prompts the user to input what type of user they are
		cout << "Please input the user type: ";
		cin >> userType;

		userType = tolower(userType); //changes any uppercase inputs to lower case

		//checks if the user wants to quit, if they are logging in then they will try to be verified before then can do further actions
		//it the upperbound will increase when teacher and librarian has been implemented
		if ((userType >= '1' && userType <= '3')) {
			//depending on what user type the user has inputted, they will use a different control panel
			switch (userType) {
			case'1':
				if ((userIndexLocation = verify(studentList)) >= 0) {
					readerControlPanel(bookList, studentList, studentList.at(userIndexLocation));
				}
				break;
			case'2':
				if ((userIndexLocation = verify(teacherList)) >= 0) {
					readerControlPanel(bookList, teacherList, teacherList.at(userIndexLocation));
				}
				break;
			case'3':
				if ((userIndexLocation = verify(librarianList)) >= 0) {
					librarianControlPanel(bookList, librarianList, librarianList.at(userIndexLocation), studentList, teacherList);
				}
				break;
			}
		}
		else if (userType == 'q')
			cout << "\nQuitting Program. . ." << endl;
		else
			cout << "\nNot a valid user type!" << endl;

		cin.ignore(numeric_limits<streamsize>::max(), '\n');;// clears input when the user does not provide a valid usery
	}

	sort(bookList,1); //sorts

	//opens and clears the book, copy, and student file to be written to
	openWriteFiles(outBookFile, bookFileName);
	openWriteFiles(outCopyFile, copyFileName);
	openWriteFiles(outStudentFile, studentFileName);
	openWriteFiles(outTeacherFile, teacherFileName);
	openWriteFiles(outLibrarianFile, librarianFileName);

	//store the book, copy, student, teachher, and librarian vectors into their respective files
	storeBookAndCopyToFile(outBookFile, outCopyFile, bookList);
	storeReaderToFile(outStudentFile, studentList);
	storeReaderToFile(outTeacherFile, teacherList);
	storeLibrarianToFile(outLibrarianFile, librarianList);
	
	return 0;
}

//opens the file to read and load information into the vector
bool openReadFiles(ifstream& fileObj, string fileName) {
	fileObj.open(fileName);
	if (fileObj.fail()) {
		cerr << "The file '" << fileName <<"' cannot be opened.";
		exit(1);
	}

	return true;
}

void sort(vector<Book>& bookList,int sortType) {

	size_t j, size = bookList.size();

	switch (sortType) {
	case 1: //sort by ISBN
		//does the sorting algorithm for ascending
		for (size_t i = 0; i < size; i++) { 
			for (j = i + 1; j < size; j++) {
				if (bookList.at(i).getISBN() > bookList.at(j).getISBN()) {
					Book tempBook(bookList.at(i));
					bookList.at(i) = bookList.at(j);
					bookList.at(j) = tempBook;
				}
			}
		}
		break;
	case 2: //sort by favors
		//does the sorting algorithm for descending
		for (size_t i = 0; i < size; i++) {
			for (j = i + 1; j < size; j++) {
				if (bookList.at(i).getFavor() < bookList.at(j).getFavor()) {
					Book tempBook(bookList.at(i));
					bookList.at(i) = bookList.at(j);
					bookList.at(j) = tempBook;
				}
			}
		}
		break;
	}
}


//loads information from the book file into the a vector of book objects
void loadBookAndCopyVector(ifstream& bookFile, ifstream& copyFile, vector<Book>& bookList) {
	//declares and initialized variables
	string newLineDetect;// holder variable to check for empty string indicating a empty line
	streampos streamPosition = bookFile.tellg();// gets the position of the first line
	Copy tempCopy;
	vector<Copy> tempCopyList;

	//declare variables to hold information being read from the book file
	static int inISBN, inMaxCount, inAvailableCount, inReserveDate, inFavor, inNumbOfReservee;
	static string inTitle, inAuthor, inCategory;
	static string tempReserveeName;
	static vector<string> tempReserveeList;
	static int inID;
	static string inReaderName;
	static int inCheckout;
	static int inExpiration;

	//loops until the end of the book file
	while (!bookFile.eof()) {
		getline(bookFile, newLineDetect);// gets the position of the first line
		if (newLineDetect != "") {
			bookFile.seekg(streamPosition);// goes to the start of the line

			//takes information from book file and loads it into the object
			bookFile >> inISBN >> inTitle >> inAuthor >> inCategory >> inMaxCount >> inAvailableCount >> inReserveDate >> inFavor >> inNumbOfReservee;
			
			//the copy vector will be populated when the copy file is read in LSM main
			
			//loops to store all reservee into a temporary vector
			if (inNumbOfReservee >= 0) {
				for (int i = 0; i < inNumbOfReservee; i++) {
					bookFile >> tempReserveeName;
					tempReserveeList.push_back(tempReserveeName);
				}
			}

			//loops to store all reservee into a t
			//loops to store all copies into a temporary vector
			if (inMaxCount >= 0) {
				for (int j = 0; j < inMaxCount; j++) {
					copyFile >> inISBN >> inID >> inTitle >> inAuthor >> inCategory >> inReaderName >> inCheckout >> inExpiration;
					Copy tempCopy(inISBN, inID, inTitle, inAuthor, inCategory, inReaderName, inCheckout, inExpiration);
					tempCopyList.push_back(tempCopy);
				}
			}
			
			//generates and objects and pushes it into the vector
			Book tempBook(inISBN, inTitle, inAuthor, inCategory, inMaxCount, inAvailableCount, tempCopyList, inReserveDate, inFavor, inNumbOfReservee, tempReserveeList);
			bookList.push_back(tempBook);

			//clear temporary holder vectors
			tempReserveeList.clear();
			tempCopyList.clear();
		}
		streamPosition = bookFile.tellg();// gets the position of the next line
	}
	bookFile.close(); // closes book file
	copyFile.close(); // closes copy file
}

//loads the student vector with student objects

template<typename tReader>
void loadReaderVector(ifstream& readerFile, vector<tReader>& readerList) {



	//declares and initialized variables
	string newLineDetect;// holder variable to check for empty string indicating a empty line
	streampos streamPosition = readerFile.tellg();// gets the position of the first line

	//declare variables used to temporarily hold information to be loaded into the object
	static string inUsername, inPassword;
	static int inCopies, inNumbOfReservedBooks, inPenalties;
	static string bookName;
	static string tempBookName;
	static vector<string> tempTitlesVec;
	static vector<string> tempReservationList;

	//loops until end of student readerFile
	while (!readerFile.eof()) {
		getline(readerFile, newLineDetect);// gets the line to check if the line is empty or not
		//checks whether or not there is a new line character, if the string is empty then it is a new line charcater
		if (newLineDetect != "") {
			readerFile.seekg(streamPosition);// goes to the start of the line


			//take information from the text readerFile
			readerFile >> inUsername >> inPassword >> inCopies >> inNumbOfReservedBooks >> inPenalties;


			//checks to see if there is any copies
			if (inCopies > 0) {
				//gets and load the books into the list(vector) of books(titles) for the reader
				for (int counter(0); counter < inCopies; counter++) {
					readerFile >> bookName;
					tempTitlesVec.push_back(bookName);
				}
			}

			//checks if book/copies have been reserved
			if (inNumbOfReservedBooks > 0) {
				//loops to get the reserved books and store them into a temporary vector
				for (int i = 0; i < inNumbOfReservedBooks; i++) {
					readerFile >> tempBookName;
					tempReservationList.push_back(tempBookName);
				}
			}

			//creates and pushes object to vector
			tReader addUser(inUsername, inPassword, inCopies, inNumbOfReservedBooks, inPenalties, tempTitlesVec, tempReservationList);
			readerList.push_back(addUser);

			//clears the tempororary vectors
			tempTitlesVec.clear();
			tempReservationList.clear();
		}
		streamPosition = readerFile.tellg();// gets the position of the next line
	}
	readerFile.close(); //closes readerFile
}

//opens the file to write into and also clear the files
bool openWriteFiles(ofstream& fileObj, string fileName) {

	fileObj.open(fileName, ios::trunc);
	if (fileObj.fail()) {
		cerr << "The file cannot be opened.";
		exit(1);
	}

	return true;
}

void loadLibrarianVector(ifstream& librarianFile, vector<Librarian>& librarianList) {
	//declares and initialized variables
	string newLineDetect;// holder variable to check for empty string indicating a empty line
	streampos streamPosition = librarianFile.tellg();// gets the position of the first line
	string inUsername;
	string inPassword;
	//int i = 0;
	//loops until end of librarian file
	while (!librarianFile.eof()) {
		getline(librarianFile, newLineDetect);// gets the line to check if the line is empty or not
		//checks whether or not there is a new line character, if the string is empty then it is a new line charcater
		if (newLineDetect != "") {
			librarianFile.seekg(streamPosition);// goes to the start of the line
			librarianFile >> inUsername >> inPassword;
			Librarian tempLibrarian(inUsername, inPassword);
			librarianList.push_back(tempLibrarian);
		}
		streamPosition = librarianFile.tellg();// gets the position of the next line
	}
	librarianFile.close(); //closes librarian file
}


void storeBookAndCopyToFile(ofstream& bookFile, ofstream& copyFile, vector<Book>& bookList) {
	//declares variables, they are temporary variables/objects to store information from the object
	int outISBN;
	int outID;
	string outTitle;
	string outAuthor;
	string outCategory;
	int outMaxCount;
	int outAvailableCount;
	int outReserveDate;
	int outFavor;
	int outNumberOfReservee;
	Copy tempCopyObj;
	string outReaderName;
	int outCheckOut;
	int outExpiration;

	//loops to put all information of the book vector into book file
	for (size_t i = 0; i < bookList.size(); i++) {
		//stores non-list attributes to a variable and stores it to the file
		outISBN = bookList.at(i).getISBN();
		outTitle = bookList.at(i).getTitle();
		outAuthor = bookList.at(i).getAuthor();
		outCategory = bookList.at(i).getCategory();
		outMaxCount = bookList.at(i).getMaxCount();
		outAvailableCount = bookList.at(i).getAvailableCount();
		outReserveDate = bookList.at(i).getReserveDate();
		outFavor = bookList.at(i).getFavor();
		outReserveDate = bookList.at(i).getReserveDate();
		outNumberOfReservee = bookList.at(i).getNumbOfReservees();


		bookFile << outISBN << " " << outTitle << " " << outAuthor << " " <<
			outCategory << " " << outMaxCount << " " << outAvailableCount << " " <<
			outReserveDate << " " << outFavor << " " << outNumberOfReservee;

		//checks to see if there is any reader's on the reservation list
		if (bookList.at(i).getReserveeList().size() > 0) {
			//loop sto store any readers that reserved the book to the file
			for (size_t j = 0; j < bookList.at(i).getReserveeList().size(); j++) {
				bookFile << " " << bookList.at(i).getReserveeList().at(j);
			}
		}
		bookFile << "\n"; //seperates each book to a different line

		//loops through all the copies of a book and stores them to a file
		for (size_t j = 0; j < bookList.at(i).getCopyList().size(); j++) {
			outISBN = bookList.at(i).getCopyList().at(j).getISBN();
			outID = bookList.at(i).getCopyList().at(j).getID();
			outTitle = bookList.at(i).getCopyList().at(j).getTitle();
			outAuthor = bookList.at(i).getCopyList().at(j).getAuthor();
			outCategory = bookList.at(i).getCopyList().at(j).getCategory();
			outReaderName = bookList.at(i).getCopyList().at(j).getReaderName();
			outCheckOut = bookList.at(i).getCopyList().at(j).getCheckOut();
			outExpiration = bookList.at(i).getCopyList().at(j).getExpiration();
			copyFile << outISBN << " " << outID << " " << outTitle << " " << outAuthor << " " << outCategory << " "
				<< outReaderName << " " << outCheckOut << " " << outExpiration;
			copyFile << "\n"; //seperates each copy to a different line
		}
	}
	bookFile.close();
	copyFile.close();
}

template<typename tReader>
void storeReaderToFile(ofstream& file, vector<tReader>& list){
	//declare temporary variables
	string outUsername;
	string outPassword;
	int outCopies;
	int outPenalties;
	int outNumberofReservedBook;

	//loops to put all information of the student vector into student file
	for (size_t i = 0; i < list.size(); i++) {
		outUsername = list.at(i).getUsername();
		outPassword = list.at(i).getPassword();
		outCopies = list.at(i).getCopies();
		outPenalties = list.at(i).getPenalties();
		outNumberofReservedBook = list.at(i).getNumbOfReservedBooks();
		

		//outputs all information into the teacher file from the object
		file << outUsername << " " << outPassword << " " << outCopies << " " << outNumberofReservedBook << " " << outPenalties;
		//loops through all titles in the vector and outputs them to the text file
		for (size_t j = 0; j < list.at(i).getTitlesVec().size(); j++) {
			file << " " << list.at(i).getTitlesVec().at(j);
		}

		//loops through all book in the reservation
		for (size_t j = 0; j < list.at(i).getReservationList().size(); j++) {
			file << " " << list.at(i).getReservationList().at(j);
		}

		file << "\n"; //seperates each reader to a different line		
	}
	file.close();
}

void storeLibrarianToFile(ofstream& librarianFile, vector<Librarian>& librarianList) {
	string outUsername;
	string outPassword;
	//loops to put all information of the librarian vector into librarian file
	for (size_t i = 0; i < librarianList.size(); i++) {
		outUsername = librarianList.at(i).getUsername();
		outPassword = librarianList.at(i).getPassword();
		librarianFile << outUsername << " " << outPassword << endl;
	}
	librarianFile.close();
}

template<typename T_vector>
int verify(vector<T_vector>& List) {
	string maskPassword();


	string inputUsername, inputPassword; //used to store the user's username and password input
	bool loginFlag = false; //used to see if the suer has logged in or not
	size_t vecLocation;// gives the location in the vector that the user is

	//loops until the user has tried to login with 5 attempts
	for (int attempts = 4; attempts >= 0; attempts--) {
		//prompts the user to input their username ans password
		cout << "\nPlease Enter your username: " << endl;
		cin >> inputUsername;
		cout << "\nPlease Enter your password: " << endl;
		inputPassword = maskPassword();

		//loops through all students to find the student the authenticate them
		for (vecLocation = 0; vecLocation < List.size(); vecLocation++) {
			//cout << "\npassword input: " << inputPassword << "vs. " << List.at(vecLocation).getPassword() << endl; //check password input
			if (inputUsername.compare(List.at(vecLocation).getUsername()) == 0) {
				//cout << "It's here!!" << endl;
				//cout << "\n testing1: |" << inputPassword << "|" << endl;
				//cout << "\n testing2: |" << List.at(vecLocation).getPassword() << "|" << endl;
				if (inputPassword.compare(List.at(vecLocation).getPassword()) == 0) {
					//cout << "---password also correct!" << endl;
					loginFlag = true; //changes flag to true if they have logged in successfully

					cout << "\nWelcome " << inputUsername << "!" << endl;
					//cout << "location: " << vecLocation << endl;
					return (int)vecLocation;
				}
			}
		}

		//if the the login flag is true, then the user has logged in, if not then they have attempted to many times
		/*if (loginFlag) {
			cout << "\nWelcome " << inputUsername << "!" << endl;
			return vecLocation;
		}*/
		if (!loginFlag)
			cout << "\nIncorrect Username or Password! You have " << attempts << " attempt(s) left!" << endl;
	}
	cout << "\nToo many wrong attempts!" << endl;
	exit(1);

}



//gives the actions that the student is able to perform
template <typename tReader>
void readerControlPanel(vector<Book>& bookList, vector<tReader>& readerList, tReader& readerObj) {
	int dayCounter();// declares the function for the time
	int selection(0);// holder variable for the user selection
	int dayCount;// declares day count to record the date to be passed into a function
	int renewISBN, CopyID;
	
	//cout << readerObj.getUsername() << endl;
	while (selection != 'l') {

		//tells the user what books they have checked out
		showCheckedOutBooks(bookList, readerObj);
		showReservedBooks(bookList, readerObj);

		//tells the user what options are available
		cout << "\n(1) - borrow copy" << endl;
		cout << "(2) - renew book" << endl; //testing. successful. issue with book.txt not updating correctly
		cout << "(3) - return copy" << endl;
		cout << "(4) - reserve book" << endl;
		cout << "(5) - cancel reservation" << endl;
		cout << "(6) - book recommendation" << endl;
		cout << "(l) - logout" << endl;

		cout << "\nCurrent Day: " << dayCounter() << endl;

		//prompts the user for an input for a selection
		cout << "\nPlease select an option: ";
		cin >> selection;

		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input stream

		selection = tolower(selection);// changes to lower case in the case that the user types an uppercase ie. B instead of b
		dayCount = dayCounter();// calculates the time prior to invoking the function

		removeReaderFromReservations(bookList, readerList, dayCount);

		//invokes a different function depending on the input for selection
		switch (selection) {
		case '1':
			readerObj.borrowCopy(bookList, dayCount);
			break;
		case '2':
			readerObj.returnCopy(bookList, dayCount);
			break;
		case '3':
			readerObj.reserveBook(bookList, dayCount);
			break;
		case '4':
			readerObj.cancelReservation(bookList);
			break;
		case '5':
			cout << "Enter ISBN" << endl;
			cin >> renewISBN;
			cout << "Enter ID" << endl;
			cin >> CopyID;
				readerObj.renewBook(bookList, dayCount, renewISBN, CopyID);
			break;
		case'6':
			readerObj.recommendBooks(bookList);
			break;
		case 'l':
			cout << "\nLogging out..." << endl;
			break;
		default:
			cout << "\nNot a valid action" << endl;
			break;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

template <typename tReader>
void removeReaderFromReservations(vector<Book>& bookList, vector<tReader> &readerList, int dayCount) {
	bool reservedBookFlag = false;
	vector<string> tempReserveList;
	//removes any person(s) who are past the days they can reserve books
	for (size_t i = 0; i < bookList.size(); i++) {
		bookList.at(i).checkReserveeList(dayCount);
	}
	//loops through all readers
	for (size_t i = 0; i < readerList.size(); i++) {
		//loops through all reserved books for the reader
		for (size_t j = 0; j < readerList.at(i).getReservationList().size(); j++) {
			reservedBookFlag = false;
			tempReserveList = readerList.at(i).getReservationList();
			//loops through all books
			for (size_t k = 0; k < bookList.size(); k++) {
				//loops through all reservees for book
				for (size_t l = 0; l < bookList.at(k).getReserveeList().size(); l++) {
					//check if the user is still able to reserve the book
					if (readerList.at(i).getUsername().compare(bookList.at(k).getReserveeList().at(l)) == 0) {
						reservedBookFlag = true;
						break;
					}
				}
				if (reservedBookFlag)
					break;
			}
			//if the book is not found in the reservee list, remove the book from teh student's list of reservatin
			if (!reservedBookFlag) {
				readerList.at(i).removeFromReservation(readerList.at(i).getReservationList().at(j));
				j--;
			}
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input stream
	}
}

//the control panel for librarian
void librarianControlPanel(vector<Book>& bookList, vector<Librarian>& librarianList, Librarian& librarianObj, vector<Student>& studentList, vector<Teacher>& teacherList) {
	int dayCounter();

	int inputSelect = 0; //the input they will enter
	int forCopy = 0;

	//Librarian libTest;

	while (inputSelect != 9) {//will only stop when they enter 9
	//the list of options
		cout << "\nWelcome Librarian!";
		cout << " What would you like to do?\n";
		cout << "(1) - Search Users\n";
		cout << "(2) - Search Books\n";
		cout << "(3) - Add Students\n";
		cout << "(4) - Remove Students\n";
		cout << "(5) - Add Teachers\n";
		cout << "(6) - Remove Teachers\n";
		cout << "(7) - Add Books\n";
		cout << "(8) - Remove Books\n";
		cout << "(9) - Return to Main Menu\n";

		cout << "\nCurrent Day: " << dayCounter() << endl;

		cin >> inputSelect;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input stream

		switch (inputSelect) {

			case 1:
				librarianObj.searchUsers(studentList, teacherList, librarianList);
				break;
			case 2:
				librarianObj.searchBooks(bookList);
				break;
			case 3:
				librarianObj.addReaders( studentList);
				break;
			case 4:
				librarianObj.removeReaders(studentList);
				break;
			case 5:
				librarianObj.addReaders(teacherList);
				break;
			case 6:
				librarianObj.removeReaders(teacherList);
				break;
			case 7:
				cout << "(1) - Add copies to a existing book\n(2) - Add new books\n";
				cin >> forCopy;
				if(forCopy == 1){
					librarianObj.addCopies(bookList);
				}
				else if (forCopy == 2) {
					librarianObj.addNewBooks(bookList);
					sort(bookList, 1);
				}
				else {
					cout << "\nInvalid input, going back to librarian control panel!\n";
				}
				break;
			case 8:
				cout << "(1) - Remove some copies to an existing book\n(2) - Remove all copies of a book\n";
				cin >> forCopy;
				if (forCopy == 1) {
					librarianObj.removeCopies(bookList);
				}
				else if (forCopy == 2) {
					librarianObj.removeBooks(bookList);
					sort(bookList, 1);
				}
				else {
					cout << "\nInvalid input, going back to librarian control panel!\n";
				}
				break;
			case 9:
				inputSelect = 9;
				cout << "\nReturning to the main menu!\n";
				break;
			default:
				cout << "\nInvalid input, please try again!\n";
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input stream
	}
}

//shows the books checked out by the student
template<typename tReader>
void showCheckedOutBooks(vector<Book>& bookList, tReader& readerObj) {
	if (readerObj.getCopies() > 0) {
		cout << "\nBooks checked out: " << endl;
		//loops through all the books checked out by the student
		for (size_t i = 0; i < readerObj.getTitlesVec().size(); i++) {
			cout << "\nBook " << (i + 1) << ":" << endl;

			//loops through the books to match the title and user to display the copy of the book the student has
			for (size_t j = 0; j < bookList.size(); j++) {
				// if ISBN matches, search copies for that book for a match
				if (readerObj.getTitlesVec().at(i).compare(bookList.at(j).getTitle()) == 0) {
					//loops through the copy list to find the reader's copy of the book
					for (size_t k = 0; k < bookList.at(j).getCopyList().size(); k++) {
						if (readerObj.getUsername().compare(bookList.at(j).getCopyList().at(k).getReaderName()) == 0) {
							cout << "ISBN: " << bookList.at(j).getCopyList().at(k).getISBN() << endl;
							cout << "ID: " << bookList.at(j).getCopyList().at(k).getID() << endl;
							cout << "Title: " << bookList.at(j).getCopyList().at(k).getTitle() << endl;
							cout << "Author: " << bookList.at(j).getCopyList().at(k).getAuthor() << endl;
							cout << "Check-out day: " << bookList.at(j).getCopyList().at(k).getCheckOut() << endl;
							cout << "Expiration day: " << bookList.at(j).getCopyList().at(k).getExpiration() << endl;
							break;
						}
					}
				}
			}
		}
	}
	else
		cout << "\nYou have not checked out any books" << endl;
}

template<typename tReader>
void showReservedBooks(vector<Book>& bookList, tReader& readerObj) {
	if (readerObj.getNumbOfReservedBooks() > 0) {
		cout << "\nBooks reserved: " << endl;
		//loops through all the books checked out by the student
		for (size_t i = 0; i < readerObj.getReservationList().size(); i++) {
			cout << "\nReserved Book: " << (i + 1) << ":" << endl;

			//loops through the books to match the title and user to display the copy of the book the student has
			for (size_t j = 0; j < bookList.size(); j++) {
				// if ISBN matches, search copies for that book for a match
				if (readerObj.getReservationList().at(i).compare(bookList.at(j).getTitle()) == 0) {
					//loops through the reserved list to find the reader's name of the book
					for (size_t k = 0; k < bookList.at(j).getReserveeList().size(); k++) {
						if (readerObj.getUsername().compare(bookList.at(j).getReserveeList().at(k)) == 0) {
							cout << "ISBN: " << bookList.at(j).getISBN() << endl;
							cout << "Title: " << bookList.at(j).getTitle() << endl;
							cout << "Author: " << bookList.at(j).getAuthor() << endl;
							break;
						}
					}
				}
			}
		}
	}
	else
		cout << "\nYou have not reserved any books" << endl;
}

//returns the current day
int dayCounter() {
	//declare and initiliaze variables
	int tempDay = 0;// keeps the current day
	int tempSecond = 0;// keeps the current seconds
	finish = clock();// stores the time as of running this function to find the seconds then converts to days

	//calculates the time in seconds
	tempSecond = (((finish - start)) / (CLK_TCK));
	//converts the time in seconds into "days"
	tempDay = tempSecond / 5;
	//cout << "the day " << tempDay << endl;
	return tempDay;
}



// shows * while entering the password
string maskPassword() {

	const char BACKSPACE = 8;//ASCII code for BACKSPACE Key
	const char ENTER = 13;//ASCII code for ENTER Key
	string pass;//initialize string
	char c = ' ';//initialize character 

	//loops until the ENTER keystroke is inputted
	while ((c = _getch()) != ENTER) {
		//checks for a backspace keystroke, take take out the last character if true, otherwise add characters to string
		if (c == BACKSPACE) {
			if (pass.length() != 0) {
				cout << "\b \b"; // deleted a character in console
				pass.resize(pass.length() - 1); //resize the length of the password, effectivly removes teh last character of password

			}
		}
		else {
			pass.push_back(c); //add a character to the end of the password
			cout << '*'; //outputs a asterisk to the console instead of the character for password
		}
	}
	cout << endl;// adds a \n to go to the next line after masking password
	return pass;
}



