#include <stdio.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;

vector<unsigned char> plainTxt;
// charToHex()
// gets char from text to be encrypted and dumps it into vector of unsigned chars
void charToHex(const char *msg)
{
  FILE * plainTxtFile;
  FILE * oFile;
  char c;

  plainTxtFile=fopen (msg,"r");
  oFile=fopen ("out.txt", "w");
  if (plainTxtFile==NULL) perror ("Error opening file");
  else
  {
    do {
      c = fgetc (plainTxtFile);
      plainTxt.push_back(c);
    } while (c != EOF);
    
    fclose (plainTxtFile);

    //debug stuff, TODO: delete all oFile stuff from this function
    for(auto i = 0; i < plainTxt.size(); i++)
    {
      fprintf(oFile, "0x%02x ", plainTxt[i]);
    }
    fclose (oFile);
  }
}
/*
// hexToDec
// gets hex value from encrypted file, converts it to its decimal value
// outputs to vector
//maybe i should just do it like I did in charToASCII in the previous project...
void hexToDec(const char *msg)
{
	FILE * pFile;
	int c; //should this be an int?
	char str[256];

	pFile=fopen(msg, "r");

	if (pFile==NULL) perror ("Error opening file");
  	else
  	{
    do {
      c = fgets (str, 2, pFile); //is this the right way to do it?!? puts string into str
      fprintf(oFile, "%02x ", c);//TODO put it into a vector of ints
    } while (c != EOF);
    
    fclose (pFile);

  }
}
*/
/*
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
}*/

/*
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
*/

int main()
{
	char msg[256] = "message.txt";
	charToHex(msg);
	return 0;
}
