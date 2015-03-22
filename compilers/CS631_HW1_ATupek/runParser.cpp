/*
Ann Tupek
CS631
HW1
runParser.cpp for use with lex.cpp and parse.cpp
*/

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;
#include "parse.h"
#include "lex.h"

int main()
{
	string testStrings[]={
		"3+(1);", "Expected Result: 4",
		"4 * 5 - 5;", "Expected Result: 15",
		"2*2*2*2/2;", "Expected Result: 8",
		"(22+22)/2;", "Expected Result: 22",
		"22 + 22 / 2 ;", "Expected Result: 33"
	};

	string testStringsWErrors[]={
		"(84 + 42) - + ;", "Expected Result: Error message",
		"2(;", "Expected Result: Error message",
		"4-3);","Expected Result: Error message",
		"1+4+3", "Expected Result: Error message",
		"1 + a + 2;", "Expected Result: Error message"
	};
	cout << "*******************************"  << endl;
	cout << "Program Strings without Errors:" << endl;
	cout << "*******************************"  << endl;

	for (int i = 0; i < 10; i+=2)
	{
		string program = testStrings[i];
		cout << "Program: " << program << endl;
		cout << testStrings[i+1] << endl;
		lex(program);
		int index = 0;
		Result result = parseStmt(index);
		tokens.clear();
		cout << endl;
	}

	cout << "****************************"  << endl;
	cout << "Program Strings with Errors:" << endl;
	cout << "****************************"  << endl;

	for (int i = 0; i < 10; i+=2)
	{
		string program = testStringsWErrors[i];
		cout << "Program: " << program << endl;
		cout << testStringsWErrors[i+1] << endl;
		lex(program);
		int index = 0;
		Result result = parseStmt(index);
		tokens.clear();
		cout << endl;
	}
	return 0;
}
