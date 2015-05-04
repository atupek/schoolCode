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

pair<string, string> incomingFact;
tuple<string, string, string> incomingRelation;

vector <pair<string, string>> savedFacts;
vector <tuple<string, string, string>> savedRelations;

void saveFact(string atom, string var)
{
	pair<string, string> newFact=std::make_pair(atom, var);
	savedFacts.push_back(newFact);
}

void saveRelation(string atom, string var1, string var2)
{
	tuple<string, string, string> newRelation = std::make_tuple(atom, var1, var2);
	savedRelations.push_back(newRelation);
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

	map<string,Variable> myVars;
	vector<pair<string, string>> myFacts;
	vector<tuple<string, string, string>> myRelations;

	string arg1, arg2;

	void addVariable(string);
	void addFact(string, string);
	void addRelation(string, string, string);
	void queryRule(string, set<string>);

};

map<string, set<string> > singleFact;
map<string, map<string, set<string>>> relationFact;
map<string, map<string, set<string>>> inverseRelationFact;
map<string, Rule> rules;

void insertFacts(string ruleName)
{
	if(!savedFacts.empty())
	{
		for(auto it = savedFacts.begin(); it != savedFacts.end(); it++)
		{
			rules[ruleName].addFact(it->first, it->second);
		}
	}
}

void insertRelations(string ruleName)
{
	if(!savedRelations.empty())
	{
		for(auto it = savedRelations.begin(); it != savedRelations.end(); it++)
		{
			rules[ruleName].addRelation(get<0>(*it), get<1>(*it), get<2>(*it));
		}
	}
}

void Rule::addVariable(string var)
{
	Variable newVar;
	myVars[var] = newVar;
}

void Rule::addFact(string factName, string var1)
{
	//check if factName exist in global facts
	if(singleFact.find(factName)!=singleFact.end())
	{
		if(myVars.find(var1)==myVars.end())
		{
			addVariable(var1);
		}
		pair<string, string> newFact = make_pair(factName, var1);
		myFacts.push_back(newFact);
	}
	//if factName does not exist, print error
	else
	{
		cout << "Existence Error: " << factName << " not found!" << endl;
	}
}

void Rule::addRelation(string relationName, string var1, string var2)
{
	//check if relationName exists in global relations
	if(relationFact.find(relationName)!=relationFact.end())
	{
		if(myVars.find(var1)==myVars.end())
		{
			addVariable(var1);
		}
		if(myVars.find(var2)==myVars.end())
		{
			addVariable(var2);
		}
		tuple<string, string, string> newRelation = make_tuple(relationName, var1, var2);
		myRelations.push_back(newRelation);
	}
	//if relationName does not exist, print error
	else
	{
		cout << "Existence Error: " << relationName << " not found!" << endl;
	}
}

set<string> intersection(set<string> set1, set<string> set2)
{
	set<string> result;
	for(auto ii = set1.begin(); ii!= set1.end(); ii++)
	{
		if(set2.find(*ii)!= set2.end())
		{
			result.insert(*ii);
		}
	}
	return result;
}

//query rule 
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
		//if it's a fact, call it & see if set in nextVar changes
		//if so, apply change to nextVar and put it back in changedVars
		for(auto factIT = myFacts.begin(); factIT!= myFacts.end(); factIT++)
		{
			if(nextVar==get<1>(*factIT))
			{
				string resultVar = get<1>(*factIT);
				set<string> factResults;
				for(auto ii = myVars[nextVar].members.begin(); ii != myVars[nextVar].members.end(); ii++)
				{
					set<string> temp = findFact(get<0>(*factIT));
					factResults.insert(temp.begin(), temp.end());
				}
				if(myVars[resultVar].isInitialized==false)
				{
					myVars[resultVar].isInitialized=true;
					myVars[resultVar].members = factResults;
					changedVars.insert(resultVar);
				}
				else
				{
					set<string> intersectionSet = intersection(factResults, myVars[resultVar].members);
					if(intersectionSet != myVars[resultVar].members) //if it changed...
					{
						myVars[resultVar].members = intersectionSet;
						changedVars.insert(resultVar);
					}
				}
			}
		}
		//if it's a relation, call it & get the result variable name & set
		//for the returned variable, union that with set currently in that variable
		//if the union is different than the value currently in that variable
		//then update that variable to the unioned value and put that variable back in changedVars
		for(auto relIT = myRelations.begin(); relIT != myRelations.end(); relIT++)
		{
			if(nextVar == get<1>(*relIT))
			{
				string resultVar = get<2>(*relIT);
				set<string> relationResults;
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
					if(intersectionSet != myVars[resultVar].members) //if it changed...
					{
						myVars[resultVar].members = intersectionSet;
						changedVars.insert(resultVar);
					}

				}
			}
			if(nextVar == get<2>(*relIT))
			{
				string resultVar = get<1>(*relIT);
				set<string> relationResults;
				for(auto ii = myVars[nextVar].members.begin(); ii!=myVars[nextVar].members.end(); ii++)
				{
					set<string> temp = findInvRelationship(get<0>(*relIT), *ii);
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
					if(intersectionSet != myVars[resultVar].members) //if it changed...
					{
						myVars[resultVar].members = intersectionSet;
						changedVars.insert(resultVar);
					}

				}
			}
			
		}
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
	}
}

void setSingleFact(string prop, string id)
{
	//if the fact is not yet listed, insert it into the map & add the identifier
	if(singleFact.find(prop)==singleFact.end())
	{
		set<string> ids;
		ids.emplace(id);
		singleFact.emplace(prop, ids);
	}
	//if the fact is in the map, insert the id into its set of ids
	else
	{
		singleFact.find(prop)->second.emplace(id);
	}
}

//for ease of searching, create an inverse relationship for each relationship
void setInverseRelateFact(string inverseRelation, string relator, string relatee)
{
	map<string, map<string, set<string> > >::iterator IRFI = inverseRelationFact.find(inverseRelation);
	if(IRFI == inverseRelationFact.end())
	{
		set<string> rels;
		rels.emplace(relator);
		map<string, set<string> > invRelFacts;
		invRelFacts[relatee] = rels;
		inverseRelationFact[inverseRelation] = invRelFacts;
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
		}
		//if the relator is already listed, insert the relatee into its set of relatees
		else
		{
			IRI->second.insert(relator);
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

			setInverseRelateFact(relationship, relator, relatee);
		}
		//if the relator is already listed, insert the relatee into its set of relatees
		else
		{
			RI->second.insert(relatee);
			setInverseRelateFact(relationship, relator, relatee);
		}
	}
}

set <string> findFact(string searchFact)
{
	if(singleFact.find(searchFact) != singleFact.end())
		{
			auto it=singleFact.find(searchFact);
			return it->second;

		}
	else
		{
			cout << "Existence Error: " << searchFact  << " not found!" << endl;
			set<string> empty;
			return empty;
		}
}

set<string> findRelationship(string searchRelationship, string relator)
{
	map<string, map<string, set<string> > >::iterator it = relationFact.find(searchRelationship); //iterator to relator
	if(it != relationFact.end())
		{
			map<string, set<string> >::iterator relateeSetIt = it->second.find(relator);

			if(relateeSetIt != it->second.end())
			{
        		return relateeSetIt->second;
      		}
      		else
      		{
      			cout << "Existence Error: " << relator << " not found for " << searchRelationship << endl;
      			set<string> empty;
      			return empty;
      		}
		}
	else
		{
			cout << "Existence Error: " << searchRelationship  << " not found!" << endl;
			set<string> empty;
      		return empty;
		}
}

set<string> findInvRelationship(string searchInvRelationship, string relatee)
{
	map<string, map<string, set<string> > >::iterator it = inverseRelationFact.find(searchInvRelationship); //iterator to relator
	if(it != inverseRelationFact.end())
		{
			map<string, set<string> >::iterator relatorSetIt = it->second.find(relatee);

			if(relatorSetIt != it->second.end())
			{
        		for(set<string>::iterator relatorIt = relatorSetIt->second.begin(); relatorIt != relatorSetIt->second.end(); relatorIt++)
        		{
          			return relatorSetIt->second;
        		}
      		}
      		else
      		{
      			cout << "Existence Error: " << relatee << " not found for " << searchInvRelationship << endl;
      			set<string> empty;
      			return empty;
      		}
		}
	else
		{
			cout << "Existence Error: " << searchInvRelationship  << " not found!" << endl;
			set<string> empty;
      		return empty;
		}
}

void setQuery(string ruleName, string varName, string queryName)
{
	querySet.clear();
	querySet.insert(queryName);
	rules[ruleName].queryRule(varName, querySet);
}

void checkRelation(string relationName, string query1, string query2)
{
	map<string, map<string, set<string>>>::iterator iter=relationFact.find(relationName);
	if(iter!=relationFact.end())
	{
		map<string, set<string> >::iterator secondIter = iter->second.find(query1);
		if(secondIter!=iter->second.end())
		{
			set<string>::iterator setIter = secondIter->second.find(query2);
			if(setIter!=secondIter->second.end())
			{
				cout <<"Yes." << endl;
			}
			else
			{
				cout << "No." << endl;
			}
		}
		else
		{
			cout << "No." << endl;
		}
	}
	else
	{
		cout << "No." << endl;
	}

}

void queryFact(string factName, string var)
{
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
