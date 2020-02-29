#include "Node.h"
#include "BpTree.h"
#include <string>
#include <vector>
#include <iostream>
#include <cmath>


Node::Node(int n) {
	size_node = n;
	left_sibling = NULL;
	right_sibling = NULL;
	next = NULL;
	parent = NULL;
	is_leaf = true;
}

Node::~Node() {
	return;
}

void Node::deletion() {
	if (is_leaf) {
		return;
	}
}

void Node::printValues() {
	Node* traverse;

	if (is_leaf) {
		for(unsigned int i = 0; i < key_value2.size(); i++) {
			printf("%s\n", key_value2[i].second.c_str());
		}
		if (next == NULL) {
			return;
		}
		else{
			next->printValues();
		}
	}

	if (!is_leaf) {
		if (key_value[0].second) {
			key_value[0].second->printValues();
		}
	}
}

void Node::printKeys() {

	if (is_leaf) {
		printf("[");
		if (key_value2.size() > 0) {
			printf("%d", key_value2[0].first);
			for (unsigned int i = 1; i < key_value2.size(); i++) {
				printf(", %d", key_value2[i].first);
			}
		}
		printf("] ");

		if (next != NULL) {
			next->printKeys();
		}
	}

	if (!is_leaf) {
		printf("[");
		if (key_value.size() > 0) {
			printf("%d", key_value[0].first);
			for (unsigned int i = 1; i < key_value.size(); i++) {
				printf(", %d", key_value[i].first);
			}
		}
		printf("] ");

		if (right_sibling) {
			right_sibling->printKeys();
		}

		if (left_sibling == NULL) {
			printf("\n");
			key_value[0].second->printKeys();
		}
	}
}

int Node::size() {
	return size_node;
}

bool Node::checkIfLeaf() {
	return is_leaf;
}

void Node::setAsLeaf() {
	is_leaf = true;
}

void Node::setAsInterior() {
	is_leaf = false;
}

Node* Node::insert(Node* root, int key, std::string val) {
	Node* return_node = NULL;

	std::pair<int, std::string> insert_key_value (key, val);
	// Case where tree is empty
	if (root == NULL) {

		root = new Node(size_node);
		return_node = root;
	}

	// Find the place to insert it
	if (is_leaf) {
		if (key_value2.size() == 0) {
			key_value2.push_back(insert_key_value);
			return return_node;
		}

		auto find_the_place = key_value2.begin();
		while (key > find_the_place->first && find_the_place != key_value2.end()) {
			find_the_place++;
		}

		if (key == find_the_place->first) {
			return return_node;
		}
		else {
			key_value2.insert(find_the_place, insert_key_value);

			// Now check the nodesize. May need to split.
			if (size_node < key_value2.size()) {
				Node* did_root_split = split();
				if (did_root_split) {
					return_node = did_root_split;
				}
			}
			return return_node;
		}

	}

	if (!is_leaf) {
		if (key < key_value[0].first) {
			return key_value[0].second->insert(root, key, val);
		}
		else if (key > key_value[key_value.size()-1].first) {
			return rightmost_pointer->insert(root, key, val);
		}
		else {
			auto iterator = key_value.begin();
			while (iterator->first <= key && iterator != key_value.end()) {
				iterator++;
			}
			return iterator->second->insert(root, key, val);
		}
	}
}

std::string Node::find(int key) {

	if (is_leaf) {
		std::pair<int, std::string> v_pair;
		Node* traverse = this;
		while (traverse != NULL){
			for (unsigned int i = 0; i < traverse->key_value2.size(); i++) {
				v_pair = traverse->key_value2[i];
				if (v_pair.first == key) {
					return v_pair.second;
				}
			}
			traverse = traverse->next;
		}
		return "";
	}

	if (!is_leaf) {
		if (key < key_value[0].first) {
			return key_value[0].second->find(key);
		}
		else if (key >= key_value[key_value.size()-1].first) {
			return rightmost_pointer->find(key);
		}
		else {
			auto iterator = key_value.begin();
			while (iterator->first < key && iterator != key_value.end()) {
				iterator++;
			}
			return iterator->second->find(key);
		}
	}


	return NULL;
}

Node* Node::split() {
	Node* return_node = NULL;

	if (is_leaf)
	{
		Node* new_node = new Node(size_node);
		int total_vals = key_value2.size();
		int first_half = ceil(total_vals/2);
		int second_half = floor(total_vals/2);
	
		std::pair<int, std::string> get_pair;
		for (int i = 0; i < second_half; i++) {
			get_pair = key_value2.back();
			key_value2.pop_back();
	
			if (new_node->key_value2.size() == 0) {
				new_node->key_value2.push_back(get_pair);
			}
			else{
				auto find_the_place = new_node->key_value2.begin();
				while (get_pair.first > find_the_place->first && find_the_place != new_node->key_value2.end()) {
					find_the_place++;
				}
	
				new_node->key_value2.insert(find_the_place, get_pair);
			}
		}
	
		// Link the nodes.
		Node* temp = next;
	
		if (next != NULL){
			new_node->next = temp;
		}	
		next = new_node;
		new_node->left_sibling = this;
		if (right_sibling != NULL) {
			new_node->right_sibling = right_sibling;
		}
		right_sibling = new_node;
	
		if (parent == NULL) {
			parent = new Node(size_node);
			parent->setAsInterior();
			int key_original = key_value2[0].first;
			int key_new_node = new_node->key_value2[0].first;
			Node* this_node = this;
			Node* that_node = new_node;
			std::pair<int, Node*> insert_key_pointer(key_new_node, this_node);
			parent->key_value.insert(key_value.begin(), insert_key_pointer);
			parent->rightmost_pointer = new_node;
	
			// Update parents.
			new_node->parent = parent;
			return_node = parent;
		}
		else {
			new_node->parent = parent;
			int key_node = new_node->key_value2[0].first;
			std::pair<int, Node*> original_key_p(key_node, this);
			std::pair<int, Node*> get_back = parent->key_value.back();
			if (get_back.first < key_node) {
				parent->key_value.push_back(original_key_p);
				parent->rightmost_pointer = new_node;
				// Case where new node is at the end. New node becomes extra
				// Original gets key of new node
				if (parent->key_value.size() > size_node) {
					 return parent->split();
				}
			}
			else{
				auto find_place = parent->key_value.begin();
				while (original_key_p.first > find_place->first && find_place != parent->key_value.end()) {
					//printf("find place interation: %d\n", find_place->first);
					find_place++;
				}
				find_place->second = new_node;
				parent->key_value.insert(find_place, original_key_p);
	
				if (parent->key_value.size() > size_node) {
					 return parent->split();

				}
			}
		}
	}


	if (!is_leaf) {
		Node* new_interior = new Node(size_node);
		new_interior->setAsInterior();

		int shalf_keys = floor(size_node/2);
		int shalf_pointers = floor( (size_node+2) /2);
		int fhalf_keys = ceil(size_node/2);
		int fhalf_pointers = ceil( (size_node+2) /2);

		if (shalf_pointers > 0) {
			new_interior->rightmost_pointer = rightmost_pointer;
			rightmost_pointer->parent = new_interior;
		}

		std::pair<int, Node*> key_node;
		for (int i = 0; i < shalf_keys; i++) {
			key_node = key_value.back();
			key_value.pop_back();

			if (new_interior->key_value.size() == 0) {
				new_interior->key_value.push_back(key_node);
			}
			else{
				auto find_place = new_interior->key_value.begin();
				while (key_node.first > find_place->first && find_place != new_interior->key_value.end()) {
					find_place++;
				}

				new_interior->key_value.insert(find_place, key_node);
			}
			key_node.second->parent = new_interior;	
		}
		key_node = key_value.back();
		key_value.pop_back();
		rightmost_pointer = key_node.second;
		int key_to_parent = key_node.first;
		new_interior->left_sibling = this;
		if (right_sibling){
			new_interior->right_sibling = right_sibling;
		}
		right_sibling = new_interior;

		if (parent == NULL) {
			parent = new Node(size_node);
			parent->setAsInterior();
			parent->rightmost_pointer = new_interior;
			key_node.second = this;
			parent->key_value.push_back(key_node);

			return_node = parent;
			new_interior->parent = parent;
		}
		else {
			new_interior->parent = parent;
			

			std::pair<int, Node*> original_key_p2(key_to_parent, this);
			std::pair<int, Node*> back_parent = parent->key_value.back();
			if (back_parent.first < key_to_parent) {
				parent->key_value.push_back(original_key_p2);
				parent->rightmost_pointer = new_interior;
			}
			else{

				auto find_p = parent->key_value.begin();
				while (original_key_p2.first > find_p->first && find_p != parent->key_value.end()) {
					find_p++;
				}
				parent->key_value.insert(find_p, original_key_p2);
				find_p++;
				find_p->second = new_interior;

				if (parent->key_value.size() > size_node) {
					parent->split();
				}
			}
		}
		return return_node;
	}
	return return_node;
}


Node* Node::remove(int key) {

	if (is_leaf) {
		auto iterator = key_value2.begin();
		int old_key;
		while (iterator != key_value2.end()) {
			if (key == iterator->first) {
				old_key = key_value2[0].first;
				key_value2.erase(iterator);
				break;
			}
			iterator++;
		}
		if (key_value2.size() > size_node/2) {
			return NULL;
		}	
		int get_size;
		
		
		if (left_sibling != NULL && left_sibling->parent == this->parent) {
			get_size = left_sibling->key_value2.size();
			if (get_size - 1 > size_node/2) {
				redistributeLeft(old_key);
				return NULL;
			}
		}
		// Redistribute right sibling + same parent
		if (right_sibling != NULL && right_sibling->parent == this->parent) {
			get_size = right_sibling->key_value2.size();
			if (get_size - 1 > size_node/2) {
			}	
		}
		// Coalesce left sibling + same parent
		if (left_sibling != NULL && left_sibling->parent == this->parent) {
			coalesceLeft(old_key);
			return NULL; // for now
		}
		// Coalesce right sibling + same parent
		if (right_sibling != NULL && right_sibling->parent == this->parent) {
			coalesceRight(old_key);
			return NULL; // for now
		}


	}

	if (!is_leaf) {
		if (key < key_value[0].first) {
			return key_value[0].second->remove(key);
		}
		else if (key >= key_value[key_value.size()-1].first) {
			return rightmost_pointer->remove(key);
		}
		else {
			auto iterator = key_value.begin();
			while (iterator->first <= key && iterator != key_value.end()) {
				iterator++;
			}
			return iterator->second->remove(key);
		}
	}
}


void Node::redistributeLeft(int old_key) {
	if (is_leaf){
		std::pair<int, std::string> move_pair;
		move_pair = left_sibling->key_value2.back();
		left_sibling->key_value2.pop_back();
		int new_key = move_pair.first;
		key_value2.insert(key_value2.begin(), move_pair);

		for (unsigned int i = 0; i < parent->key_value.size(); i++) {
			if (parent->key_value[i].first == old_key) {
				parent->key_value[i].first = new_key;
				break;
			}
		}
	}

	if (!is_leaf) {
		std::pair<int, Node*> redistribute = left_sibling->key_value.back();
		int int_key_to_parent = redistribute.first; // to go to root
		Node* to_move_right = left_sibling->rightmost_pointer;

		auto iterator = parent->key_value.begin();
		while(iterator != parent->key_value.end() && iterator->second != left_sibling) {
			iterator++;
		}

		if (iterator->second == left_sibling) {
			std::pair<int, Node*> node_to_right(iterator->first, to_move_right);
			iterator->first = int_key_to_parent;
			left_sibling->rightmost_pointer = redistribute.second;
			left_sibling->key_value.pop_back();
			key_value.insert(key_value.begin(), node_to_right);
			iterator->second->parent = this;
		}
	}
}

void Node::redistributeRight() {

	if (is_leaf){
		std::pair<int, std::string> move_pair;
		move_pair = right_sibling->key_value2.front();
		int old_key_right = move_pair.first;

		key_value2.push_back(move_pair);
		right_sibling->key_value2.erase(right_sibling->key_value2.begin());
		int new_key_right = right_sibling->key_value2[0].first;

		for (unsigned int i = 0; i < right_sibling->parent->key_value.size(); i++) {
			if (right_sibling->parent->key_value[i].first == old_key_right) {
				right_sibling->parent->key_value[i].first = new_key_right;
				break;
			}
		}
	}

	if (!is_leaf) {
		std::pair<int, Node*> front_right;
		front_right = right_sibling->key_value.front();
		int front_right_key = front_right.first;

		auto iterator = parent->key_value.begin();
		while (iterator != parent->key_value.end() && iterator->second != this) {
			iterator++;
		}

		if (iterator->second == this) {
			std::pair<int, Node*> redistribute_right (iterator->first, rightmost_pointer);
			iterator->first = front_right.first;
			rightmost_pointer = front_right.second;
			key_value.insert(key_value.end(), redistribute_right);
			right_sibling->key_value.erase(right_sibling->key_value.begin());
		}
	}
}

void Node::coalesceLeft(int old_key) {
	if (is_leaf){
		std::pair<int, std::string> move_pair;
		std::pair<int, Node*> int_node_pair;
		for (unsigned int i = 0; i < key_value2.size(); i++) {
			move_pair = key_value2[i];
			left_sibling->key_value2.push_back(move_pair);
		}

		left_sibling->right_sibling = right_sibling;
		if (old_key >= parent->key_value.end()->first) {
			int_node_pair = parent->key_value.back();
			rightmost_pointer = int_node_pair.second;
			parent->key_value.pop_back();

		}

		else{
			auto iterator = parent->key_value.begin();
			int test = 0;
			while (iterator != parent->key_value.end()) {
				if (iterator->second == this) {
					test = iterator->first;
					parent->key_value.erase(iterator);
					break;
				}
				iterator++;
			}

			for (unsigned int i = 0; i < parent->key_value.size(); i++) {
				if (parent->key_value[i].second == left_sibling) {
					parent->key_value[i].first = test;
				}
			}
		}
		
		int size_parent = parent->key_value.size();

		// Restructuring of interior nodes
		if ( (size_parent) < (size_node + 1)/2 ) {
			if (parent->left_sibling && parent->left_sibling->parent == parent->parent) {
				if (parent->left_sibling->key_value.size() + 1 > (size_node +1)/2) {
					int old_parent_key = parent->key_value[0].first; // Not sure if needed
					parent->redistributeLeft(old_parent_key); // PARAM IS PLACEHOLDER
					return;
				}
			}

			if (parent->right_sibling && parent->right_sibling->parent == parent->parent) {
				if (parent->right_sibling->key_value.size() + 1 > (size_node +1)/2) {
					
					parent->redistributeRight();
					return;
				}
			}

			if (parent->left_sibling && parent->left_sibling->parent == parent->parent) {
				
			}

			if (parent->right_sibling && parent->right_sibling->parent == parent->parent) {

			}
		}

		left_sibling->next = right_sibling;
	}

	if (!is_leaf) {

	}
}

void Node::coalesceRight(int old_key) {
	std::pair<int, std::string> move_pair;
	for (int i = key_value2.size()-1; i >= 0; i--) {
		move_pair = key_value2[i];
		right_sibling->key_value2.insert(right_sibling->key_value2.begin(), move_pair);
	}
	right_sibling->left_sibling = left_sibling;

	auto iterator = parent->key_value.begin();
	while (iterator != parent->key_value.end()) {
		if (iterator->second == this) {
			parent->key_value.erase(iterator);
			break;
		}
		iterator++;
	}

	int size_parent = parent->key_value.size();

	if ( (size_parent + 1) < (size_node + 1)/2 ) {
		
		if (parent->left_sibling && parent->left_sibling->parent == parent->parent) {
			if (parent->left_sibling->key_value.size() + 1 > (size_node +1)/2) {
				parent->redistributeLeft(old_key);
				return;
			}
		}
		
		if (parent->right_sibling && parent->right_sibling->parent == parent->parent) {
			if (parent->right_sibling->key_value.size() + 1 > (size_node +1)/2) {
				parent->redistributeRight();
				return;
			}
		}

		if (parent->left_sibling && parent->left_sibling == parent->parent) {
		}

		if (parent->right_sibling && parent->right_sibling == parent->parent) {
		}
	}
}