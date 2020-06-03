#include "BinaryTree.h"



BinaryTree::BinaryTree()
{
	NODE_BIN* root = makeNode(1);
}

BinaryTree::~BinaryTree()
{
}



NODE_BIN* BinaryTree::makeNode(int data)
{
	NODE_BIN* newNode = new NODE_BIN;
	newNode->data = data;
	newNode->left = nullptr;
	newNode->right = nullptr;

	return newNode;
}
