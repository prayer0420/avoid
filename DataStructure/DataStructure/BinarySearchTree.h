#pragma once

namespace BST
{
	struct Node
	{
		int value;
		Node* right;
		Node* left;
		Node* parent;
	};

	class BinarySearchTree
	{

	public:

		//추가
		void Insert(int value);
		//탐색
		Node* Search(Node* SearchNode, int key);

		//삭제
		Node* Min(Node* node);
		Node* Max(Node* node);
		Node* Next(Node* node);
		Node* Prev(Node* node);
		void Replace(Node* deleteNode, Node* replaceNode);

		void Delete(int value);
		void Delete(Node* deleteNode);

		void Print();

	private:
		Node* _root = nullptr;
	};
}