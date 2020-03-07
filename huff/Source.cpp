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

	void Print(int i);
	
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
	l = NULL;
	r = NULL;
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
		chars[other1->charnum + i] = other2->chars[i];
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

void Node::Print(int i) {
	cout << "Node " << i << endl;
	cout << "w = " << weight << " charnum = " << charnum << endl; 
	for (int i = 0; i < charnum; i++) {
		cout << (char) chars[i] << " ";
	}
	cout << endl;
	if (l != NULL) {
		l->Print(i + 1);
	}
	else {
		cout << "no l\n";
	}
	if (r != NULL) {
		r->Print(i + 1);
	}
	else {
		cout << "no r\n";
	}
}


struct CompareNodes {
    bool operator()(Node *p1, Node *p2) {
        return p1->weight > p2->weight;
    }
};

void encode(ifstream &f1, ofstream &f2) {
	int frq[256];
	for (int i = 0; i < 256; i++) {
		frq[i] = 0;
	}
	
	char inp;
	while (f1 >> inp) {
		frq[inp] += 1;
	}
	f1.close();

	
	vector<Node> v;
	for (int i = 0; i < 256; i++) {
		if (frq[i]) {
			Node n((char) i, frq[i]);
			v.push_back(n);
		}
	}
	
	cout << "number of leafs: " << v.size() << endl;
	
	priority_queue<Node*, vector<Node*>, CompareNodes> q;
	for (int i = 0; i < v.size(); i++) {
		q.push(&v[i]);
	}
	
	Node *head, *head2;
	head = NULL;
	while(!q.empty()) {
		head = q.top();
		q.pop();
		if (q.empty()) {
			break;
		}
		head2 = q.top();
		q.pop();
	
		Node n(head, head2);
		v.push_back(n);
		q.push(&v[v.size() - 1]);
	}

	head->Print(0);
}


int main() {
	//todo: take the filenames from the console
	/*
	ifstream f1("input.txt");
	if (!f1) {
		cerr << "File not found\n";
		exit(1);
	}
	ofstream f2("output.txt");
	
	encode(f1, f2);
	*/
	Node na('a', 10), nb('b', 8), nc('c', 5), nd('d', 2);
	Node n1(&nd, &nc);
	Node n2(&n1, &nb);
	Node n3(&na, &n2);
	n3.Print(0);
	return 0;
}
