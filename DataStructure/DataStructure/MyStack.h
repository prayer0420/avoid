#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<queue>
using namespace std;

//List
//struct Node
//{
//	int value;
//	Node* next;
//	Node* prev;
//};
//
//class MyStack
//{
//private:
//
//	Node* head = nullptr;
//	Node* tail = nullptr;
//
//public:
//	void Push(int value)
//	{
//		Node* newNode = new Node();
//		newNode->value = value;
//
//		if (head == nullptr)
//		{
//			head = newNode;
//		}
//
//		else
//		{
//			newNode->prev = tail;
//			tail->next = newNode;
//		}
//		tail = newNode;
//	}
//
//	void Pop()
//	{
//		if (tail == nullptr)
//			return;
//
//		Node* popNode = tail;
//		tail = tail->prev;
//		delete popNode;
//	}
//
//	int Top()
//	{
//		if (tail == nullptr)
//			return;
//		return tail->value;
//	}
//};

//vector
//class MyStack
//{
//
//private:
//	vector<int> myVector;
//	int idx = 0;
//
//public:
//
//	void Push(int value)
//	{
//		myVector[idx++] = value;
//	}
//
//	void Pop()
//	{
//		idx--;
//	}
//
//	int Top()
//	{
//		return myVector[idx];
//	}
//};


//queue
class MyStack
{
private:
	queue<int> q;
public:

	void Push(int value)
	{
		int size = q.size();
		q.push(value);
		for (int i = 0; i < size; i++)
		{
			q.push(q.front());
			q.pop();
		}
	}

	void Pop()
	{
		q.pop();
	}

	int Top()
	{
		return q.front();
	}
};