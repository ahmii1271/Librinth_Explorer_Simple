#ifndef AVLTREE_H
#define AVLTREE_H


#include "Utils.h"


class AVLNode {
	
public:
	int data;
	int height;
	AVLNode* left;
	AVLNode* right;
	AVLNode();
	AVLNode(int data);
	
	int getData();
	int getHeight();
	AVLNode* getLeft();
	AVLNode* getRight();

	void setData(int data);
	void setHeight(int height);
	void setLeft(AVLNode* left);
	void setRight(AVLNode* right);

};

class AVLTree {
public:
	AVLNode* root;
	AVLTree();

	AVLNode* createNode(int data);
	AVLNode* rotateRight(AVLNode* node);
	AVLNode* rotateLeft(AVLNode* node);

	int getBalance(AVLNode* node);
	AVLNode* insertNode(AVLNode* node, int data);
	void insert(int data);
	void remove(int value);


	AVLNode* findMin(AVLNode* node);
	AVLNode* deleteNode(AVLNode* root, int data);
	void inorderTraverse(AVLNode* root, std::string indent, bool last);
	
	AVLNode* getRoot();
	bool isEmpty();
	int size(AVLNode* node, int& count);
	int max(int a, int b);
	int getHeight(AVLNode* node);
	int findFrequency(int target);
	void deleteTree(AVLNode*& root);

};
#endif 