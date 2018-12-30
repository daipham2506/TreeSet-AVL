/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/


#pragma once
#include<iostream>
using namespace std;
class AVLNode {
public:
	int key;			// data 
	AVLNode* left;		// left child
	AVLNode* right;		// right child
	int balance;		// balance factor

	AVLNode(int key) {
		this->key = key;
		left = right = NULL;
		balance = 0;
	}
	AVLNode(int key, int balance) {
		this->key = key;
		this->balance = balance;
		left = right = NULL;
	}
};
