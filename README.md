# BPlusTree
An implementation of a B+ Tree in C++ to simulate a database system index. This tree is in-memory and behaves like a traditional map by storing key/value pairs.

## Tree specifications
1. Keys are integers
2. Values are strings 
3. Duplicate keys should not be inserted

## B+ Tree Interface
The following methods are implemented:
1. BpTree(int) – this constructor creates an empty tree; the parameter sets the number of keys
that can be stored in each node (leaf and interior)
2. bool insert(int, string) – inserts the key (int) and value (string) into the tree unless the key is
in the tree; returns true if the insertion was successful and false otherwise
3. bool remove(int) – searches the tree for the key (int); if found removes the key and associated
value from the tree; returns true if the key was found and removed and false otherwise
4. string find(int) – searches the tree for the key (int); if found returns the matching value
(string), otherwise returns the empty string
5. void printKeys() – prints the keys in each node with nodes of the same level appearing on the
same line
6. void printValues() – prints the values in key (not value) order
