/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#pragma once
#include"AVLNode.h"
class TreeSet
{
private:
	AVLNode * root;
	int count;

protected:
	void clearRec(AVLNode*root);
	

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

