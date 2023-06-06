#ifndef LOG_H__
#define LOG_H__


#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "User.h"
#include "library.h"
using namespace std;
class logo
{
public:

	int Sturegist(const char* temp);
	int Stulog(const char* temp);
	int Maglog(const char* temp);
	void encryption(char* a, int n,char*filename);
		//
};

#ifndef LOG__
#define LOG__

extern logo LOG;

#endif

#endif