/*
 Name: Nathan Hubbell
 Email: nchubbell@crimson.ua.edu
 Course Section: Fall 2024 CS 201
 Homework #: 2
 To Compile: g++ -std=c++20 hw2.cpp ST.hpp
 To Run: ./a input.txt
*/

#ifndef _ST_HPP_
#define _ST_HPP_

#include <utility>
#include <iostream>

#include "RBT.hpp"
#include "RBTPrint.hpp"

using namespace std;

template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
	typedef RBTNode<Key, Type>* iterator;

	// Constructors
	// constant
	ST() : nodeCount(0) { // sets default count of nodes to 0
	}; 

	// Destructor
	// linear in the size of the ST
	~ST(){
		clear(); // calls clear function
	};

	// access or insert specifies element
	// inserts if the key is not present and returns a reference to
	// the value corresponding to that key
	// O(LogN), N size of ST
	Type& operator[](const Key& key) {
		iterator node = find(key);
        if (node) { // ensure the node exists
            return node->value;  // return the value
        } else {
            insert(key, Type());  // insert the new value
            return find(key)->value;  // finds the new value and returns it
        }
	}; 

	// insert a (key, value) pair, if the key already exists
	// set the new value to the existing key
	// O(LogN), N size of ST
	void insert(const Key& key, const Type& value) {
		if (!find(key)) {  // insert if the key doesn't exist
            this->Insert(key, value);  // inserts the key
            nodeCount++; // update the count
        } else { // if the key does exist
            iterator node = find(key);
            node->value = value;  // updates the key's value
        }
	};

	// remove element at the given position
	// amortized constant
	void remove(iterator position) {
        this->RemoveNode(position);  // listed in RBT.hpp
        nodeCount--; // decreases amount of nodes by 1
	};

        // remove element with keyvalue key and 
	// return number of elements removed (either 0 or 1)
	// O(logN), N size of ST
	size_t remove(const Key& key) {
		if (find(key)) { // ensure the key exists
            remove(find(key)); 
            return 1;  // true that one key was removed
        }
        return 0;  // couldn't find the key
	};  

	// removes all elements from the ST, after this size() returns 0
	// linear in the size of the ST
	void clear() {
		while (!empty()) { // loops to remove the root
            remove(this->root);  // removes the root
        }
        nodeCount = 0; // set number of nodes to 0
	}; 

	// checks if ST has no elements; true is empty, false otherwise
	// constant
	bool empty() const {
		if (nodeCount == 0) { // checks if the tree is empty
			return true; // tree is empty
		}
		return false; // tree is not empty
	}; 

	// returns number of elements in ST
	// constant
	size_t size() const {	
		return nodeCount; // returns the number of nodes in the tree
	}; 

	// returns number of elements that match keyvalue key
	// value returned is 0 or 1 since keys are unique
	// O(LogN), N size of ST
	size_t count(const Key& key) {
		if (find(key)) {
        	return 1;  // found a match
    	}
    	return 0; // did not find a match
	}; 

	// find an element with keyvalue key and return 
	// the iterator to the element found, nullptr if not found
	// O(LogN), N size of ST
	iterator find(const Key& key) {
		return this->Search(key); // method in RBT.hpp
	};

	// check if key exists in ST
	// O(LogN), N size of ST
	bool contains(const Key& key) {
		if (find(key) != nullptr) {
        	return 1;  // key found
    	}
    	return 0;  // key not found
	};

	std::vector<std::pair<Key, Type>> toVector() {
        std::vector<std::pair<Key, Type>> vec; // creates vector pair
        Traverse(this->root, vec); // call traversal
        return vec; // return vector
    }

    void Traverse(RBTNode<Key, Type>* node, std::vector<std::pair<Key, Type>>& vec) {
        if (node) { // if node exists exists
            Traverse(node->left, vec); // goes left side
            vec.emplace_back(node->key, node->value); // puts key and value into vector
            Traverse(node->right, vec); // goes right side
        }
    }

	// print the symbol table as Red-Black Tree
	// O(N), N size of ST
	void displayTree() {
		cout << RBTPrint<Key, Type>::TreeToString(this->root) << endl;	 // creates and displays tree using function in RBTPrint.hpp
	};

	// print the symbol table in sorted order
	// O(N), N size of ST
	void display() {
		vector<pair<Key, Type>> vec = toVector(); // makes it into a vector
        for (const auto& temp : vec) {
            cout << temp.first << ": " << temp.second << endl; // loop outputs each key along with its value
        }
	};

private:
	size_t nodeCount;

};

#endif

