// DataStructure.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "MyList.h"
#include "MyVector.h"
#include "BinarySearchTree.h"
#include "MyQueue.h"
#include "MyStack.h"

using namespace std;


int main()
{
//#pragma region myVector
//	MyVector<int> myVector;
//
//	myVector.push_back(1);
//	myVector.push_back(2);
//	myVector.push_back(3);
//	myVector.push_back(4);
//	myVector.push_back(5);
//
//	MyVector<int>::iterator it = myVector.begin();
//	for (; it != myVector.end();)
//	{
//		int data = *it;
//		if (data % 2 == 0)
//		{
//			myVector.erase(it);
//		}
//		it++;
//	}
//
//	MyVector<int>::iterator it2 = myVector.begin();
//	for (; it2 != myVector.end();)
//	{
//		cout << *it2 << " ";
//		it2++;
//	}
//
//	return 0;
#pragma endregion


#pragma region myList
	MyList<int> myList;

	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);
	myList.push_back(4);
	myList.push_back(5);

	MyList<int>::iterator it = myList.begin();
	for (; it != myList.end();)
	{
		int data = *it;
		//cout << *it << " ";
		if (data % 2 == 0)
		{
			it = myList.erase(it);
		}
		else
			it++;
	}

	MyList<int>::iterator it2 = myList.begin();
	for (; it2 != myList.end();)
	{
		cout << *it2 << " ";
		it2++;
	}

	return 0;
#pragma endregion


//#pragma region Binary Serach
//
//    numbers = { 1,8,15,23,32,44,56,63,81,91 };
//    BinarySearch(81);
//#pragma endregion

#pragma region BinarySearchTree

    //BinarySearchTree* BST = new BinarySearchTree();
    //BST->Insert(10);
    //BST->Insert(5);
    //BST->Insert(20);
    //BST->Insert(8);
    //BST->Insert(15);
    //BST->Insert(30);
    //BST->Delete(20);

    //BST->ReversePrint();
    //BST->Print();
#pragma endregion


#pragma region MyQueue

//    MyQueue myQ;
//    myQ.Enqueue(1);
//    myQ.Enqueue(2);
//    myQ.Enqueue(3);
//    myQ.Dequeue();
//    int a = myQ.Front();
//
//#pragma endregion
//
//#pragma region MyStack
//    MyStack myST;
//    myST.Push(1);
//    myST.Push(2);
//    myST.Push(3);
//    myST.Pop();
//    int b = myST.Top();

#pragma endregion










    return 0;
}