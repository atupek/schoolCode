//  Ann Tupek
//  CS 680
//  Project 2
//  cryptoProj.cpp
//  Further experiments with stego'ing gcode extruder commands.
//	Histograms of the files are included in the folder.
//	Also used a larger message file (first half of first chapter of Frankenstein) to see if the
//	ratio of modfied extruder commands to unmodified extruder commands makes a difference
//	(in the first project, the message replaced 63% of the extruder commands, this one
//	replaces 99% of the extruder commands)
//
//  Encrypt: Determines whether or not there is enough room in the gcode file for the message.
//			Converts secret message into ASCII decimal value
//  		Parses through gcode file for Extruder commands
//  		Replaces last three decimal places of extruder commands with ASCII
//  Decrypt: Parses through gcode file for Extruder commands and removes last three decimal places
//			Converts last three decimal places to ASCII value
//			Dumps into text file
//  stegoGcode2 replaces all decimal places of extruder commands with ASCII values, to show how
//			the physical print is affected.

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
// gets char from text to be encrypted, sets it to its ASCII value
// dumps it into a vector of ints
void charToASCII(string msg)
{
	ifstream inFile(msg);
	char c;
	while(inFile.get(c))
    {
    	int number = c;
    	encryptedMessage.push_back(number);
    }
    encryptedMessage.push_back(999); //sentinel for end of message
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
   		if(number == 999) //for end of message sentinel
   		{
   			return;
   		}
   		else
   		{
   			number = decryptedMessage[i];
   		}
   		fprintf(outFile, "%c", number);
   }
   fclose (outFile);
}

// stegoGcode()
// regular expression matches extruder gCode commands w 5 places after the decimal
// replaces last three decimal digits with number from ASCII vector
void stegoGcode(string gcodeFile)
{
	string line;
	int i = 0;
	ifstream inFile(gcodeFile);
	FILE * outFile;
    outFile = fopen("20mm_cube_wMessage.gcode", "w");
	while(!inFile.eof())
    {
    	getline(inFile, line);
    	// regex matches EXX.XXXXX where X is a digit
        regex expr("(\\x45\\d+\\.\\d{5})");
		smatch match;
		if(!regex_search(line, match, expr))
		{
			fprintf(outFile, "%s\n", line.c_str());
		}
		else
		{
			regex_search (line,match,expr);
			if(i<encryptedMessage.size())
			{
				string prefix = match.prefix().str();
		    	fprintf(outFile, "%s", prefix.c_str());
		    	string edited = match.str();
		    	line = match.suffix().str();
		    	//remove last three digits of matched extruder command
			    edited.pop_back();
		    	edited.pop_back();
		    	edited.pop_back();
		    	fprintf(outFile, "%s", edited.c_str());
		    	// put ASCII from message into gcode
		    	fprintf(outFile, "%03d", encryptedMessage[i]);
		    	i++;
		    	fprintf(outFile, "%s\n", line.c_str());
			}
			else
			{
				fprintf(outFile, "%s\n", line.c_str());
			}

		}
    }
    fclose(outFile);
}

// stegoGcode2()
// regular expression matches extruder gCode commands w 5 places after the decimal
// replaces fractional part of command with number from ASCII vector
// NOTE: this changes the number of decimal digits from 5 to 3, so two 0's are tacked
// onto the end to retain 5 decimal digits
void stegoGcode2(string gcodeFile)
{
	string line;
	int i = 0;
	ifstream inFile(gcodeFile);
	FILE * outFile;
    outFile = fopen("20mm_cubewMessage2.gcode", "w");
	while(!inFile.eof())
    {
    	getline(inFile, line);
    	// regex matches EXX.XXXXX where X is a digit
        regex expr("(\\x45\\d+\\.\\d{5})");
		smatch match;
		if(!regex_search(line, match, expr))
		{
			fprintf(outFile, "%s\n", line.c_str());
		}
		else
		{
			regex_search (line,match,expr);
			if(i<encryptedMessage.size())
			{
				string prefix = match.prefix().str();
		    	fprintf(outFile, "%s", prefix.c_str());
		    	string edited = match.str();
		    	line = match.suffix().str();
		    	//remove last five digits of matched extruder command
			    edited.pop_back();
		    	edited.pop_back();
		    	edited.pop_back();
		    	edited.pop_back();
		    	edited.pop_back();
		    	fprintf(outFile, "%s", edited.c_str());
		    	// put ASCII from message into gcode
		    	// tack two 0's onto the end to retain 5 decimal points
		    	fprintf(outFile, "%03d00", encryptedMessage[i]);
		    	i++;
		    	fprintf(outFile, "%s\n", line.c_str());
			}
			else
			{
				fprintf(outFile, "%s\n", line.c_str());
			}

		}
    }
    fclose(outFile);
}

// deStegoGcode()
// regular expression matches extruder commands w 5 places after the decimal
// pulls out last three decimal places (our ASCII characters)
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
		    //get last three digits of extruder command
		   	string nums = edited.substr(edited.length()-3, 3);
		   	int num1 = atoi(nums.c_str());
		   	//if not end of message sentinel, add number to vector
		   	if(num1 != 999)
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
	//frankensteinC1.txt for the 20mm cube
	//frankAll.txt for the soap dish
	cout << "Enter the name of the message file: ";
	cin.getline(msgFile, 256);
}

void getGcodeFromUser()
{
	// 20mm_cube.gcode or soapdish.gcode
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
	cout << "Number of Extruder Commands: " << numExtrudeCommands << endl;
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
  	stegoGcode(gcodeFile);
  	stegoGcode2(gcodeFile);
  	deStegoGcode();
  	ASCIIToChar();
  	cout << "Message processed." << endl;

  return 0;
}