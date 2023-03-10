
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#pragma once
//class Student;
using namespace std;

class User {

protected:
	string Username;
	string Password;


public:
	//constructors
	User();
	User( string username, string password);


	//acessor methods
	string getUsername();
	string getPassword();

	//mutator functions
	void setUsername(string inUsername);
	void setPassword(string inPassword);



};



