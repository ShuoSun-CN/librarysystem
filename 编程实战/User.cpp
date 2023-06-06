#define _CRT_SECURE_NO_WARNINGS
#include "User.h"

Student::Student()
{
	idOfBorrowBook.reserve(MAXBOOKS);
	stuBorrowNum = 0;
}

Student::Student(std::string id)
{
	idNum = id;
	passWord = "none";
	idOfBorrowBook.reserve(MAXBOOKS);
	stuBorrowNum = 0;
}
curUser::curUser() {}

curUser::curUser(std::string id)
{
	this->idNum = id;
}

void curUser::setID(std::string id)
{
	this -> idNum = id;
}

std::string curUser::getID()
{
	return idNum;
}