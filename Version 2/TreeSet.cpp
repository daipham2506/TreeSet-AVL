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


int TreeSet::add(int val) {
	bool check = true;
	root = insert(root, val, check);
	if (check == true) {
		count++;
		return 1;
	}
	else
		return 0;
}

int TreeSet::remove(int val) {
	bool check = false;
	root = deleteNode(root, val, check);
	if (check == true) {
		count--;
		return 1;
	}
	else
		return 0;
}

// Check Node contains val exist???
bool TreeSet::contains(int val) {
	return (contain(root, val) == 1);
}



int TreeSet::first() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}
	AVLNode* node = root;
	while (node->left != NULL)
		node = node->left;
	return node->key;
}

int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}
	AVLNode* node = root;
	while (node->right != NULL)
		node = node->right;
	return node->key;
}

// Return min val of TreeSet but > val
int TreeSet::higher(int val) {
	int kq = -1;
	AVLNode* node = root;
	while (node != NULL)
	{
		if (node->key > val) {
			kq = node->key;
			node = node->left;
		}
		else
			node = node->right;
	}
	return kq;
}

//Return max val of TreeSet but < val
int TreeSet::lower(int val) {
	int kq = -1;
	AVLNode* node = root;
	while (node != NULL)
	{
		if (node->key < val) {
			kq = node->key;
			node = node->right;
		}
		else
			node = node->left;
	}
	return kq;
}


// Copy all node
void TreeSet::copy(const TreeSet& set) {
	/*if (set.count == 0) return;
	queue<AVLNode*> que;
	que.push(set.root);
	while (!que.empty()) {
		AVLNode* temp = que.front(); que.pop();
		this->add(temp->key);
		if (temp->left != NULL) que.push(temp->left);
		if (temp->right != NULL) que.push(temp->right);
	}*/
	if (set.count == 0) return;
	this->root = clone(set.root);
	this->count = set.count;
}


TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	TreeSet *ketqua = new TreeSet();
	queue<AVLNode*> que;
	que.push(root);
	while (!que.empty()) {
		AVLNode *temp = que.front(); que.pop();
		if (temp->key >= fromVal && temp->key < toVal)
			ketqua->add(temp->key);
		if (temp->left != NULL) que.push(temp->left);
		if (temp->right != NULL) que.push(temp->right);
	}
	return ketqua;
}

int TreeSet::size() {
	return count;
}


// utility function
int TreeSet::height(AVLNode* root) {
	return (root == NULL) ? 0 : root->balance;
}

AVLNode* TreeSet::rightRotate(AVLNode* &y) {
	AVLNode *x = y->left;
	AVLNode *T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights 
	y->balance = max(height(y->left), height(y->right)) + 1;
	x->balance = max(height(x->left), height(x->right)) + 1;

	// Return new root 
	return x;
}

AVLNode* TreeSet::leftRotate(AVLNode* &x) {
	AVLNode *y = x->right;
	AVLNode *T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	//  Update heights 
	x->balance = max(height(x->left), height(x->right)) + 1;
	y->balance = max(height(y->left), height(y->right)) + 1;

	// Return new root 
	return y;
}

int TreeSet::getBalance(AVLNode* root) {
	if (root == NULL)
		return 0;
	return height(root->left) - height(root->right);
}

AVLNode* TreeSet::minValueNode(AVLNode* root) {
	AVLNode* current = root;

	// loop down to find the leftmost leaf 
	while (current->left != NULL)
		current = current->left;

	return current;
}

AVLNode* TreeSet::insert(AVLNode* &root, int val, bool &check) {
	/* 1.  Perform the normal BST rotation */
	if (root == NULL)
		return new AVLNode(val);

	if (val < root->key)
		root->left = insert(root->left, val,check);
	else if (val > root->key)
		root->right = insert(root->right, val,check);
	else // Equal keys not allowed 
	{
		check = false;
		return root;
	}

	/* 2. Update height of this ancestor node */
	root->balance = 1 + max(height(root->left), height(root->right));
		

	/* 3. Get the balance factor of this ancestor
	node to check whether this node became
	unbalanced */
	int balance = getBalance(root);

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && val < root->left->key)
		return rightRotate(root);

	// Right Right Case 
	if (balance < -1 && val > root->right->key)
		return leftRotate(root);

	// Left Right Case 
	if (balance > 1 && val > root->left->key)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Left Case 
	if (balance < -1 && val < root->right->key)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	/* return the (unchanged) node pointer */
	return root;
}


AVLNode* TreeSet::deleteNode(AVLNode* &root, int val, bool &check) {
	// STEP 1: PERFORM STANDARD BST DELETE 

	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the 
	// root's key, then it lies in left subtree 
	if (val < root->key)
		root->left = deleteNode(root->left, val, check);

	// If the key to be deleted is greater than the 
	// root's key, then it lies in right subtree 
	else if (val > root->key)
		root->right = deleteNode(root->right, val, check);

	// if key is same as root's key, then This is 
	// the node to be deleted 
	else
	{
		check = true;
		// node with only one child or no child 
		if ((root->left == NULL) || (root->right == NULL))
		{
			AVLNode *temp = root->left ? root->left : root->right;
				

			// No child case 
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case 
				*root = *temp; // Copy the contents of 
							   // the non-empty child 
			delete temp;
		}
		else
		{
			// node with two children: Get the inorder 
			// successor (smallest in the right subtree) 
			AVLNode* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node 
			root->key = temp->key;

			// Delete the inorder successor 
			root->right = deleteNode(root->right, temp->key,check);
		}
	}

	// If the tree had only one node then return 
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	root->balance = 1 + max(height(root->left), height(root->right));
		

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
	// check whether this node became unbalanced) 
	int balance = getBalance(root);

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case 
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case 
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case 
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

int TreeSet::contain(AVLNode* root, int val) {
	if (root == NULL)
		return 0;
	if (val < root->key)
		return contain(root->left, val);
	else if (val > root->key)
		return contain(root->right, val);
	else
		return 1;
}

AVLNode* TreeSet::clone(AVLNode* root) {
	if (root == NULL) return NULL;
	AVLNode* node = new AVLNode(root->key);
	node->left = clone(root->left);
	node->right = clone(root->right);
	return node;
}


