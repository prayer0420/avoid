#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std; 

//�߰�
void BinarySearchTree::Insert(int value)
{
	//�߰��� ��� ����
	Node* newNode = new Node();
	newNode->value = value;

	//ó���̶��
	if (nullptr == _root)
	{
		_root = newNode;
		return;
	}

	//Ž����弳��
	Node* CompareNode = _root;
	//�θ� ����
	Node* parent = nullptr;
	
	//Ž�� ��尡 null�϶����� ��� �ݺ�
	while (CompareNode)
	{
		parent = CompareNode;
		if (value < newNode->value)
			CompareNode = CompareNode->left;
		else
			CompareNode = CompareNode->right;
	}
	newNode->parent = parent;

	if (value < parent->value)
		parent->left = newNode;
	else if(value > parent->value)
		parent->right = newNode;
}

Node* BinarySearchTree::Search(Node* SearchNode, int value)
{
	//������ ��ã�� ��� �Ǵ� ã�� ���
	if (SearchNode == nullptr || value == SearchNode->value)
		return SearchNode;


	if (value < SearchNode->value)
		return Search(SearchNode->left, value);
	else if(value > SearchNode->value)
		return Search(SearchNode->right, value);
}

Node* BinarySearchTree::Min(Node* node)
{
	if (node == nullptr)
		return nullptr;

	//node->left�� null�϶����� ���~
	while (node->left)
	{
		node = node->left;
	}
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node && node->right)
		node = node->right;
	return node;
}

//���� ū �� ã��
Node* BinarySearchTree::Next(Node* node)
{
	//node�� ������ �߿� ���� ������ ã��
	if (node->right)
		return Min(node->right);

	//node->right�� null�̶��, �θ��߿� ���� left�� ���� �θ� ã��
	Node* parentNode = node->parent;
	while (parentNode && node == parentNode->right)
	{
		//parent->left�� ã���� return
		node = parentNode;
		parentNode = parentNode->parent;
	}
	return parentNode;
}

Node* BinarySearchTree::Prev(Node* node)
{
	if (node->left)
		return Max(node->left);

	Node* parentNode = node->parent;
	while (parentNode && node == node->left)
	{
		//node.right�϶� return
		node = parentNode;
		parentNode = parentNode->parent;
	}

	return parentNode;
}

void BinarySearchTree::Replace(Node* deleteNode, Node* replaceNode)
{
	if (deleteNode->parent == nullptr)
		_root = replaceNode;
	//�ڽ��� 1���� ������
	//�θ� �ִ� ���� �ڽ� �϶�
	else if (deleteNode == deleteNode->parent->left)
		deleteNode->parent->left = replaceNode;
    //�ڽ��� �����ʿ��� ������
	else
		deleteNode->parent->right = replaceNode;

	if(replaceNode)
		replaceNode->parent = deleteNode->parent;
}

void BinarySearchTree::Delete(int value)
{
	Node* node = Search(_root, value);
	Delete(node);
}

void BinarySearchTree::Delete(Node* deleteNode)
{
	if (deleteNode == nullptr)
		return;

	//�ڽ��� ���ʿ��� ������
	if (deleteNode->right == nullptr)
	{
		Replace(deleteNode, deleteNode->left);
	}
	//�ڽ��� �����ʿ��� ������
	else if (deleteNode->left== nullptr)
	{
		Replace(deleteNode, deleteNode->right);
	}

	//�ڽ��� 2�� ������
	else 
	{
		Node* nextNode = Next(deleteNode);
		deleteNode->value = nextNode->value;
		Delete(nextNode);
	}
	delete deleteNode;
}

void BinarySearchTree::Print()
{
	//���� ���� �� ã��
	Node* PrintNode = Min(_root);

	while (PrintNode)
	{
		cout << PrintNode->value << " ";
		PrintNode = Next(PrintNode);
	}
}

