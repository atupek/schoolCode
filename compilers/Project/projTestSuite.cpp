// Ann Tupek
// CS631
// Project
//
// Test Suite for Prolog Interpreter
// requires proj.l, proj.y, db.pl

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

string parserOutput = "";

string runParser(string input)
{
	parserOutput.clear();
	parserOuput = yyparse(input);
	return parserOutput;
}

bool testFunction(string input, string expected)
{
	string output= runParser(input);
	return output==expected;
}

vector<string> arithmeticTests
{
	"X is 6+2.", "X=8",
	"X is 6-2.", "X=4",
	"X is 6*2.", "X=12",
	"X is 6/2.", "X=3",
	"X is 6+3*2", "X=12",
	"X is 6+2/2", "X=7",
	"X is mod(7,2).", "X=1",
	"X=3+2.", "yes",
	"add3andDouble(X, Y):- Y is (X+3)*2. ?-add3andDouble(1, X).", "X=8",
	"halveandAdd1(X, Y):- Y is (X/2)+1. ?-halveandAdd1(6, X)", "X=4"
};

vector<string> dbTests
{
	"consult(db.pl). ?-wrote(X, frankenstein).", "X=maryShelley", //loads db file for querying
	"?-wrote(nealStephenson, X).", "X=anathem",
	";", "X=cryptonomicon",
	";", "no",
	"?-wrote(lainiTaylor, X).", "X=daughterOfSmokeAndBone",
	";", "X=dreamsOfGodsAndMonsters",
	";", "no",
	"?-wrote(X, wool).", "X=hughHowey",
	";", "X=juanitaDavis",
	";", "no",
	"?-character(X, sarahCynthiaSylviaStout).", "X=whereTheSidewalkEnds",
	"?-character(X, karou).", "X=daughterOfSmokeAndBone",
	";", "X=dreamsOfGodsAndMonsters",
	";", "no",
	"?-wroteAbout(X, juliette).", "X=hughHowey",
	";", "X=juanitaDavis",
	";", "X=williamShakespeare",
	";", "no",
	"?-wroteAbout(douglasAdams, X).", "X=fordPrefect",
	";", "X=marvin",
	";", "no",
	"?-wroteAbout(X, sarahCynthiaSylviaStout).", "X=shelSilverstein"
};

vector<string> listTests
{
	"?-member(childrensBooks, wool)", "no",
	"?-member(childrensBooks, whereTheSidewalkEnds", "yes",
	"append(childrensBooks, matilda). ?-member(X, childrensBooks).", "X=whereTheSidewalkEnds",
	";", "X=neverEndingStory",
	";", "X=frogAndToadAreFriends",
	";", "X=matilda",
	";", "no",
	"reverse(stephensonsBooks). ?-member(X, stephensonsBooks)", "X=cryptonomicon",
	";", "X=anathem",
	";", "no"
};

void testSuite()
{
	int testsPassed = 0;
	int testsFailed = 0;
	cout << "***** Arithmetic Tests *****" << endl;
	for(auto i=0; i< arithmeticTests.size(); i+=2)
	{
		if(testFunction(arithmeticTests[i], arithmeticTests[i+1]))
		{
			cout << "Test " << i/2 << " passed." << endl;
			testsPassed++;
		}
		else
		{
			cout << "Test " << i/2 << " failed." << endl;
			testsFailed++;
		}
	}

	cout << "***** Database Tests *****" << endl;
	for(auto i=0; i< dbTests.size(); i+=2)
	{
		if(testFunction(dbTests[i], dbTests[i+1]))
		{
			cout << "Test " << i/2 << " passed." << endl;
			testsPassed++;
		}
		else
		{
			cout << "Test " << i/2 << " failed." << endl;
			testsFailed++;
		}
	}

	cout << "***** List Tests *****" << endl;
	for(auto i=0; i< listTests.size(); i+=2)
	{
		if(testFunction(listTests[i], listTests[i+1]))
		{
			cout << "Test " << i/2 << " passed." << endl;
			testsPassed++;
		}
		else
		{
			cout << "Test " << i/2 << " failed." << endl;
			testsFailed++;
		}
	}

	cout << testsPassed << " Tests passed." << endl;
	cout << testsFailed << " Tests failed." << endl;
}

int main()
{
	testSuite();
}
