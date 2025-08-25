// hybridList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HybridList.h"
using namespace std;

void printHybridList(const HybridList& h) {
	for (int i = 0; i < h.size(); i++)
		cout << h.at(i) << " ";
	cout << endl;
}

void printBoundedArray(const BoundedArray& h) {
	for (int i = 0; i < h.size(); i++)
		cout << h.at(i) << " ";
	cout << endl;
}

int main()
{
	cout << "Testing push_back() function" << endl;
	HybridList a;
	a.push_back(5);
	printHybridList(a);
	cout << a.size() << endl;
	cout << a.capacity() << endl;
	a.push_back(10);
	printHybridList(a);
	cout << a.size() << endl;
	cout << a.capacity() << endl;
	for (int i = 0; i < 15; i++) {
		a.push_back(i);
		printHybridList(a);
		HybridListNode* aFront = a.front();
		cout << "Front: " << aFront << endl;
		printBoundedArray(*aFront);
		if (aFront->next != nullptr) {
			cout << "Node 2: " << aFront->next << endl;
			printBoundedArray(*(aFront->next));
		}
	}
	printHybridList(a);
	cout << a.size() << endl;
	cout << a.capacity() << endl;

	HybridListNode* aFront = a.front(), * aBack = a.back();
	printBoundedArray(*aFront);
	printBoundedArray(*(aFront->next));
	printBoundedArray(*(aFront->next->next));

	cout << endl << "Testing at() function" << endl;
	cout << a.at(0) << endl;
	cout << a.at(6) << endl;
	cout << a.at(12) << endl;
	a.at(14) = 0;
	cout << a.at(14) << endl;
	printHybridList(a);
	cout << a.size() << endl;
	cout << a.capacity() << endl;

	cout << endl << "Testing pop_back() function" << endl;
	for (int i = 0; i < 5; i++) {
		a.pop_back();
		printHybridList(a);
		cout << a.size() << endl;
		cout << a.capacity() << endl;
	}
	cout << "Front: " << aFront << endl;
	cout << "Node 2: " << aFront->next << endl;
	cout << "Node 3: " << aFront->next->next << endl;
	cout << (aFront->next->next == nullptr) << endl;
	a.pop_back();
	printHybridList(a);
	printBoundedArray(*aFront);
	printBoundedArray(*(aFront->next));
	cout << a.size() << endl;
	cout << a.capacity() << endl;

	cout << endl << "Testing insert() function" << endl;
	for (int i = 0; i < 6; i++) {
		a.insert(6, -1);
		printHybridList(a);
		aFront = a.front();
		aBack = a.back();
		printBoundedArray(*aFront);
		printBoundedArray(*(aFront->next));
		printBoundedArray(*(aBack));
		cout << a.size() << endl;
		cout << a.capacity() << endl;
	}
	printBoundedArray(*(aFront->next->next));
	// The following line should cause result in an index out of bounds error
	//a.insert(a.size(), 10);
	//printHybridList(a);

	cout << endl << "Testing erase() function" << endl;
	for (int i = 0; i < 4; i++) {
		a.erase(13);
		printHybridList(a);
		aFront = a.front();
		aBack = a.back();
		printBoundedArray(*aFront);
		printBoundedArray(*(aFront->next));
		printBoundedArray(*(aBack));
		cout << a.size() << endl;
		cout << a.capacity() << endl;
	}

	cout << endl << "Testing copy constructor" << endl;
	a.insert(1, 6);
	cout << aFront << endl << aBack << endl;
	printHybridList(a);
	printBoundedArray(*aFront);
	printBoundedArray(*(aFront->next));
	printBoundedArray(*(aBack));
	cout << a.size() << endl;
	cout << a.capacity() << endl;
	HybridList b(a);
	HybridListNode* bFront = b.front(), * bBack = b.back();
	printHybridList(b);
	cout << bFront << endl << bBack << endl;
	printBoundedArray(*bFront);
	printBoundedArray(*(bFront->next));
	printBoundedArray(*(bBack));
	cout << b.size() << endl;
	cout << b.capacity() << endl;
	
	cout << endl << "Testing = operator" << endl;
	HybridList c;
	c.push_back(4);
	c.push_back(6);
	HybridListNode* cFront = c.front();
	printHybridList(c);
	cout << c.size() << endl;
	cout << c.capacity() << endl;
	cout << cFront << endl;
	c = a;
	printHybridList(c);
	cout << c.size() << endl;
	cout << c.capacity() << endl;
	cout << c.front() << endl;
	c.push_back(-2);
	printHybridList(c);
	printHybridList(a);

	cout << endl << "Testing push_back() on empty list and erase() on singleton list"
		<< endl;
	a.clear();
	printHybridList(a);
	aFront = a.front();
	aBack = a.back();
	cout << (aFront == nullptr) << endl;
	cout << (aBack == nullptr) << endl;
	cout << a.size() << endl;
	cout << a.capacity() << endl;
	a.push_back(3);
	cout << a.size() << endl;
	cout << a.capacity() << endl;
	aFront = a.front();
	printHybridList(a);
	cout << aFront << endl;
	printBoundedArray(*aFront);
	//a.pop_back();
	a.erase(0);
	printHybridList(a);
	aFront = a.front();
	cout << aFront << endl;
	cout << a.size() << endl;
	cout << a.capacity() << endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file