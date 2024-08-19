#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std; 




Node* BinarySearchTree::Search(Node* SearchNode, int key)
{
	// Ž����尡 null�̰ų�, Ž������� Ű�� ã������ Ű�� ��ġ�ϴ� ���
	if (SearchNode == nullptr || key == SearchNode->key)
		return SearchNode;

	//ã���� �ϴ� Ű�� ���� Ž�� ����� Ű���� �۴ٸ�
	//���� Ž������� ���� �ڽĳ�带 Ž��
	if (key < SearchNode->key)
	{
		return Search(SearchNode->left, key);
	}

	// ã���� �ϴ� Ű�� ���� ����� Ű���� ũ�ٸ� ������ ����Ʈ������ �˻�
	else if (key > SearchNode->key)
	{
		return Search(SearchNode->right, key);
	}
}

void BinarySearchTree::Insert(int key)
{
	//���Ӱ� ���� ���
	Node* newNode = new Node();
	//���Ӱ� ���� ����� �� ����
	newNode->key = key;

	//�ƹ����� �����ٸ�(ó��)
	if (_root == nullptr)
	{
		//��Ʈ ��带 ���Ӱ� �߰��� ���� ����
		_root = newNode;
		return;
	}

	// �� ���
	Node* CompareNode = _root;
	Node* parent = nullptr;	

	//�񱳳�尡 null�� �ɶ����� �ݺ�
	while (CompareNode != nullptr)
	{
		//���� �θ�� �ڱ� �ڽ�
		parent = CompareNode;

		//���Ӱ� ���� ��尡 �񱳳�庸�� �۴ٸ� 
		if (newNode->key < CompareNode->key)
		{
			//�񱳳�带 �񱳳���� �����ڽ� ���� ����
			CompareNode = CompareNode->left;
		}

		//���Ӱ� ���� ��尡 �񱳳�庸�� ũ�ٸ�
		else if (newNode->key > CompareNode->key)
		{
			//�񱳳�带 �񱳳���� ������ �ڽ� ���� ����
			CompareNode = CompareNode->right;
		}
	}

	newNode->parent = parent; 

	if (newNode->key > parent->key)
	{
		parent->right= newNode;
	}
	else if (newNode->key < parent->key)
	{
		parent->left = newNode;
	}
}

//Ʈ���� ���� ���� ��(��� �������� �̵��ϸ��)
Node* BinarySearchTree::Min(Node* node)
{
	if (node == nullptr)
		return nullptr;

	while (node->left)
	{
		node = node->left;
	}
	return node;
}

//Ʈ���� ���� ���� ��(��� ���������� �̵��ϸ��)
Node* BinarySearchTree::Max(Node* node)
{

	if (node == nullptr)
		return nullptr;

	while (node->right)
	{
		node = node->right;
	}
	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	//�������ڽ��� ���� �������� ��ȯ
	if (node->right)
		return Min(node->right);
	//������ �ڽ��� ���ٸ�, ���� �ڽ� �� ���� ū ��
	Node* parent = node->parent;
	//���� �����ڽ����� ����ִ� ���� ���� ���������� �ö�
	while (parent && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

Node* BinarySearchTree::Prev(Node* node)
{
	//���� �ڽ��� nullptr�� �ƴ϶��
	//���� �ڽ� �� ���� ū ���� ã��
	if (node->left)
		return Max(node->left);

	//���� �ڽ��� nullptr�̶��
	Node* parent = node->parent;
	//���� ������ �ڽ����� ������ �θ� ã���� ���� �ݺ� ��ȸ
	while (parent&&node==parent->left)
	{
		node= parent;
		parent = parent->parent;
	}
	return parent;
}

void BinarySearchTree::Replace(Node* deleteNode, Node* replaceNode)
{
	//�����Ϸ��� ��尡 ��Ʈ����϶�
	if (deleteNode->parent == nullptr)
		_root = replaceNode;

	//�θ� �ִ� ���� �ڽ��϶�
	else if (deleteNode == deleteNode->parent->left)
		deleteNode->parent->left = replaceNode;
	//�θ� �ִ� ������ �ڽ��϶�
	else
		deleteNode->parent->right = replaceNode;
	//�������� ��尡 nullptr�� �ƴ϶��, �θ��带 ������ ����� �θ���� ����
	if (replaceNode)
		replaceNode->parent = deleteNode->parent;

	delete deleteNode;
}

void BinarySearchTree::Delete(int key)
{
	//��Ʈ������ Ű�� �ش��ϴ� ���� �� ã�Ƽ�~
	Node* deleteNode = Search(_root, key);
	//����
	Delete(deleteNode);

}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	//���� �ڽ��� ���°��(������ �ڽĸ� ������)
	if (node->left == nullptr)
	{
		Replace(node, node->right);
	}
	//������ �ڽ��� ���� ���(���� �ڽĸ� ������)
	else if (node->right == nullptr)
	{
		Replace(node, node->left);
	}

	//�ڽ��� 2���ִ� ���
	else
	{
		//�����Ϸ��� ����� ������� ã�Ƽ� 
		Node* nextNode = Next(node);
		//�����س���
		node->key = nextNode->key;
		Delete(nextNode);
	}
}

void BinarySearchTree::Print()
{
	//����Ʈ������ ���� ���� ���� ã��
	Node* PrintNode = Min(_root);
	
	while (PrintNode)
	{
		cout << PrintNode->key << " ";
		Node* node = Next(PrintNode);
		PrintNode = node;
	}
}

void BinarySearchTree::ReversePrint()
{
	//����Ʈ������ ���� ū ���� ã��
	Node* PrintNode = Max(_root);

	while (PrintNode)
	{
		cout << PrintNode->key << " ";
		Node* node = Prev(PrintNode);
		PrintNode = node;
	}
}
