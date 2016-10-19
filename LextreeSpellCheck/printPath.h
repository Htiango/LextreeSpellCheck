#ifndef _PRINTPATH_H_
#define _PRINTPATH_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
//#include <Windows.h>

using namespace std;

//gap between characters when print path table
#define TABLE_GAP (8)

void printSinglePath(const string& s1, const string& s2, string filePath, string fileName);
void print(string s1, string s2, ofstream& out);
void printString(const vector<string>& s1, const vector<string>& s2, ofstream& out, int* errorRecord);

#endif
