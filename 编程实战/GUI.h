#ifndef GUI_H__
#define GUI_H__
#include "library.h"
#include "logo.h"
#include <graphics.h>
#include<iostream>
using namespace std;
//��ť
void button(int, int, int, int, const char*);

//������ͼ
void drawBackground(const char* s);

//������
void welcome();
 

//�����汳��ͼ
void welcomeBk();

//����Ա����
void manager();


//����Ա���汳��ͼ
void managerBk();

//ѧ������
void student();


//ѧ�����汳��ͼ
void studentBk();

void drawMethod();

int chooseMethod();


#endif
