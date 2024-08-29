// DataStructure.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "MyList.h"
#include "MyVector.h"
#include "MyBst.h"
#include "MyQueue.h"
#include "MyStack.h"
#include "MyString.h"
#include "MySet.h"
#include "MyMap.h"
#include "MyUnorderedMap.h"
#include "MyUnorderedSet.h"
using namespace std;


int main()
{
//#pragma region myVector
	//test_push_back();
	//test_insert();
	//test_erase();
	//test_resize();
	//test_iterators();

	//std::cout << "All tests passed!" << std::endl;
	//return 0;
//#pragma endregion


#pragma region myList
    //test_push_back();
    //test_push_front();
    //test_insert();
    //test_erase();
    //test_iterators();

    //std::cout << "All tests passed!" << std::endl;
    //return 0;
#pragma endregion


//#pragma region Binary Serach
//
//    numbers = { 1,8,15,23,32,44,56,63,81,91 };
//    BinarySearch(81);
//#pragma endregion

#pragma region BinarySearchTree

    //BST::MyBST bst;
    //bst.insert(10);
    //bst.insert(5);
    //bst.insert(20);
    //bst.insert(3);
    //bst.insert(7);
    //bst.insert(15);
    //bst.insert(30);

    //cout << "중위순회";
    //bst.inOrderTraversal(bst.root);
    //cout << endl;

    //cout << "Search 7: " << (bst.search(7) ? "Found" : "Not Found") << endl;
    //cout << "Search 25: " << (bst.search(25) ? "Found" : "Not Found") << endl;

    //bst.remove(10);
    //cout << "중위순회 후 10제거 : ";
    //bst.inOrderTraversal(bst.root);
    //cout << endl;

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


#pragma region MyString

    //MyWString str1(L"안녕하세요");
    //MyWString str2(L" 세계");

    //// 문자열 연결
    //MyWString str3 = str1 + str2;
    //std::wcout << str3 << std::endl; // 출력: "안녕하세요 세계"

    //// 문자열 비교
    //if (str1 == MyWString(L"안녕하세요")) {
    //    std::wcout << L"str1은 '안녕하세요'입니다." << std::endl;
    //}

    //// 문자열 길이 출력
    //std::wcout << L"str3의 길이: " << str3.size() << std::endl; // 출력: 8

    //return 0;
#pragma endregion


#pragma region MySet
   //MySet::MySet mySet;

   //mySet.insert(10);
   //mySet.insert(5);
   //mySet.insert(20);
   //mySet.insert(10);

   //cout << "Set contents (in-order): ";
   //mySet.inOrderTraversal(mySet.root);
   //cout << endl;

   //// 특정 값이 집합에 있는지 확인
   //cout << "Contains 10: " << (mySet.contains(10) ? "Yes" : "No") << endl;
   //cout << "Contains 15: " << (mySet.contains(15) ? "Yes" : "No") << endl;


#pragma endregion


#pragma region MyMap

//MyMap::MyMap<const char*, int> myMap;

//// 값 삽입
//myMap.insert(MyMap::makePair("apple", 10));
//myMap.insert(MyMap::makePair("banana", 20));
//myMap.insert(MyMap::makePair("cherry", 30));
//
//// operator[]로 값 접근 및 수정
//myMap["banana"] = 25;
//
//// 검색 및 출력
//cout << "apple: " << myMap.search("apple") << endl;
//cout << "banana: " << myMap["banana"] << endl;
//
//// 값 삭제
//myMap.remove("banana");
//myMap.print();

#pragma endregion


#pragma region MyUnorderedMap

//MyUnorderedMap<const char*, int> myMap;
//
//// 값 삽입
//myMap.insert(makePair("apple", 10));
//myMap.insert(makePair("banana", 20));
//myMap.insert(makePair("cherry", 30));
//
//// operator[]로 값 접근 및 수정
//myMap["banana"] = 25;
//
//// 검색 및 출력
//int value;
//if (myMap.find("apple", value))
//{
//    cout << "apple: " << value << endl;
//}
//else
//{
//    cout << "apple not found" << endl;
//}
//
//if (myMap.find("banana", value))
//{
//    cout << "banana: " << value << endl;
//}
//else
//{
//    cout << "banana not found" << endl;
//}
//
//// 값 삭제
//myMap.erase("banana");
//
//if (myMap.find("banana", value))
//{
//    cout << "banana: " << value << endl;
//}
//else
//{
//    cout << "banana not found" << endl;
//}

#pragma endregion

#pragma region MyUnorderedSet
MyUS :: MyUnorderedSet<string> mySet;

// 요소 삽입
mySet.insert("apple");
mySet.insert("banana");
mySet.insert("cherry");

// 이미 있는 요소 삽입 시도
mySet.insert("banana");  // 중복된 요소는 삽입되지 않음

// 검색 및 출력
if (mySet.find("apple"))
{
    cout << "apple found" << endl;
}
else
{
    cout << "apple not found" << endl;
}

if (mySet.find("banana"))
{
    cout << "banana found" << endl;
}
else
{
    cout << "banana not found" << endl;
}

if (mySet.find("orange"))
{
    cout << "orange found" << endl;
}
else
{
    cout << "orange not found" << endl;
}

// 요소 삭제
mySet.erase("banana");

// 삭제 후 검색
if (mySet.find("banana"))
{
    cout << "banana found" << endl;
}
else
{
    cout << "banana not found" << endl;
}

#pragma endregion

return 0;
}