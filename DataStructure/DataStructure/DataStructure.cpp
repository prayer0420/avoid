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

    BST::MyBST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(3);
    bst.insert(7);
    bst.insert(15);
    bst.insert(30);

    cout << "중위순회";
    bst.inOrderTraversal(bst.root);
    cout << endl;

    cout << "Search 7: " << (bst.search(7) ? "Found" : "Not Found") << endl;
    cout << "Search 25: " << (bst.search(25) ? "Found" : "Not Found") << endl;

    bst.remove(10);
    cout << "중위순회 후 10제거 : ";
    bst.inOrderTraversal(bst.root);
    cout << endl;

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

   //MyMap::MyMap myMap;

   //// 맵에 키-값 쌍 삽입
   //myMap.insert("apple", 5);
   //myMap.insert("banana", 3);
   //myMap.insert("cherry", 7);
   //myMap.insert("date", 2);
   //myMap.insert("elderberry", 8);

   //// 맵의 내용을 중위 순회로 출력 (키 기준으로 오름차순 출력됨)
   //cout << "중위순회: ";
   //myMap.inOrderTraversal(myMap.root);
   //cout << endl;

   //// 특정 키에 대한 값을 검색하여 출력
   //try {
   //    int& value = myMap.search("banana");
   //    cout << "Value for 'banana': " << value << endl;
   //}
   //catch (const std::runtime_error& e) {
   //    cout << "banana없음" << endl;
   //}

   //// 존재하지 않는 키에 대한 검색 시도
   //try {
   //    int& value = myMap.search("fig");
   //    cout << "Value for 'fig': " << value << endl;
   //}
   //catch (const std::runtime_error& e) {
   //    cout << "'fig' 없음" << endl;
   //}

   //// 특정 키에 해당하는 노드를 삭제
   //myMap.remove("cherry");
   //cout << "'cherry' 제거 후 중위순회 : ";
   //myMap.inOrderTraversal(myMap.root);
   //cout << endl;
#pragma endregion

    return 0;
}