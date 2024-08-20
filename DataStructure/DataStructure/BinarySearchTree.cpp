#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std; 

//추가
void BinarySearchTree::Insert(int value)
{
	//추가할 노드 셋팅
	Node* newNode = new Node();
	newNode->value = value;

	//처음이라면
	if (nullptr == _root)
	{
		_root = newNode;
		return;
	}

	//탐색노드설정
	Node* CompareNode = _root;
	//부모 설정
	Node* parent = nullptr;
	
	//탐색 노드가 null일때까지 계속 반복
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
	//끝까지 못찾은 경우 또는 찾은 경우
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

	//node->left가 null일때까지 계속~
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

//다음 큰 값 찾기
Node* BinarySearchTree::Next(Node* node)
{
	//node의 오른쪽 중에 가장 작은값 찾기
	if (node->right)
		return Min(node->right);

	//node->right가 null이라면, 부모중에 나를 left로 갖는 부모를 찾음
	Node* parentNode = node->parent;
	while (parentNode && node == parentNode->right)
	{
		//parent->left를 찾으면 return
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
		//node.right일때 return
		node = parentNode;
		parentNode = parentNode->parent;
	}

	return parentNode;
}

void BinarySearchTree::Replace(Node* deleteNode, Node* replaceNode)
{
	if (deleteNode->parent == nullptr)
		_root = replaceNode;
	//자식이 1개만 있을때
	//부모가 있는 왼쪽 자식 일때
	else if (deleteNode == deleteNode->parent->left)
		deleteNode->parent->left = replaceNode;
    //자식이 오른쪽에만 있을때
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

	//자식이 왼쪽에만 있을때
	if (deleteNode->right == nullptr)
	{
		Replace(deleteNode, deleteNode->left);
	}
	//자식이 오른쪽에만 있을때
	else if (deleteNode->left== nullptr)
	{
		Replace(deleteNode, deleteNode->right);
	}

	//자식이 2명 있을때
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
	//제일 작은 값 찾기
	Node* PrintNode = Min(_root);

	while (PrintNode)
	{
		cout << PrintNode->value << " ";
		PrintNode = Next(PrintNode);
	}
}

