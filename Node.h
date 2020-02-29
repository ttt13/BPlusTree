#include <vector>
#include <string>
#ifndef NODE_H
#define NODE_H

class Node {
public:

	Node(int n);

	~Node();

	void deletion();

	int size();

	void printValues();

	void printKeys();

	void setAsLeaf();

	bool checkIfLeaf();

	void setAsInterior();

	Node* insert(Node* root, int key, std::string val);

	Node* remove(int key);

	std::string find(int key);

	Node* split();

	void redistributeLeft(int old_key);

	void redistributeRight();

	void coalesceLeft(int old_key);

	void coalesceRight(int old_key);

private:
	bool is_leaf;
	int size_node;
	Node* right_sibling;
	Node* left_sibling;
	Node* rightmost_pointer;
	Node* parent;
	Node* next;
	std::vector <std::pair <int, Node*>> key_value; 
	std::vector <std::pair <int, std::string>> key_value2;
};

#endif