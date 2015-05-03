//map stuff for prolog parser...
#include <iostream>
#include <string>
#include <map>
#include <set>

using std::cout;
using std::cin;
using std::endl;

using std::string;

using std::map;

using std::set;

map<string, set<string> > singleFact;
//map<string, set<string> > relFacts;
map<string, set<string> > invRelFacts;
map<string, map<string, set<string> > > relationFact;
map<string, map<string, set<string> > > inverseRelationFact;


void setSingleFact(string prop, string id)
{
	//if the property is not yet listed, insert it into the map & add the identifier
	if(singleFact.find(prop)==singleFact.end())
	{
		set<string> ids;
		ids.insert(id);
		singleFact[prop] = ids;
		cout << "new property added: " << id << " added to " << prop << endl;
	}
	//if the property is in the map, insert the id into its set of ids
	else
	{
		singleFact.find(prop)->second.insert(id);
		cout << id << " added to " << prop << endl;
	}
}

void setInverseRelateFact(string relationship, string relator, string relatee)
{
	string inverseRelation = relationship + "_inv";
	
	if(inverseRelationFact.find(inverseRelation)==inverseRelationFact.end())
	{
		set<string> rels;
		rels.insert(relator);
		invRelFacts[relatee] = rels;
		inverseRelationFact[inverseRelation] = invRelFacts;
		cout << "new inverse relationship added: " << inverseRelation << "(" << relatee << ", " << relator << ")" << endl;

	}
	//if the relationship is in the map, insert the relator-relatee into its set
	else
	{
		// if the relatee is not yet listed, insert it & add the relator
		if(invRelFacts.find(relatee)==invRelFacts.end())
		{
			set<string> ids;
			ids.insert(relator);
			invRelFacts[relatee] = ids;
			cout << inverseRelation << "(" << relatee << ", " << relator << ")" << endl;
		}
		//if the relator is already listed, insert the relatee into its set of relatees
		else
		{
			invRelFacts.find(relatee)->second.insert(relator);
			cout << inverseRelation << "(" << relatee << ", " << relator << ")" << endl;
		}
	}
}

void setRelateFact(string relationship, string relator, string relatee)
{
	//if the relationship is not yet listed, insert it into the map
  	map<string, map<string, set<string> > >::iterator RFI = relationFact.find(relationship);
	if(RFI == relationFact.end())
	{
		set<string> rels;
		rels.insert(relatee);
    	map<string, set<string> > relFacts;
    	relFacts[relator] = rels;
    	relationFact[relationship] = relFacts;

		cout << "new relationship added: " << relationship << "(" << relator << ", " << relatee << ")" << endl;
		setInverseRelateFact(relationship, relator, relatee);

	}	else {
    // if the relationship is in the map, 
    // but this relator is not
    // insert the relator-relatee into its set
    map<string, set<string> >::iterator RI = RFI->second.find(relator);

		if(RI == RFI->second.end())
		{
			set<string> ids;
			ids.insert(relatee);

      RFI->second[relator] = ids;

      //map<string, set<string> > relFacts;
      ///relFacts[relator] = rels;

			//relFacts[relator] = ids;
			cout << relationship << "(" << relator << ", " << relatee << ")" << endl;
			setInverseRelateFact(relationship, relator, relatee);
		}
		//if the relator is already listed, insert the relatee into its set of relatees
		else
		{
      RI->second.insert(relatee);
			//relFacts.find(relator)->second.insert(relatee);
			cout << relationship << "(" << relator << ", " << relatee << ")" << endl;
			setInverseRelateFact(relationship, relator, relatee);
		}
	}
	//setInverseRelateFact(relationship, relator, relatee);
}

void findFact(string searchFact)
{
	if(singleFact.find(searchFact) != singleFact.end())
	{
			cout << "Found Fact: " << searchFact << endl;
      map<string, set<string> >::iterator it=singleFact.find(searchFact);
      for(set<string>::iterator ii = it->second.begin(); ii != it->second.end(); ii++)
			{
				cout << *ii << endl;
			}

	}
	else
	{
			cout << "Existence Error: " << searchFact  << " not found!" << endl;
	}
}

void findRelationship(string searchRelationship, string relator)
{
  map<string, map<string, set<string> > >::iterator it = relationFact.find(searchRelationship); //iterator to relator
	if(it != relationFact.end())
		{
			cout << "Found Relationship: " << searchRelationship << endl;
      map<string, set<string> >::iterator relateeSetIt = it->second.find(relator);
      if(relateeSetIt != it->second.end()) {
        cout << "Found relatOR: " << relator << endl;
        for(set<string>::iterator relateeIt = relateeSetIt->second.begin(); relateeIt != relateeSetIt->second.end(); relateeIt++) {
          cout << "    " << *relateeIt << endl;
        }
      }
		}
	else
		{
			cout << "Existence Error: " << searchRelationship  << " not found!" << endl;
		}
}


int main()
{
	//string property;
	//property = "human";
	/*set<string> identifier;
	
	identifier.emplace("annie");
	identifier.emplace("gregg");
	identifier.emplace("bozo");

	singleFact.emplace(property, identifier);*/
/*
	setSingleFact("animal", "dog");
	setSingleFact("animal", "cat");		
	setSingleFact("human", "annie");
	setSingleFact("human", "gregg");
	setSingleFact("bird", "eagle");*/
/*
	setRelateFact("likes", "annie", "homework");*/
	setRelateFact("likes","annie", "chocolate");
	setRelateFact("likes", "dinah", "moose");
	setRelateFact("likes", "annie", "gregg");

	setRelateFact("wrote", "maryShelley", "frankenstein");

	//setInverseRelateFact("likes", "annie", "gregg");
/*
	string searchFact = "human";

	findFact(searchFact);
	findFact("bird");*/

	string searchRelationship = "likes";
	string relator = "annie";

	findRelationship(searchRelationship,relator);

	cout << "singleFact size: " << singleFact.size() << endl;
	cout << "relationFact size: " << relationFact.size() << endl;
	cout << "inverseRelationFact size: " << inverseRelationFact.size() << endl;

	//cout << "relFacts size: " << relFacts.size() << endl;
	cout << "invRelFacts size: " << invRelFacts.size() << endl;

  for(map<string, map<string, set<string> > >::iterator ii = relationFact.begin(); ii != relationFact.end(); ii++) {
    cout << ii->first << endl;
    for(map<string, set<string> >::iterator jj = ii->second.begin(); jj != ii->second.end(); jj++) {
      cout << "    " << jj->first << endl;
      for(set<string>::iterator kk = jj->second.begin(); kk != jj->second.end(); kk++) {
        cout << "        " << *kk << endl;
      }
    }
  }

  cout << endl;
  for(map<string, map<string, set<string> > >::iterator ii = inverseRelationFact.begin(); ii != inverseRelationFact.end(); ii++) {
    cout << ii->first << endl;
    for(map<string, set<string> >::iterator jj = ii->second.begin(); jj != ii->second.end(); jj++) {
      cout << "    " << jj->first << endl;
      for(set<string>::iterator kk = jj->second.begin(); kk != jj->second.end(); kk++) {
        cout << "        " << *kk << endl;
      }
    }
  }



	return 0;
}