#ifndef LIBRARY_H__
#define LIBRARY_H__

#include "Book.h"
#include "User.h"
#include "Table.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include <iomanip>
#include<cstring>
using namespace std;

class Library {
private:
    vector<Book> dataOfBooks;
    vector<Student> dataOfUsers;
public:
    Library();
    void addBook(const char* temp);  //增加图书 √
    void deleteBook(const char* temp);//删除图书 √
    void borrowBook(string id, string bookName);//借阅图书 √
    void returnBook(string id, string nameOfBackBook);//归还图书 √
    void showAllBook(); //输出系统所有图书

    void searchBookPosWithName(); //按书名查询
    void searchBookPosWithId();  //按检索号搜寻


    void saveBook();  //存入图书馆文件
    void saveStudent();//存入学生文件

    void printBook(Book a);//输出某本书的所有信息
    void reviseBook(const char* temp);//修改某本书的信息

    void addStudent(const Student stu);
    
    int getBookNum();
    int getStudentNum();

    friend class Table;
};

#ifndef LIBRARY__
#define LIBRARY__

extern Library lib;

#endif

#endif
