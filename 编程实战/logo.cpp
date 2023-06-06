
#include "logo.h"
curUser cur;
int logo::Sturegist(const char* temp)
{
	stringstream outStr(temp);
	/*cout << "请输入用户名：";*/
	char userName[50];
	
	/*cin >> userName;*/
	/*cout << "请输入用户密码：";*/
	char userPass[50];
	/*cin >> userPass;*/
	outStr >> userName >> userPass;

	char key[5]= "+-*/";
	fstream username("Stuuser.txt", ios::in | ios::binary);
	if (username.fail())
	{
		cout << "文件打开失败！！" << endl;
		exit(1);
	}

	

	//验证用户名是否重复...
	int nameexist = 0;
	int count3=0;

	while (!username.eof())
	{
		char correctName[50];
		count3 = 0;
		for (int i = 0;;i++)
		{
			username.read(&correctName[i], sizeof(char));
			if (correctName[i] == ' ')
				break;
			correctName[i] ^= key[count3];
			count3++;
			if (count3 == 4)
			{
				count3 = 0;
			}

		}
		if (strcmp(userName, correctName) == 0)
		{


			nameexist = 1;
			/*cout << "用户名已经存在，请重新输入新的用户名！！！" << endl;*/
			return 1;
			//用户名重复返回值为1....
		}
		char overpass[50];
		for (int i = 0;; i++)
		{
			username.read(&overpass[i], sizeof(char));
			if (overpass[i] == '\n')
				break;

		}
	}


	//检查完毕，重新打开文件写入信息
	
	username.close();
	username.open("Stuuser.txt", ios::app | ios::binary);

	lib.addStudent(Student(userName));
	
	int count = 0;
	int length = strlen(userName) + 1;
	for (int i = 0;i < length;i++)
	{
		userName[i] ^= key[count];
		count++;
		if (count == 4)
		{
			count = 0;
		}
		username.write(&userName[i], sizeof(char));

	}
	char insert = ' ';
	username.write(&insert, sizeof(char));


	int count2 = 0;
	int length1 = strlen(userPass) + 1;
	for (int i = 0;i < length1;i++)
	{
		userPass[i] ^= key[count2];
		count2++;
		if (count2 == 4)
		{
			count2 = 0;
		}
		username.write(&userPass[i], sizeof(char));
	}
	char nextline = '\n';
	username.write(&nextline, sizeof(char));
	//cout <</* "注册成功！！！"*/<<endl;
	return 2;//注册成功，返回2
}


int logo::Stulog(const char* temp)
{
	stringstream outStr(temp);
	char userName[50];
	char userPass[50];
	outStr >> userName >> userPass;
	cur.setID(userName);
	/*cout << "请输入用户名：";
	cin >> userName;
	cout << "请输入用户密码：";
	cin >> userPass;*/
	fstream username("Stuuser.txt", ios::in | ios::binary);
	if (username.fail())
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	int namelen = strlen(userName) + 1;
	

	int nameexist = 0;

	int count = 0;
	int count2 = 0;
	char key[5] = "+-*/";
	while (!username.eof())//验证用户名是否存在
	{
		char correctName[50];
		count = 0;
		for (int i = 0;;i++)
		{
			username.read(&correctName[i], sizeof(char));
			if (correctName[i] == ' ')
				break;
			correctName[i] ^= key[count];
			count++;
			if (count == 4)
			{
				count = 0;
			}
			
		}
		if (strcmp(userName, correctName) == 0)
		{

			
			nameexist = 1;
			break;
		}
		char overpass[50];
		for (int i = 0;;i++)
		{
			username.read(&overpass[i], sizeof(char));
			if (overpass[i] == '\n')
				break;

		}
	}
	if (nameexist == 0)
	{
		/*cout << "用户名不存在" << endl;*/
		return 1;//用户名不存在，返回1


	}
	else
	{
		char correctpass[50];
		for (int i = 0;;i++)
		{
			username.read(&correctpass[i], sizeof(char));
			
			if (correctpass[i] == '\n')
				break;
			correctpass[i] ^= key[count2];
			count2++;
			if (count2 == 4)
			{
				count2 = 0;
			}

		}
		if (strcmp(correctpass, userPass) == 0)
		{
			/*cout << "登陆成功！！！" << endl;*/
			return 2;//登陆成功，返回2
		}
		else
		{
			/*cout << "密码错误！！!" << endl;*/
			return 3;//用户名存在，但密码错误，返回3
		}



	}
}


int logo::Maglog(const char* temp)
{
	stringstream outStr(temp);
	char userName[50];
	char userPass[50];
	outStr >> userName >> userPass;
	cur.setID(userName);


	fstream username("Maguser.txt", ios::in | ios::binary);
	if (username.fail())
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	int namelen = strlen(userName) + 1;


	int nameexist = 0;

	int count = 0;
	int count2 = 0;
	char key[5] = "+-*/";
	while (!username.eof())//验证用户名是否存在
	{
		char correctName[50];
		count = 0;
		for (int i = 0;;i++)
		{
			username.read(&correctName[i], sizeof(char));
			if (correctName[i] == ' ')
				break;
			correctName[i] ^= key[count];
			count++;
			if (count == 4)
			{
				count = 0;
			}

		}
		if (strcmp(userName, correctName) == 0)
		{


			nameexist = 1;
			break;
		}
		char overpass[50];
		for (int i = 0;;i++)
		{
			username.read(&overpass[i], sizeof(char));
			if (overpass[i] == '\n')
				break;

		}
	}
	if (nameexist == 0)
	{
		/*cout << "用户名不存在" << endl;*/
		return 1;//用户名不存在，返回1


	}
	else
	{
		char correctpass[50];
		for (int i = 0;;i++)
		{
			username.read(&correctpass[i], sizeof(char));

			if (correctpass[i] == '\n')
				break;
			correctpass[i] ^= key[count2];
			count2++;
			if (count2 == 4)
			{
				count2 = 0;
			}

		}
		if (strcmp(correctpass, userPass) == 0)
		{
			/*cout << "登陆成功！！！" << endl;*/
			return 2;//登陆成功，返回2
		}
		else
		{
			/*cout << "密码错误！！!" << endl;*/
			return 3;//用户名存在，但密码错误，返回3
		}



	}
}


void logo::encryption(char* a, int n,char*filename)
{

	char* date = new char[n];
	char passward[] = "5201";
	int count = 0;
	ofstream fout(filename, ios::binary);

	if (fout.fail())
	{
		cout << "open file faily!!" << endl;
		exit(1);
	}
	for (int i = 0;i < n;i++)
	{
		//if (a[i] == ' ' || a[i] == '\n'||a[i]=='\0'||a[i]=='5')
		//{
		//	date[i] = a[i];
		//	fout.write((char*)&date[i], sizeof(char));
		//	continue;
		//}
		if (count == 4)
		{
			count = 0;
		}
		date[i] = a[i] ^ passward[count];
		count++;
		fout.write((char*)&date[i], sizeof(char));
		
	}
	//cout << date << endl;
	fout.close();

}
