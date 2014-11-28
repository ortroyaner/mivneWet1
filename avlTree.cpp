//
//  main.cpp
//  mivneWet1
//
//  Created by Or Troyaner on 27/11/14.
//  Copyright (c) 2014 Or Troyaner. All rights reserved.
//

#include <iostream>

// =====================================================================
//                           CLASSES DECLERATION
// =====================================================================

template<typename keyType, typename valueType>
class avlTree;


// =====================================================================
//                            GENERAL EXCEPTIONS
// =====================================================================
class TreeIsEmpty : public std::exception {
	const char* what() {
		return "TREE_IS_EMPTY";
	}
};
class NoSuchKey : public std::exception {
	const char* what() {
		return "KEY_DOESNT_EXISTS_IN_THE_TREE";
	}
};

class KeyAlreadyExists : public std::exception {
	const char* what() {
		return "KEY_ALREADY_EXISTS";
	}
};

// =====================================================================
//                             avlTree CLASS
// =====================================================================

template<typename keyType, typename valueType>
class avlTree {
private:
	class Node {
	public:
		keyType key;
		valueType value;
		Node* right;
		Node* left;
		Node* parent;
		int balanceFactor;
		int height;
		Node(keyType key, valueType value, Node* right = NULL, Node* left = NULL, Node*  parent = NULL, int balanceFactor = 0, int height = 0) :keyType(key), valueType(value), right(right), left(left), parent(parent), balanceFactor(balanceFactor), height(height) {};
		Node() : keyType(key), valueType(), right(NULL), left(NULL), parent(NULL), balanceFactor(0), height(0) {}; //no-parameters Node constructor
		bool isEmpty() {
			return (this == NULL);
		};
		bool isLeaf(Node* node) {
			return (node->right == NULL && node->left == NULL);
		};
	};
	Node* root;
	int treeSize;
	valueType& find(Node* node, const keyType& key); //this is an aux version of find function.
	Node* getNextNodeInOrderAux(Node* node) {
		if (node->left == NULL) {
			return node;
		}
		else getNextNodeInOrderAux(node->left);
	}
	Node* getNextNodeInOrder(Node* node) {
		if ((node->right)->left == NULL) {
			return node->right;
		}
		getNextNodeInOrderAux((node->right)->left);
	}
	Node* insert(Node* node, const keyType& key, const valueType& value);
	Node* remove(Node* node, const keyType& key);
	Node* removeForLeaf(Node* node, const keyType& key);
	Node* removeForPartialNode(Node* node, const keyType& key);
public:
	avlTree() :root(NULL), treeSize(0) {} //avlTree constructor
	valueType& find(const keyType& key);
	bool isEmpty() {
		return (NULL == this->root);
	}
	void insert(const keyType& key, const valueType& value);
	void remove(const keyType& key){
		remove(this->root, key);
	}
};

template<typename keyType, typename valueType>
valueType& avlTree<keyType, valueType>::find(Node* node, const keyType& key) { //this is an aux version of find function.
	if (node->isEmpty()) throw NoSuchKey(); //if the tree is empty, throw exception.
	if (key == node->key) { //if we got the the key, let's return the value of it.
		return node->value;
	}
	if (key >= node->key) {
		return find(node->right, key);
	}
	else {
		find(node->left, key);
	}
}

template<typename keyType, typename valueType>
void avlTree<keyType, valueType>::insert(const keyType& key, const valueType& value) {
	try{
		this->find(key);
		throw KeyAlreadyExists();
	}
	catch (const NoSuchKey& e){
		if (this->isEmpty()){
			Node* newNode = new Node(key, value);
			this->root = newNode;
			return;
		}
		insert(this->root, key, value);
	}
}

template<typename keyType, typename valueType>
typename avlTree<keyType, valueType>::Node* avlTree<keyType, valueType>::insert(Node* node, const keyType& key, const valueType& value) {
	if (!node){
		Node* newNode = new Node(key, value);
		this->treeSize++;
		return newNode;
	}

	if (key >= node->key){
		node->right = insert(node->right, key, value);
		node->right->parent = node;
	}
	else{
		node->left = insert(node->left, key, value);
		node->left->parent = node;
	}

	node->height++;
	//TODO: add balance fix;
	return node;
}

template<typename keyType, typename valueType>
typename avlTree<keyType, valueType>::Node* avlTree<keyType, valueType>::removeForPartialNode(Node* node, const keyType& key){
	if (node->right){
		node->right->parent = node->parent;
		Node* temp = node->right;
		delete(node);
		return temp;
	}
	else {
		node->left->parent = node->parent;
		Node* temp = node->left;
		delete(node);
		return temp;
	}
}

template<typename keyType, typename valueType>
typename avlTree<keyType, valueType>::Node* avlTree<keyType, valueType>::remove(Node* node, const keyType& key) {
	if (!node){
		throw NoSuchKey();
	}

	if (key == node->key){
		if (isLeaf(node)){
			delete(node);
			return NULL;
		}
		else if (node->right && node->left){
			swapNodes(node, getNextInOrder(node));
			if (isLeaf(node)){
				delete(node);
				return NULL;
			}
			else{
				return removeForPartialNode(node, key);
			}
		}
		else {
			return removeForPartialNode(node, key);
		}
	}

	if (key > node->key){
		node->right = remove(node->right, key);
	}
	else {
		node->left = remove(node->left, key);
	}

	node->height--;
	//TODO: add balance fix;
	return node;
}


int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	return 0;
}