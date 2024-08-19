#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std; 




Node* BinarySearchTree::Search(Node* SearchNode, int key)
{
	// 탐색노드가 null이거나, 탐색노드의 키가 찾으려는 키와 일치하는 경우
	if (SearchNode == nullptr || key == SearchNode->key)
		return SearchNode;

	//찾고자 하는 키가 현재 탐색 노드의 키보다 작다면
	//현재 탐색노드의 왼쪽 자식노드를 탐색
	if (key < SearchNode->key)
	{
		return Search(SearchNode->left, key);
	}

	// 찾고자 하는 키가 현재 노드의 키보다 크다면 오른쪽 서브트리에서 검색
	else if (key > SearchNode->key)
	{
		return Search(SearchNode->right, key);
	}
}

void BinarySearchTree::Insert(int key)
{
	//새롭게 넣을 노드
	Node* newNode = new Node();
	//새롭게 넣을 노드의 값 셋팅
	newNode->key = key;

	//아무값도 없었다면(처음)
	if (_root == nullptr)
	{
		//루트 노드를 새롭게 추가한 노드로 설정
		_root = newNode;
		return;
	}

	// 비교 노드
	Node* CompareNode = _root;
	Node* parent = nullptr;	

	//비교노드가 null이 될때까지 반복
	while (CompareNode != nullptr)
	{
		//최초 부모는 자기 자신
		parent = CompareNode;

		//새롭게 넣을 노드가 비교노드보다 작다면 
		if (newNode->key < CompareNode->key)
		{
			//비교노드를 비교노드의 왼쪽자식 노드로 설정
			CompareNode = CompareNode->left;
		}

		//새롭게 넣을 노드가 비교노드보다 크다면
		else if (newNode->key > CompareNode->key)
		{
			//비교노드를 비교노드의 오른쪽 자식 노드로 설정
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

//트리중 가장 작은 값(계속 왼쪽으로 이동하면됨)
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

//트리중 가장 작은 값(계속 오른쪽으로 이동하면됨)
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
	//오른쪽자식중 제일 작은값을 반환
	if (node->right)
		return Min(node->right);
	//오른쪽 자식이 없다면, 왼쪽 자식 중 제일 큰 값
	Node* parent = node->parent;
	//나를 왼쪽자식으로 들고있는 조상 님을 만날때까지 올라감
	while (parent && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

Node* BinarySearchTree::Prev(Node* node)
{
	//왼쪽 자식이 nullptr이 아니라면
	//왼쪽 자식 중 제일 큰 값을 찾음
	if (node->left)
		return Max(node->left);

	//왼쪽 자식이 nullptr이라면
	Node* parent = node->parent;
	//나를 오른쪽 자식으로 가지는 부모를 찾을때 까지 반복 순회
	while (parent&&node==parent->left)
	{
		node= parent;
		parent = parent->parent;
	}
	return parent;
}

void BinarySearchTree::Replace(Node* deleteNode, Node* replaceNode)
{
	//삭제하려는 노드가 루트노드일때
	if (deleteNode->parent == nullptr)
		_root = replaceNode;

	//부모가 있는 왼쪽 자식일때
	else if (deleteNode == deleteNode->parent->left)
		deleteNode->parent->left = replaceNode;
	//부모가 있는 오른쪽 자식일때
	else
		deleteNode->parent->right = replaceNode;
	//재조정할 노드가 nullptr만 아니라면, 부모노드를 삭제할 노드의 부모노드로 설정
	if (replaceNode)
		replaceNode->parent = deleteNode->parent;

	delete deleteNode;
}

void BinarySearchTree::Delete(int key)
{
	//루트노드부터 키에 해당하는 값을 쭉 찾아서~
	Node* deleteNode = Search(_root, key);
	//삭제
	Delete(deleteNode);

}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	//왼쪽 자식이 없는경우(오른쪽 자식만 있으면)
	if (node->left == nullptr)
	{
		Replace(node, node->right);
	}
	//오른쪽 자식이 없는 경우(왼쪽 자식만 있으면)
	else if (node->right == nullptr)
	{
		Replace(node, node->left);
	}

	//자식이 2개있는 경우
	else
	{
		//삭제하려는 노드의 다음노드 찾아서 
		Node* nextNode = Next(node);
		//복사해놓고
		node->key = nextNode->key;
		Delete(nextNode);
	}
}

void BinarySearchTree::Print()
{
	//이진트리에서 가장 작은 값을 찾음
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
	//이진트리에서 가장 큰 값을 찾음
	Node* PrintNode = Max(_root);

	while (PrintNode)
	{
		cout << PrintNode->key << " ";
		Node* node = Prev(PrintNode);
		PrintNode = node;
	}
}
