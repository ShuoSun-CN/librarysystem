
#include "library.h"


Library::Library() {
    int AllBook, AllStudent;
    ifstream fin("books.txt");
    if (fin) {
        fin >> AllBook;
        for (int i = 0; i < AllBook; i++) {
            Book tem;
            fin >> tem.idNum >> tem.bookName >> tem.totalNum >> tem.restNum;
            dataOfBooks.push_back(tem);
        }
        fin.close();
    }
    showAllBook();

    ifstream sfin("students.txt");
    string s;
    if (sfin) {
        sfin >> AllStudent;
        for (int i = 0; i < AllStudent; i++) {
            Student tem;
            sfin >> tem.idNum >> tem.stuBorrowNum;
            for (int j = 0; j < tem.stuBorrowNum; j++) {
                sfin >> s;
                tem.idOfBorrowBook.push_back(s);
            }
            dataOfUsers.push_back(tem);
        }
        sfin.close();
    }
}

void Library::addBook(const char* temp)
{
    bool err = false;
    stringstream outStr(temp);
    Book* newBook = new Book;
    outStr >> newBook->idNum >> newBook->bookName >> newBook->totalNum;
    newBook->restNum = newBook->totalNum;
    cout << newBook->idNum << newBook->bookName << newBook->totalNum << newBook->totalNum << endl;
    for (int i = 0; i < (int)dataOfBooks.size(); i++) {
        if (newBook->idNum == dataOfBooks[i].idNum) {
            MessageBox(GetHWnd(), "该书籍已存在，书籍添加失败", "提示", MB_OK);
            err = true;
            break;
        }
    }
    if (err == false) dataOfBooks.push_back(*newBook);
}

void Library::deleteBook(const char* temp)//删除图书
{
    int pos = -1;
    string id, bookname;
    stringstream outStr(temp);
    outStr >> id >> bookname;
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        //同时依据编号和书名判断
        if (dataOfBooks[i].idNum == id && dataOfBooks[i].bookName == bookname){
            pos = i;
        }
    }
    if (pos == -1){
        MessageBox(GetHWnd(), "查无此书！", "提示", MB_OK);
    }
    else{
        dataOfBooks.erase(dataOfBooks.begin() + pos);
    }

}

void Library::borrowBook(string id, string bookName) {
    int pos = -1;
    //找到要借阅的书籍
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        if (bookName == dataOfBooks[i].bookName) {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        MessageBox(GetHWnd(), "查无此书，借书失败！", "提示", MB_OKCANCEL);
        return;
    }

    /*判断是否可借*/
    if (dataOfBooks[pos].restNum > 0) {
        /*可借*/
        dataOfBooks[pos].restNum -= 1;
        int posOfStu = -1;
        for (int i = 0; i != dataOfUsers.size(); ++i) {
            if (id == dataOfUsers[i].idNum) {
                posOfStu = i;
                break;
            }
        }

        dataOfUsers[posOfStu].idOfBorrowBook.push_back(dataOfBooks[pos].idNum);
        dataOfUsers[posOfStu].stuBorrowNum += 1;
        for (size_t i = 0; i < dataOfUsers[posOfStu].idOfBorrowBook.size(); i++)
        {
            cout << dataOfUsers[posOfStu].idOfBorrowBook[i] << ' ';
        }
        cout << dataOfUsers[posOfStu].stuBorrowNum << endl;
        MessageBox(GetHWnd(), "借书成功！", "提示", MB_OK);

    }

    else {
        MessageBox(GetHWnd(), "此书余量不足,借书失败", "提示", MB_OKCANCEL);
    }

}

void Library::returnBook(string id, string nameOfBackBook) {
    /*找到被借的书*/
    int posOfBook = -1;
    for (int i = 0; i != (int)dataOfBooks.size(); ++i) {
        if (dataOfBooks[i].bookName == nameOfBackBook) {
            posOfBook = i;
            break;
        }
    }
    if (posOfBook < 0) {
        MessageBox(GetHWnd(), "书库里没有这本书", "提示", MB_OKCANCEL);
        return;
    }

    /*被借的书余量+1*/
    dataOfBooks[posOfBook].restNum += 1;

    /*找到借书的学生*/
    int posOfStu = -1;
    for (int i = 0; i != (int)dataOfUsers.size(); ++i) {
        if (dataOfUsers[i].idNum == id) {
            posOfStu = i;
            break;
        }
    }

    cout << dataOfUsers[posOfStu].idNum << endl;

    /*学生借书-1，删除学生处的借书记录*/
    int _pos = -1;
    for (int i = 0; i != dataOfUsers[posOfStu].idOfBorrowBook.size(); ++i) {
        if (dataOfBooks[posOfBook].idNum == dataOfUsers[posOfStu].idOfBorrowBook[i]) {
            _pos = i;
            break;
        }
    }

    dataOfUsers[posOfStu].idOfBorrowBook.erase(dataOfUsers[posOfStu].idOfBorrowBook.begin() + _pos);
    dataOfUsers[posOfStu].stuBorrowNum -= 1;
    showAllBook();
    cout << "还书成功！" << endl;
    MessageBox(GetHWnd(), "还书成功！", "提示", MB_OK);
}

void Library::saveStudent() {
    ofstream out("students.txt");
    if (out) {
        out << dataOfUsers.size() << endl;
        for (int i = 0; i < (int)dataOfUsers.size(); i++) {
            out << dataOfUsers[i].idNum << " " << dataOfUsers[i].stuBorrowNum << " ";
            for (int j = 0; j < dataOfUsers[i].stuBorrowNum; j++) {
                out << dataOfUsers[i].idOfBorrowBook[j] << " ";
            }
        }
        out.close();
    }
}

void Library::saveBook() {
    ofstream out("books.txt");
    if (out) {
        out << dataOfBooks.size() << endl;
        for (int i = 0; i < (int)dataOfBooks.size(); i++) {
            out << dataOfBooks[i].idNum << " " << dataOfBooks[i].bookName << " "
                << dataOfBooks[i].totalNum <<" "<<dataOfBooks[i].restNum << endl;
        }
        out.close();
    }
}


void Library::searchBookPosWithName() //按书名查询
{
    int pos = -1;
    char temp[50];
    InputBox(temp, 50, "请输入要查询书籍的名字：");
    string thebook = temp;
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        if (dataOfBooks[i].bookName == thebook){
            pos = i;
        }
    }
    if (pos == -1){
        MessageBox(GetHWnd(), "查无此书！", "提示", MB_OKCANCEL);
    }
    else{
        Table bookTable(112, 200, 1, 4, 200, 30);
        drawMethod();
        bookTable.drawTableGrid();
        setbkmode(TRANSPARENT);
        settextcolor(RGB(5, 5, 5));
        settextstyle(20, 0, "楷体");
        outtextxy(112 + (200 - textwidth(dataOfBooks[pos].idNum.c_str())) / 2, 200 + (30 - textheight(dataOfBooks[pos].idNum.c_str())) / 2, dataOfBooks[pos].idNum.c_str());
        outtextxy(312 + (200 - textwidth(dataOfBooks[pos].bookName.c_str())) / 2, 200 + (30 - textheight(dataOfBooks[pos].bookName.c_str())) / 2, dataOfBooks[pos].bookName.c_str());
        outtextxy(512 + (200 - textwidth(to_string(dataOfBooks[pos].totalNum).c_str())) / 2, 200 + (30 - textheight(to_string(dataOfBooks[pos].totalNum).c_str())) / 2, to_string(dataOfBooks[pos].totalNum).c_str());
        outtextxy(712 + (200 - textwidth(to_string(dataOfBooks[pos].restNum).c_str())) / 2, 200 + (30 - textheight(to_string(dataOfBooks[pos].restNum).c_str())) / 2, to_string(dataOfBooks[pos].restNum).c_str());
    }
}

void Library::searchBookPosWithId() //按检索号搜寻
{
    int pos = -1;
    char temp[50];
    InputBox(temp, 50, "请输入要查询书籍的编号：");
    string id = temp;
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        if (dataOfBooks[i].idNum == id){
            pos = i;
        }
    }
    if (pos == -1){
        MessageBox(GetHWnd(), "查无此书！", "提示", MB_OKCANCEL);
    }
    else {
        Table bookTable(112, 200, 1, 4, 200, 30);
        drawMethod();
        bookTable.drawTableGrid();
        setbkmode(TRANSPARENT);
        settextcolor(RGB(5, 5, 5));
        settextstyle(20, 0, "楷体");
        outtextxy(112 + (200 - textwidth(dataOfBooks[pos].idNum.c_str())) / 2, 200 + (30 - textheight(dataOfBooks[pos].idNum.c_str())) / 2, dataOfBooks[pos].idNum.c_str());
        outtextxy(312 + (200 - textwidth(dataOfBooks[pos].bookName.c_str())) / 2, 200 + (30 - textheight(dataOfBooks[pos].bookName.c_str())) / 2, dataOfBooks[pos].bookName.c_str());
        outtextxy(512 + (200 - textwidth(to_string(dataOfBooks[pos].totalNum).c_str())) / 2, 200 + (30 - textheight(to_string(dataOfBooks[pos].totalNum).c_str())) / 2, to_string(dataOfBooks[pos].totalNum).c_str());
        outtextxy(712 + (200 - textwidth(to_string(dataOfBooks[pos].restNum).c_str())) / 2, 200 + (30 - textheight(to_string(dataOfBooks[pos].restNum).c_str())) / 2, to_string(dataOfBooks[pos].restNum).c_str());
    }
}


void Library::printBook(Book a) {
    cout << setw(8) << a.idNum;
    cout << setw(14) << a.bookName;
    cout << setw(14) << a.totalNum;
    cout << setw(14) << a.restNum << endl;
}

void Library::showAllBook() {
    cout << left;
    cout << setw(8) << "编号" << setw(14) << "书名" << setw(14) << "总数" << setw(14) << "余数" << endl;
    for (int i = 0; i < (int)dataOfBooks.size(); i++) {
        printBook(dataOfBooks[i]);
    }
}

int Library::getBookNum()
{
    return dataOfBooks.size();
}

int Library::getStudentNum()
{
    return dataOfUsers.size();
}

void Library::reviseBook(const char* temp)
{
    stringstream outStr(temp);
    string tarID;//要修改书籍的编号
    outStr >> tarID;

    //找到目的书籍
    int pos = -1;
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        if (dataOfBooks[i].idNum == tarID){
            pos = i;
        }
    }
    if (pos == -1){
        MessageBox(GetHWnd(), "查无此书！", "提示", MB_OK);
    }
    //把修改后的信息输入到目的书籍里
    else {
        outStr >> dataOfBooks[pos].idNum >> dataOfBooks[pos].bookName >> dataOfBooks[pos].totalNum >> dataOfBooks[pos].restNum;
        MessageBox(GetHWnd(), "修改书籍信息成功！", "提示", MB_OK);
    }
    saveBook();
}

void Library::addStudent(const Student stu)
{
    dataOfUsers.push_back(stu);
}
