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
//    MyVector<int>* myVector = new MyVector<int>();
//    MyVector<int>* myVector2 = new MyVector<int>();
//    myVector->Add(1);
//    myVector->Add(2);
//    myVector->Add(3);
//    myVector->Add(4);
//    myVector->Add(5);
//    myVector->Add(6);
//
//    myVector2->Add(7);
//    myVector2->Add(8);
//    myVector2->Add(9);
//
//    myVector->AddRange(myVector2);
//    myVector->Add(10);
//
//    myVector->Remove(1);
//    myVector->RemoveAt(1);
//    int value = myVector->FindIdx(3);
//    bool IsValue = myVector->FindValue(2);
//    myVector->Clear();
//#pragma endregion
//
//
//#pragma region myList
//    MyList<int>* myList = new MyList<int>();
//    MyList<int>* myList2 = new MyList<int>();
//
//    //myList
//    myList->push_back(1);
//    myList->push_back(2);
//    myList->push_back(3);
//    myList->push_back(4);
//    myList->push_back(5);
//    myList->push_front(0);
//    myList->pop_back();
//    myList->pop_front();
//    myList->Find(1);
//    myList->insert(1, 0);
//    myList->erase(1);
//
//    //myList2
//    myList2->push_back(6);
//    myList2->push_back(7);
//    myList2->push_back(8);
//    myList2->push_back(9);
//
//    myList->AddRanage(myList2);
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

    MyQueue myQ;
    myQ.Enqueue(1);
    myQ.Enqueue(2);
    myQ.Enqueue(3);
    myQ.Dequeue();
    int a = myQ.Front();

#pragma endregion

#pragma region MyStack
    MyStack myST;
    myST.Push(1);
    myST.Push(2);
    myST.Push(3);
    myST.Pop();
    int b = myST.Top();

#pragma endregion










    return 0;
}