/*
Ann Tupek
CS631
HW1
parse.h header for parse.cpp
*/

#ifndef PARSE_H
#define PARSE_H

typedef pair<bool, int> Result;

bool matchSym(int &index, const char symbol);
bool checkResult(Result result);
Result badResult();
Result parseStmt(int & index);
Result parseExpr(int & index);
Result parseExprRest(int & index, Result & currResult);
Result parseTerm(int & index);
Result parseTermRest(int & index, Result & currResult);
Result parseFactor(int & index);
Result parseDigit(int & index);

#endif