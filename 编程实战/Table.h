#ifndef TABLE_H__
#define TABLE_H__
#include "GUI.h"

class Table
{
private:
	//�������
	int m_x;
	int m_y;
	//�С�����
	int m_rows;
	int m_cols;
	//���ӵĿ�Ⱥͳ���
	int gridWidth;
	int gridHeight;
public:
	Table(int, int, int, int, int, int);
	void drawTableGrid();
	void drawBookData();
	//void drawStudentData();

	std::vector<std::string> split(std::string str, char separator);
};


#endif // !TABLE_H__



