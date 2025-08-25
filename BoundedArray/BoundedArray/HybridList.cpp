/*Jackson Oravetz; Ahmed, Kishwar. file containing hybrid list methods. Refer to header file for method use*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "HybridList.h"
using namespace std;

HybridList::HybridList() {}		

HybridList::HybridList(int blockSize) {	
	if (blockSize <= 0)
		throw out_of_range("Invalid block size " + to_string(blockSize));
	this->blockSize = blockSize;
}

HybridList::HybridList(const HybridList& h) {	
	operator=(h);
}

HybridList::~HybridList() {
	clear();
}

int HybridList::size() const {
	return numElements;
}

int HybridList::capacity() const {
	return numBlocks * blockSize;
}

int HybridList::block_size() const {
	return blockSize;
}

HybridListNode* HybridList::front() const {
	return head;
}

HybridListNode* HybridList::back() const {
	return tail;
}

double& HybridList::at(int index) const {
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index < elementsSearched + curNode->size()) {
			// Element is in this block so just return the correct element from
			// this block
			return curNode->at(index - elementsSearched);
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
	}

	// Iterator went beyond last block so something went horribly wrong
	abort();
}

HybridList& HybridList::operator=(const HybridList& h) {
	HybridListNode* curNode = h.front();	//create tracking node that starts at front of copied list
	clear();
	if (numBlocks == 0) {	//Hybrid list is empty so creating a new node that will be both the head 
							//and tail and append the element to it
		HybridListNode* newTail = new HybridListNode(blockSize);
		tail = newTail;
		head = newTail;
		numBlocks = 1;
	}
	HybridListNode* newNode = head;	//tracking node of the head of new list
	while (curNode != nullptr) {	//loop for every node
		for (int i = 0; i < curNode->size(); i++) {	//loop for every element in curNode
			newNode->push_back(curNode->at(i));	//push each element of curNode into newNode 
			numElements++;	//inc numElements for new hybrid list
		}
		curNode = curNode->next;	//go to next node in copied list
		if (curNode != nullptr) {	//create new node and set links for new hybrid list
			HybridListNode* newestNode = new HybridListNode(blockSize);
			newestNode->next = newNode->next;
			newNode->next = newestNode;
			tail = newestNode;
			newNode = newNode->next;
			numBlocks++;
		}
		
	}

	return *this;	//return the new hybrid list
}

void HybridList::push_back(double value) {
	if (numBlocks == 0) {
		// Hybrid list is empty so creating a new node that will be both the head
		// and tail and append the element to it
		HybridListNode* newTail = new HybridListNode(blockSize);
		newTail->push_back(value);
		tail = newTail;
		head = newTail;
		numBlocks = 1;
	}
	else if (tail->size() == blockSize) {
		// Tail node is full so create a new tail node and copy the back half of
		// the old tail node to the new tail node
		HybridListNode* newTail = new HybridListNode(blockSize);

		// Copy just under half of elements from old tail to new tail
		for (int i = blockSize / 2 + 1; i < blockSize; i++)
			newTail->push_back(tail->at(i));
		tail->resize(blockSize / 2 + 1);
		//cout << tail->size() << endl;
		// Append new item to new tail
		newTail->push_back(value);
		tail->next = newTail;
		//cout << newTail->size() << endl;
		//cout << "Tail: " << tail << endl;
		//cout << "New tail: " << newTail << endl;
		tail = newTail;
		numBlocks++;
	}
	else
		tail->push_back(value);	// Tail isn't full so just append to tail

	numElements++;
}

void HybridList::pop_back() {
	HybridListNode* curNode = head;
	int elementsSearched = 0;
	if (numElements == 0)	//if there are no elements throw exception
		throw std::out_of_range("Array has no elements");
	numElements--;
	tail->pop_back();
	if (tail->size() == 0) {	//if pop_back made node empty
		while (curNode->next != tail) {	//get the node befoe curNode for delete
			curNode = curNode->next;
		}
		delete tail;	//delete the tail and fix links/numBlocks
		tail = curNode;
		curNode = tail;
		tail->next = nullptr;
		numBlocks--;
	}
}

void HybridList::insert(int index, double value) {
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)	//if index is negative or too large, throw exception
		throw out_of_range("Invalid index " + to_string(index));

	 if (numBlocks == 0) {	//in list is empty, create new node and set to head and tail. Insert new value
		 HybridListNode* newTail = new HybridListNode(blockSize);
		 newTail->push_back(value);
		 tail = newTail;
		 head = newTail;
		 numBlocks = 1;
	}

	 else {
		 while (curNode != nullptr) {	//loop for each node
			 if (index < elementsSearched + curNode->size()) {	//found node containing index
				 if (curNode->size() == blockSize) {	//if node is full
					 HybridListNode* newNode = new HybridListNode(blockSize);	//create new node
					 for (int i = blockSize / 2; i < blockSize; i++)	//move half of full node to previous node
						 newNode->push_back(curNode->at(i));
					 curNode->resize(blockSize / 2);	//change numElemnts of previously full node
					 newNode->next = curNode->next;	//fix links for the newnode
					 curNode->next = newNode;
					 if (curNode == tail)	//if newNode is the tail, account for it
						 tail = newNode;
					 numBlocks++;
					 curNode->insert(index - elementsSearched, value);	//insert new value at requested index
					 numElements++;
					 return;
				 }
				 else {
					 curNode->insert(index - elementsSearched, value);	//insert new value
					 numElements++;
					 return;
				 }
			 }
			 elementsSearched += curNode->size();	//track elements search for finding indexes.
			 curNode = curNode->next;	//go to next node
		 }
	 }
	
}

void HybridList::erase(int index) {
	HybridListNode* curNode = head;
	HybridListNode* nextNode = nullptr;
	int elementsSearched = 0;
	if (index >= numElements || index < 0) //if index is negative or too large, throw exception
		throw std::out_of_range("Invalid index " + std::to_string(index));
	
	while (curNode != nullptr) {	//loop for each node
		if (index < elementsSearched + curNode->size()) {	//found node containing index
			curNode->erase(index - elementsSearched);	//erase at index
			numElements--;
			if (numElements == 0) {	//if erase made node empty, delete the node and fix links
				nextNode = curNode->next;
				delete curNode;
				curNode = nextNode;
			}
			return;
		}
		elementsSearched += curNode->size();	//track to find index
		curNode = curNode->next;	//go to next node
	}
	
}

void HybridList::clear() {
	HybridListNode* curNode = head, * nextNode = nullptr;
	// Iterate through each node starting from the head and delete it
	while (curNode != nullptr) {
		nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
	head = tail = nullptr;
	numElements = numBlocks = 0;
}





