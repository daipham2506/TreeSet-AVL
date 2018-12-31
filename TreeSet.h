/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

//#pragma once
#include"AVLNode.h"
class TreeSet
{
private:
	AVLNode * root;
	int count;

protected:
	void clearRec(AVLNode*root);
	void insert(AVLNode* &root, int val);
	AVLNode* del(AVLNode* &root, int val);
	int height(AVLNode* root);
	int updateBalance(AVLNode* root);
	AVLNode* rotateLeft(AVLNode* &root);
	AVLNode* rotateRight(AVLNode* &root);
	void RightRight(AVLNode* &root);
	void LeftLeft(AVLNode* &root);
	void RightLeft(AVLNode* &root);
	void LeftRight(AVLNode* &root);
	int _contains_(AVLNode* root, int val);
	int findMax(AVLNode* root);
	int findMin(AVLNode* root);
	void _copy_(AVLNode* root,TreeSet* &result);
	void _subSet_(AVLNode* root, TreeSet* &tree, int fromVal, int toVal);
public:
	TreeSet();
	~TreeSet();
	void clear();
	// print out the set in ascending order
	friend ostream& operator<<(ostream& os, const TreeSet& t);

	// YOUR TASKS START HERE	
	int add(int val);
	bool contains(int val);
	void copy(const TreeSet& set);
	int first();
	int higher(int val);
	int last();
	int lower(int val);
	int remove(int val);
	TreeSet* subSet(int fromVal, int toVal);
	int size();
	// END HERE
};

