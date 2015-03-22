/*
Ann Tupek
CS631
HW1
lex.cpp for use with parse.cpp and runParser.cpp
*/
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <cctype>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;
#include "lex.h"

vector<Token> tokens;

void match(const string & program, int & currentChar)
{
	int value = 0;
	int length = 0;
	int firstChar = currentChar;
	Token newTok;

	if(isdigit(program[currentChar]))
	{
		while(isdigit(program[currentChar]))
		{
			currentChar++;
			length++;
		}

		sscanf(program.substr(firstChar, length).c_str(), "%d", &value);
		newTok = make_pair('d', value);
		tokens.push_back(newTok);
	}
	else if(isspace(program[currentChar]))
	{
		while(isspace(program[currentChar]))
		{
			currentChar++;
		}
	}
	else
	{
		switch(program[currentChar])
		{
			case '+': newTok = make_pair('+', 0);
				tokens.push_back(newTok);
				break;
			case '-': newTok = make_pair('-', 0);
				tokens.push_back(newTok);
				break;
			case '*': newTok = make_pair('*', 0);
				tokens.push_back(newTok);
				break;
			case '/': newTok = make_pair('/', 0);
				tokens.push_back(newTok);
				break;
			case '(': newTok = make_pair('(', 0);
				tokens.push_back(newTok);
				break;
			case ')': newTok = make_pair(')', 0);
				tokens.push_back(newTok);
				break;
			case ';': newTok = make_pair(';', 0);
				tokens.push_back(newTok);
				break;
			default: cout << program[currentChar] << " Is not a valid character" << endl;
				break;
		}
		currentChar++;
	}
}

void lex(string program)
{
	int index = 0;

	while(index < program.length())
	{
		match(program, index);
	}
}