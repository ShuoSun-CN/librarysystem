
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
            MessageBox(GetHWnd(), "���鼮�Ѵ��ڣ��鼮���ʧ��", "��ʾ", MB_OK);
            err = true;
            break;
        }
    }
    if (err == false) dataOfBooks.push_back(*newBook);
}

void Library::deleteBook(const char* temp)//ɾ��ͼ��
{
    int pos = -1;
    string id, bookname;
    stringstream outStr(temp);
    outStr >> id >> bookname;
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        //ͬʱ���ݱ�ź������ж�
        if (dataOfBooks[i].idNum == id && dataOfBooks[i].bookName == bookname){
            pos = i;
        }
    }
    if (pos == -1){
        MessageBox(GetHWnd(), "���޴��飡", "��ʾ", MB_OK);
    }
    else{
        dataOfBooks.erase(dataOfBooks.begin() + pos);
    }

}

void Library::borrowBook(string id, string bookName) {
    int pos = -1;
    //�ҵ�Ҫ���ĵ��鼮
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        if (bookName == dataOfBooks[i].bookName) {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        MessageBox(GetHWnd(), "���޴��飬����ʧ�ܣ�", "��ʾ", MB_OKCANCEL);
        return;
    }

    /*�ж��Ƿ�ɽ�*/
    if (dataOfBooks[pos].restNum > 0) {
        /*�ɽ�*/
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
        MessageBox(GetHWnd(), "����ɹ���", "��ʾ", MB_OK);

    }

    else {
        MessageBox(GetHWnd(), "������������,����ʧ��", "��ʾ", MB_OKCANCEL);
    }

}

void Library::returnBook(string id, string nameOfBackBook) {
    /*�ҵ��������*/
    int posOfBook = -1;
    for (int i = 0; i != (int)dataOfBooks.size(); ++i) {
        if (dataOfBooks[i].bookName == nameOfBackBook) {
            posOfBook = i;
            break;
        }
    }
    if (posOfBook < 0) {
        MessageBox(GetHWnd(), "�����û���Ȿ��", "��ʾ", MB_OKCANCEL);
        return;
    }

    /*�����������+1*/
    dataOfBooks[posOfBook].restNum += 1;

    /*�ҵ������ѧ��*/
    int posOfStu = -1;
    for (int i = 0; i != (int)dataOfUsers.size(); ++i) {
        if (dataOfUsers[i].idNum == id) {
            posOfStu = i;
            break;
        }
    }

    cout << dataOfUsers[posOfStu].idNum << endl;

    /*ѧ������-1��ɾ��ѧ�����Ľ����¼*/
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
    cout << "����ɹ���" << endl;
    MessageBox(GetHWnd(), "����ɹ���", "��ʾ", MB_OK);
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


void Library::searchBookPosWithName() //��������ѯ
{
    int pos = -1;
    char temp[50];
    InputBox(temp, 50, "������Ҫ��ѯ�鼮�����֣�");
    string thebook = temp;
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        if (dataOfBooks[i].bookName == thebook){
            pos = i;
        }
    }
    if (pos == -1){
        MessageBox(GetHWnd(), "���޴��飡", "��ʾ", MB_OKCANCEL);
    }
    else{
        Table bookTable(112, 200, 1, 4, 200, 30);
        drawMethod();
        bookTable.drawTableGrid();
        setbkmode(TRANSPARENT);
        settextcolor(RGB(5, 5, 5));
        settextstyle(20, 0, "����");
        outtextxy(112 + (200 - textwidth(dataOfBooks[pos].idNum.c_str())) / 2, 200 + (30 - textheight(dataOfBooks[pos].idNum.c_str())) / 2, dataOfBooks[pos].idNum.c_str());
        outtextxy(312 + (200 - textwidth(dataOfBooks[pos].bookName.c_str())) / 2, 200 + (30 - textheight(dataOfBooks[pos].bookName.c_str())) / 2, dataOfBooks[pos].bookName.c_str());
        outtextxy(512 + (200 - textwidth(to_string(dataOfBooks[pos].totalNum).c_str())) / 2, 200 + (30 - textheight(to_string(dataOfBooks[pos].totalNum).c_str())) / 2, to_string(dataOfBooks[pos].totalNum).c_str());
        outtextxy(712 + (200 - textwidth(to_string(dataOfBooks[pos].restNum).c_str())) / 2, 200 + (30 - textheight(to_string(dataOfBooks[pos].restNum).c_str())) / 2, to_string(dataOfBooks[pos].restNum).c_str());
    }
}

void Library::searchBookPosWithId() //����������Ѱ
{
    int pos = -1;
    char temp[50];
    InputBox(temp, 50, "������Ҫ��ѯ�鼮�ı�ţ�");
    string id = temp;
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        if (dataOfBooks[i].idNum == id){
            pos = i;
        }
    }
    if (pos == -1){
        MessageBox(GetHWnd(), "���޴��飡", "��ʾ", MB_OKCANCEL);
    }
    else {
        Table bookTable(112, 200, 1, 4, 200, 30);
        drawMethod();
        bookTable.drawTableGrid();
        setbkmode(TRANSPARENT);
        settextcolor(RGB(5, 5, 5));
        settextstyle(20, 0, "����");
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
    cout << setw(8) << "���" << setw(14) << "����" << setw(14) << "����" << setw(14) << "����" << endl;
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
    string tarID;//Ҫ�޸��鼮�ı��
    outStr >> tarID;

    //�ҵ�Ŀ���鼮
    int pos = -1;
    for (int i = 0; i < (int)dataOfBooks.size(); i++){
        if (dataOfBooks[i].idNum == tarID){
            pos = i;
        }
    }
    if (pos == -1){
        MessageBox(GetHWnd(), "���޴��飡", "��ʾ", MB_OK);
    }
    //���޸ĺ����Ϣ���뵽Ŀ���鼮��
    else {
        outStr >> dataOfBooks[pos].idNum >> dataOfBooks[pos].bookName >> dataOfBooks[pos].totalNum >> dataOfBooks[pos].restNum;
        MessageBox(GetHWnd(), "�޸��鼮��Ϣ�ɹ���", "��ʾ", MB_OK);
    }
    saveBook();
}

void Library::addStudent(const Student stu)
{
    dataOfUsers.push_back(stu);
}
