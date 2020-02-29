#ifndef BPTREE_H
#define BPTREE_H

#include "Node.h"
#include <string>

class BpTree{

public:
	BpTree(int n);

	BpTree(BpTree & copy);

	~BpTree();

	bool insert(int n, std::string val);

	bool remove(int key);

	std::string find(int n);

	void printKeys();

	void printValues();

private:

	int treesize;
	int nodesize;
	Node* root;
};

#endif