#pragma once
enum way{
	LEFT,
	RIGHT
};

typedef struct node_b
{
	int data;
	struct node_b* left;
	struct node_b* right;

}NODE_BIN;

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

private:

public:
	NODE_BIN* makeNode(int data);
	void setNode(NODE_BIN* a, way);

	//전위순회
	void preOrder();

};

