#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <queue>
using namespace std;

class Node {
	public:
	Node *l, *r;
	int weight;
	int charnum;
	char* chars;

	Node(char k, int w);
	Node(const Node &other);
	Node(Node *other1, Node *other2);
	~Node();

	
	Node& operator =(const Node& other);
	

};


Node::Node(char k, int w) {
	try {
		chars = (char*) new char[1];
	}
	catch(const bad_alloc &e) {
		cerr << "alloc error\n";
		exit(1);
	}
	weight = w;
	charnum = 1;
	chars[0] = k;
	l = r = NULL;
}


Node::Node(const Node &other) {
	try {
		chars = (char*) new char[other.charnum];
	}
	catch(const bad_alloc &e) {
		cerr << "alloc error\n";
		exit(1);
	}
	
	weight = other.weight;
	
	charnum = other.charnum;
	for (int i; i < charnum; i++) {
		chars[i] = other.chars[i];
	}
	
	l = other.l;
	r = other.r;
}


Node::Node(Node *other1, Node *other2) {
	charnum = other1->charnum + other2->charnum;
	try {
		chars = (char*) new char[charnum];
	}
	catch(const bad_alloc &e) {
		cerr << "alloc error\n";
		exit(1);
	}
	
	for (int i = 0; i < other1->charnum; i++) {
		chars[i] = other1->chars[i];
	}
	for (int i = 0; i < other2->charnum; i++) {
		chars[other1->charnum + i] = other1->chars[i];
	}
	
	weight = other1->weight + other2->weight;
	l = other1;
	r = other2;
}


Node::~Node() {
	if (chars) {
		delete[] chars;
	}
}


Node& Node::operator =(const Node &other) {
	if (this == &other) {
		return *this;
	}
	if (chars) {
		delete[] chars;
	}
	
	try {
		chars = (char*) new char[other.charnum];
	}
	catch(const bad_alloc &e) {
		cerr << "alloc error\n";
		exit(1);
	}
	weight = other.weight;
	charnum = other.charnum;
	for (int i; i < charnum; i++) {
		chars[i] = other.chars[i];
	}
	
	l = other.l;
	r = other.r;

	return *this;
}


int main() {
	//todo: take the filename from the console
	int frq[256];
	for (int i = 0; i < 256; i++) {
		frq[i] = 0;
	}
	ifstream f("input.txt");
	if (!f) {
		cerr << "File not found\n";
		exit(1);
	}
	char inp;
	while (f >> inp) {
		frq[inp] += 1;
	}
	f.close();

	return 0;
}
