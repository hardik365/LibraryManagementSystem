//ESE 224 Project 2nd Submission
//Copyright by the following
//Brian Cheung 112797337
//Beryl Chen 112691811
//Sila Atalar 113165359
//Hardik Shahu 170060996

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
using namespace std;
class Book;
class Student;
class Teacher;
class Reader;


class Librarian: virtual public User
{
public:
	//constructors
	Librarian() : User() {}
	Librarian(string username, string password) : User(username, password) {}

	//librarian functions
	void addNewBooks(vector<Book>& bookList);
	void removeBooks(vector<Book>& bookList);

	void removeCopies(vector<Book>& bookList);
	void addCopies(vector<Book>& bookList);

	void searchBooks(vector<Book>& bookList);
	void searchUsers(vector<Student>& studentList, vector<Teacher>& teacherList, vector<Librarian>& librarianList);
	
	template<typename tReader>
	void addReaders(vector<tReader>& readerList) {
		string inputUsername, inputPassword; //the inputs that will be needed for adding a new user
		int cond = 1, inputSelect;
		int successUser = 1;

		while (cond == 1) { //will stop until cond is 0

			cout << "Enter username for the new user: ";
			cin >> inputUsername;
			cout << "\nEnter the password for the new user: ";
			cin >> inputPassword;


			for (size_t i = 0; i < readerList.size(); i++) { //checks a user with that name is already present, if so it will not let them add that user
				if (inputUsername.compare(readerList.at(i).getUsername()) == 0) {
					successUser = 0;
					break;
				}
			}

			if (successUser == 0) {
				cout << "\nError! A user with this username already exists, adding user function cancelled!\n";
				break;
			}

			vector<string> TempTitles;
			vector<string> TempBookReserve;

			//Reader Text File Format: username, password, copies, penalties, reserved books
			tReader newReader(inputUsername, inputPassword,0,0,0,TempTitles, TempBookReserve);
			readerList.push_back(newReader);

			cout << "\nSuccessfully, added " << inputUsername << " as a user!\n";

			cout << "Would you like to add another user?\n(1) - Yes\n(2)- No\n"; //if they want to stop adding a user
			cin >> inputSelect;

			if (inputSelect == 2)// will stop the loop
				cond = 0;
			else if (inputSelect == 1) //will continue the loop
				cond = 1;
			else {//if they try to be enter a wrong function
				cout << "\nWarning, you pressed an incorrect input, exiting the adding users fucnction!\n";
				cond = 0;
			}
		}
	}
	
	template<typename tReader>
	void removeReaders(vector<tReader>& readerList) {

		string inputUsername; //username they are inputing to remove
		int cond = 1; //master loop
		int successUser = 0;
		static int eraseTeacherLocation; //stores the location for its offset in the list to erase it from the list
		int inputSelect; //if they want to continue the program or stop;

		while (cond == 1) {

			cout << "\nEnter the username of the user you would like to remove: ";
			cin >> inputUsername;

			for (size_t i = 0; i < readerList.size(); i++) {//finds that reader
				if (inputUsername.compare(readerList.at(i).getUsername()) == 0) {
					if (readerList.at(i).getCopies() == 0) { //checks if they have any books checked out, bc if they do, then it wont let them remove taht reader.
						successUser = 1; //flags that they can remove that reader
						eraseTeacherLocation = (int)i;
						break;
					}
					else
						successUser = -1; //flags that they can't remove that reader bc they have a book checked out
				}
			}
			if (successUser == 0) {
				cout << "\nError! Couldn't find username ' " << inputUsername << " ' , the removing users program will exit!\n";
				break;
			}
			else if (successUser == -1) {
				cout << "\nError! Couldn't remove user because they have a book checked out! The removing users program will exit!\n";
				break;
			}


			readerList.erase(readerList.begin() + eraseTeacherLocation); //erases the user

			cout << "\nUser " << inputUsername << " has been removed!\n";
			cout << "Would you like to remove another user?\n(1) - Yes\n(2) - No\n";
			cin >> inputSelect;

			if (inputSelect == 2)// will stop the loop
				cond = 0;
			else if (inputSelect == 1) //will continue the loop
				cond = 1;
			else { //if they enter a wrong input
				cout << "\nWarning, you pressed an incorrect input, exiting the removing users fucnction!\n";
				cond = 0;
			}
		}
	}
};

