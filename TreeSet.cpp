/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include "TreeSet.h"

TreeSet::TreeSet()
{
	root = NULL;
	count = 0;
}

TreeSet::~TreeSet()
{
	clear();
}

void TreeSet::clearRec(AVLNode* root) {
	if (root != NULL) {
		clearRec(root->left);
		clearRec(root->right);
		delete root;
	}
}

void TreeSet::clear() {
	clearRec(root);
	root = NULL;
	count = 0;
}

// add new node contains val into Tree
int TreeSet::add(int val) {
	bool check = contains(val);
	if (check == true) return 0;
	insert(root, val);
	++count;
	return 1;
}

// delete node contains val
int TreeSet::remove(int val) {
	bool check = contains(val);
	if (check == false) return 0;
	root=del(root, val);
	--count;
	return 1;
}

// Check Node contains val exist???
bool TreeSet::contains(int val) {
	return (_contains_(root, val) == 1);
}

//min value of Tree
int TreeSet::first() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}
	return findMin(root);
}

//max value of Tree
int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}
	return findMax(root);
}

// min value of Tree but > val
int TreeSet::higher(int val) {
	int rs = -1;
	AVLNode* temp = root;
	while (temp != NULL)
	{
		if (temp->key > val) {
			rs = temp->key;
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	return rs;
}

// max value of Tree but < val
int TreeSet::lower(int val) {
	int rs = -1;
	AVLNode* temp = root;
	while (temp != NULL)
	{
		if (temp->key < val) {
			rs = temp->key;
			temp = temp->right;
		}
		else {
			temp = temp->left;
		}
	}
	return rs;
}

// Copy all node
void TreeSet::copy(const TreeSet& set) {
	if (set.count == 0) return;
	TreeSet* result = new TreeSet();
	_copy_(set.root, result);
	this->root = result->root;
	this->count = set.count;
}

//Copy fromVal <= val_node < toVal
TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	TreeSet *result = new TreeSet();
	_subSet_(root, result, fromVal, toVal);
	return result;
}

// Quantity node into TreeSet
int TreeSet::size() {
	return count;
}



// Utility function

int TreeSet::height(AVLNode* root) {
	if (root != NULL)
		return root->balance;
	else return -1;
	//return (root != NULL)? root->balance:-1;
}

int TreeSet::updateBalance(AVLNode* root) {
	int hl = height(root->left);
	int hr = height(root->right);
	return (hl>hr ? hl : hr) + 1;
}

AVLNode* TreeSet::rotateLeft(AVLNode* &root) {
	//rotate perform
	AVLNode* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	//update balance factor
	root->balance = updateBalance(root);
	temp->balance = updateBalance(temp);
	// return new root
	return temp;
}

AVLNode* TreeSet::rotateRight(AVLNode* &root) {
	//rotate perform
	AVLNode* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	//update balance factor
	root->balance = updateBalance(root);
	temp->balance = updateBalance(temp);
	// return new root
	return temp;
}


void TreeSet::RightRight(AVLNode* &root) {
	root=rotateRight(root);
}
void TreeSet::LeftLeft(AVLNode* &root) {
	root = rotateLeft(root);
}
void TreeSet::RightLeft(AVLNode* &root) {
	RightRight(root->right);
	LeftLeft(root);
}
void TreeSet::LeftRight(AVLNode* &root) {
	LeftLeft(root->left);
	RightRight(root);
}

void TreeSet::insert(AVLNode* &root,int val) {
	if (root == NULL) root = new AVLNode(val);
	else if (val < root->key) {
		insert(root->left, val);
		if (height(root->left) - height(root->right) == 2) {
			if (val < root->left->key)
				RightRight(root);
			else
				LeftRight(root);
		}
	}
	else if (val > root->key) {
		insert(root->right, val);
		if (height(root->right) - height(root->left) == 2) {
			if (val > root->right->key)
				LeftLeft(root);
			else
				RightLeft(root);
		}
	}
	else return;
	//update height
	root->balance = updateBalance(root);
}

AVLNode* TreeSet::del( AVLNode* &root,int val) {
	if (root == NULL) return NULL;
	if (val < root->key)
		root->left = del(root->left, val);
	else if (val > root->key)
		root->right = del(root->right, val);
	else {
		// two children
		if (root->left != NULL && root->right != NULL) {
			// Find min val of right tree
			AVLNode* temp = root->right;
			while (temp->left != NULL) temp = temp->left;
			// Delete val
			root->key = temp->key;
			root->right = del(root->right, temp->key);
		}
		// one or zero children
		else {
			AVLNode *temp = root;
			if (root->left == NULL)
				root = root->right;
			else if (root->right == NULL)
				root = root->left;
			delete temp;
			return root;
		}
	}
	// Update height
	root->balance = updateBalance(root);
	// Rebalance
	if (height(root->left) - height(root->right) == 2) {
		// rotate right
		if (height(root->left->left) >= height(root->left->right) )
			RightRight(root);
		// after rotate left, rotate right
		else
			LeftRight(root);
	}
	if (height(root->right) - height(root->left) == 2) {
		// rotate left
		if (height(root->right->right) >= height(root->right->left) )
			LeftLeft(root);
		// after rotate right , rotate left
		else
			RightLeft(root);
	}
	return root;
}


int TreeSet::_contains_(AVLNode* root, int val) {
	if (root == NULL) return 0;
	if (val < root->key)
		return _contains_(root->left, val);
	else if (val > root->key)
		return _contains_(root->right, val);
	else return 1;
}

int TreeSet::findMax(AVLNode* root) {
	if (root->right == NULL)
		return root->key;
	return findMax(root->right);
}

int TreeSet::findMin(AVLNode* root) {
	if (root->left == NULL)
		return root->key;
	return findMin(root->left);
}

void TreeSet::_copy_(AVLNode* root,TreeSet* &result) {
	if (root == NULL) return ;
	result->add(root->key);
	_copy_(root->left, result);
	_copy_(root->right, result);	
}

void TreeSet::_subSet_(AVLNode* root, TreeSet* &tree, int fromVal, int toVal) {
	if (root == NULL) return ;
	if (root->key >= fromVal && root->key < toVal) tree->add(root->key);
	_subSet_(root->left, tree, fromVal, toVal);
	_subSet_(root->right, tree, fromVal, toVal);
}
		
