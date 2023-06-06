#define _CRT_SECURE_NO_WARNINGS
#include "GUI.h"
Library lib;
logo LOG;
//绘制按钮
void button(int x, int y, int width, int height,const char* s)
{
	roundrect(x, y, x + width, y + height, 10, 10);

	//文字居中对齐
	int tx = x + (width - textwidth(s)) / 2;
	int ty = y + (height - textheight(s)) / 2;
	//输出文字
	outtextxy(tx, ty, s);

}

void drawBackground(const char* s)
{
	cleardevice();
	IMAGE img;
	loadimage(&img, s, 1024, 640);
	putimage(0, 0, &img);
}

//绘制主界面的背景图
void welcomeBk()
{
	drawBackground("../images/main_bk.jpg");
	SetWindowText(GetHWnd(), "主界面");


	//按钮
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(20, 0, "楷体");
	button(412, 340, 200, 50, "我是管理员");
	button(412, 400, 200, 50, "我是学生");
	button(412, 460, 200, 50, "学生注册");
	button(412, 520, 200, 50, "退出系统");


	//标题
	settextstyle(50, 0, "黑体");
	settextcolor(RGB(6, 6, 6));
	const char* s = "图书管理系统";


	//标题水平居中对齐
	int tx = (1024 - textwidth(s)) / 2;
	outtextxy(tx, 150, s);
	FlushBatchDraw();
}

//主界面函数
void welcome()
{
	initgraph(1024, 640, SHOWCONSOLE);
	welcomeBk();
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				/* 管理员登录操作 */
				if (msg.x >= 412 && msg.x <= 612 && msg.y >= 340 && msg.y <= 390)
				{
					cout << "\n\t进入管理员系统" << endl;
					char temp[105];
					int flag, op=IDOK;
					while (1)
					{
						InputBox(temp, 105, "请输入用户名 密码：");
						flag = LOG.Maglog(temp);
						/*用户名不存在*/
						if (flag == 1)
						{
							op = MessageBox(GetHWnd(), "用户名不存在！", "提示", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
						/*登陆成功*/
						else if (flag == 2)
						{
							MessageBox(GetHWnd(), "登陆成功！！", "提示", MB_OK);
							manager();
							welcomeBk();
							break;
						}
						/* 用户名存在但是密码错误 */
						else if (flag == 3)
						{
							op = MessageBox(GetHWnd(), "密码错误，请重新输入！", "提示", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
					}
				}
				
				/* 学生登录操作 */
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 400 && msg.y <= 450)
				{
					cout << "\n\t进入学生系统" << endl;
					char temp[105];
					int flag, op = IDOK;
					while (1)
					{
						InputBox(temp, 105, "请输入用户名 密码：");
						flag = LOG.Stulog(temp);
						/* 用户名不存在 */
						if (flag == 1)
						{
							op = MessageBox(GetHWnd(), "用户名不存在！", "提示", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
						/* 登陆成功 */
						else if (flag == 2)
						{
							MessageBox(GetHWnd(), "登陆成功！！", "提示", MB_OK);
							student();
							welcomeBk();
							break;
						}
						/* 用户名存在但是密码错误 */
						else if (flag == 3)
						{
							op = MessageBox(GetHWnd(), "密码错误，请重新输入！", "提示", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
					}
				}

				/* 学生注册操作 */
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 460 && msg.y <= 510)
				{
					cout << "\n\t学生注册" << endl;
					/* 学生注册函数 */
					char temp[105];
					int flag, op = IDOK;
					while (1)
					{
						InputBox(temp, 105, "请输入用户名 密码：");
						flag = LOG.Sturegist(temp);
						/* 用户名重复，注册失败 */
						if (flag == 1)
						{
							op = MessageBox(GetHWnd(), "用户名重复，注册失败！", "提示", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
						/* 注册成功 */
						else if (flag == 2)
						{
							MessageBox(GetHWnd(), "注册成功！", "提示", MB_OK);
							break;
						}
					}
					lib.saveStudent();
				}
				/* 退出系统 */
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 520 && msg.y <= 570)
				{
					cout << "\n\t退出系统" << endl;
					lib.saveBook();
					lib.saveStudent();
					break;
				}
			}
		}
		FlushMouseMsgBuffer();
	}
	closegraph();
}

//绘制管理员界面的背景图
void managerBk()
{
	drawBackground("../images/manager_bk.jpg");
	SetWindowText(GetHWnd(), "管理书籍");
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "楷体");
	settextcolor(WHITE);
	button(412, 340, 200, 50, "增加书籍");
	button(412, 400, 200, 50, "删除书籍");
	button(412, 460, 200, 50, "修正书籍信息");
	button(412, 520, 200, 50, "返回");
	FlushBatchDraw();
} 

//管理员界面函数---已完成：增加书籍、删除书籍、修改书籍信息
void manager()
{
	managerBk();
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x >= 412 && msg.x <= 612 && msg.y >= 340 && msg.y <= 390)
				{
					cout << "\n\t增加书籍" << endl;
					//调用增加书籍的函数
					char temp[sizeof(Book)];
					InputBox(temp, sizeof(Book), "输入书籍信息(编号 书名 总数)：");
					lib.addBook(temp);
					lib.showAllBook();
				}
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 400 && msg.y <= 450)
				{
					cout << "\n\t删除书籍" << endl;
					//调用删除书籍的函数
					char temp[105];
					InputBox(temp, 105, "输入要删除书籍的编号和名称：");
					lib.deleteBook(temp);
					lib.showAllBook();
				}
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 460 && msg.y <= 510)
				{
					cout << "\n\t修正书籍信息" << endl;
					//调用修改的函数
					Table bookTable(112, 100, lib.getBookNum(), 4, 200, 30);
					bookTable.drawBookData();
					button(212, 580, 200, 50, "修改信息");
					button(612, 580, 200, 50, "返回");
					ExMessage msg_t;
					while (1)
					{
						if (peekmessage(&msg_t, EM_MOUSE))
						{
							if (msg_t.message == WM_LBUTTONDOWN)
							{
								if (msg_t.x >= 212 && msg_t.x <= 412 && msg_t.y >= 580 && msg_t.y <= 630)
								{
									char temp[205];
									InputBox(temp, 205, "请输入要修改书籍的编号以及修改后的信息(编号 书名 总数 余数)：");
									lib.reviseBook(temp);
									bookTable.drawBookData();
									button(212, 580, 200, 50, "修改信息");
									button(612, 580, 200, 50, "返回");
								}
								else if (msg_t.x >= 612 && msg_t.x <= 812 && msg_t.y >= 580 && msg_t.y <= 630)
								{
									managerBk();
									goto end;
								}
							}
						}
					}
				end:;
				}
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 520 && msg.y <= 570)
				{
					cout << "\n\t返回主界面" << endl;
					lib.saveBook();
					break;
				}
			}
			FlushMouseMsgBuffer();
		}
	}
	FlushMouseMsgBuffer();
}

//绘制学生界面的背景图
void studentBk()
{
	drawBackground("../images/student_bk.jpg");
	SetWindowText(GetHWnd(), "学生借阅");

	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "楷体");
	settextcolor(WHITE);
	button(412, 340, 200, 50, "借阅书籍");
	button(412, 400, 200, 50, "查询书籍");
	button(412, 460, 200, 50, "还书");
	button(412, 520, 200, 50, "返回");

	FlushBatchDraw();
}

//学生界面函数---已完成：查询书籍、借阅书籍、还书
void student()
{
	studentBk();
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x >= 412 && msg.x <= 612 && msg.y >= 340 && msg.y <= 390)
				{
					cout << "\n\t借阅书籍" << endl;
					//调用借阅书籍的函数
					char temp[50];
					InputBox(temp, 50, "请输入要借阅书籍的名称：");
					lib.borrowBook(cur.getID(), temp);
					lib.showAllBook();
				}
				
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 400 && msg.y <= 450)
				{
					cout << "\n\t查询书籍" << endl;
					//调用查询书籍的函数
					/* 选择查询方法 */
					drawMethod();
					int choice;
					while (1)
					{
						choice = chooseMethod();
						if (choice == 1){
							lib.searchBookPosWithName();
						}
						else if (choice == 2){
							lib.searchBookPosWithId();
						}
						else if (choice == 3)
							break;
					}
					lib.showAllBook();
					studentBk();
					continue;
				}
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 460 && msg.y <= 510)
				{
					cout << "\n\t还书" << endl;
					//调用还书的函数
					char temp[50];
					InputBox(temp, 50, "请输入要归还书籍的名称：");
					lib.returnBook(cur.getID(), temp);
				}
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 520 && msg.y <= 570)
				{
					cout << "\n\t返回主界面" << endl;
					lib.saveBook();
					break;
				}
			}
		}
		FlushMouseMsgBuffer();
	}
	FlushMouseMsgBuffer();
}

void drawMethod()
{
	cleardevice();
	drawBackground("../images/student_bk.jpg");
	SetWindowText(GetHWnd(), "学生借阅");
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "楷体");
	settextcolor(BLACK);

	button(262, 50, 200, 50, "按书名查询");
	button(562, 50, 200, 50, "按编号查询");
	button(774, 580, 200, 50, "返回");
}

int chooseMethod()
{
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				/* 返回1，按书名查询 */
				if (msg.x >= 262 && msg.x <= 462 && msg.y >= 50 && msg.y <= 100)
				{
					cout << "\n\t按书名查询" << endl;
					return 1;
				}

				/* 返回2，按编号查询 */
				else if (msg.x >= 562 && msg.x <= 762 && msg.y >= 50 && msg.y <= 100)
				{
					cout << "\n\t按编号查询" << endl;
					return 2;
				}

				/* 返回3，返回上一级页面 */
				else if (msg.x >= 774 && msg.x <= 974 && msg.y >= 580 && msg.y <= 630)
				{
					cout << "\n\t返回" << endl;
					return 3;
				}
			}
		}
	}
}