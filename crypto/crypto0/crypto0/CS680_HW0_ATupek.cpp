//  Ann Tupek
//  CS 680
//  HW0
//  main.cpp
//  due 1/23/15
//
//  Vigenere Cipher to determine which words in the Shakespeare dictionary (dict.txt)
//  combine in plaintext and key to produce ciphertexts starting with 'moose'

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using std::vector;
using std::ifstream;
using std::string;
using std::ofstream;

using std::cout;
using std::endl;

//convert letter from ASCII value to 0-25 value
int convert(char letter)
{
    int num = (letter);
    num -= 97;
    return num;
}

int main()
{
    vector<string> ourWords;
    string line;
    ifstream inFile("dict.txt");
    ofstream outFile("pairs.txt");
    while(!inFile.eof())
    {
        inFile>>line;
        ourWords.push_back(line);
    }
    
    for(int i = 0; i<ourWords.size()-1; i++)
    {
        for(int j = 0; j<ourWords.size()-1;)
        {
            string string1=ourWords[i]; //the message
            string string2=ourWords[j]; //the key
            string stringTemp = string2; //temp key
            
            while(stringTemp.length()<5) //if our key is less than 5 characters, cycle it
            {
                stringTemp+=string2;
            }

            if((convert(string1[0])+convert(stringTemp[0]))%26 == 'm'-97)
            {
                if((convert(string1[1])+convert(stringTemp[1]))%26 == 'o'-97)
                {
                    if((convert(string1[2])+convert(stringTemp[2]))%26 == 'o'-97)
                    {
                        if((convert(string1[3])+convert(stringTemp[3]))%26 == 's'-97)
                        {
                            if((convert(string1[4])+convert(stringTemp[4]))%26 == 'e'-97)
                            {
                                outFile << string1 << "|" << string2 << endl;
                                j++;
                            }
                            else
                            {
                                j++;
                                if(ourWords[j][4]==ourWords[j-1][4])
                                {
                                    j++; //skip to next letter
                                }
                            }
                        }
                        else
                        {
                            j++;
                            if(ourWords[j][3]==ourWords[j-1][3])
                            {
                                j++; //skip to next letter
                            }
                        }
                    }
                    else
                    {
                        j++;
                        if(ourWords[j][2]==ourWords[j-1][2])
                        {
                            j++; //skip to next letter
                        }
                    }
                }
                else
                {
                    j++;
                    if(ourWords[j][1]==ourWords[j-1][1])
                    {
                        j++; //skip to next letter
                    }
                }
            }
            else
            {
                j++;
                if(ourWords[j][0]==ourWords[j-1][0])
                {
                    j++; //skip to next letter
                }
            }
        }
    }
    
    return 0;
}
