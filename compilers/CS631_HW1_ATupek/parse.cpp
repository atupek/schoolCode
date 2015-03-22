/*
Ann Tupek
CS631
HW1
parse.cpp for use with lex.cpp and runParser.cpp
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
#include "parse.h"
#include "lex.h"

bool matchSym(int &index, const char symbol)
	{
    if(index < tokens.size())
    	{
        if(tokens[index].first == symbol)
        {
            index++;
            return true;
        }
    }
    return false;
}


bool checkResult(Result result)
{
	return result.first;
}

Result badResult()
{
	Result badResult = make_pair(false, 0);
	return badResult;
}

Result parseStmt(int & index)
{
	Result result = parseExpr(index);

	if(checkResult(result))
	{

		if(matchSym(index, ';'))
		{
			cout << "Final Result: " << result.second << endl;
			return result;
		}
		else if(index== tokens.size()-1)
		{
			cout << "Error: missing final semicolon." << endl;
			return badResult();
		}
		else
		{
			cout << "Error: expected an operator." << endl;
			return badResult();
		}
	}
}

Result parseExpr(int & index)
{
	Result result = parseTerm(index);

	if(checkResult(result))
	{
		return parseExprRest(index, result);
	}
	else
	{
		return badResult();
	}
}

Result parseExprRest(int & index, Result & currResult)
{

	if(checkResult(currResult))
	{
		if(matchSym(index, '+'))
		{
			Result newResult = parseTerm(index);
			if(checkResult(newResult))
			{
				Result result = make_pair(true, (currResult.second + newResult.second));
				return parseExprRest(index, result);
			}
			else
			{
				cout << "Error: Missing operand for + " << endl;
				return badResult();
			}
		}
		else if(matchSym(index, '-'))
		{
			Result newResult = parseTerm(index);
			if(checkResult(newResult))
			{
				Result result = make_pair(true, (currResult.second - newResult.second));
				return parseExprRest(index, result);
			}
			else
			{
				cout << "Error: Missing operand for - " << endl;
				return badResult();
			}
		}
		Result result = make_pair(true, currResult.second);
		return result;
	}
	else
	{
		return badResult();
	}
}

Result parseTerm(int & index)
{
	Result result = parseFactor(index);
	if(checkResult(result))
	{
		return parseTermRest(index, result);
	}
	else
	{
		return badResult();
	}
}

Result parseTermRest(int & index, Result & currResult)
{
	if(checkResult(currResult))
	{
		if(matchSym(index, '*'))
		{
			Result newResult = parseFactor(index);
			if(checkResult(newResult))
			{
				Result result = make_pair(true, (currResult.second * newResult.second));
				return parseTermRest(index, result);
			}
			else
			{
				cout << "Error: Missing operand for * " << endl;
				return badResult();
			}
		}
		else if(matchSym(index, '/'))
		{
			Result newResult = parseFactor(index);
			if(checkResult(newResult))
			{
				Result result = make_pair(true, (currResult.second / newResult.second));
				return parseTermRest(index, result);
			}
			else
			{
				cout << "Error: Missing operand for / " << endl;
				return badResult();
			}
		}
		Result result = make_pair(true, currResult.second);
		return result;
	}
	else
	{
		return badResult();
	}
}

Result parseFactor(int & index)
{
	if(matchSym(index, '('))
	{
		Result result = parseExpr(index);
		if(matchSym(index, ')'))
		{
			return result;
		}
		else
		{
			result = badResult();
			return result;
		}
	}
	else
	{
		Result result = parseDigit(index);
		if(checkResult(result))
		{
			return result;
		}
		else
		{
			return badResult();
		}
	}
}

Result parseDigit(int & index)
{
	if(index < tokens.size())
	{
		if(tokens[index].first == 'd')
	{
		Result result = make_pair(true, tokens[index].second);
		index++;
		return result;
	}
	cout << "Error: Expected a digit or a (." << endl;
	return badResult();
	}
}