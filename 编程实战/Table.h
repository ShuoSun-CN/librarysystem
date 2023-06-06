#ifndef TABLE_H__
#define TABLE_H__
#include "GUI.h"

class Table
{
private:
	//表格坐标
	int m_x;
	int m_y;
	//行、列数
	int m_rows;
	int m_cols;
	//格子的宽度和长度
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



