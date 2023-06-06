#include "Table.h"

Table::Table(int x, int y, int row, int col, int gridW, int gridH)
	:m_x(x), 
	m_y(y), 
	m_rows(row), 
	m_cols(col), 
	gridWidth(gridW), 
	gridHeight(gridH) {}

void Table::drawTableGrid()
{
	setlinecolor(RGB(5, 5, 5));
	//������
	for (int i = 0; i < m_rows + 1; i++)
	{
		line(m_x, m_y + gridHeight * i, m_x + gridWidth * m_cols, m_y + gridHeight * i);
	}
	//������
	for (int i = 0; i < m_cols + 1; i++)
	{
		line(m_x + gridWidth * i, m_y, m_x + gridWidth * i, m_y + gridHeight * m_rows);
	}
	setlinecolor(WHITE);
}

vector<string> Table::split(string str, char separator)
{
	vector<string> res;
	for (size_t pos = 0; pos != string::npos;) { //npos��һ����������ʾsize_t�����ֵ
	//����ָ���ָ��ַ���λ��
		pos = str.find(separator);
		//����ÿ���ַ����ĳ���ȡ���ַ���
		res.push_back(str.substr(0, pos));
		//��ʣ�µ��ַ������浽str,pos����ǰһ���ַ���,1����'\t'
		str = std::string(str.c_str() + pos + 1);
	}
	return res;
}

void Table::drawBookData()
{
	cleardevice();
	drawBackground("../images/manager_bk.jpg");
	SetWindowText(GetHWnd(), "�����鼮");
	drawTableGrid();
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(20, 0, "����");
	int tx, ty;
	for (int row = 0; row < m_rows; row++)
	{
		string temp("");
		temp = temp + lib.dataOfBooks[row].idNum + " " + lib.dataOfBooks[row].bookName + " " + to_string(lib.dataOfBooks[row].totalNum) + " " + to_string(lib.dataOfBooks[row].restNum);
		cout << temp << endl;
		vector<string> lineData = split(temp, ' ');
		for (int col = 0; col < m_cols; col++)
		{
			ty = m_y + gridHeight * row + (gridHeight - textheight(lineData[col].c_str())) / 2;
			tx = m_x + gridWidth * col + (gridWidth - textwidth(lineData[col].c_str())) / 2;
			outtextxy(tx, ty, lineData[col].c_str());
		}
	}
}

