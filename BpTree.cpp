#include "BpTree.h"
#include "Node.h"
#include <string>
#include <vector>
#include <iostream>


BpTree::BpTree(int n) {
	nodesize = n;
	treesize = 1;
	root = NULL;
}

BpTree::BpTree(BpTree & copy) {
	return;
}

BpTree::~BpTree() {
	if (root == NULL) {
		return;
	}
	root->deletion();
	delete root;
}

void BpTree::printValues() {
	if (root == NULL) {
		printf("The tree is empty.\n");
		return;
	}
	root->printValues();
}

void BpTree::printKeys() {
	if (root == NULL) {
		printf("The tree is empty.\n");
		return;
	}
	root->printKeys();
	printf("\n");
}


bool BpTree::insert(int key, std::string val) {

	if (root == NULL) {
		root = new Node(nodesize);
	}

	Node* is_new_root = NULL;
	is_new_root = root->insert(root, key, val);

	if (is_new_root) {
		root = is_new_root;
	}
}

bool BpTree::remove(int key) {
	printf("Please note that remove is not implemented for 2 cases: coalescing right for interior nodes, and coalescing left for interior nodes. all four cases should work for leaf nodes, and redistribution for interior nodes.\n");
	if (root == NULL) {
		printf("Nothing to remove because tree is empty.\n");
		return false;
	}

	Node* is_new_root = NULL;
	is_new_root = root->remove(key);

	if (is_new_root) {
		root = is_new_root;
	}
	return true;
}


std::string BpTree::find(int key) {
	if(root == NULL) {
		printf("Find returned nothing because the tree is empty.\n");
		return "";
	}
	std::string find_key_string = root->find(key);
	if (find_key_string == "") {
		return "";
	}
	return find_key_string;
}