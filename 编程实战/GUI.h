#ifndef GUI_H__
#define GUI_H__
#include "library.h"
#include "logo.h"
#include <graphics.h>
#include<iostream>
using namespace std;
//按钮
void button(int, int, int, int, const char*);

//画背景图
void drawBackground(const char* s);

//主界面
void welcome();
 

//主界面背景图
void welcomeBk();

//管理员界面
void manager();


//管理员界面背景图
void managerBk();

//学生界面
void student();


//学生界面背景图
void studentBk();

void drawMethod();

int chooseMethod();


#endif
