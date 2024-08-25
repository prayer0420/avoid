#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<stack>
using namespace std;


//List
//struct Node
//{
//	int value;
//	Node* next;
//	Node* prev;
//};
//
//class MyQueue
//{
//private:
//	Node* head = nullptr;
//	Node* tail = nullptr;
//
//public:
//	void Enqueue(int value)
//	{
//		Node* newNode = new Node();
//		newNode->value = value;
//
//		if (head == nullptr)
//			head = newNode;
//
//		else
//		{
//			newNode->prev = tail;
//			tail->next = newNode;
//		}
//		tail = newNode;
//	}
//
//	void Dequeue()
//	{
//		if (head == nullptr)
//			return;
//
//		Node* DqNode = head;
//		head = head->next;
//		head->prev = nullptr;
//		delete DqNode;
//	}
//
//
//	int Front()
//	{
//		return head->value;
//	}
//
//};

//vector
//class MyQueue
//{
//private:
//	vector<int> v;
//	int idx = 0;
//	int head= 0;
//public:
//	
//	void Enqueue(int value)
//	{
//		v[idx++] = value;
//	}
//
//	void Dequeue()
//	{
//		head++;
//		idx--;
//	}
//
//	int Front()
//	{
//		return v[head];
//	}
//
//};

//Stack
class MyQueue
{
private:
	stack<int> myStack1;
	stack<int> myStack2;

public:

	void Enqueue(int value)
	{
		int size2 = myStack2.size();
		for (int i = 0; i < size2; i++)
		{
			myStack1.push(myStack2.top());
			myStack2.pop();
		}

		myStack1.push(value);

		int size1 = myStack1.size();
		for (int i = 0; i < size1; i++)
		{
			myStack2.push(myStack1.top());
			myStack1.pop();
		}
	}

	void Dequeue()
	{
		myStack2.pop();
	}

	int Front()
	{
		return myStack2.top();
	}
};