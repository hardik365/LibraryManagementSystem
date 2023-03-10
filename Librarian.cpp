//ESE 224 Project 2nd Submission
//Copyright by the following
//Brian Cheung 112797337
//Beryl Chen 112691811
//Sila Atalar 113165359
//Hardik Shahu 170060996

#include "Librarian.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#include "Reader.h"
#include "Student.h"
#include "Teacher.h"
#include "Book.h"
#include "User.h"


//Librarian.txt format: username password

//takes information from istream and sets the object with those values
istream& operator >> (istream& librarianFile, Librarian& librarianObj) {
	//declare variables used to temporarily hold information to be loaded into the object
	static string inUsername, inPassword;

	librarianFile >> inUsername >> inPassword;

	librarianObj.getUsername() = inUsername;
	librarianObj.getPassword() = inPassword;

	return librarianFile;
}

ostream& operator << (ostream& outputStream, Librarian& librarianObj) {
	string outUsername = librarianObj.getUsername();
	string outPassword = librarianObj.getPassword();

	outputStream << left << setw(10) << outUsername << left << setw(20) << outPassword << endl;

	outputStream << "\n"; //seperates each librarian to a different line
	return outputStream;
}




// librarian functions
void Librarian::searchBooks(vector<Book>& bookList) {//searches for books regardless by any keywords
	//declares the variables
	string inputTitle, inputAuthor, inputCat; //varibles for the inputs they might enter depending on which case they pick
	int inputISBN, inputSelect;				 //^^
	int cond = 1; //so they enter a wrong input it will allow them to try again
	int anyBooks = 0; //flag for if any books are found with a case


	while (cond == 1) {
		//inputSelect = 1;
		anyBooks = 0;
		cout << "\nHow would you like to search for a book?\n";
		cout << "(1) - By Title\n";
		cout << "(2) - By ISBN\n";
		cout << "(3) - By Category\n";
		cout << "(4) - By Author\n";
		cout << "(5) - Quit\n";
		cin >> inputSelect;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');


		if (inputSelect == 1) {//if they want to search by title
			cout << "Enter a title:(Use '-' for spaces)\n";
			getline(cin, inputTitle);
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
			cin.clear();
		}

		else if (inputSelect == 3) { //if they want to search by category
			cout << "Enter a Category: ";
			cin >> inputCat;
			for (size_t i = 0; i < bookList.size(); i++) { //loops through the book class and searches for the matching Category
				if (inputCat.compare(bookList.at(i).getCategory()) == 0) {
					anyBooks = 1;
					cout << "\nISBN: " << bookList.at(i).getISBN() << endl;
					cout << "Title: " << bookList.at(i).getTitle() << endl;
					cout << "Author: " << bookList.at(i).getAuthor() << endl;
					cout << "Category: " << bookList.at(i).getCategory() << endl;
				}
			}
			if (anyBooks == 0)
				cout << "\nNo books were found with that Category!\n";
		}

		else if (inputSelect == 4) { //if they want to search by author
			cout << "Enter a Author: ";
			cin >> inputAuthor;
			for (size_t i = 0; i < bookList.size(); i++) {  //loops through the book class and searches for the matching author
				if (inputAuthor.compare(bookList.at(i).getAuthor()) == 0) {
					anyBooks = 1;
					cout << "\nISBN: " << bookList.at(i).getISBN() << endl;
					cout << "Title: " << bookList.at(i).getTitle() << endl;
					cout << "Author: " << bookList.at(i).getAuthor() << endl;
					cout << "Category: " << bookList.at(i).getCategory() << endl;
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void Librarian::searchUsers(vector<Student>& studentList, vector<Teacher>& teacherList, vector<Librarian>& librarianList) //searches for users 
{
	//delacares our variables we will need
	vector <Librarian> Test = librarianList;

	string inputUsername; //username they wish to search for
	int inputSelect; //choice they will make 
	int cond = 1; //to enable loop
	int success; //to see if they found the username they searched for
	while (cond == 1) { //will loop until the conditonal is 1

		success = 0; //0 means not successful and it's thew default case, and 1 is successful and it will be activited when it finds a user with that username
		cout << "What type of user would you like to search for?\n";
		cout << "(1) - Student\n";
		cout << "(2) - Teacher\n";
		cout << "(3) - Librarian\n";
		cout << "(4) - Quit\n";
		std::cin >> inputSelect;

		switch (inputSelect) {
		case 1: //if they wish to search a student
			cout << "Enter a Student's Username\n";
			cin >> inputUsername;
			for (size_t i = 0; i < studentList.size(); i++) {
				if (inputUsername.compare(studentList.at(i).getUsername()) == 0) {
					success = 1;
					cout << "\nUsername: " << studentList.at(i).getUsername() << endl;
					cout << "Password: " << studentList.at(i).getPassword() << endl;

					//loops through all the books checked out by the student
					for (size_t j = 0; j < studentList.at(i).getTitlesVec().size(); j++) {
						cout << "Book " << (j + 1) << ": ";
						cout << studentList.at(i).getTitlesVec().at(j) << endl;
					}
				}
			}
			if (success == 0) //if not found
				cout << "Username with " << inputUsername << " was not found!\n";
			break;
		case 2: //if they wish to search for teacher
			cout << "Enter a Teacher's Username\n";
			cin >> inputUsername;
			for (size_t i = 0; i < teacherList.size(); i++) {
				if (inputUsername.compare(teacherList.at(i).getUsername()) == 0) {
					success = 1;
					cout << "\nUsername: " << teacherList.at(i).getUsername() << endl;
					cout << "Password: " << teacherList.at(i).getPassword() << endl;

					//loops through all the books checked out by the student
					for (size_t j = 0; j < teacherList.at(i).getTitlesVec().size(); j++) {
						cout << "Book " << (j + 1) << ": ";
						cout << teacherList.at(i).getTitlesVec().at(j) << endl;

					}
				}

			}
			if (success == 0) //if not found
				cout << "Username with " << inputUsername << " was not found!\n";
			break;
		case 3: //if they wish to search for a librarian
			cout << "Enter a Librarian's Username\n";
			cin >> inputUsername;
			for (size_t i = 0; i < librarianList.size(); i++) {
				if (inputUsername.compare(Test.at(i).getUsername()) == 0) {
					success = 1;
					cout << "\nUsername: " << librarianList.at(i).getUsername() << endl;
					cout << "Password: " << librarianList.at(i).getPassword() << endl;
				}
			}
			if (success == 0)
				cout << "Username with " << inputUsername << " was not found!\n";
			break;
		case 4: //will quit the program if they hit 4
			cout << "Quiting the search users prgram!";
			cond = 0;
			break;
		default://if they type a wrong input
			cout << "Error: Wrong input, please try again!";
			break;
		}
	}
}

void Librarian::addNewBooks(vector<Book>& bookList) { //adds new books

	//these will be inputed by the librarian
	string inputAuthor, inputTitle, inputCat;
	int inputISBN, inputNumberCopies;
	int inputSelect;
	int successISBN = 1, successTitle = 1;

	string defaultReader = "[available]"; //is the default

	int cond = 1; //will be used for the master loop

	while (cond == 1) { // 1 means go 0 means stop

		cout << "\nEnter the ISBN for the new book: ";
		cin >> inputISBN;

		cout << "\nEnter the title for the new book(use '-' for spaces): ";
		cin >> inputTitle;

		cout << "\nEnter the author for the new book(use '-' for spaces): ";
		cin >> inputAuthor;

		cout << "\nEnter the category for the new book: ";
		cin >> inputCat;

		cout << "\nHow many of copies these books will be added? (must be atleast 1):";
		cin >> inputNumberCopies;

		for (size_t i = 0; i < bookList.size(); i++) {
			if (inputTitle.compare(bookList.at(i).getTitle()) == 0) {
				successTitle = 0;
				break;
			}
		}
		for (size_t i = 0; i < bookList.size(); i++) {
			if (inputISBN == bookList.at(i).getISBN()) {
				successISBN = 0;
				break;
			}
		}

		if (inputNumberCopies <= 0) {
			cout << "\nError! Book adding cancelled, the number of copies can't be less than 1!\n";
			break;
		}
		if (successISBN == 0) {
			cout << "\nError! Book adding cancelled, book with this ISBN already exists!\n";
			break;
		}
		if (successTitle == 0) {
			cout << "\nError! Book adding cancelled, book with this Title already exists!\n";
			break;
		}
		//needed to add the new entry to the vector
		vector<Copy> tempCpyVec;
		vector<string> tempStrVec;

		Book tempBook(inputISBN, inputTitle, inputAuthor, inputCat, inputNumberCopies, inputNumberCopies, tempCpyVec, 0, 0, 0, tempStrVec);
		bookList.push_back(tempBook);

		cout << bookList.size();

		cout << "\nSuccessfully added the book to the library!\n";//lets the user know that they were able to add that book

		cout << "Would you like to add another book?\n(1) - Yes\n(2) - No\n"; //if they want to stop adding a book
		cin >> inputSelect;

		if (inputSelect == 2)// will stop the loop
			cond = 0;
		else if (inputSelect == 1) //will not stop
			cond = 1;
		else { //if they try to enter a wrong input
			cout << "\nWarning, you pressed an incorrect input, exiting the adding books function!\n";
			cond = 0;
		}
	}
}

void Librarian::removeBooks(vector<Book>& bookList) { //removes all copies of a book
	string inputTitle; //the inputed title
	int cond = 1; //for the master loop
	int successTitle = 0; //flag to check for if that title exists in the list
	static int eraseBookLocation; //stores the location where the book is in the list
	int userInput; //if they want to continue or not

	while (cond == 1) {
		cout << "Enter the title of the book you wanna delete: ";
		cin >> inputTitle;

		for (size_t i = 0; i < bookList.size(); i++) {
			if (inputTitle.compare(bookList.at(i).getTitle()) == 0) {//to find that book
				if (bookList.at(i).getAvailableCount() == bookList.at(i).getMaxCount()) { //makes sure that no one has that book checked out
					successTitle = 1; //able to remove the book
					eraseBookLocation = (int)i; //location of the book
					break;
				}
				else {
					successTitle = -1; //can't remove that book bc someone has it checked out
					break;
				}
			}

		}
		if (successTitle == 0) {
			cout << "\nError! The title you entered does not exist in the library! Exiting the remove books function!\n";
			break;

		}
		else if (successTitle == -1) {
			cout << "\nError! The title you entered can't be removed because it is checked out by some students! Exiting the remove books function\n";
			break;
		}

		bookList.erase(bookList.begin() + eraseBookLocation); //erases the book

		cout << "\nAll copies of " << inputTitle << " have been removed!\n"; //lets them know that all copies of that book have been deleted
		cout << "\nWanna remove more books?\n(1) - Yes\n(2) - No\n"; //asks them if they want to remove more books or stop
		cin >> userInput;

		if (userInput == 2) //stops the loop
			cond = 0;
		else if (userInput == 1) //continues the loop
			cond = 1;
		else //if they try to enter a wrong input
			cout << "\nWrong input, the remove books function is now being exited!\n";
		cond = 0;
	}
}

void Librarian::removeCopies(vector<Book>& bookList) { //remove copies from a book

	string inputTitle; //title of the book they wish to add copies to
	int inputCopies; //number or copies they wish to add
	int cond = 1;//for the masterloop
	int successTitle = 0; //flag for finding the title successfully
	int NumCopies; //the number of copies the book initially has that arent checked out
	int location; //the index of where the book is located in the booklist
	int maxCopies; //the max number of copies that book has
	int select; //if they want to continue or stop

	while (cond == 1) { //will stop until it reaches 0

		cout << "Enter the title of the book you would like to remove copies of(use '-' for spaces!): ";
		cin >> inputTitle;

		for (size_t i = 0; i < bookList.size(); i++) { //checks to see if the book is there
			if (inputTitle.compare(bookList.at(i).getTitle()) == 0) {
				successTitle = 1; //flag for the finding the title
				NumCopies = bookList.at(i).getAvailableCount(); //stores the numb of copies available
				maxCopies = bookList.at(i).getMaxCount(); //stores the max number of copies
				location = (int)i; //stores the index of that title
				break;
			}
		}

		if (successTitle == 0) { //if the title was not found
			cout << "\nError! Book title not found, removing copies has been canceled!\n";
			break;
		}

		cout << "\nHow many copies would you like to remove? (Must have atleast 1 remaining): ";
		cin >> inputCopies;
		if (inputCopies <= 0) {
			cout << "\nCan't remove negative or zero books!adding copies has been canceled!\n";
			break;
		}

		if ((NumCopies - inputCopies) <= 0) { //if they try to remove more copies than available
			cout << "\nError! Trying to remove more copies than the library has available, removing copies has been canceled!\n";
			break;
		}

		//removes the copies  
		bookList.at(location).setAvailableCount(NumCopies - inputCopies);
		bookList.at(location).setMaxCount(maxCopies - inputCopies);

		cout << "\n" << inputCopies << " copies has been removed!\nWould you like to remove more copies of another book?";// tells them that the copies has been removed and asks them if they want to continue removing copies
		cout << "\n(1) - Yes\n(2) - No\n";
		cin >> select;

		if (select == 2) //if they want to stop
			cond = 0;
		else if (select == 1)//if they want to continue
			cond = 1;
		else { //if they enter a wrong input
			cout << "Warning! Incorrect selection, exiting the remove copies function!\n";
			cond = 0;
		}
	}
}

void Librarian::addCopies(vector<Book>& bookList) //adds copies to pre existing books
{
	string inputTitle; //title of the book they wish to add copies to
	int inputCopies; //number or copies they wish to add
	int cond = 1;//for the masterloop
	int successTitle = 0; //flag for finding the title successfully
	int location; //the index of where the book is located in the booklist
	int NumCopies, maxCopies; //to store the number that the library currently has and the max they can ever have
	int select;

	while (cond == 1) {

		cout << "Enter the title of the book you would like to add copies of(use '-' for spaces!): ";
		cin >> inputTitle;

		for (size_t i = 0; i < bookList.size(); i++) { //checks to see if the book is there
			if (inputTitle.compare(bookList.at(i).getTitle()) == 0) {
				successTitle = 1; //flag for the finding the title
				NumCopies = bookList.at(i).getAvailableCount(); //stores the numb of copies available
				maxCopies = bookList.at(i).getMaxCount(); //stores the max number of copies
				location = (int)i; //stores the index of that title
				break;
			}
		}

		if (successTitle == 0) { //if the title was not found
			cout << "\nError! Book title not found, adding copies has been canceled!\n";
			break;
		}

		cout << "\nHow many copies would you like to add?: ";
		cin >> inputCopies;
		if (inputCopies <= 0) {
			cout << "\nCan't add negative or zero books! Adding copies has been canceled!\n";
			break;
		}

		//adds those copies
		bookList.at(location).setAvailableCount(NumCopies + inputCopies);
		bookList.at(location).setMaxCount(maxCopies + inputCopies);

		cout << "\n" << inputCopies << " copies has been added!\nWould you like to add more copies of another book?";// tells them that the copies has been added and asks them if they want to continue adding copies
		cout << "\n(1) - Yes\n(2) - No\n";
		cin >> select;

		if (select == 2) //if they want to stop
			cond = 0;
		else if (select == 1) //if they want to continue
			cond = 1;
		else { //if they try to enter wrong input
			cout << "Warning! Incorrect selection, exiting the adding copies function!\n";
			cond = 0;
		}
	}
}
