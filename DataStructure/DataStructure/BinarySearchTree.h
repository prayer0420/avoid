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
	
	//Ʈ���� ���� ���� ��(��� �������� �̵��ϸ��)
	Node* Min(Node* node);
	//Ʈ���� ���� ���� ��(��� ���������� �̵��ϸ��)
	Node* Max(Node* node);
	
	Node* Next(Node* node);

	Node* Prev(Node* node);

	//������ ��尡 �ڽ��� 1�� �ִ� ���
	void Replace(Node* deleteNode, Node* replaceNode);
	//Ű������ ����
	void Delete(int key);
	//���� ����
	void Delete(Node* node);

	void Print();
	void ReversePrint();

private:

	Node* _root = nullptr;


};

