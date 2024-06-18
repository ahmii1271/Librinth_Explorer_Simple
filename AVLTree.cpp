#include "AVLTree.h"


/////////////  AVL Node /////////////////

AVLNode::AVLNode() {
	data = 0;
	left = right = NULL;
}


AVLNode::AVLNode(int data) {
	this->data = data;
	left = right = NULL;
}


int AVLNode::getData() {
	return data;
}


int AVLNode::getHeight() {
	return height;
}


AVLNode* AVLNode::getLeft() {
	return left;
}


AVLNode* AVLNode::getRight() {
	return right;
}


void AVLNode::setData(int data) {
	this->data = data;
}


void AVLNode::setHeight(int height) {
	this->height = height;
}


void AVLNode::setLeft(AVLNode* left) {
	this->left = left;
}


void AVLNode::setRight(AVLNode* right) {
	this->right = right;
}



////////////// AVL Tree //////////////

AVLTree::AVLTree() {
	root = NULL;
}


AVLNode* AVLTree::getRoot() {
	return root;
}


bool AVLTree::isEmpty() {
	return (root == NULL);
}

int AVLTree::size(AVLNode* node, int& count) {
	if (node == NULL) {
		return count;
	}
	size(node->left, count);
	count++;
	size(node->right, count);
}


int AVLTree::max(int a, int b) {
	return (a > b) ? a : b;
}


int AVLTree::getHeight(AVLNode* node) {
	if (node == NULL)
		return 0;
	return node->height;
}


AVLNode* AVLTree::createNode(int data) {
	AVLNode* node = new AVLNode();
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return (node);
}


AVLNode* AVLTree::rotateRight(AVLNode* node) {
	AVLNode* rotNode = node->left;
	AVLNode* T2 = rotNode->right;
	rotNode->right = node;
	node->left = T2;
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	rotNode->height = max(getHeight(rotNode->left), getHeight(rotNode->right)) + 1;
	return rotNode;
}


AVLNode* AVLTree::rotateLeft(AVLNode* node) {
	AVLNode* rotNode = node->right;
	AVLNode* T2 = rotNode->left;
	rotNode->left = node;
	node->right = T2;
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	rotNode->height = max(getHeight(rotNode->left), getHeight(rotNode->right)) + 1;
	return rotNode;
}


int AVLTree::getBalance(AVLNode* node) {
	if (node == NULL)
		return 0;
	return getHeight(node->left) - getHeight(node->right);
}


AVLNode* AVLTree::insertNode(AVLNode* node, int data) {
	if (node == NULL)
		return (createNode(data));
	if (data < node->data)
		node->left = insertNode(node->left, data);
	else if (data >= node->data)
		node->right = insertNode(node->right, data);
	else
		return node;

	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	int balance = getBalance(node);
	if (balance > 1) {
		if (data < node->left->data) {
			return rotateRight(node);
		}
		else if (data > node->left->data) {
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
	}
	if (balance < -1) {
		if (data > node->right->data) {
			return rotateLeft(node);
		}
		else if (data < node->right->data) {
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
	}
	return node;
}


void AVLTree::insert(int data) {
	root = insertNode(root, data);
}


AVLNode* AVLTree::findMin(AVLNode* node) {
	AVLNode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}


AVLNode* AVLTree::deleteNode(AVLNode* root, int data) {
	if (root == NULL)
		return root;
	if (data < root->data)
		root->left = deleteNode(root->left, data);
	else if (data > root->data)
		root->right = deleteNode(root->right, data);
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			AVLNode* temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			delete temp;
		}
		else {
			AVLNode* temp = findMin(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	int balance = getBalance(root);
	if (balance > 1) {
		if (getBalance(root->left) >= 0) {
			return rotateRight(root);
		}
		else {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
	}
	if (balance < -1) {
		if (getBalance(root->right) <= 0) {
			return rotateLeft(root);
		}
		else {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
	}
	return root;
}


void AVLTree::remove(int value) {
	root = deleteNode(root, value);
}


void AVLTree::inorderTraverse(AVLNode* root, std::string indent, bool last) {
	if (root != nullptr) {
		inorderTraverse(root->left, indent, false);
		std::cout << root->data << " ";
		inorderTraverse(root->right, indent, true);
	}
}


int AVLTree::findFrequency(int target) {
	if (root == nullptr) 
		return 0;

	int count = 0;

	while (root != nullptr) {
		if (root->data == target)
			count++;

		if (root->data >= target)
			root = root->left;
		else
			root = root->right;
	}

	return count;
}

void AVLTree::deleteTree(AVLNode*& root) {
	if (root == nullptr)
		return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
	root = nullptr;
}
