#define _CRT_SECURE_NO_WARNINGS
#include "GUI.h"
Library lib;
logo LOG;
//���ư�ť
void button(int x, int y, int width, int height,const char* s)
{
	roundrect(x, y, x + width, y + height, 10, 10);

	//���־��ж���
	int tx = x + (width - textwidth(s)) / 2;
	int ty = y + (height - textheight(s)) / 2;
	//�������
	outtextxy(tx, ty, s);

}

void drawBackground(const char* s)
{
	cleardevice();
	IMAGE img;
	loadimage(&img, s, 1024, 640);
	putimage(0, 0, &img);
}

//����������ı���ͼ
void welcomeBk()
{
	drawBackground("../images/main_bk.jpg");
	SetWindowText(GetHWnd(), "������");


	//��ť
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(20, 0, "����");
	button(412, 340, 200, 50, "���ǹ���Ա");
	button(412, 400, 200, 50, "����ѧ��");
	button(412, 460, 200, 50, "ѧ��ע��");
	button(412, 520, 200, 50, "�˳�ϵͳ");


	//����
	settextstyle(50, 0, "����");
	settextcolor(RGB(6, 6, 6));
	const char* s = "ͼ�����ϵͳ";


	//����ˮƽ���ж���
	int tx = (1024 - textwidth(s)) / 2;
	outtextxy(tx, 150, s);
	FlushBatchDraw();
}

//�����溯��
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
				/* ����Ա��¼���� */
				if (msg.x >= 412 && msg.x <= 612 && msg.y >= 340 && msg.y <= 390)
				{
					cout << "\n\t�������Աϵͳ" << endl;
					char temp[105];
					int flag, op=IDOK;
					while (1)
					{
						InputBox(temp, 105, "�������û��� ���룺");
						flag = LOG.Maglog(temp);
						/*�û���������*/
						if (flag == 1)
						{
							op = MessageBox(GetHWnd(), "�û��������ڣ�", "��ʾ", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
						/*��½�ɹ�*/
						else if (flag == 2)
						{
							MessageBox(GetHWnd(), "��½�ɹ�����", "��ʾ", MB_OK);
							manager();
							welcomeBk();
							break;
						}
						/* �û������ڵ���������� */
						else if (flag == 3)
						{
							op = MessageBox(GetHWnd(), "����������������룡", "��ʾ", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
					}
				}
				
				/* ѧ����¼���� */
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 400 && msg.y <= 450)
				{
					cout << "\n\t����ѧ��ϵͳ" << endl;
					char temp[105];
					int flag, op = IDOK;
					while (1)
					{
						InputBox(temp, 105, "�������û��� ���룺");
						flag = LOG.Stulog(temp);
						/* �û��������� */
						if (flag == 1)
						{
							op = MessageBox(GetHWnd(), "�û��������ڣ�", "��ʾ", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
						/* ��½�ɹ� */
						else if (flag == 2)
						{
							MessageBox(GetHWnd(), "��½�ɹ�����", "��ʾ", MB_OK);
							student();
							welcomeBk();
							break;
						}
						/* �û������ڵ���������� */
						else if (flag == 3)
						{
							op = MessageBox(GetHWnd(), "����������������룡", "��ʾ", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
					}
				}

				/* ѧ��ע����� */
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 460 && msg.y <= 510)
				{
					cout << "\n\tѧ��ע��" << endl;
					/* ѧ��ע�ắ�� */
					char temp[105];
					int flag, op = IDOK;
					while (1)
					{
						InputBox(temp, 105, "�������û��� ���룺");
						flag = LOG.Sturegist(temp);
						/* �û����ظ���ע��ʧ�� */
						if (flag == 1)
						{
							op = MessageBox(GetHWnd(), "�û����ظ���ע��ʧ�ܣ�", "��ʾ", MB_RETRYCANCEL);
							if (op == IDRETRY)
								continue;
							else
								break;
						}
						/* ע��ɹ� */
						else if (flag == 2)
						{
							MessageBox(GetHWnd(), "ע��ɹ���", "��ʾ", MB_OK);
							break;
						}
					}
					lib.saveStudent();
				}
				/* �˳�ϵͳ */
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 520 && msg.y <= 570)
				{
					cout << "\n\t�˳�ϵͳ" << endl;
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

//���ƹ���Ա����ı���ͼ
void managerBk()
{
	drawBackground("../images/manager_bk.jpg");
	SetWindowText(GetHWnd(), "�����鼮");
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "����");
	settextcolor(WHITE);
	button(412, 340, 200, 50, "�����鼮");
	button(412, 400, 200, 50, "ɾ���鼮");
	button(412, 460, 200, 50, "�����鼮��Ϣ");
	button(412, 520, 200, 50, "����");
	FlushBatchDraw();
} 

//����Ա���溯��---����ɣ������鼮��ɾ���鼮���޸��鼮��Ϣ
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
					cout << "\n\t�����鼮" << endl;
					//���������鼮�ĺ���
					char temp[sizeof(Book)];
					InputBox(temp, sizeof(Book), "�����鼮��Ϣ(��� ���� ����)��");
					lib.addBook(temp);
					lib.showAllBook();
				}
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 400 && msg.y <= 450)
				{
					cout << "\n\tɾ���鼮" << endl;
					//����ɾ���鼮�ĺ���
					char temp[105];
					InputBox(temp, 105, "����Ҫɾ���鼮�ı�ź����ƣ�");
					lib.deleteBook(temp);
					lib.showAllBook();
				}
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 460 && msg.y <= 510)
				{
					cout << "\n\t�����鼮��Ϣ" << endl;
					//�����޸ĵĺ���
					Table bookTable(112, 100, lib.getBookNum(), 4, 200, 30);
					bookTable.drawBookData();
					button(212, 580, 200, 50, "�޸���Ϣ");
					button(612, 580, 200, 50, "����");
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
									InputBox(temp, 205, "������Ҫ�޸��鼮�ı���Լ��޸ĺ����Ϣ(��� ���� ���� ����)��");
									lib.reviseBook(temp);
									bookTable.drawBookData();
									button(212, 580, 200, 50, "�޸���Ϣ");
									button(612, 580, 200, 50, "����");
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
					cout << "\n\t����������" << endl;
					lib.saveBook();
					break;
				}
			}
			FlushMouseMsgBuffer();
		}
	}
	FlushMouseMsgBuffer();
}

//����ѧ������ı���ͼ
void studentBk()
{
	drawBackground("../images/student_bk.jpg");
	SetWindowText(GetHWnd(), "ѧ������");

	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "����");
	settextcolor(WHITE);
	button(412, 340, 200, 50, "�����鼮");
	button(412, 400, 200, 50, "��ѯ�鼮");
	button(412, 460, 200, 50, "����");
	button(412, 520, 200, 50, "����");

	FlushBatchDraw();
}

//ѧ�����溯��---����ɣ���ѯ�鼮�������鼮������
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
					cout << "\n\t�����鼮" << endl;
					//���ý����鼮�ĺ���
					char temp[50];
					InputBox(temp, 50, "������Ҫ�����鼮�����ƣ�");
					lib.borrowBook(cur.getID(), temp);
					lib.showAllBook();
				}
				
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 400 && msg.y <= 450)
				{
					cout << "\n\t��ѯ�鼮" << endl;
					//���ò�ѯ�鼮�ĺ���
					/* ѡ���ѯ���� */
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
					cout << "\n\t����" << endl;
					//���û���ĺ���
					char temp[50];
					InputBox(temp, 50, "������Ҫ�黹�鼮�����ƣ�");
					lib.returnBook(cur.getID(), temp);
				}
				else if (msg.x >= 412 && msg.x <= 612 && msg.y >= 520 && msg.y <= 570)
				{
					cout << "\n\t����������" << endl;
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
	SetWindowText(GetHWnd(), "ѧ������");
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "����");
	settextcolor(BLACK);

	button(262, 50, 200, 50, "��������ѯ");
	button(562, 50, 200, 50, "����Ų�ѯ");
	button(774, 580, 200, 50, "����");
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
				/* ����1����������ѯ */
				if (msg.x >= 262 && msg.x <= 462 && msg.y >= 50 && msg.y <= 100)
				{
					cout << "\n\t��������ѯ" << endl;
					return 1;
				}

				/* ����2������Ų�ѯ */
				else if (msg.x >= 562 && msg.x <= 762 && msg.y >= 50 && msg.y <= 100)
				{
					cout << "\n\t����Ų�ѯ" << endl;
					return 2;
				}

				/* ����3��������һ��ҳ�� */
				else if (msg.x >= 774 && msg.x <= 974 && msg.y >= 580 && msg.y <= 630)
				{
					cout << "\n\t����" << endl;
					return 3;
				}
			}
		}
	}
}