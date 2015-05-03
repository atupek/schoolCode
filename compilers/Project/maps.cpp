//map stuff for prolog parser...
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <tuple>
#include <queue>

using std::cout;
using std::endl;

using std::string;

using std::map;

using std::set;

using std::vector;

using std::pair;

using std::tuple;
using std::get;

using std::queue;

set<string> findRelationship(string searchRelationship, string relator);
set<string> findInvRelationship(string searchRelationship, string relator);
set<string> findFact(string searchFact);

set<string> querySet;

string currentString;

void setCurrentString(string str)
{
	currentString = str;
}

class Variable
{
public:
	//string label;
	set<string> members;
	bool isInitialized;

	void addMembers(set<string>, string);
	void initialize();
	void unInitialize();
};

void Variable::addMembers(set<string> members, string newMember)
{
	members.insert(newMember);
}

void Variable::initialize()
{
	this->isInitialized = true;
}

void Variable::unInitialize()
{
	this->isInitialized = false;
}

class Rule
{
public:
	//string ruleName;
	map<string,Variable> myVars;
	vector<pair<string, string>> myFacts;
	vector<tuple<string, string, string>> myRelations;
	vector<tuple<string, string, string>> myRules;

	string arg1, arg2;

	void addVariable(string);
	void addFact(string, string);
	void addRelation(string, string, string);
	void addRule(string, string, string);
	void queryRule(string, set<string>);
	//set<string> queryRule(string, set<string>);
};

map<string, set<string> > singleFact;
map<string, map<string, set<string>>> relationFact;
map<string, map<string, set<string>>> inverseRelationFact;
map<string, Rule> rules;

void Rule::addVariable(string var)
{
	Variable newVar;
	myVars[var] = newVar;
}

void Rule::addFact(string factName, string var1)
{
	//does factName exist in global facts?
	if(singleFact.find(factName)!=singleFact.end())
	{
		if(myVars.find(var1)==myVars.end())
		{
			addVariable(var1);
			//cout << "variable added" << endl;
		}
		pair<string, string> newFact = make_pair(factName, var1);
		myFacts.push_back(newFact);
		//cout << "fact added" << endl;
	}
	else
	{
		//cout << "Existence Error: Fact: " << factName << " not found!" << endl;
	}
}

void Rule::addRelation(string relationName, string var1, string var2)
{
	//does relationName exist in global relations?
	if(relationFact.find(relationName)!=relationFact.end())
	{
		//is the variable already listed in the rule?
		if(myVars.find(var1)==myVars.end())
		{
			addVariable(var1);
			//cout << "variable added" << endl;
		}
		if(myVars.find(var2)==myVars.end())
		{
			addVariable(var2);
			//cout << "variable added" << endl;
		}
		tuple<string, string, string> newRelation = make_tuple(relationName, var1, var2);
		myRelations.push_back(newRelation);
		//cout << "relation added" << endl;
	}
	else
	{
		cout << "Existence Error: Relation: " << relationName << " not found!" << endl;
	}
}

void Rule::addRule(string ruleName, string var1, string var2)
{
	tuple<string, string, string> newRule = make_tuple(ruleName, var1, var2);
	myRules.push_back(newRule);
}

set<string> intersection(set<string> set1, set<string> set2)
{
	set<string> result;
	//cout << "Begin Set Intersection" << endl;
	for(auto ii = set1.begin(); ii!= set1.end(); ii++)
	{
		if(set2.find(*ii)!= set2.end())
		{
			result.insert(*ii);
		}
	}
	return result;
}

//query rule (changed from returning set<string> to return void...)
void Rule::queryRule(string var, set<string> inputSet)
{
	set<string> results;
	set<string> changedVars;
	//first go through all vars, if not the one that passed in, set to empty & uninitialized
	//if is the one passed in, set its set to the inputSet and set it to initialized
	map<string, Variable>::iterator mapIT;
	for(mapIT = myVars.begin(); mapIT != myVars.end(); mapIT++)
	{
		if(mapIT->first==var)
		{
			mapIT->second.isInitialized = true;
			mapIT->second.members = inputSet;
		}
		else
		{
			mapIT->second.isInitialized = false;
			mapIT->second.members.clear();
		}

	}
	changedVars.insert(var);
	while(!changedVars.empty())
	{
		string nextVar = *changedVars.begin();

		changedVars.erase(nextVar);
		//cout << "FACTS: working on variable: " << nextVar << endl;
		//for each fact, relationship, rule that uses nextVar
		//if it's a fact, call it & see if set in nextVar changes
		//if so, apply change to nextVar and put it back in changedVars
		for(auto factIT = myFacts.begin(); factIT!= myFacts.end(); factIT++)
		{
			cout << "FACT CALLED" << endl;
			if(nextVar==get<1>(*factIT))
			{
				string resultVar = get<1>(*factIT);
				set<string> factResults;
				//cout << "checking fact: " << get<0>(*factIT) << endl;
				for(auto ii = myVars[nextVar].members.begin(); ii != myVars[nextVar].members.end(); ii++)
				{
					set<string> temp = findFact(get<0>(*factIT));
					factResults.insert(temp.begin(), temp.end());
					//cout << "FOR LOOP" << endl;
				}
				if(myVars[resultVar].isInitialized==false)
				{
					myVars[resultVar].isInitialized=true;
					myVars[resultVar].members = factResults;
					changedVars.insert(resultVar);
					//cout << "IF LOOP" << endl;
				}
				else
				{
					set<string> intersectionSet = intersection(factResults, myVars[resultVar].members);
					if(intersectionSet != myVars[resultVar].members) //if we changed it...
					{
						myVars[resultVar].members = intersectionSet;
						changedVars.insert(resultVar);
					}
					//cout << "ELSE LOOP" << endl;
				}
			}
		}
		//if it's a relation, call it & get the result variable name & set
		//for the returned variable, union that with set currently in that variable
		//if the union is different than the value currently in that variable
		//then update that variable to the unioned value and put that variable back in changedVars
		for(auto relIT = myRelations.begin(); relIT != myRelations.end(); relIT++)
		{
			cout << "RELATION CALLED" << endl;
			if(nextVar == get<1>(*relIT))
			{
				string resultVar = get<2>(*relIT);
				set<string> relationResults;
				//cout << "RELATIONS: checking relationship: " << get<0>(*relIT) << " into var: " << get<2>(*relIT)<< endl;
				for(auto ii = myVars[nextVar].members.begin(); ii!=myVars[nextVar].members.end(); ii++)
				{
					set<string> temp = findRelationship(get<0>(*relIT), *ii);
					relationResults.insert(temp.begin(), temp.end());
				}
				if(myVars[resultVar].isInitialized==false)
				{
					myVars[resultVar].isInitialized = true;
					myVars[resultVar].members = relationResults;
					changedVars.insert(resultVar);
				}
				else
				{
					set<string> intersectionSet = intersection(relationResults, myVars[resultVar].members);
					if(intersectionSet != myVars[resultVar].members) //if we changed it...
					{
						myVars[resultVar].members = intersectionSet;
						changedVars.insert(resultVar);
					}

				}
			}
			if(nextVar == get<2>(*relIT))
			{
				cout << "INVERSE RELATION CALLED" << endl;
				string resultVar = get<1>(*relIT);
				set<string> relationResults;
				//cout << "RELATIONS: checking inverse relationship: " << get<0>(*relIT) << " into var: " << get<1>(*relIT)<< endl;
				for(auto ii = myVars[nextVar].members.begin(); ii!=myVars[nextVar].members.end(); ii++)
				{
					//cout << "get<0>(*relIT)" << get<0>(*relIT) << ", " << *ii << endl;
					set<string> temp = findInvRelationship(get<0>(*relIT), *ii);
					//cout << "temp SIZE: " << temp.size() << endl;
					relationResults.insert(temp.begin(), temp.end());
					//return relationResults;
				}
				//cout << "relation results size (line228): " << relationResults.size() << endl;
				if(myVars[resultVar].isInitialized==false)
				{
					myVars[resultVar].isInitialized = true;
					myVars[resultVar].members = relationResults;
					changedVars.insert(resultVar);
				}
				else
				{
					set<string> intersectionSet = intersection(relationResults, myVars[resultVar].members);
					if(intersectionSet != myVars[resultVar].members) //if we changed it...
					{
						myVars[resultVar].members = intersectionSet;
						changedVars.insert(resultVar);
					}

				}
			}
			
		}
		//if it's a rule, do the same thing as relation -- TODO
		/*
		for(auto ruleIT = myRules.begin(); ruleIT != myRules.end(); ruleIT++)
		{
			cout << "RULE CALLED" << endl;
			cout << "FIRST INDEX: " << get<1>(*ruleIT) << endl;
			if(nextVar == get<1>(*ruleIT))
			{
				string resultVar = get<2>(*ruleIT);
				cout << "SECOND INDEX: " << get<2>(*ruleIT) << endl;
				cout << "RULE 0: " << get<0>(*ruleIT) << endl;
				set<string> ruleResults;
				cout << "NUM VARS: " << myVars[nextVar].members.size() << endl;
				for(auto ii = myVars[nextVar].members.begin(); ii!=myVars[nextVar].members.end(); ii++)
				{
					cout << "QUERY RULE: " << get<0>(*ruleIT) << endl;
					cout << "INDEX: " << *ii << endl;
					//set<string> temp = queryRule(get<0>(*ruleIT), *ii);
					//ruleResults.insert(temp.begin(), temp.end());
				}
				if(myVars[resultVar].isInitialized==false)
				{
					myVars[resultVar].isInitialized = true;
					myVars[resultVar].members = ruleResults;
					changedVars.insert(resultVar);
				}
				else
				{
					set<string> intersectionSet = intersection(ruleResults, myVars[resultVar].members);
					if(intersectionSet != myVars[resultVar].members) //if we changed it...
					{
						myVars[resultVar].members = intersectionSet;
						changedVars.insert(resultVar);
					}

				}
			}
		}*/
	}
	if(var == arg1)
	{
		set<string> resultSet = myVars[arg2].members;
		if(resultSet.empty())
		{
			cout << "No." << endl;
		}
		else
		{
			for(auto ii= resultSet.begin(); ii!= resultSet.end(); ii++)
			{
				cout << "     " << *ii << endl;
			}
		}
		//return myVars[arg2].members;
	}
	else
	{
		set<string> resultSet = myVars[arg1].members;
		if(resultSet.empty())
		{
			cout << "No." << endl;
		}
		else
		{
			for(auto ii= resultSet.begin(); ii!= resultSet.end(); ii++)
			{
				cout << "     " << *ii << endl;
			}
		}
		//return myVars[arg1].members;
	}
}

void setSingleFact(string prop, string id)
{
	//if the property is not yet listed, insert it into the map & add the identifier
	if(singleFact.find(prop)==singleFact.end())
	{
		set<string> ids;
		ids.emplace(id);
		singleFact.emplace(prop, ids);
		//cout << "new property added: " << id << " added to " << prop << endl;
	}
	//if the property is in the map, insert the id into its set of ids
	else
	{
		singleFact.find(prop)->second.emplace(id);
		//cout << id << " added to " << prop << endl;
	}
	cout << "SINGLE FACT SET! " << endl;
}

void setInverseRelateFact(string inverseRelation, string relator, string relatee)
{
	//string inverseRelation = relationship + "_inv";
	map<string, map<string, set<string> > >::iterator IRFI = inverseRelationFact.find(inverseRelation);
	if(IRFI == inverseRelationFact.end())
	{
		set<string> rels;
		rels.emplace(relator);
		map<string, set<string> > invRelFacts;
		invRelFacts[relatee] = rels;
		inverseRelationFact[inverseRelation] = invRelFacts;
		//cout << "new inverse relationship added: " << inverseRelation << "(" << relatee << ", " << relator << ")" << endl;

	}
	//if the relationship is in the map, insert the relator-relatee into its set
	else
	{
		// if the relatee is not yet listed, insert it & add the relator
		map<string, set<string> >::iterator IRI = IRFI->second.find(relatee);
		if(IRI == IRFI->second.end())
		{
			set<string> ids;
			ids.emplace(relator);

			IRFI->second[relatee] = ids;
			//cout << inverseRelation << "(" << relatee << ", " << relator << ")" << endl;
		}
		//if the relator is already listed, insert the relatee into its set of relatees
		else
		{
			IRI->second.insert(relator);
			//cout << inverseRelation << "(" << relatee << ", " << relator << ")" << endl;
		}
	}
}

void setRelateFact(string relationship, string relator, string relatee)
{
	//if the relationship is not yet listed, insert it into the map
	map<string, map<string, set<string> > >::iterator RFI = relationFact.find(relationship);
	if(RFI==relationFact.end())
	{
		set<string> rels;
		rels.emplace(relatee);
		map<string, set<string> > relFacts;
    	relFacts[relator] = rels;
    	relationFact[relationship] = relFacts;

		//cout << "new relationship added: " << relationship << "(" << relator << ", " << relatee << ")" << endl;
		setInverseRelateFact(relationship, relator, relatee);

	}
	//if the relationship is in the map, insert the relator-relatee into its set
	else
	{
		map<string, set<string> >::iterator RI = RFI->second.find(relator);
		if(RI == RFI->second.end())
		{
			set<string> ids;
			ids.emplace(relatee);

			RFI->second[relator] = ids;

			//cout << relationship << "(" << relator << ", " << relatee << ")" << endl;
			setInverseRelateFact(relationship, relator, relatee);
		}
		//if the relator is already listed, insert the relatee into its set of relatees
		else
		{
			RI->second.insert(relatee);
			//cout << relationship << "(" << relator << ", " << relatee << ")" << endl;
			setInverseRelateFact(relationship, relator, relatee);
		}
	}
	//setInverseRelateFact(relationship, relator, relatee);
	cout << "RELATIONSHIP ADDED" << endl;
}

//TODO: change from void to return a set//DONE
set <string> findFact(string searchFact)
{
	if(singleFact.find(searchFact) != singleFact.end())
		{
			//cout << "Found Fact: " << searchFact << endl;
			auto it=singleFact.find(searchFact);
			for(auto i = it->second.begin(); i!= it->second.end(); i++)
			{
				//cout << *i << endl;
			}
			return it->second;

		}
	else
		{
			//cout << "Existence Error: " << searchFact  << " not found!" << endl;
			set<string> empty;
			return empty;
		}
}

//TODO: change from void to return a set//DONE
set<string> findRelationship(string searchRelationship, string relator)
{
	map<string, map<string, set<string> > >::iterator it = relationFact.find(searchRelationship); //iterator to relator
	if(it != relationFact.end())
		{
			//cout << "Found Relationship: " << searchRelationship << endl;
			map<string, set<string> >::iterator relateeSetIt = it->second.find(relator);

			if(relateeSetIt != it->second.end())
			{
        		//cout << "Found relatOR: " << relator << endl;
        		for(set<string>::iterator relateeIt = relateeSetIt->second.begin(); relateeIt != relateeSetIt->second.end(); relateeIt++)
        		{
          			//cout << "    " << *relateeIt << endl;
        		}
        		return relateeSetIt->second;
      		}
      		else
      		{
      			//cout << "Existence Error for relatOR: " << relator << " not found for " << searchRelationship << endl;
      			set<string> empty;
      			return empty;
      		}
		}
	else
		{
			//cout << "Existence Error: " << searchRelationship  << " not found!" << endl;
			set<string> empty;
      		return empty;
		}
}

//TODO: change from void to return a set
set<string> findInvRelationship(string searchInvRelationship, string relatee)
{
	map<string, map<string, set<string> > >::iterator it = inverseRelationFact.find(searchInvRelationship); //iterator to relator
	if(it != inverseRelationFact.end())
		{
			//cout << "Found Relationship: " << searchInvRelationship << endl;
			map<string, set<string> >::iterator relatorSetIt = it->second.find(relatee);

			if(relatorSetIt != it->second.end())
			{
        		//cout << "Found relatEE: " << relatee << endl;
        		for(set<string>::iterator relatorIt = relatorSetIt->second.begin(); relatorIt != relatorSetIt->second.end(); relatorIt++)
        		{
          			//cout << "    " << *relatorIt << endl;
          			return relatorSetIt->second;
        		}
      		}
      		else
      		{
      			//cout << "Existence Error for relatEE: " << relatee << " not found for " << searchInvRelationship << endl;
      			set<string> empty;
      			return empty;
      		}
		}
	else
		{
			//cout << "Existence Error: " << searchInvRelationship  << " not found!" << endl;
			set<string> empty;
      		return empty;
		}
}

//Just for testing...
void setFacts()
{
	setSingleFact("animal", "dog");
	setSingleFact("animal", "cat");	
	setSingleFact("animal", "moose");	
	setSingleFact("human", "annie");
	setSingleFact("human", "gregg");
	setSingleFact("bird", "eagle");

	setRelateFact("likes", "annie", "homework");
	setRelateFact("likes","annie", "chocolate");
	setRelateFact("likes", "dinah", "moose");
	setRelateFact("likes","dinah","gregg");
	setRelateFact("likes", "annie", "gregg");

	setRelateFact("wrote", "maryShelley", "frankenstein");
	setRelateFact("wrote", "williamShakespeare", "romeo&juliette");
	setRelateFact("wrote", "williamShakespeare", "kingLear");
	setRelateFact("wrote", "hughHowey", "wool");
	setRelateFact("wrote", "hughHowey", "nothing");

	setSingleFact("dead", "williamShakespeare");
	setSingleFact("dead", "maryShelley");

	setRelateFact("character", "romeo&juliette", "juliette");
	setRelateFact("character", "wool", "juliette");
	setRelateFact("character", "kingLear", "dog");
}

//Just for testing...
void searchingFacts()
{
	string searchFact = "human";

	findFact(searchFact);
	findFact("bird");

	string searchRelationship = "wrote";
	string relator = "annie";

	string searchInvRelationship = "likes_inv";
	string relatee = "gregg";

	findRelationship(searchRelationship,relator);
	findInvRelationship(searchInvRelationship, relatee);
}

//Just for testing...
void printSets()
{
	//for printing out set members
	for(map<string, map<string, set<string> > >::iterator ii = relationFact.begin(); ii != relationFact.end(); ii++)
	{
    	cout << ii->first << endl;
    	for(map<string, set<string> >::iterator jj = ii->second.begin(); jj != ii->second.end(); jj++)
    	{
      		cout << "    " << jj->first << endl;
      		for(set<string>::iterator kk = jj->second.begin(); kk != jj->second.end(); kk++)
      		{
        		cout << "        " << *kk << endl;
      		}
    	}
  	}

  	cout << endl;
  	for(map<string, map<string, set<string> > >::iterator ii = inverseRelationFact.begin(); ii != inverseRelationFact.end(); ii++)
  	{
    	cout << ii->first << endl;
    	for(map<string, set<string> >::iterator jj = ii->second.begin(); jj != ii->second.end(); jj++)
    	{
      		cout << "    " << jj->first << endl;
      		for(set<string>::iterator kk = jj->second.begin(); kk != jj->second.end(); kk++)
      		{
        		cout << "        " << *kk << endl;
      		}
    	}
	}
}

//setRule for testing...
// wroteAbout(X, Y):- wrote(X, Z), character(Z, Y)
// going to test for wroteAbout(X, juliette)
// should get williamShakespeare & hughHowey
void setRule1()
{
	Rule rule;
	rule.arg1="X";
	rule.arg2="Y";
	rule.addRelation("wrote", "X", "Z");
	rule.addRelation("character", "Z", "Y");
	rules["wroteAbout"]=rule;
}

void setRule2()
{
	Rule rule;
	rule.arg1="X";
	rule.arg2="Y";
	rule.addRelation("wrote","X","Y");
	rule.addFact("dead","X");
	rules["bookByDeadAuthor"]=rule;
}

void setRule3()
{
	Rule rule;
	rule.arg1="X";
	rule.arg2="Y";
	rule.addRelation("likes", "X", "Y");
	rule.addFact("animal", "Y");
	rules["likesAnimal"]= rule;
}

//wroteAboutAnimal(X, Y):-wroteAbout(X, Y), animal(Y)
void setRule4()
{
	Rule rule;
	rule.arg1="X";
	rule.arg2="Y";
	rule.addRule("wroteAbout", "X", "Y");
	rule.addFact("animal", "Y");
	//rule.addFact("character", "Y");
	rules["wroteAboutAnimal"]=rule;
}

void setRule5()
{
	Rule rule;
	rule.arg1="X";
	rule.arg2="Y";
	rule.addRelation("wrote", "X", "Y");
	rules["wrote"]=rule;
}

void setRule6()
{
	Rule rule;
	rule.arg1="X";
	rule.addFact("animal", "X");
	rules["animal"]=rule;
}

//for testing...
void printToken(string token)
{
	cout << "Token found: " << token << endl;
}

void setQuery(string ruleName, string varName, string queryName)
{
	querySet.clear();
	querySet.insert(queryName);
	rules[ruleName].queryRule(varName, querySet);
}

void queryRelationship()
{

}

void queryFact(string factName, string var)
{
	cout << "QUERYING FACT." << endl;
	set<string> resultSet = findFact(factName);
	if(resultSet.empty())
	{
		cout << "No." << endl;
	}
	else
	{
		for(auto ii= resultSet.begin(); ii!= resultSet.end(); ii++)
			{
				cout << "     " << *ii << endl;
			}
	}
}


void checkFact(string factName, string queryItem)
{
	cout << "CHECKING FACT." << endl;
	set<string> resultSet = findFact(factName);
	if(resultSet.find(queryItem)==resultSet.end())
	{
		cout << "No." << endl;
	}
	else
	{
		cout << "Yes." << endl;
	}
}
/*
int main()
{
	//for testing...
	setFacts();

	//for testing...
	//searchingFacts();

	//for testing...
	//printSets();

	setRule1();
	setRule2();
	setRule3();
	setRule5();
	setRule4();

	//queryRule("wroteAbout", "X", "juliette");
	set<string> resultSet;
	set<string> querySet;
	querySet.insert("juliette");
	resultSet=rules["wroteAbout"].queryRule("Y", querySet);
	//cout << "size of result set: " << resultSet.size() << endl;
	cout << "wroteAbout RESULTS: " << endl;
	for(auto ii= resultSet.begin(); ii!= resultSet.end(); ii++)
	{
		cout << "     " << *ii << endl;
	}
	querySet.clear();
	querySet.insert("frankenstein");
	resultSet=rules["bookByDeadAuthor"].queryRule("Y", querySet);
	cout << "dead RESULTS: " << endl;
	for(auto ii= resultSet.begin(); ii!= resultSet.end(); ii++)
	{
		cout << "     " << *ii << endl;
	}
	querySet.clear();
	querySet.insert("moose");
	resultSet=rules["likesAnimal"].queryRule("Y", querySet);
	cout << "Animal RESULTS: " << endl;
	for(auto ii= resultSet.begin(); ii!= resultSet.end(); ii++)
	{
		cout << "     " << *ii << endl;
	}

	querySet.clear();
	querySet.insert("hughHowey");
	resultSet=rules["wrote"].queryRule("X", querySet);
	cout << "Wrote RESULTS: " << endl;
	for(auto ii= resultSet.begin(); ii!= resultSet.end(); ii++)
	{
		cout << "     " << *ii << endl;
	}
	
	querySet.clear();
	querySet.insert("williamShakespeare");
	resultSet=rules["wroteAboutAnimal"].queryRule("X", querySet);
	cout << "WroteAboutAnimal RESULTS: " << endl;
	for(auto ii= resultSet.begin(); ii!= resultSet.end(); ii++)
	{
		cout << "     " << *ii << endl;
	}
	//cout << "singleFact size: " << singleFact.size() << endl;
	//cout << "relationFact size: " << relationFact.size() << endl;
	//cout << "inverseRelationFact size: " << inverseRelationFact.size() << endl;

	return 0;
}*/
