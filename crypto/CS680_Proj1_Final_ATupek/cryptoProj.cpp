//  Ann Tupek
//  CS 680
//  Project 1
//  cryptoProj.cpp
//  due 3/25/15
//
//  Encrypt: Determines whether or not there is enough room in the gcode file for the message.
//			Converts secret message into ASCII decimal value -32
//  		(to get rid of non-printable chars & limit number to two places)
//  		Parses through gcode file for Extruder commands
//  		Replaces last two decimal places of extruder commands with ASCII
//  Decrypt: Parses through gcode file for Extruder commands and removes last two decimal places
//			Converts last two decimal places to ASCII value + 32
//			Dumps into text file
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <vector>
#include <regex>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::fstream;
using std::ofstream;
using std::string;
using std::vector;
using std::getline;
using std::regex;
using std::regex_match;
using std::smatch;
using std::regex_search;
using std::match_results;

char gcodeFile[256];
char msgFile[256];

vector<int> encryptedMessage;
vector<int> decryptedMessage;

// charToASCII()
// gets char from text to be encrypted, sets it to its ASCII value -32
// dumps it into a vector of ints
void charToASCII(string msg)
{
	ifstream inFile(msg);
	char c;
	while(inFile.get(c))
    {
    	int number = c-32; //to keep numbers between 0 and 95
    	if(number == -22) // for newline
    	{
    		encryptedMessage.push_back(99);
    	}
    	else
    	{
    		encryptedMessage.push_back(number);
    	}
    }
    encryptedMessage.push_back(98); //sentinel for end of message
}

// ASCIIToChar()
// gets int from vector of ASCII values, dumps it to file as characters
void ASCIIToChar()
{
   FILE * outFile;
   outFile = fopen ("decodedMessage.txt","w");
   int number;
   for(int i = 0; i<decryptedMessage.size(); i++)
   {
   		number = decryptedMessage[i];
   		if(number == 99) //for new line
   		{
   			number = 10;
   		}
   		else if(number == 98) //for end of message sentinel
   		{
   			return;
   		}
   		else
   		{
   			number = decryptedMessage[i]+32;
   		}
   		fprintf(outFile, "%c", number);
   }
   fclose (outFile);
}

// stegoGcode()
// regular expression matches extruder gCode commands w 5 places after the decimal
// replaces last two decimal digits with number from ASCII vector
void stegoGode(string gcodeFile)
{
	string line;
	int i = 0;
	ifstream inFile(gcodeFile);
    ofstream outFile("20mm_cube_wMessage.gcode");
	while(!inFile.eof())
    {
    	getline(inFile, line);
    	// regex matches EXX.XXXXX where X is a digit
        regex expr("(\\x45\\d+\\.\\d{5})");
		smatch match;
		if(!regex_search(line, match, expr))
		{
			outFile << line << endl;
		}
		else
		{
			regex_search (line,match,expr);
			if(i<encryptedMessage.size())
			{
				string prefix = match.prefix().str();
		    	outFile << prefix;
		    	string edited = match.str();
		    	line = match.suffix().str();
		    	//remove last two digits of matched extruder command
			    edited.pop_back();
		    	edited.pop_back();
		    	outFile << edited;
		    	// put ASCII from message into gcode
		    	if(encryptedMessage[i] == 0) //for space 
		    	{
		    		outFile << "00";
		    	}
		    	else
		    	{
		    		outFile << encryptedMessage[i];
		    	}
		    	i++;
		    	outFile << line;
		    	outFile << endl;
			}
			else
			{
				outFile<<line << endl;
			}

		}
    }
}

// deStegoGcode()
// regular expression matches extruder commands w 5 places after the decimal
// pulls out last two decimal places (our ASCII characters)
// and dumps them to vector of ints
void deStegoGcode()
{
	string line;
	int i = 0;
	ifstream inFile("20mm_cube_wMessage.gcode");
	while(!inFile.eof())
    {
    	getline(inFile, line);

    	// regex matches EXX.XXXXX where X is a digit
        regex expr("(\\x45\\d+\\.\\d{5})");
		smatch match;
		if(!regex_search(line, match, expr))
		{
			//do nothing for no match
		}
		else
		{
			regex_search (line,match,expr);
		    string edited = match.str();
		    //get last two digits of extruder command
		   	string nums = edited.substr(edited.length()-2, 2);
		   	int num1 = atoi(nums.c_str());
		   	//if not end of message sentinel, add number to vector
		   	if(num1 != 98)
	    	{
	    		decryptedMessage.push_back(num1);
		    }
		   	else
		   	{
		   		return;
		   	}
		}
    }
}

void getMessageFromUser()
{
	cout << "Enter the name of the message file: ";
	cin.getline(msgFile, 256);
}

void getGcodeFromUser()
{
	cout << "Enter the name of the gcode file: ";
	cin.getline(gcodeFile, 256);
}

void checkForSpace(string gcodeFile)
{
	int numExtrudeCommands = 0;
	string command;
	ifstream gcode(gcodeFile);
	while(!gcode.eof())
	{
		gcode>>command;
		if(command[0]=='E' && command.length() >=8)
		{
			numExtrudeCommands++;
		}
	}
	//cout << "Number of Extruder Commands: " << numExtrudeCommands << endl;
	if(encryptedMessage.size()>numExtrudeCommands)
	{
		cout << "Not enough room in gcode for your message.  Exiting." << endl;
		exit(0);
	}
	else
	{
		cout << "Pleny of room.  Processing your message..." << endl;
	}
}

int main ()
{
	getMessageFromUser();
	getGcodeFromUser();
  	
  	charToASCII(msgFile);
  	checkForSpace(gcodeFile);
  	stegoGode(gcodeFile);
  	deStegoGcode();
  	ASCIIToChar();
  	cout << "Message processed." << endl;

  return 0;
}