#include <iostream>
#include <fstream>
using namespace std;

int main() {
	//todo: take the filename the from console
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