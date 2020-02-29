# BPlusTree
An implementation of a B+ Tree in C++ to simulate a database system index. This tree is in-memory and behaves like a traditional map by storing key/value pairs.

## Tree specifications
1. Keys are integers
2. Values are strings 
3. Duplicate keys should not be inserted

## B+ Tree Interface
The following methods are implemented:
1. **BpTree(int)** – this constructor creates an empty tree; the parameter sets the number of keys
that can be stored in each node (leaf and interior)
2. **bool insert(int, string)** – inserts the key (int) and value (string) into the tree unless the key is
in the tree; returns true if the insertion was successful and false otherwise
3. **bool remove(int)** – searches the tree for the key (int); if found removes the key and associated
value from the tree; returns true if the key was found and removed and false otherwise
4. **string find(int)** – searches the tree for the key (int); if found returns the matching value
(string), otherwise returns the empty string
5. **void printKeys()** – prints the keys in each node with nodes of the same level appearing on the
same line
6. **void printValues()** – prints the values in key (not value) order

## Implementation Details
### Node Structure
The structure of a node consists of n keys (where n is the value of the parameter passed to the tree's constructor) and n+1 pointers. Leaf nodes' pointers should point to values, except for one pointer which should point to the next leaf' Interior nodes' pointers should point to other nodes. A pointer in each node points to the node's parent. Each node also contains a pointer to its left and right sibling.

### Insertion
Insertion may cause a node to split. If an odd number of values (keys or pointers) are to be
distributed between the two nodes, then the original – left hand – node should contain one more
value than the new – right hand – node.

### Removal
When removing a key from a node it may be necessary to redistribute values from sibling nodes
or coalesce the node and a sibling. This priority ranking determines how to proceed where
choices exist.
1. Redistribute values from the left sibling
2. Redistribute values from the right sibling
3. Coalesce with the left sibling
4. Coalesce with the right sibling

### Print Keys
Print the tree's keys to show the structure of the tree. Each level should be printed on one line,
and nodes should be distinguished from each other. An example tree could look like this:
```
[17]
[10] [27,87]
[2,5] [10,13,15] [17,22] [27,35] [87,91]
```
### Print Values
Print the tree's values (the strings) in the order in which they are referred to by the keys. This can
be implemented by traversing the entire leaf level. Print one value per line.
