/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include "TreeSet.h"

TreeSet::TreeSet()
{
	root == NULL;
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


int TreeSet::add(int val) {
	// TODO
}

bool TreeSet::contains(int val) {
	// TODO
}

void TreeSet::copy(const TreeSet& set) {
	// TODO
}

int TreeSet::first() {	
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	// TODO
}

int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	// TODO
}

int TreeSet::higher(int val) {
	// TODO
}

int TreeSet::lower(int val) {
	// TODO
}

int TreeSet::remove(int val) {
	// TODO
}


TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	// TODO
}

int TreeSet::size() {
	// TODO
}

