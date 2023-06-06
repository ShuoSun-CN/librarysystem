#ifndef USER_H__
#define USER_H__


#include<vector>
#include<string>

#define MAXBOOKS 10

class Manager
{
public:
	std::string idNum;
	std::string password;
};

class Student
{
public:
	std::string idNum;//学号
	std::string passWord;//密码
	std::vector<std::string> idOfBorrowBook;//已借书籍编号
	int stuBorrowNum;//借书数
	Student();
	Student(std::string id);
};

class curUser
{
private:
	std::string idNum;
public:
	curUser();
	curUser(std::string);
	void setID(std::string);
	std::string getID();
} ;
#ifndef CURRENTUSER__
#define CURRENTUSER__

extern curUser cur;

#endif // !CURRENTUSER__


#endif
