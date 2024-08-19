#pragma once

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = 0;
};


class BinarySearchTree
{

public:

	Node* Search(Node* SearchNode, int key);

	void Insert(int key);
	
	//트리중 가장 작은 값(계속 왼쪽으로 이동하면됨)
	Node* Min(Node* node);
	//트리중 가장 작은 값(계속 오른쪽으로 이동하면됨)
	Node* Max(Node* node);
	
	Node* Next(Node* node);

	Node* Prev(Node* node);

	//삭제할 노드가 자식이 1개 있는 경우
	void Replace(Node* deleteNode, Node* replaceNode);
	//키값으로 삭제
	void Delete(int key);
	//노드로 삭제
	void Delete(Node* node);

	void Print();
	void ReversePrint();

private:

	Node* _root = nullptr;


};

