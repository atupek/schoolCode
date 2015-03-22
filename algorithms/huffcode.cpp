// huffcode.h 
// Ann Tupek
// CS 611
// 6 Dec 2012
// Assignment 6
// 
// Source for class HuffCode
// Skeleton from Glenn G Chappell

#include "huffcode.h"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;

#include <iostream>
using std::cout;
using std::endl;


typedef tuple<char, int, int, int> node;

const int CHAR = 0;
const int WEIGHT = 1;
const int PARENT = 2;
const int SIDE = 3;

vector<node> vecNode; // Array to store the nodes

// Comparison function: given the indices of two nodes in the array, compare their weights. 
auto comp = [&](const int & a, const int & b)
{
	auto wta = get<WEIGHT>(vecNode[a]);
	auto wtb = get<WEIGHT>(vecNode[b]);
	return wtb < wta;
};

priority_queue<int, vector<int>, decltype(comp)> qNode(comp);

  map<char, string> encodeMap;
  map<string, char> decodeMap;

void HuffCode::setWeights(const unordered_map<char, int> & theweights)
{
    vecNode.clear();
    encodeMap.clear();
    decodeMap.clear();

    for (auto it = theweights.begin(); it != theweights.end(); ++it)
    {
    	node leafNode = make_tuple(it->first, it->second, -1, 0);
    	vecNode.push_back(leafNode); // Put the newly created node in the array
    	qNode.push(vecNode.size()-1); // The index of this node is the array size - 1
    }

    cout << "vecNode size before: " << vecNode.size() << endl;
    
    while(!qNode.empty())
    {
      int firstChildIndex = qNode.top(); // Index of the lowest-weight node
    	qNode.pop();
      int secondChildIndex = qNode.top(); // Index of the second-lowest-weight node
    	qNode.pop();
      
    	node internalNode = make_tuple(0, get<WEIGHT>(vecNode[firstChildIndex])+get<WEIGHT>(vecNode[secondChildIndex]), -1, 0);
      get<PARENT>(vecNode[firstChildIndex]) = vecNode.size();
      get<SIDE>(vecNode[firstChildIndex]) = 0;
      get<PARENT>(vecNode[secondChildIndex]) = vecNode.size();
      get<SIDE>(vecNode[secondChildIndex]) = 1;
    	vecNode.push_back(internalNode);

      if(!qNode.empty()) {
        qNode.push(vecNode.size()-1);
      }
    }

    for(int i = 0; i< theweights.size(); ++i)
    {
      string code;
      //figure out code for given char
      int j = i;
      while(get<PARENT>(vecNode[j]) != -1)
      {
        code.insert(0, std::to_string(get<SIDE>(vecNode[j])));
        j=get<PARENT>(vecNode[j]);
      }
      encodeMap[get<CHAR>(vecNode[i])] = code;
      decodeMap[code] = get<CHAR>(vecNode[i]);
    }
}


string HuffCode::encode(const string & text) const
{
    string encodedString;
    for(auto i = 0; i<text.size(); i++)
    {
      encodedString = encodedString + encodeMap[text[i]];
    }
    return encodedString;
}


string HuffCode::decode(const string & codestr) const
{
  string tempString = codestr;
  string decodedString;
  while (tempString.size() > 0)
  {
    int i = 1;
    while (decodeMap.find(tempString.substr(0, i)) == decodeMap.end()) //while we don't find a match, keep looking
    {
      ++i;
    }
    decodedString.append(1, decodeMap[tempString.substr(0, i)]);
    tempString = tempString.substr(i, tempString.size()-i);
  }
    return decodedString;
}

