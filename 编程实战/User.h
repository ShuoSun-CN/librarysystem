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
	std::string idNum;//ѧ��
	std::string passWord;//����
	std::vector<std::string> idOfBorrowBook;//�ѽ��鼮���
	int stuBorrowNum;//������
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
