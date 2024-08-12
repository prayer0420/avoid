#pragma once
#include <iostream>
#include<assert.h>
using namespace std;

template <typename T>
struct MyNode
{
    T _data; //값
    MyNode<T>* _next; //다음 노드
    MyNode<T>* _prev; //이전 노드

    MyNode()
        :_data(0)
        , _next(nullptr)
        , _prev(nullptr)
    {}

    MyNode(int data)
        :_data(data)
        , _next(nullptr)
        , _prev(nullptr)
    {}
};

template <typename T>
class MyList
{
private:
    int _size; //현재 개수
    MyNode<T>* _head; //첫번째 노드
    MyNode<T>* _tail; //두번째 노드

public:
    MyList()
        :_size(0)
        , _head(nullptr)
        , _tail(nullptr)
    {}

    MyList(int size, MyNode<T>* head, MyNode<T>* tail)
        :_size(size)
        , _head(head)
        , _tail(tail)
    {}

    ~MyList()
    {
        MyNode<T>* deleteNode = _head;
        for (int i = 0; i < _size; i++)
        {
            MyNode* tempNode = deleteNode->_next;
            delete deleteNode;
            deleteNode = tempNode;
            if (deleteNode == nullptr)
                break;
        }
    }
    //맨 앞에 넣기
    void push_front(T data)
    {
        //일단 data를 가지는 MyNode 생성
        MyNode<T>* newNode = new MyNode<T>(data);

        //기존에 값이 없었다면
        if (_head == nullptr)
        {
            _tail = newNode;
        }
        //기존에 값이 1개이상 있었으면
        else
        {
            newNode->_next = _head;
            _head->_prev = newNode;
        }

        //첫번째 노드를 새로 추가한 노드로 설정
        _head = newNode;

        //현재 개수 증가
        _size++;
    }

    //맨 뒤에 넣기
    void push_back(T data)
    {
        MyNode<T>* newNode = new MyNode<T>(data);

        //기존에 값이 없었다면
        if (_head == nullptr)
        {
            _head = newNode;
        }
        //기존에 값이 1개이상 있었으면
        else
        {
            newNode->_prev = _tail;
            _tail->_next = newNode;
        }

        //첫번째 노드를 새로 추가한 노드로 설정
        _tail = newNode;

        //현재 개수 증가
        _size++;

    }

    //맨뒤 제거
    void pop_back()
    {
        if (_tail == _head)
        {
            delete _tail;
            _tail = nullptr;
            _head = nullptr;
        }
        else
        {
            _tail = _tail->_prev;
            delete _tail->_next;
            _tail->_next = nullptr;
        }
        _size--;

    }

    void pop_front()
    {
        if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else
        {
            _head = _head->_next;
            delete _head->_prev;
            _head->_prev = nullptr;
        }
        _size--;

    }

    MyNode<T>* Find(T data)
    {
        MyNode<T>* tempNode = _head;
        for (int i = 0; i < _size; i++)
        {
            if (tempNode == nullptr)
                return nullptr;
            if (tempNode->_data == data)
                return tempNode;
            tempNode = tempNode->_next;
        }
        return nullptr;
    }

    //특정 값 앞에 특정 값 넣기
    void insert(T findData, T data)
    {
        MyNode<T>* newNode = new MyNode<T>(data);
        MyNode<T>* findNode = Find(findData);

        newNode->_prev = findNode->_prev;

        if (findNode->_prev != nullptr)
            findNode->_prev->_next = newNode;

        newNode->_next = findNode;
        findNode->_prev = newNode;

        if (findNode == _head)
            _head = newNode;

        _size++;
    }

    //특정 값 제거
    void erase(T data)
    {
        MyNode<T>* findNode = Find(data);

        findNode->_prev->_next = findNode->_next;
        findNode->_next->_prev = findNode->_prev;
        delete findNode;
        _size--;
    }

    void AddRanage(const MyList<T>* other)
    {
        _tail->_next = other->_head;
        other->_head->_prev = _tail;
        _tail = other->_tail;
    }

};