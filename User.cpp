#include"User.h"
#include<iostream>
#include<string>

using namespace std;

User::User() {
//	cout << "U" << endl;
};

User::User( string username,  string password) {
	Username = username;
	Password = password;
}

//User::User(string username, string password, int num, int penalty) : Username(username), Password(password){};


string User::getUsername() {
	return Username;
}

string User::getPassword() {
	return Password;
}

void User::setUsername(string inUsername) {
	Username = inUsername;
}

void User::setPassword(string inPassword) {
	Password = inPassword;
}

