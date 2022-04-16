#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

struct AdjacencyList {
	struct Person {
		Person() {
			name = "";
			company = "";
			sameName = nullptr;
			id = 0;
		}
		Person(string n, string c) {
			name = n;
			company = c;
			sameName = nullptr;
			id = 0;
		}
		Person operator=(const Person& d) {
			name = d.name;
			company = d.company;
			sameName = d.sameName;
			id = d.id;
			return *this;
		}
		bool operator==(const Person& d) {
			return ((d.name == name) && (d.company == company) && (d.adjNodes == adjNodes) && (d.id == id));
		}
		void setID(unsigned int i) {
			id = i;
		}
		unsigned int getID() {
			return id;
		}
		Person* getSameName() {
			return sameName;
		}
		void chainNames(Person* p) {
			if (sameName == nullptr) {
				sameName = p;
			}
			else {
				chainNames(sameName);
			}
		}
		void addAdj(Person* n) {
			adjNodes.push_back(n);
		}
		vector<Person*> getAdj() {
			return adjNodes;
		}
		string name;
		string company;
		unsigned int id;
		vector<Person*> adjNodes;
		Person* sameName;
	};
	AdjacencyList() {
		root = nullptr;
		size = 0;
	}
	Person* newPerson(string name, string company, bool namePresent) {
		Person* p = new Person(name, company);
		p->setID(size + 1);
//		bool namePresent = false;
		if (namePresent) {
			nodes[name]->chainNames(p);
			size++;
		}
		else {
			if (root == nullptr) {
				root = p;
			}
			nodes.emplace(name, p);
			size++;
		}
		return p;
	}
	void addEdge(string srcName, string srcComp, string destName, string destComp) {
		Person* tempSrc;
		Person* tempDest;
		if (nodes.find(srcName) == nodes.end()) {
			tempSrc = newPerson(srcName, srcComp, false);
		}
		else {
			if (nodes[srcName]->company != srcComp) {
				tempSrc = newPerson(srcName, srcComp, true);
			}
			else {
				tempSrc = nodes[srcName];
				while (tempSrc->company != srcComp) {
					tempSrc = tempSrc->sameName;
				}
			}
		}
		if (nodes.find(destName) == nodes.end()) {
			tempDest = newPerson(destName, destComp, false);
		}
		else {
			if (nodes[destName]->company != srcComp) {
				tempDest = newPerson(destName, destComp, true);
			}
			else {
				tempDest = nodes[destName];
				while (tempDest->company != destComp) {
					tempDest = tempDest->sameName;
				}
			}
		}
		tempSrc->addAdj(tempDest);
	}
	Person* getPerson(string name, unsigned int id_) {
		Person* temp = nodes[name];
		if (!temp) {
			return nullptr;
		}
		if (temp->id == id_) {
			return temp;
		}
		else {
			while (temp->id != id_ && temp != nullptr) {
				temp = temp->sameName;
			}
			return temp;
		}
	}
	//add algorithms here for djik and bfs

private:
	Person* root;
	//size represents total number of PEOPLE stored, not necessarily unique names
	//can find the number of unique names by size - nodes.size
	int size;
	map<string, Person*> nodes;
};

