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
#include "Reader.h"
using namespace std;
//class Book;

class Teacher : virtual public Reader
{
public:
	//constructors
	Teacher() : Reader() {}
	Teacher(string username, string password, int copies = 0, int numReservedBook = 0, int penalties = 0, int maxCopies = 5, int maxTime = 30) :
		Reader(username, password, copies, numReservedBook, penalties, maxTime, maxCopies) {}
	Teacher(string username, string password, int copies, int numReservedBook, int penalties,
		vector<string> titlesVec, vector<string> bookReservationList, int maxCopies = 5, int maxTime = 30) :
		Reader(username, password, copies, numReservedBook, penalties, titlesVec, bookReservationList, maxTime, maxCopies) {}

};